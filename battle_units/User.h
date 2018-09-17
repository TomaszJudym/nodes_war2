//
// Created by Ackan on 17.09.2018.
//

#ifndef ABSEIL_USER_H
#define ABSEIL_USER_H

#include "Node.h"
#include <SFML/Graphics.hpp>

class User : public Node
{
public:
    User( const std::string& _name, sf::Vector2f& _pos, sf::RenderWindow& _rw );
};


#endif //ABSEIL_USER_H
