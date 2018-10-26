//
// Created by ezjakko on 24.10.2018.
//

#include "MainPlayerHud.h"

MainPlayerHud::MainPlayerHud(unsigned _width, unsigned _height, sf::RenderWindow& _window)
: width(_width)
, height(_height)
, window(_window)
{
}

void MainPlayerHud::initHud(sf::Texture& _back, sf::Texture& _inventory, sf::Texture& _portrait)
{
    auto fwidth = static_cast<float>(width);
    auto fheight = static_cast<float>(height);

    backgroundSprite.setTexture(_back);
    inventorySprite.setTexture(_inventory);
    unitPortraitSprite.setTexture(_portrait);

    backgroundSprite.setTextureRect({0, 0, width, height});


    backgroundSprite.setOrigin(fwidth/2, fheight/2);                                  // middle of background tab
    backgroundSprite.setPosition(fwidth/2             // middle of screen
                               , window.getSize().y - fheight/2);                                         // bottom of screen like in RTS games

    // inventory sprite to right side of HUD
    inventorySprite.setOrigin(inventorySprite.getGlobalBounds().width / 2, inventorySprite.getGlobalBounds().height / 2);
    inventorySprite.setPosition(fwidth-inventorySprite.getGlobalBounds().width / 2, window.getSize().y-fheight / 2);


    unitPortraitSprite.setOrigin(unitPortraitSprite.getGlobalBounds().width/2, unitPortraitSprite.getGlobalBounds().height/2);
    unitPortraitSprite.setScale(0.20f, 0.20f);

    unitPortraitSprite.setPosition(inventorySprite.getPosition().x - inventorySprite.getGlobalBounds().width/2 - unitPortraitSprite.getGlobalBounds().width/2
                                 , inventorySprite.getPosition().y);
}

void MainPlayerHud::setUnitPortrait(sf::Sprite& _newPortrait)
{
    unitPortraitSprite = _newPortrait;
}

MainPlayerHud& MainPlayerHud::getInstance(unsigned _width, unsigned _height, sf::RenderWindow& _window)
{
    // constructor will be called only the first time, despite the different arguments
    static MainPlayerHud instance(_width, _height, _window);
    return instance;
}

void MainPlayerHud::draw(sf::RenderTarget& _rw, sf::RenderStates _states) const
{
    _rw.draw(backgroundSprite);
    _rw.draw(inventorySprite);
    _rw.draw(unitPortraitSprite);
}
