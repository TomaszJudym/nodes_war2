//
// Created by ezjakko on 16.10.2018.
//

#include "NodesBattlefield.h"

using std::make_shared;
using std::make_unique;
using std::cout;
using std::endl;

const float NodesBattlefield::VIEW_WIDTH = 1400.f;
const float NodesBattlefield::VIEW_HEIGHT = 768.f;

NodesBattlefield::NodesBattlefield()
: window(sf::VideoMode(1400, 768), "nodes_war", sf::Style::Close | sf::Style::Titlebar)
, manip_state(none)
, unitManipulator(UnitManip::getInstance())
, texturesHolder(std::make_unique<ResourceHolder<sf::Texture, const std::string>>())
, playerHud(MainPlayerHud::getInstance(1400, 200, window))
, mainView(sf::Vector2f(0.f, 0.f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT))
{
    initLoad();
}

bool NodesBattlefield::initLoad()
{
    bool initPassed = true;

    window.setKeyRepeatEnabled(false); // true for moving units in real time
    window.setFramerateLimit(60);
    window.setActive(false); // deactivating OpenGL context, because
                             // it can run only in 1 thread at the same time

    texturesHolder->load("server1", "img/server800x800.jpg");
    texturesHolder->load("user1", "img/computer630x630.jpg");
    texturesHolder->load("mainHudBackground", "img/mainHudBackground.jpg");
    texturesHolder->load("inventorySpace", "img/inventorySpace.jpg");

    texturesHolder->get("mainHudBackground").setRepeated(true); // image to short for screen width

    playerHud.initHud(texturesHolder->get("mainHudBackground"), texturesHolder->get("inventorySpace"), texturesHolder->get("user1"));

    servers.reserve(10);
    users.reserve(10);

    terminal = make_unique<Terminal>();
    if(!terminal) initPassed = false;

    users.emplace_back( User::spawnUser(400.f, 350.f, texturesHolder->get("user1")));
    users.emplace_back( User::spawnUser(800.f, 500.f, texturesHolder->get("user1")));
    users.emplace_back( User::spawnUser(350.f, 650.f, texturesHolder->get("user1")));
    users.emplace_back( User::spawnUser(150.f, 700.f, texturesHolder->get("user1")));
    users.emplace_back( User::spawnUser(500.f, 630.f, texturesHolder->get("user1")));

    servers.emplace_back( "DANK_3", sf::Vector2f(150, 300), texturesHolder->get("server1"));

    std::cout << "serv: " << sizeof(Server) << " usr: " << sizeof(User) << std::endl;

    return initPassed;
}

void NodesBattlefield::resizeView(const sf::RenderWindow& _window, sf::View& _view)
{
    float aspectRatio = static_cast<float>(_window.getSize().x) / static_cast<float>(_window.getSize().y);

    mainView.setSize(aspectRatio * VIEW_HEIGHT, VIEW_HEIGHT);
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

            case sf::Event::MouseButtonPressed:
                handlePlayerInputMouse(event.mouseButton.button, true);
                break;

            case sf::Event::MouseMoved:
                handlePlayerMouseMove();
                break;

            case sf::Event::Resized:
               // resizeView(window, mainView); // TODO decide is resizing neccesary
            default:
                break;
        }
    }
}

inline void NodesBattlefield::backToChoosingState()
{
    delete unitManipulator.memorisUnit->currentlyCreatedLine;
    unitManipulator.memorisUnit->currentlyCreatedLine = nullptr;
    unitManipulator.memorisUnit->unitToManip = nullptr;
    manip_state = none;
}

Node* NodesBattlefield::containsUnit(const sf::Vector2f& _pos)
{
    Node* chosenUnit = nullptr;
    auto foundServer = std::find_if( servers.begin(), servers.end(), [&_pos](Server& _server){ // address of object from_under iterator
        return _server.getSprite().getGlobalBounds().contains(_pos);
    } );

    if (foundServer == servers.end()) // no server is pointed to by cursor, so maybe user has been clicked
    {
        auto foundUser = std::find_if(users.begin(), users.end(), [&_pos](std::shared_ptr<User> _userPtr){
            return _userPtr->getSprite().getGlobalBounds().contains(_pos);
        });
        // TODO refactor method for better searching through game objects to click
        if( foundUser != users.end() )
        {
            chosenUnit = foundUser->get();
        }
    } else
    {
        chosenUnit = &*foundServer; // address of server object from_under iterator
    }
    return chosenUnit;
}

