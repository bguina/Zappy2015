

#ifndef		SERVER_H
# define	SERVER_H

# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/select.h>
# include <signal.h>

# define	USAGE1		"usage : ./server [-p PORT] [-x LARGEUR] [-y HAUTEUR] "
# define	USAGE2		"-n TEAM1NAME TEAM2NAME ... [-c MAXCLIENTS] [-t TIME]\n"

# define	P_MIN_SIZE	1
# define	P_MAX_SIZE	100
# define	P_MIN_TEAM	1
# define	P_MAX_TEAM	5
# define	P_MIN_CLIENT	1
# define	P_MAX_CLIENT	10
# define	P_MIN_TIME	1
# define	P_MAX_TIME	1000
# define	TEAM_NAME_SIZE	100

# define	FOOD		0
# define	LINEMATE	1
# define	DERAUMERE	2
# define	SIBUR		3
# define	MENDIANE	4
# define	PHIRAS		5
# define	THYSTAME	6
# define	NB_OBJECTS	7

# define	G_LINEMATE	9
# define	G_DERAUMERE	8
# define	G_SIBUR		10
# define	G_MENDIANE	5
# define	G_PHIRAS	6
# define	G_THYSTAME	1

# define	NORTH		1
# define	EAST		2
# define	SOUTH		3
# define	WEST		4

# define	S_LEVEL1	".100000"
# define	S_LEVEL2	".111000"
# define	S_LEVEL3	".201020"
# define	S_LEVEL4	".112010"
# define	S_LEVEL5	".121300"
# define	S_LEVEL6	".123010"
# define	S_LEVEL7	".222221"

# define	ANGLE1		0.321751
# define	ANGLE2		1.249046
# define	ANGLE3		1.892547
# define	ANGLE4		2.819842

# define	CMDNM_MAX_SZ	11
# define	NB_COMMANDS	12
# define	NB_REQUESTS	9

# define	CLIENT_IN_MAX	32
# define	MSG_IN_MAX	10
# define	IN_BUFSIZE	10
# define	IAMDISPLAY	"GRAPHIC"
# define	WELCOME		"BIENVENUE\n"
# define	WELCOME_BUFSZ	42
# define	WELCOME_FMT	"%%i\n%i %i\n"
# define	RESP_KO		"ko\n", 3

# define	MY_MIN(x, y)	(((x) < (y)) ? (x) : (y))
# define	MY_MAX(x, y)	(((x) > (y)) ? (x) : (y))

# define	BAD_PARAM	"sbp\n"

# define	WRITE_ERROR	"write(2) failed\n"
# define	MALLOC_ERROR	"malloc(3) failed\n"
# define	REALLOC_ERROR	"realloc(3) failed\n"

typedef struct	s_msg
{
  int		buf_size;
  char		*buf;
  int		cursor;
  int		delta;
  struct s_msg	*next;
}		t_msg;

typedef struct		s_action
{
  int			cmd_idx;
  struct s_player	*player;
  char			*param;
  struct timeval	time;
  struct s_action	*next;
}			t_action;

typedef struct		s_egg
{
  int			id;
  int			team_idx;
  int			x;
  int			y;
  struct timeval	birth;
  int			born;
  int			food;
  struct s_egg		*next;
}			t_egg;

typedef struct		s_player
{
  int			id;
  int			team_idx;
  char			*team;
  int			x;
  int			y;
  int			level;
  int			dir;
  unsigned char		bag[NB_OBJECTS];
  int			busy;
  t_action		*action_list;
  t_action		*action_back;
  struct s_client	*client_data;
  struct s_player	*next_t;
  struct s_player	*next_g;
}			t_player;

typedef struct		s_client
{
  int			fd;
  char			must_die;
  int			in_pend_msg_nb;
  int			in_buf_nb;
  t_msg			*in_buf_list;
  t_msg			*out_msg_list;
  t_msg			*ibl_back;
  t_msg			*oml_back;
  t_player		*player_data;
  struct s_client	*next;
}			t_client;

typedef struct	s_tile
{
  unsigned char	objects[NB_OBJECTS];
  t_player	*players;
}		t_tile;

typedef struct	s_game
{
  t_tile	*map;
  t_player	**players;
  t_action	*actions;
  t_egg		*eggs;
  t_player	*ghosts;
  int		current_food;
}		t_game;

typedef struct	s_team
{
  char		*name;
  int		egg_slot_nb;
  int		member_nb;
}		t_team;

struct s_server;

typedef struct	s_command
{
  char		name[CMDNM_MAX_SZ + 1];
  int		nb_cycle;
  void		(*ptrfunc)(struct s_server *, t_player *, char *);
}		t_command;

typedef struct	s_request
{
  char		name[4];
  void		(*ptrfunc)(struct s_server *, t_client *, int, int);
}		t_request;

