//
// Created by ezjakko on 24.10.2018.
//

#include "MainPlayerHud.h"

MainPlayerHud::MainPlayerHud(unsigned _width, unsigned _height, sf::Font& _font, sf::RenderWindow& _window)
: width(_width)
, height(_height)
, unitData(_font)
, window(_window)
{
    unitData.setFont(_font);
}

void MainPlayerHud::initHud(sf::Texture& _back, sf::Texture& _inventory, sf::Sprite& _portrait)
{
    auto fwidth = static_cast<float>(width);
    auto fheight = static_cast<float>(height);

    backgroundSprite.setTexture(_back);
    inventorySprite.setTexture(_inventory);
    unitData.setPortrait(_portrait);

    backgroundSprite.setTextureRect({0, 0, width, height});


    backgroundSprite.setOrigin(fwidth/2, fheight/2);                                  // middle of background tab
    backgroundSprite.setPosition(fwidth/2                                             // middle of screen
                               , window.getSize().y - fheight/2);                     // bottom of screen like in RTS games

    // inventory sprite to right side of HUD
    inventorySprite.setOrigin(inventorySprite.getGlobalBounds().width / 2, inventorySprite.getGlobalBounds().height / 2);
    inventorySprite.setPosition(fwidth-inventorySprite.getGlobalBounds().width / 2, window.getSize().y-fheight / 2);


    unitData.getPortrait().setOrigin(unitData.getPortrait().getGlobalBounds().width/2,
                                     unitData.getPortrait().getGlobalBounds().height/2);
    unitData.getPortrait().setScale(0.20f, 0.20f);

    unitData.setPosition(inventorySprite.getPosition().x - inventorySprite.getGlobalBounds().width/2
                          - unitData.getPortrait().getGlobalBounds().width
            , inventorySprite.getPosition().y);
}

void MainPlayerHud::setUnitPortrait(sf::Sprite& _newPortrait)
{
    unitData.setPortrait(_newPortrait);
}

MainPlayerHud& MainPlayerHud::getInstance(unsigned _width, unsigned _height, sf::Font& _font, sf::RenderWindow& _window)
{
    // constructor will be called only the first time, despite the different arguments
    static MainPlayerHud instance(_width, _height, _font, _window);
    return instance;
}

void MainPlayerHud::draw(sf::RenderTarget& _rw, sf::RenderStates _states) const
{
    _rw.draw(backgroundSprite);
    _rw.draw(inventorySprite);
    _rw.draw(unitData.getPortrait());
    _rw.draw(unitData);
}

void MainPlayerHud::updateUnitData(sf::Sprite& _portrait, std::wstring& _name, int _hp)
{
    setUnitPortrait(_portrait);
    unitData.setName(_name);
    unitData.setHp(_hp);
}




ChosenUnitData::ChosenUnitData(sf::Font& _font)
: unitName("_undfined_", _font, 12)
, unitHealth("-- / --", _font, 15)
{
    unitName.setOrigin(unitName.getGlobalBounds().width / 2 + 20.f, unitName.getGlobalBounds().height / 2 + 40.f);
    unitHealth.setOrigin(unitHealth.getGlobalBounds().width / 2 - 20.f, unitHealth.getGlobalBounds().height / 2 + 40.f);
}

void ChosenUnitData::draw(sf::RenderTarget& _rw, sf::RenderStates _rs) const
{
    _rw.draw(unitName);
    _rw.draw(unitHealth);
}

void ChosenUnitData::setPosition(const sf::Vector2f& _pos)
{
    unitPortrait.setPosition(_pos);
    unitName.setPosition(_pos.x-70.f, _pos.y - unitPortrait.getGlobalBounds().height/2 - unitName.getGlobalBounds().height + 10.f);
    unitHealth.setPosition(_pos.x, _pos.y - unitPortrait.getGlobalBounds().height/2 - unitName.getGlobalBounds().height + 10.f);
}

void ChosenUnitData::setPosition(float _x, float _y)
{
    setPosition(sf::Vector2f(_x, _y));
}

void ChosenUnitData::setFont(sf::Font& _font)
{
    unitName.setFont(_font);
    unitHealth.setFont(_font);
}

void ChosenUnitData::setName(const std::wstring _name)
{
    unitName.setString(_name);
}

void ChosenUnitData::setHp(const unsigned& _hp)
{
    currentHp = _hp;
}

void ChosenUnitData::setPortrait(sf::Sprite& _spr)
{
    unitPortrait = _spr;
}