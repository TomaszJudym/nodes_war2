//
// Created by Ackan on 17.09.2018.
//

#ifndef ABSEIL_NODE_H
#define ABSEIL_NODE_H

#include <SFML/Graphics.hpp>
#include <string>

class Node {
protected:
    std::string             name;
    static sf::Font         font;
    sf::Texture             image;
    sf::Sprite              sprite;
    sf::Text                displayedName;
    sf::Vector2f            position;
    void                    initSprite();
    void                    setTextPosition( float _x, float _y );
    sf::RenderWindow& renderWindow;
public:
    explicit Node( const std::string& _name, sf::Vector2f& _pos, sf::RenderWindow& _rw );
    void setPosition( const sf::Vector2f& _pos );
    void draw();
    const sf::Vector2f& getPosition();
    virtual void makeConnection( const Node* _target ) = 0;
};


#endif //ABSEIL_NODE_H
