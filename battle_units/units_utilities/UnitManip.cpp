//
// Created by ezjakko on 15.10.2018.
//

#include "UnitManip.h"

UnitManip::UnitManip()
: connectionsMap()
, currentlyCreatedLine(nullptr)
, unitToManip(nullptr)
{}

UnitManip& UnitManip::getInstance()
{
    static UnitManip instance;
    return instance;
}

ThicknessLine* UnitManip::connect2Units( Node* _connecter, Node* _connected, sf::Color _color )
{
    // for testing purpuses, line is leaking, shall b auto as object member and deleted with destruction

    sf::Vector2f dirVecNorm = _connected->getPosition() - _connecter->getPosition(); // from connecter to connected

    double length = sqrt(pow(dirVecNorm.x, 2) + pow(dirVecNorm.y, 2));

    dirVecNorm = sf::Vector2f( 
             static_cast<float>(dirVecNorm.x/length)
           , static_cast<float>(dirVecNorm.y/length));

   
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
    std::wstringstream ss;
    ss << _connecter->getName() << "_to_" << _connected->getName();
    std::wstring connectionName = ss.str();
    auto* connData = new ConnectionData(_connecter, _connected, connectionName);
    connectionsMap[connData] = connect2Units(_connecter, _connected);

}

const std::map< ConnectionData*, ThicknessLine* >* UnitManip::getConnectionsMap()
{
    return &connectionsMap;
}

void UnitManip::updateTransitions(const Node* _changedNode)
{
    int i=0;
    std::cout << "updating map of size: " << connectionsMap.size() << std::endl;
    for(auto& x : connectionsMap)
    {
        connNodeType type = NONE; // need to know which end of transition change, and which to hold in same place
        if( _changedNode == x.first->connecter) // in struct those are represented as connecter and connected
            type = CONNECTER;
        else if( _changedNode == x.first->connected )
            type = CONNECTED;

        if( type == CONNECTER )
        {
            delete x.second;
            x.second = new ThicknessLine(_changedNode->getPosition(), x.first->connecter->getPosition());
        }
        else if( type == CONNECTED )
        {
            delete x.second;
            x.second = new ThicknessLine(x.first->connecter->getPosition(), _changedNode->getPosition());
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

// END_CONNECTION_MAP_DATA