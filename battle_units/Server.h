//
// Created by Ackan on 17.09.2018.
//

#ifndef ABSEIL_SERVER_H
#define ABSEIL_SERVER_H

#include "Node.h"
#include <SFML/Graphics.hpp>
#include <string>

class Server : public Node
{
public:
    Server( const std::string& _name, sf::Vector2f& _pos, sf::RenderWindow& _rw );
};


#endif //ABSEIL_SERVER_H
