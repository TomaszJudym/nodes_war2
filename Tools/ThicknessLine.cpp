//
// Created by Ackan on 07.10.2018.
//

#include "ThicknessLine.h"

ThicknessLine::ThicknessLine( const sf::Vector2f& _point1, const sf::Vector2f& _point2, sf::Color _col)
        : thickness(5.f)
        , color(_col)
{
    sf::Vector2f direction = _point2 - _point1;
    sf::Vector2f unitDirection = direction/
                                 static_cast<float>(sqrt(direction.x*direction.x + direction.y*direction.y));
    sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

    sf::Vector2f offset = (thickness/2.f)*unitPerpendicular;

    vertices[0].position = _point1 + offset;
    vertices[1].position = _point2 + offset;
    vertices[2].position = _point2 - offset;
    vertices[3].position = _point1 - offset;

    for( auto& vert : vertices ) vert.color = color;
}

const sf::Vector2f ThicknessLine::getMiddle()
{
    // just pitagoras divided by 2 to get middle of path we need to travel
    double length = sqrt(pow((vertices[1].position.x - vertices[0].position.x), 2) +
                    pow((vertices[1].position.y - vertices[0].position.y), 2)) / 2;
    // now gonna remind ourselves what direction was it
    sf::Vector2f direction = vertices[1].position - vertices[0].position;

    // normalize it to size 1
    sf::Vector2f unitDirection =
            direction / static_cast<float>(sqrt(direction.x*direction.x + direction.y*direction.y));

    // offset in correct normalized direction
    sf::Vector2f offset = 2.5f * unitDirection;
    // substracting perpendiculat offset is for getting middle of our thick line ( its const 5.f )

    return (vertices[1].position + vertices[0].position)/2.f;
}

void ThicknessLine::draw(sf::RenderTarget& _rw, sf::RenderStates _states) const
{
    _rw.draw(vertices, 4, sf::Quads);
}