void NodesBattlefield::handlePlayerInputMouse( sf::Mouse::Button _button, bool _pressed )
{
    Node* clickedUnit = containsUnit(getMousePos());

    if ( _button == sf::Mouse::Right )
    {
        if(clickedUnit)
            handleUnitsAction(clickedUnit, _pressed);
    }
    else if ( _button == sf::Mouse::Left )
    {
            handleUnitsMove(clickedUnit, _pressed);
    }

    if ( !clickedUnit )
    {
        if ( unitManipulator.memorisUnit->currentlyCreatedLine )
        {
            backToChoosingState();
        }
    }

}

void NodesBattlefield::handleUnitsAction(Node* _unit, bool _pressed)
{
    if ( !_pressed )
    {
        if (manip_state == none ) // server or user has been found as marked by mouse cursor
        {
            manip_state = choosing;
            unitManipulator.memorisUnit->currentlyCreatedLine = new ThicknessLine(_unit->getPosition()
                    , getMousePos());
            unitManipulator.memorisUnit->unitToManip = _unit;
        }
        else if (manip_state == choosing)
        {
            if(_unit != unitManipulator.memorisUnit->unitToManip)   // we' ve chosen unit to make connection to
            {
                unitManipulator.addConnection( unitManipulator.memorisUnit->unitToManip, _unit );
            }
            // transition has been added to map, no need to draw transition pointed
            // to mouse cursor anymore
            backToChoosingState();
        }
    }
}

void NodesBattlefield::handleUnitsMove(Node* _unit, bool _pressed)
{
    if ( _pressed )
    {
        if ( manip_state == none && _unit ) // we have chosen units to manipulate
        {
            manip_state = moving;
            unitManipulator.memorisUnit->unitToManip = _unit;
            unitManipulator.memorisUnit->movingUnitOffset = UnitManip::getDirVec(_unit->getPosition(), getMousePos());
        }
        else if ( manip_state == moving )
        {
            sf::Vector2f newPos = unitManipulator.selectNewUnitPosition(_unit, window);

            unitManipulator.memorisUnit->unitToManip->setPosition(newPos);
            unitManipulator.updateTransitions(_unit);
        }
    }
    else if ( !_pressed )
    {
        if ( manip_state == moving )
        {
            if ( unitManipulator.memorisUnit->unitWasMoved )
            {
                sf::Vector2f newPos = unitManipulator.selectNewUnitPosition(unitManipulator.memorisUnit->unitToManip, window);
                unitManipulator.memorisUnit->unitToManip->setPosition(newPos);
                unitManipulator.memorisUnit->unitWasMoved = false;
            }
            manip_state = none;                                                      // we've stopped moving
            unitManipulator.memorisUnit->unitToManip = nullptr;                      // we're no longer manipulating this unit
            unitManipulator.memorisUnit->movingUnitOffset = sf::Vector2f(0.f, 0.f);
        }
    }
}

void NodesBattlefield::handlePlayerInputKeyboard( sf::Keyboard::Key _key, bool _pressed )
{

}

void NodesBattlefield::handlePlayerMouseMove()
{
    if ( manip_state == moving )
    {
        sf::Vector2f newPos = unitManipulator.selectNewUnitPosition(unitManipulator.memorisUnit->unitToManip, window);

        unitManipulator.memorisUnit->unitToManip->setPosition(newPos);
        unitManipulator.memorisUnit->unitWasMoved = true;
        unitManipulator.updateTransitions(unitManipulator.memorisUnit->unitToManip);
    }
}

void NodesBattlefield::handleTerminal(sf::Uint32 _key)
{
    if (_key < 128)
    {
        if (_key == '\b') // backspace
            terminal->update((short)-1);
        else if ( _key == sf::Keyboard::Return )
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
    if(unitManipulator.memorisUnit->currentlyCreatedLine)
    {
        delete unitManipulator.memorisUnit->currentlyCreatedLine;
        unitManipulator.memorisUnit->currentlyCreatedLine = new ThicknessLine(unitManipulator.memorisUnit->unitToManip->getPosition()
                                             , getMousePos());
    }
}

void NodesBattlefield::render()
{
    window.clear(sf::Color::Black);
    mainView.setCenter(window.getSize().x / 2, window.getSize().y / 2);
    window.setView(mainView);


    playerHud.draw(window);

    terminal->draw(window);

    for( const auto& x : servers )
        x.draw(window);

    for( const auto& x : users)
        x->draw(window);

    for( const auto& x : *unitManipulator.getConnectionsMap() )
        x.second->draw(window);

    if( unitManipulator.memorisUnit->currentlyCreatedLine != nullptr )
        unitManipulator.memorisUnit->currentlyCreatedLine->draw(window);

    window.display();
}

const sf::Vector2f NodesBattlefield::getMousePos()
{
    return sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
}