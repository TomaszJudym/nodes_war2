//
// Created by ezjakko on 16.10.2018.
//

#include "NodesBattlefield.h"

using std::make_shared;
using std::make_unique;

NodesBattlefield::NodesBattlefield()
: window(sf::VideoMode(1400, 1050), "nodes_war", sf::Style::Close | sf::Style::Titlebar)
, choosing_state(not_choosing)
, unitManipulator(UnitManip::getInstance())
{
    initLoad();
}

bool NodesBattlefield::initLoad()
{
    bool initPassed = true;

    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);
    window.setActive(false); // deactivating OpenGL context, because
                             // it can run only in 1 thread at the same time

    servers.reserve(10);
    users.reserve(10);

    terminal = make_unique<Terminal>();
    if(!terminal) initPassed = false;

    users.emplace_back( User::spawnUser(400.f, 350.f));
    users.emplace_back( User::spawnUser(600.f, 500.f));
    users.emplace_back( User::spawnUser(800.f, 650.f));

    servers.emplace_back( "DANK_3", sf::Vector2f(150, 300));

    unitManipulator.addConnection(&servers[0], users[0].get());

    return initPassed;
}

NodesBattlefield& NodesBattlefield::getInstance()
{
    static NodesBattlefield instance;   // Guaranteed to be destroyed
                                        // instantiated on first use
    return instance;
}

void NodesBattlefield::run()
{
    while(window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void NodesBattlefield::processEvents()
{
    sf::Event event = sf::Event();

    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                handlePlayerInputKeyboard(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                handlePlayerInputKeyboard(event.key.code, false);
                break;

            case sf::Event::TextEntered:
                handleTerminal(event.text.unicode);
                break;

            case sf::Event::MouseButtonReleased:
                handlePlayerInputMouse(event.mouseButton.button, false);
                break;

            default:
                break;
        }
    }
}

void NodesBattlefield::handlePlayerInputMouse( sf::Mouse::Button _button, bool _pressed )
{
    sf::Vector2f mousePos = sf::Vector2f( sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y );
    Node* choosedUnit = nullptr;

    if ( !_pressed )
    {
        auto foundServer = std::find_if( servers.begin(), servers.end(), [&mousePos](Server& _server){ // address of object from_under iterator
            return _server.getSprite().getGlobalBounds().contains(mousePos);
        } );

        if (foundServer == servers.end()) // no server is pointed to by cursor, so maybe user has been clicked
        {
            auto foundUser = std::find_if(users.begin(), users.end(), [&mousePos](std::shared_ptr<User> _userPtr){
                return _userPtr->getSprite().getGlobalBounds().contains(mousePos);
            });
            // TODO refactor method for better searching through game objects to click
            if( foundUser != users.end() )
            {
                std::cout << "user_clicked" << std::endl;
                choosedUnit = foundUser->get();
            }
        } else
        {
            choosedUnit = &*foundServer; // address of server object from_under iterator
            std::cout << "server_clicked" << std::endl;
        }

        if (choosing_state == not_choosing && choosedUnit) // server or user has been found as marked by mouse cursor
        {
                choosing_state = choosing;
                unitManipulator.currentlyCreatedLine = new ThicknessLine(choosedUnit->getPosition(), mousePos);
                unitManipulator.unitToMakeConnectionFrom = choosedUnit;
        }
        else if (choosing_state == choosing)
        {
            if( choosedUnit && choosedUnit != unitManipulator.unitToMakeConnectionFrom)   // we' ve chosen unit to make connection to
            {
                unitManipulator.addConnection( unitManipulator.unitToMakeConnectionFrom, choosedUnit );
            }
            // otherwise we clicked in same unit we've made connection from or clicked in nothing,
            // so procedure of making connection is broken
            delete unitManipulator.currentlyCreatedLine;
            unitManipulator.currentlyCreatedLine = nullptr;
            unitManipulator.unitToMakeConnectionFrom = nullptr;
            choosing_state = not_choosing;
        }
    }
}

void NodesBattlefield::handlePlayerInputKeyboard( sf::Keyboard::Key _key, bool pressed )
{

}

void NodesBattlefield::handleTerminal(sf::Uint32 _key)
{
    if (_key < 128)
    {
        if (_key == '\b') // backspace
            terminal->update((short)-1);
        else if( _key == sf::Keyboard::Return )
        {
            // TODO make new line AND loading command if any present
            //terminal.update( (char)'\n' );
            //terminal.catchCommand();
        }
        else
            terminal->update((char) _key);
    }
}

void NodesBattlefield::update()
{
    if(unitManipulator.currentlyCreatedLine)
    {
        delete unitManipulator.currentlyCreatedLine;
        unitManipulator.currentlyCreatedLine = new ThicknessLine(unitManipulator.unitToMakeConnectionFrom->getPosition()
                                             , sf::Vector2f( sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
    }
}

void NodesBattlefield::render()
{
    window.clear(sf::Color::Black);

    terminal->draw(window);

    for( const auto& x : servers )
        x.draw(window);

    for( const auto& x : users)
        x->draw(window);

    for( const auto& x : *unitManipulator.getConnectionsMap() )
        x.second->draw(window);

    if( unitManipulator.currentlyCreatedLine != nullptr )
        unitManipulator.currentlyCreatedLine->draw(window);

    window.display();
}
