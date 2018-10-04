#include "mainHeader.h"
#include <thread>
#include <chrono>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Terminal.h"
#include "LoadRing.h"

#include <string>
#include <fstream>
#include <streambuf>
#include <conio.h>

#include "battle_units/Server.h"
#include "battle_units/User.h"
#define DEBUG_LOGS 1

using milisec = std::chrono::milliseconds;

void initialize_log( std::string& );

int main() {

    sf::RenderWindow window( sf::VideoMode(1024, 768),
                             "kill_yourself",
                             sf::Style::Titlebar | sf::Style::Close);

    window.setFramerateLimit(60);

    Terminal terminal( window );

    LoadRing loadRing( window, sf::Color::Red );

    bool szmato(false);

    sf::Vector2f serverPosition = {300, 400};

    std::array< sf::Vector2f, 3 > clientsPositions =
    {
            sf::Vector2f{ 500, 300 },
            sf::Vector2f{ 500, 400 },
            sf::Vector2f{ 500, 500 }
    };

// initialize combat units

    Server server1( "server_1", serverPosition, window );
    std::array< std::shared_ptr<User>, 3 > users =
    {
            User::spawnUser( clientsPositions[0], window ),
            User::spawnUser( clientsPositions[1], window ),
            User::spawnUser( clientsPositions[2], window )
    };

    for( auto& x : users )
        cout << "address " << x << endl;

    std::string init_log_file = "dank_terminal_data.txt";
    loadRing.setPosition( 500, 500 );

    bool shitShown(false);
    //##############################################
    // END OF INIT PART
    //###############################################


    sf::Event event;

    //window.setVerticalSyncEnabled(true);
    terminal.update( (short) 69 );
    terminal.loadInitLog( init_log_file );
    terminal.update( (char)'\n' );
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::TextEntered:
                    if (event.text.unicode < 128)
                    {
                        if (event.text.unicode == '\b') // backspace
                            terminal.update((short)-1);
                        else if( event.text.unicode == sf::Keyboard::Return )
                        {
                            cout << "pressed enter" << endl;
                            //terminal.update( (char)'\n' );
                            //terminal.catchCommand();
                        }
                        else
                        terminal.update((char) event.key.code);
                    }
                    break;
            }

        }
        window.clear(sf::Color::Black);

        terminal.draw();
        for( auto& x : users )
            x->draw();


        loadRing.draw();
        server1.draw();
        window.display();
    }
    return 0;
}
