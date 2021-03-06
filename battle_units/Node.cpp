//
// Created by Ackan on 17.09.2018.
//

#include "Node.h"

sf::Font Node::font = sf::Font();

Node::Node(const sf::Vector2f& _pos, sf::Texture& _texture) :
position(_pos)
{
    initSprite(_texture);
}

Node::Node( const Node& _cpyNode ) :
name( _cpyNode.name ),
position( _cpyNode.position ),
sprite( _cpyNode.sprite )
{
    initText();
}

void Node::initText()
{
    font.loadFromFile( "font/Osaka.ttc" );
    displayedName.setFont( font );
    displayedName.setFillColor( sf::Color::White );
    displayedName.setCharacterSize( 16 );
    displayedName.setString( name );
    displayedName.setOrigin( displayedName.getGlobalBounds().width/2, displayedName.getGlobalBounds().height/2 );
    setTextPosition( position.x, position.y-sprite.getGlobalBounds().height * 0.75f );
}

void Node::initSprite(const sf::Texture& _texture)
{
    sprite.setTexture( _texture );
    sprite.setOrigin( sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height/2 );
    sprite.setScale( 0.15f, 0.15f );
    sprite.setPosition( position );
}

sf::Sprite& Node::getSprite()
{
    return sprite;
}

void Node::setPosition( const sf::Vector2f& _pos )
{
    position = _pos;
    sprite.setPosition( position );
    setTextPosition( position.x, position.y-sprite.getGlobalBounds().height * 0.75f );
}

void Node::draw(sf::RenderTarget& _rw, sf::RenderStates _rs) const
{
    _rw.draw(sprite);
    _rw.draw(displayedName);
}

void Node::setTextPosition( float _x, float _y )
{
    displayedName.setPosition( _x, _y );
}

std::wstring& Node::getName()
{
    return name;
}

const sf::Vector2f& Node::getPosition() const
{
    return position;
}

sf::Font& Node::getFont()
{
    return font;
}