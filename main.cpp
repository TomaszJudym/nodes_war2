#include "mainHeader.h"
#include <thread>
#include <chrono>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Terminal.h"
#include "LoadRing.h"
#include <array>

#include <string>
#include <fstream>
#include <streambuf>

#include "battle_units/Server.h"
#include "battle_units/User.h"
#define DEBUG_LOGS 1

using milisec = std::chrono::milliseconds;

void initialize_log( std::string& );

sf::RenderWindow window( sf::VideoMode(1024, 768),
                         "kill_yourself",
                        sf::Style::Titlebar | sf::Style::Close);

Terminal terminal( window );
LoadRing loadRing( window, sf::Color::Red );
bool szmato(false);
sf::Vector2f serverPosition = {300, 300};
std::array< sf::Vector2f, 3 > clientsPositions =
        {
                sf::Vector2f{ 500, 300 },
                sf::Vector2f{ 500, 400 },
                sf::Vector2f{ 500, 500 }
        };

// initialize combat units

Server server1( "server_1", serverPosition, window );
std::array< User, 3 > users =
        {
                User( "user_1", clientsPositions[0], window ),
                User( "user_2", clientsPositions[1], window ),
                User( "user_3", clientsPositions[2], window )
        };


int main() {
    std::string init_log_file = "dank_terminal_data.txt";
    loadRing.setPosition( 500, 500 );
    sf::Event event;
    window.setFramerateLimit(60);
    //window.setVerticalSyncEnabled(true);
    bool shitShown(false);
    terminal.loadInitLog( init_log_file );
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
                        else {
                            terminal.update((char) event.key.code);
                        }
                        break;
                    }
            }

        }
        window.clear(sf::Color::Black);

        terminal.draw();
        for( auto& x : users )
            x.draw();


        loadRing.draw();
        if( !shitShown )
        {
            loadRing.load();
            shitShown = true;
        }
        server1.draw();
        window.display();
    }
    return 0;
}
