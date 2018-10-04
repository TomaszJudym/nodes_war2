//
// Created by Ackan on 17.09.2018.
//

#include "Server.h"

Server::Server( const std::string& _name, sf::Vector2f& _pos, sf::RenderWindow& _rw ) :
Node( _pos, _rw ),
connectedUsersVector()
{
    image.loadFromFile( "img/server800x800.jpg" );
    setName( L"DANK_3" );
    initSprite();
    initText();
}

void Server::makeConnection( Node* _target )
{
    connectedUsersVector.push_back( reinterpret_cast<User*>(_target) );
}

