//
// Created by Ackan on 17.09.2018.
//

#include "User.h"

User::User( const std::string& _name, sf::Vector2f& _pos, sf::RenderWindow& _rw ) :
Node( _name, _pos, _rw )
{
    image.loadFromFile( "img/camputer480x480.jpg" );
    initSprite();
}