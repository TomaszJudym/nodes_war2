//
// Created by ezjakko on 15.10.2018.
//

#include "UnitManip.h"

UnitManip::UnitManip()
: connectionsMap()
, memorisUnit(new MemorisUnit())
{}

UnitManip& UnitManip::getInstance()
{
    static UnitManip instance;
    return instance;
}

bool UnitManip::mouseIsInScreenBorders(const sf::RenderWindow& _window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
    return  mousePos.x > 0 && mousePos.x <= _window.getSize().x &&
           mousePos.y > 0 && mousePos.y <= _window.getSize().y;
}

sf::Vector2f UnitManip::selectNewUnitPosition(const sf::RenderWindow& _window)
{
    sf::Vector2f newPos;
    if(UnitManip::mouseIsInScreenBorders(_window))
    {
        newPos =   sf::Vector2f(
                   sf::Mouse::getPosition(_window).x
                 , sf::Mouse::getPosition(_window).y)
                 + memorisUnit->movingUnitOffset; // last setting position of controlled unit
    }
    else
    {
        newPos = UnitManip::coordinatePositionToWindow(memorisUnit->unitToManip->getPosition(), _window);
    }
    
    return newPos;
}

sf::Vector2f UnitManip::coordinatePositionToWindow(const sf::Vector2f& _pos, const sf::RenderWindow& _window)
{
    sf::Vector2f fixedPos;
    if (_pos.x > _window.getSize().x) fixedPos.x = _window.getSize().x;
    else if(_pos.x < 0) fixedPos.x = 0;
    else fixedPos.x = _pos.x;
    if(_pos.y > _window.getSize().y) fixedPos.y = _window.getSize().y;
    else if(_pos.y < 0) fixedPos.y = 0;
    else fixedPos.y = _pos.y;

    return fixedPos;
}

sf::Vector2f UnitManip::getDirVec(const sf::Vector2f& _first, const sf::Vector2f& _second)
{
    sf::Vector2f directionalVector = _first - _second;                                      // correct direction
    return directionalVector;
}

ThicknessLine* UnitManip::connect2Units( Node* _connecter, Node* _connected, sf::Color _color )
{
    // for testing purpuses, line is leaking, shall b auto as object member and deleted with destruction

    sf::Vector2f dirVecNorm = UnitManip::getDirVec(_connected->getPosition(), _connecter->getPosition()); // from connecter to connected

    sf::Vector2f connecterPos = _connecter->getPosition();
    sf::Vector2f connectedPos = _connected->getPosition();

    while ( _connecter->getSprite().getGlobalBounds().contains(connecterPos) )
        connecterPos += dirVecNorm;

    while ( _connected->getSprite().getGlobalBounds().contains(connectedPos) )
        connectedPos -= dirVecNorm;

    auto* connector = new ThicknessLine( connecterPos, connectedPos, _color );
    return connector;
}

void UnitManip::addConnection(Node* _connecter, Node* _connected)
{
    // if connection already exist ( may be reversed by connecter / connected, we are not making new one
    if (std::find_if(connectionsMap.begin(), connectionsMap.end(),
            [&_connecter, &_connected](std::pair<ConnectionData*, ThicknessLine*> _p){
            return (_p.first->connecter == _connecter && _p.first->connected == _connected)
                || (_p.first->connecter == _connected && _p.first->connected == _connecter);
    }) == connectionsMap.end())
    {
        std::wstringstream ss;
        ss << _connecter->getName() << "_to_" << _connected->getName();
        std::wstring connectionName = ss.str();
        auto* connData = new ConnectionData(_connecter, _connected, connectionName);
        connectionsMap[connData] = connect2Units(_connecter, _connected);
    }
}

const std::map< ConnectionData*, ThicknessLine* >* UnitManip::getConnectionsMap()
{
    return &connectionsMap;
}

void UnitManip::updateTransitions(Node* _changedNode)
{
    for (auto& x : connectionsMap)
    {
        connNodeType type = NONE; // need to know which end of transition change, and which to hold in same place
        if ( _changedNode == x.first->connecter) // in struct those are represented as connecter and connected
            type = CONNECTER;
        else if ( _changedNode == x.first->connected )
            type = CONNECTED;

        if ( type == CONNECTER )
        {
            delete x.second;
            x.second = connect2Units(_changedNode, x.first->connected);
        }
        else if ( type == CONNECTED )
        {
            delete x.second;
            x.second = connect2Units(x.first->connecter, _changedNode);
        }

    }
}

// CONNECTION_MAP_DATA

unsigned ConnectionData::connectionCounter = 0;

ConnectionData::ConnectionData(Node* _from, Node* _to, const std::wstring& _connName)
: connecter(_from)
, connected(_to)
, connectionName(_connName)
, connectionId(connectionCounter++)
{}

inline bool ConnectionData::operator< (const ConnectionData& _cmp)
{
    return this->connectionId < _cmp.connectionId;
}

ConnectionData::~ConnectionData()
{
    --connectionCounter;
}


// END_CONNECTION_MAP_DATA

// MEMORIS_UNIT
MemorisUnit::MemorisUnit()
: unitWasMoved(false)
, unitToManip(nullptr)
, currentlyCreatedLine(nullptr)
, movingUnitOffset({0.f, 0.f})
{}
// END_MEMORIS_UNIT