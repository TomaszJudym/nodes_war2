//
// Created by Ackan on 17.09.2018.
//

#ifndef _SERVER_H
#define _SERVER_H

#include "Node.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>

class User;

class Server : public Node
{
    std::vector< User* > connectedUsersVector;
    static sf::Texture image;
public:
    Server( const std::string& _name, const sf::Vector2f& _pos );
    void makeConnection( Node* _target ) override;
    static sf::Texture& getTexture();
};


#endif // _SERVER_H
