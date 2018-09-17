//
// Created by Ackan on 11.09.2018.
//

#ifndef ABSEIL_TERMINAL_H
#define ABSEIL_TERMINAL_H

#define DEBUG_LOGS 1

#define DLOG( x ) { if( DEBUG_LOGS ) std::cout << x << std::endl; }

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

class Terminal {
public:
    explicit Terminal( sf::RenderWindow& );
    void draw();
    void update( const char );
    bool update( short );
    void loadInitLog( std::string& _logFileDir );
private:
    typedef std::chrono::milliseconds mili;

    sf::Vector2f position;
    short terminalCharacterSize;
    std::string terminalFontDir;
    sf::Font terminalFont;
    sf::Text text;
    std::string ss;
    sf::RenderWindow& renderWindowPtr;

private:
    std::string getLastNLines( unsigned int _nLines, std::string::const_iterator _str );
};


#endif //ABSEIL_TERMINAL_H
