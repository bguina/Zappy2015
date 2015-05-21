
#include "ServerCommandFactoryManager.hpp"

ServerCommandFactoryManager::ServerCommandFactoryManager()
    : m_last_id(0)
{
}

ServerCommandFactoryManager& ServerCommandFactoryManager::singleton()
{
    static ServerCommandFactoryManager f;

    return f;
}   

IServerCommand* ServerCommandFactoryManager::make(std::string const& str) const
{
    for (FactoriesContainerType::const_iterator it = m_factories.begin(); it != m_factories.end(); ++it)
    {
        try
        {
            IServerCommand* command((*it)(str));

            if (command)
                return command;
        }
        catch (std::exception&)
        {
            // your filthy exceptions are silently ignored, keep an eye on them yourself and deal with it
        }
    }

    return 0;
}

