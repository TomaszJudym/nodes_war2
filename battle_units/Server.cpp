//
// Created by Ackan on 17.09.2018.
//

#include "Server.h"

Server::Server( const std::string& _name, sf::Vector2f& _pos, sf::RenderWindow& _rw ) :
Node( _name, _pos, _rw )
{
    image.loadFromFile( "img/server800x800.jpg" );
    initSprite();
}
