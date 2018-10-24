//
// Created by ezjakko on 24.10.2018.
//

#ifndef _MAINPLAYERHUD_H
#define _MAINPLAYERHUD_H

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Window.hpp>

class MainPlayerHud {
    const int width;
    const int height;
    sf::RenderWindow& window;
};


#endif //_MAINPLAYERHUD_H
