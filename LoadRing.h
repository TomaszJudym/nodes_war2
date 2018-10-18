//
// Created by Ackan on 11.09.2018.
//

#ifndef ABSEIL_LOADRING_H
#define ABSEIL_LOADRING_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <array>
#include <chrono>
#include <thread>

class LoadRing
{
public:
    LoadRing( sf::RenderWindow& _window, sf::Color _color = sf::Color::Red );
    void setPosition( const sf::Vector2f& );
    void setPosition( float, float );
    void load();
    void draw();

private:
    bool fullyLoaded;
    unsigned short activeTriangles;
    sf::RenderWindow& window;
    std::array<sf::ConvexShape, 8> triangles;
    sf::Vector2f center;
    sf::Color color;
};


#endif //ABSEIL_LOADRING_H
