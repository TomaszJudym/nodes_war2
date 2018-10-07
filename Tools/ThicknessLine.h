//
// Created by Ackan on 07.10.2018.
//

#ifndef THICKNESSLINE_H
#define THICKNESSLINE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>

class ThicknessLine : public sf::Drawable
{
public:
    ThicknessLine(const sf::Vector2f& _point1, const sf::Vector2f& _point2, sf::Color _col = sf::Color::Yellow );
    void draw(sf::RenderTarget& _rw, sf::RenderStates = sf::RenderStates()) const; // draw is abstract, RenderStates needed in definition
private:
    sf::Vertex vertices[4];
    float thickness;
    sf::Color color;
};


#endif //ABSEIL_THICKNESSLINE_H
