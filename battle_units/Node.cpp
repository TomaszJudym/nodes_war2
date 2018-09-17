//
// Created by Ackan on 17.09.2018.
//

#include "Node.h"

sf::Font Node::font = sf::Font();

Node::Node( const std::string& _name, sf::Vector2f& _pos, sf::RenderWindow& _rw ) :
name( _name ),
position(_pos),
renderWindow( _rw )
{
    font.loadFromFile( "font/batmfa__.ttf" );
    displayedName.setFillColor( sf::Color::White );
    displayedName.setCharacterSize( 16 );
    displayedName.setString( name );
}

void Node::initSprite()
{
    sprite.setTexture( image );
    sprite.setOrigin( image.getSize().x/2, image.getSize().y/2 );
    sprite.setScale( 0.15f, 0.15f );
    sprite.setPosition( position );
}

void Node::setPosition( const sf::Vector2f& _pos )
{
    setTextPosition( _pos.x, _pos.y-image.getSize().y/2 );
    sprite.setPosition( _pos );
}

void Node::draw()
{
    renderWindow.draw( sprite );
}

void Node::setTextPosition( float _x, float _y )
{
    displayedName.setPosition( _x, _y );
}

const sf::Vector2f& Node::getPosition()
{
    return position;
}