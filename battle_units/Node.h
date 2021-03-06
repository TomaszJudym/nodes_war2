//
// Created by Ackan on 17.09.2018.
//

#ifndef ABSEIL_NODE_H
#define ABSEIL_NODE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <locale>
#include <codecvt>

class Node : public sf::Drawable {
protected:

    std::wstring            name;
    static sf::Font         font;
    sf::Sprite              sprite;
    sf::Text                displayedName;
    sf::Vector2f            position;
    void                    setTextPosition( float _x, float _y );
    void                    initSprite(const sf::Texture& _texture);
    void                    initText();
public:
    explicit                Node(const sf::Vector2f& _pos, sf::Texture& _texture);
                            Node( const Node& _cpyNode );
    void                    setPosition( const sf::Vector2f& _pos );
    void                    draw(sf::RenderTarget& _rw, sf::RenderStates = sf::RenderStates::Default) const override;
    const sf::Vector2f&     getPosition() const;
    sf::Sprite&             getSprite();
    std::wstring&           getName();
    inline void             setName( const std::wstring& _name ) { name = _name; }
    static sf::Font&        getFont();

    virtual void             makeConnection( Node* _target ) = 0;
    virtual                  ~Node() = default;
};


#endif //ABSEIL_NODE_H
