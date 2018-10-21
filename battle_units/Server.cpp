//
// Created by Ackan on 17.09.2018.
//

#include "Server.h"

sf::Texture Server::image = sf::Texture();

Server::Server( const std::string& _name, const sf::Vector2f& _pos ) :
Node( _pos ),
connectedUsersVector()
{
    setName( L"DANK_3" );
    initSprite(Server::image);
    initText();
}

void Server::makeConnection( Node* _target )
{
    connectedUsersVector.push_back( reinterpret_cast<User*>(_target) );
}

sf::Texture& Server::getTexture()
{
    return image;
}

