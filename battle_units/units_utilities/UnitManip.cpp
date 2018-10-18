//
// Created by ezjakko on 15.10.2018.
//

#include "UnitManip.h"

UnitManip::UnitManip()
: connectionsMap()
, currentlyCreatedLine(nullptr)
, unitToMakeConnectionFrom(nullptr)
{

}

UnitManip& UnitManip::getInstance()
{
    static UnitManip instance;
    return instance;
}

ThicknessLine* UnitManip::connect2Units( Node* _connecter, Node* _connected, sf::Color _color )
{
    // for testing purpuses, line is leaking, shall b auto as object member and deleted with destruction

    sf::Vector2f dirVecNorm = _connected->getPosition() - _connecter->getPosition(); // from connecter to connected

    std::cout << "dirVecNorm< " << dirVecNorm.x << " " << dirVecNorm.y << " >" << std::endl;
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
    std::cout << "conn_coods:< " << connecterPos.x << " | " << connectedPos.y << " || " << connecterPos.x << " | " <<
    connectedPos.y << " >" << std::endl;
    return connector;
}

void UnitManip::addConnection(Node* _connecter, Node* _connected)
{
    std::wstringstream ss;
    ss << _connecter->getName() << "_to_" << _connected->getName();
    std::wstring connectionName = ss.str();
    std::wcout << "Inserting to map: < " << connectionName << " >" << std::endl;
    connectionsMap[connectionName] = connect2Units(_connected, _connected);
    std::cout << "after insertion: " << connectionsMap.size() << std::endl;
}

const std::map< std::wstring, ThicknessLine* >* UnitManip::getConnectionsMap()
{
    return &connectionsMap;
}