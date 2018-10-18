//
// Created by Ackan on 11.09.2018.
//

#include <SFML/System/Sleep.hpp>
#include "LoadRing.h"

LoadRing::LoadRing( sf::RenderWindow& _window, sf::Color _color ) :
window(_window),
color( _color ),
center(300, 300),
activeTriangles(0),
fullyLoaded(false)
{
    for( int i=0; i<8; ++i )
    {
        triangles[i].setPointCount(3);
        triangles[i].setPoint(0, sf::Vector2f(0, 0));
        triangles[i].setPoint(1, sf::Vector2f(20, 0));
        triangles[i].setPoint(2, sf::Vector2f(10, 30));
        triangles[i].setFillColor( sf::Color::Blue );
        // default pos to validate if someone went wrong
        // at positioning
        triangles[i].setPosition( 0, 0 );
        triangles[i].setOrigin( 10, 30 );
        triangles[i].rotate( (i)*45 );
    }

}

void LoadRing::draw()
{
    for( int i=0; i<activeTriangles; ++i )
    {
        window.draw( triangles[i] );
    }
}

void LoadRing::setPosition( const sf::Vector2f& _newPos )
{
    for( auto& x : triangles )
        setPosition(_newPos.x, _newPos.y);
}

void LoadRing::setPosition( float _x, float _y )
{
    for( auto& x : triangles )
        x.setPosition( _x, _y );
}

void LoadRing::load()
{
    window.setActive(false);
    for( int i=0; i<8; ++i )
    {
        draw();
        ++activeTriangles;
        sf::sleep(sf::milliseconds(400));
        std::cout << "triangle " << i << std::endl;
        window.display();
    }
    fullyLoaded = true;

    std::cout << "death" << std::endl;
}