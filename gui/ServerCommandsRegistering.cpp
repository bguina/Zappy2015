
#include "ServerCommandFactoryManager.hpp"
#include "ServerCommands.hpp"

// No need to register it in the factory manager, Connection instanciates it itself
IServerCommand::ID const UnrecognizedServerCommand::id = 0;

SERVERCOMMAND_REGISTER(BadParameterServerCommand);
SERVERCOMMAND_REGISTER(BroadcastServerCommand);
SERVERCOMMAND_REGISTER(ContentServerCommand);
SERVERCOMMAND_REGISTER(DieServerCommand);
SERVERCOMMAND_REGISTER(DropServerCommand);
SERVERCOMMAND_REGISTER(EggBornServerCommand);
SERVERCOMMAND_REGISTER(EggDieServerCommand);
SERVERCOMMAND_REGISTER(EggHatchServerCommand);
SERVERCOMMAND_REGISTER(ExpulsionServerCommand);
SERVERCOMMAND_REGISTER(ForkServerCommand);
SERVERCOMMAND_REGISTER(GameEndServerCommand);
SERVERCOMMAND_REGISTER(GetServerCommand);
SERVERCOMMAND_REGISTER(HandshakeServerCommand);
SERVERCOMMAND_REGISTER(IncantationCastServerCommand);
SERVERCOMMAND_REGISTER(IncantationEndServerCommand);
SERVERCOMMAND_REGISTER(InventoryServerCommand);
SERVERCOMMAND_REGISTER(LevelServerCommand);
SERVERCOMMAND_REGISTER(MapSizeServerCommand);
SERVERCOMMAND_REGISTER(MessageServerCommand);
SERVERCOMMAND_REGISTER(NewEggServerCommand);
SERVERCOMMAND_REGISTER(NewPlayerServerCommand);
SERVERCOMMAND_REGISTER(PositionServerCommand);
SERVERCOMMAND_REGISTER(TeamNameServerCommand);
SERVERCOMMAND_REGISTER(TimeServerCommand);
SERVERCOMMAND_REGISTER(UnknownCommandServerCommand);

