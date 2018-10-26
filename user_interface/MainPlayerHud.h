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
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Window.hpp>

class MainPlayerHud : public sf::Drawable{
    sf::RenderWindow& window;

    const int width;
    const int height;
    sf::Sprite backgroundSprite;
    sf::Sprite unitPortraitSprite;
    sf::Sprite inventorySprite;

    MainPlayerHud(unsigned _width, unsigned _height, sf::RenderWindow& _window);
public:
    static MainPlayerHud& getInstance(unsigned _width, unsigned _height, sf::RenderWindow& _window);

    void draw(sf::RenderTarget& _rw, sf::RenderStates = sf::RenderStates::Default) const override;
    void initHud(sf::Texture& _back, sf::Texture& _inventory, sf::Texture& _portrait);
    void setUnitPortrait(sf::Sprite& _newPortrait);


    MainPlayerHud(const MainPlayerHud&) = delete;
    MainPlayerHud& operator=(const MainPlayerHud&) = delete;
};


#endif //_MAINPLAYERHUD_H
