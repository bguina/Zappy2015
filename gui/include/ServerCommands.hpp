
#ifndef HPP_SERVERCOMMANDS
#define HPP_SERVERCOMMANDS

#include "ServerCommands/UnrecognizedServerCommand.hpp"

//      Classe                          String                                          Description                             Reponse attendue
//  BadParameterServerCommand       sbp\n                                           mauvais parametre de commande client    -
#include "ServerCommands/BadParameterServerCommand.hpp"
//  BroadcastServerCommand          pbc <n> <M>\n                                   broadcast d'un joueur                   -
#include "ServerCommands/BroadcastServerCommand.hpp"
//  ContentServerCommand            bct <X> <Y> <q> <q> <q> <q> <q> <q> <q>\n       contenu d'une case                      -
#include "ServerCommands/ContentServerCommand.hpp"
//  DieServerCommand                pdi <n>\n                                       joueur mort de faim                     -
#include "ServerCommands/DieServerCommand.hpp"
//  DropServerCommand               pdr <n> <i>\n                                   depot d'une ressource                   -
#include "ServerCommands/DropServerCommand.hpp"
//  EggBornServerCommand            ebo <e>\n                                       nouveau joueur pour oeuf                -
#include "ServerCommands/EggBornServerCommand.hpp"
//  EggDieServerCommand             edi <e>\n                                       mort de l'oeuf eclos                    -
#include "ServerCommands/EggDieServerCommand.hpp"
//  EggHatchServerCommand           eht <e>\n                                       eclosion d'oeuf                         -
#include "ServerCommands/EggHatchServerCommand.hpp"
//  ExpulsionServerCommand          pex <n>\n                                       expulsion par un joueur                 -
#include "ServerCommands/ExpulsionServerCommand.hpp"
//  ForkServerCommand               pfk <n>\n                                       ponte d'un oeuf                         -
#include "ServerCommands/ForkServerCommand.hpp"
//  GameEndServerCommand            seg <N>\n                                       fin de la partie                        -
#include "ServerCommands/GameEndServerCommand.hpp"
//  GetServerCommand                pgt <n> <i>\n                                   obtention d'une ressource               -
#include "ServerCommands/GetServerCommand.hpp"
//  HandshakeServerCommand          BIENVENUE\n                                     handshake                               GRAPHIC\n
#include "ServerCommands/HandshakeServerCommand.hpp"
//  IncantationCastServerCommand    pic <X> <Y> <L> <n> <n> ...\n                   debut d'incantation                     -
#include "ServerCommands/IncantationCastServerCommand.hpp"
//  IncantationEndServerCommand     pie <X> <Y> <R>\n                               fin d'incantation                       -
#include "ServerCommands/IncantationEndServerCommand.hpp"
//  InventoryServerCommand          pin <n> <X> <Y> <q> <q> <q> <q> <q> <q> <q>\n   inventaire d'un joueur                  -
#include "ServerCommands/InventoryServerCommand.hpp"
//  LevelCommand                    plv <n> <L>\n                                   niveau d'un joueur                      -
#include "ServerCommands/LevelServerCommand.hpp"
//  MapSizeServerCommand            msz <X> <Y>\n                                   taille de la map                        -
#include "ServerCommands/MapSizeServerCommand.hpp"
//  MessageServerCommand            smg <M>\n                                       message serveur                         -
#include "ServerCommands/MessageServerCommand.hpp"
//  NewEggServerCommand             enw <e> <n> <X> <Y>\n                           nouvel oeuf                             -
#include "ServerCommands/NewEggServerCommand.hpp"
//  NewPlayerServerCommand          pnw <n> <X> <Y> <O> <L> <N>\n                   connexion d'un joueur                   -
#include "ServerCommands/NewPlayerServerCommand.hpp"
//  PositionCommand                 ppo <n> <X> <Y> <O>\n                           position d'un joueur                    -
#include "ServerCommands/PositionServerCommand.hpp"
//  TeamNameServerCommand           tna <N>\n                                       nom d'une equipe                        -
#include "ServerCommands/TeamNameServerCommand.hpp"
//  TimeServerCommand               sgt <T>\n                                       unite de temps                          -
#include "ServerCommands/TimeServerCommand.hpp"
//  UnknownCommandServerCommand     suc\n                                           mauvaise commande client                -
#include "ServerCommands/UnknownCommandServerCommand.hpp"

#endif

