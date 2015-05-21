
#ifndef HPP_COMMANDFACTORYMANAGER
#define HPP_COMMANDFACTORYMANAGER

#include <cassert>
#include <string>
#include <set>

#include "IServerCommand.hpp"

class ServerCommandFactoryManager
{
    private:
    typedef std::set<IServerCommand::Factory> FactoriesContainerType;
    
    ServerCommandFactoryManager();

    public:
    static ServerCommandFactoryManager& singleton();

    // Register a command factory and assign an arbitrary identifier to this command
    // Dumb people might need the macro defined below
    template<class T>
    IServerCommand::ID register_command()
    {
        assert(m_factories.insert(&T::factory).second);
        
        // ServerCommand ID = 0 is reserved for UnrecognizedServerCommand
        ++m_last_id;
        return m_last_id;
    }

    // Parse a command
    IServerCommand* make(std::string const& str) const;

    private:
    FactoriesContainerType m_factories;
    IServerCommand::ID m_last_id;
};

#define SERVERCOMMAND_REGISTER(command_class)\
    IServerCommand::ID const command_class::id = ServerCommandFactoryManager::singleton().register_command<command_class>()

#endif

