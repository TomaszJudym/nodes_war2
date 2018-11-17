//
// Created by ezjakko on 24.10.2018.
//

#ifndef _MAINPLAYERHUD_H
#define _MAINPLAYERHUD_H

#include <iostream>
#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/Font.hpp>

class ChosenUnitData : public sf::Drawable{
    sf::Sprite unitPortrait;
    sf::Text   unitName;
    sf::Text   unitHealth;
    unsigned   maxHp;
    unsigned   currentHp;
public:
    ChosenUnitData(sf::Font&  _font);
    void draw(sf::RenderTarget& _rw, sf::RenderStates = sf::RenderStates::Default) const override;
    void setPosition(const sf::Vector2f& _pos);
    void setPosition(float, float);
    void setFont(sf::Font& _font);
    void setName(const std::wstring _name);
    void setPortrait(sf::Sprite& _spr);
    void setHp(const unsigned& _hp);
    inline sf::Sprite& getPortrait() { return unitPortrait; }
    inline const sf::Sprite& getPortrait() const { return unitPortrait; }
};

class MainPlayerHud : public sf::Drawable{
    sf::RenderWindow& window;

    const int width;
    const int height;
    sf::Sprite backgroundSprite;
    sf::Sprite inventorySprite;
    ChosenUnitData unitData;

    void setUnitPortrait(sf::Sprite& _newPortrait);

    MainPlayerHud(unsigned _width, unsigned _height, sf::Font& _font, sf::RenderWindow& _window);
public:
    static MainPlayerHud& getInstance(unsigned _width, unsigned _height, sf::Font& _font, sf::RenderWindow& _window);

    void draw(sf::RenderTarget& _rw, sf::RenderStates = sf::RenderStates::Default) const override;
    void initHud(sf::Texture& _back, sf::Texture& _inventory, sf::Sprite& _portrait);
    void updateUnitData(sf::Sprite& _portrait, std::wstring& _name, int _hp);


    MainPlayerHud(const MainPlayerHud&) = delete;
    MainPlayerHud& operator=(const MainPlayerHud&) = delete;
};


#endif //_MAINPLAYERHUD_H
