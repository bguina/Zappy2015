
#include <iostream>
#include <sstream>

#include "ServerCommandFactoryManager.hpp"
#include "GUI.hpp"


int main(int argc, char** argv)
{
    int exit_code(0);
    
    if (argc < 2 || argc > 3)
    {
        std::cerr << "usage: " << argv[0] << " host [port]" << std::endl;
        exit_code = 1;
    }
    else
    {
        int port(GUI::default_port);

        if (argc == 3)
        {   // Lazy parsing of the port string
            std::stringstream ss;
        
            ss << argv[2];
            ss >> port;
        }

        {   // Run
            GUI cu;
            
            exit_code = cu.run(argv[1], port);
        }
    }
    return exit_code;
}

