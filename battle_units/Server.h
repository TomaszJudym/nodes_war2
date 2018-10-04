//
// Created by Ackan on 17.09.2018.
//

#ifndef ABSEIL_SERVER_H
#define ABSEIL_SERVER_H

#include "Node.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>

class User;

class Server : public Node
{
    std::vector< User* > connectedUsersVector;
public:
    Server( const std::string& _name, sf::Vector2f& _pos, sf::RenderWindow& _rw );
    void makeConnection( Node* _target ) override;
};


#endif //ABSEIL_SERVER_H
