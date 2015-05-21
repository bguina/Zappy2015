
#ifndef HPP_CLIENTCOMMANDS
#define HPP_CLIENTCOMMANDS

//          Commandes client
//      String          Description                                 Classe de la reponse serveur
//  msz\n           demande la taille de la carte               MapSizeServerCommand
//  bct <X> <Y>\n   demande le contenu d'une case               ContentServerCommand
//  mct\n           demande le contenu de toutes les cases      ContentServerCommand * X * Y
//  tna\n           demande les noms des equipes                TeamNameServerCommand * N teams
//  ppo <n>\n       demande la position d'un joueur             PositionServerCommand
//  plv <n>\n       demande le niveau d'un joueur               LevelServerCommand
//  pin <n>\n       demande l'inventaire d'un joueur            InventoryServerCommand
//  sgt\n           demande l'unite de temps                    TimeUnitServerCommand
//  sst <T>\n       demande le changement de l'unite de temps   TimeUnitServerCommand
//  GRAPHIC\n       annonce le type du client (graphique)       -

#endif

