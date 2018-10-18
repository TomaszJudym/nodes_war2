//
// Created by Ackan on 11.09.2018.
//

#ifndef ABSEIL_TERMINAL_H
#define ABSEIL_TERMINAL_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <map>

class Terminal : public sf::Drawable
{

public:
    explicit                             Terminal();
    void                                 draw(sf::RenderTarget& _rw, sf::RenderStates = sf::RenderStates::Default) const override;
    void                                 update( const char );
    bool                                 update( short );
    void                                 update( const std::string& _str );
    void                                 loadInitLog( std::string& _logFileDir, sf::RenderWindow& _renderWin );
    void                                 clear();
    std::string                          catchCommand(sf::RenderWindow& _windowRef);


private:
    typedef std::chrono::milliseconds   mili;

    sf::Vector2f                        position;
    short                               terminalCharacterSize;
    std::string                         terminalFontDir;
    sf::Font                            terminalFont;
    sf::Text                            text;
    std::string                         ss;

private:
    std::string                         getLastNLines( unsigned int _nLines, std::string::const_iterator _str );
};


#endif //ABSEIL_TERMINAL_H
