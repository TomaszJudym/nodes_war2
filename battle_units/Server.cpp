//
// Created by Ackan on 17.09.2018.
//

#include "Server.h"

Server::Server( const std::string& _name, const sf::Vector2f& _pos, sf::Texture& _texture ) :
Node( _pos, _texture ),
connectedUsersVector()
{
    setName( L"DANK_3" );

    initText();
}

void Server::makeConnection( Node* _target )
{
    connectedUsersVector.push_back( reinterpret_cast<User*>(_target) );
}