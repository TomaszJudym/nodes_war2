//
// Created by Ackan on 17.09.2018.
//

#ifndef ABSEIL_USER_H
#define ABSEIL_USER_H


#include "Node.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <atomic>

enum JAP_NAMES
{
    WOLF=0,
    IDIOT,
    COUNTERPUNCH,
    DELTA,
    YELLOW,
    MATILDA
};

class Server;

class User : public Node
{
    static const std::map< int, std::wstring > names;
    static size_t userCount;

    User( const sf::Vector2f& _pos, sf::Texture& _texture );

    Server* connectedServerPtr;

public:
    static std::shared_ptr<User> spawnUser( const sf::Vector2f& _pos, sf::Texture& _texture);
    static std::shared_ptr<User> spawnUser( float _x, float _y, sf::Texture& _texture ); // wrapper for calling sf::Vector2f&

    User(const User&) = default;
    User(User&&) = default;
    void makeConnection( Node* _target ) override;
    ~User() override;
};


#endif //ABSEIL_USER_H
