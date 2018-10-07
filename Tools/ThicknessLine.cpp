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
void ThicknessLine::draw(sf::RenderTarget& _rw, sf::RenderStates _states) const
{
    _rw.draw(vertices, 4, sf::Quads);
}