typedef struct	s_server
{
  int		sockfd;
  int		co_nb;
  int		co_nb_max;
  char		welcome_fmt[WELCOME_BUFSZ];
  int		player_nb;
  t_client	*player_list;
  t_client	*display_list;
  t_client	*newcomer_list;
  int		team_size;
  int		team_nb;
  t_team	*teams;
  int		port;
  int		x;
  int		y;
  int		f;
  t_game	game;
  t_command	commands[NB_COMMANDS];
  t_request	requests[NB_REQUESTS];
  long		maxfd;
}		t_server;

extern volatile sig_atomic_t	g_interrupt;

/*
** bags.c
*/
void		inventaire(t_server *, t_player *, char *);
void		prend(t_server *, t_player *, char *);
void		pose(t_server *, t_player *, char *);

/*
** command.c
*/
void		init_command(t_server *s);

/*
** communication(_init).c
** Le moteur de jeu utilise ces fonctions uniquement
*/
char		communication(t_server *, struct timeval *);
char		communication_sendto(t_client *, char *, char);
char		communication_broadcast(t_client *, char *);
char		communication_init(t_server *);
void		communication_end(t_server *);

/*
** communication_list.c
*/
int		list_fdset(t_client **, t_server *, fd_set *, fd_set *);
t_client	*list_move(t_client **, t_client **, t_client *);
void		list_write(t_server *, t_client *, fd_set *);
void		list_read(t_server *, t_client *, fd_set *);

/*
** client.c
*/
void		client_newcomer(t_server *, int);
void		client_shutdown(t_server *, t_client *);
t_client	*client_discard(t_client *,
				t_server *,
				t_client **,
				t_client *);

/*
** client_msg.c
*/
t_msg		*client_msg_init(int);
char		client_msg_process(t_server *, t_client *);
t_msg		*client_msg_prepop(t_msg **);
t_msg		*client_msg_read_slot(t_client *);

/*
** crequest.c
*/
char		crequest_newcomer(t_server *, t_client *, char *);
char		crequest_oldfag(t_server *, t_client *, char *);

/*
** death.c
*/
void		player_death(t_server *, t_player *);
void		ghost_death(t_server *, t_player *);
void		egg_death(t_server *, t_egg *);

/*
** expulse.c
*/
void		expulse(t_server *, t_player *, char *);

/*
** food.c
*/
void		dinner_time(t_server *, struct timeval *);

/*
** game_requests.c
*/
void		msz(t_server *, t_client *, int, int);
void		bct(t_server *, t_client *, int, int);
void		mct(t_server *, t_client *, int, int);
void		tna(t_server *, t_client *, int, int);
void		sgt(t_server *, t_client *, int, int);

/*
** ia.c
*/
void		connect_nbr(t_server *, t_player *, char *);
void		broadcast(t_server *, t_player *, char *);
void		lay_egg(t_server *, t_player *, char *);

/*
** incantation.c
*/
int		incantation_valide(t_server *, t_player *);
void		incantation(t_server *, t_player *, char *);

/*
** init_game.c
*/
void		init_game(t_server *);

/*
** map_utilities.c
*/
t_tile		*get_front_tile(t_server *, t_player *);
int		get_dir(t_server *, t_player *, int , int);
void		gen_rsc(t_server *, int, int);
void            append_text(char *, char *, int);

/*
** move.c
*/
void		remove_from_map(t_server *, t_player *);
void		avance(t_server *, t_player *, char *);
void		droite(t_server *, t_player *, char *);
void		gauche(t_server *, t_player *, char *);

/*
** new_action.c
*/
void		insert_action_in_queue(t_server *, t_action *);
int		new_action(t_server *, t_player *, int, char *);

/*
** new_player.c
*/
int		new_player(t_server *, t_client *, int);

/*
** player_dc.c
*/
void		player_dc(t_server *, t_client *);

/*
** player_requests.c
*/
void		ppo(t_server *, t_client *, int, int);
void		plv(t_server *, t_client *, int, int);
void		pin(t_server *, t_client *, int, int);
void		pnw(t_server *, t_client *, int, int);
void		sst(t_server *, t_client *, int, int);

/*
** request.c
*/
void		init_request(t_server *);
void		request_broadcast(t_server *,
				  void (*)(t_server *, t_client *, int, int),
				  int, int);
void		new_graphic_info(t_server *, t_client *);

/*
** server.c
*/
void		game_shutdown(t_server *);
void		do_server_stuff(t_server *);

/*
** signaling.c
*/
void		signaling_init();
void		signaling_interrupt(int);

/*
** voir.c
*/
void		voir(t_server *, t_player *, char *);

/*
** xfunc.c
*/
void		xwrite(int, void *, int);
void		*xmalloc(int);
void		*xrealloc(void *, int);

#endif
