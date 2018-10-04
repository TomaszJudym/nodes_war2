//
// Created by Ackan on 17.09.2018.
//

#include "Node.h"

sf::Font Node::font = sf::Font();

void Node::initText()
{
    font.loadFromFile( "font/Osaka.ttc" );
    displayedName.setFont( font );
    displayedName.setFillColor( sf::Color::White );
    displayedName.setCharacterSize( 16 );
    displayedName.setString( name );
    displayedName.setOrigin( displayedName.getGlobalBounds().width/2, 2*(displayedName.getGlobalBounds().height) );
    setTextPosition( position.x, position.y );
}

Node::Node( sf::Vector2f& _pos, sf::RenderWindow& _rw ) :
position(_pos),
renderWindow( _rw )
{}

Node::Node( const Node& _cpyNode ) :
name( _cpyNode.name ),
position( _cpyNode.position ),
sprite( _cpyNode.sprite ),
renderWindow( _cpyNode.renderWindow )
{
    initText();
}

void Node::initSprite()
{
    sprite.setTexture( image );
    sprite.setScale( 0.15f, 0.15f );
    sprite.setOrigin( sprite.getGlobalBounds().width, sprite.getGlobalBounds().height/2 );
    sprite.setPosition( position );
}

void Node::setPosition( const sf::Vector2f& _pos )
{
    sprite.setPosition( _pos );
    setTextPosition( position.x, position.y-image.getSize().y );
}

void Node::draw()
{
    renderWindow.draw( sprite );
    renderWindow.draw( displayedName );
}

void Node::setTextPosition( float _x, float _y )
{
    displayedName.setPosition( _x, _y );
}

const sf::Vector2f& Node::getPosition()
{
    return position;
}