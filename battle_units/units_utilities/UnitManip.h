//
// Created by ezjakko on 15.10.2018.
//

#ifndef NODE_WARS_UNITMANIP_H
#define NODE_WARS_UNITMANIP_H


#include <cmath>
#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "../Node.h"
#include "../../Tools/ThicknessLine.h"

struct ConnectionData
{
    static unsigned connectionCounter;

    ConnectionData(Node* _from, Node* to, const std::wstring& _connName);
    unsigned connectionId;
    Node* connecter;
    Node* connected;

    std::wstring connectionName;

    inline bool operator< (const ConnectionData& _cmp);

    ~ConnectionData();
};

struct MemorisUnit
{
    MemorisUnit();
    // we need to remember if unit was moved in previous state in case of
    // click - release LMB without moving it
    bool           unitWasMoved;
    Node*          unitToManip;
    ThicknessLine* currentlyCreatedLine;
    // to avoid first-frame-move when unit is "jumping" to center with cursor
    // in first frame of moving it
    sf::Vector2f   movingUnitOffset;
};

struct UnitManip
{
private:
    std::map< ConnectionData*, ThicknessLine* > connectionsMap;
    static bool                  mouseIsInScreenBorders(const sf::RenderWindow& _window);
    static sf::Vector2f          coordinatePositionToWindow(const sf::Vector2f& _pos, const sf::RenderWindow& _window);
public:
    static ThicknessLine*        connect2Units( Node* _connecter, Node* _connected, sf::Color _color = sf::Color(118, 56, 100) );
    static sf::Vector2f          getDirVec(const sf::Vector2f&, const sf::Vector2f&);
    sf::Vector2f                 selectNewUnitPosition(const sf::RenderWindow& _window);
    std::unique_ptr<MemorisUnit> memorisUnit;

    void                        addConnection(Node* _connecter, Node* _connected);
    const                       std::map< ConnectionData*, ThicknessLine* >* getConnectionsMap();
    void                        updateTransitions(Node* _changedNode);

    static UnitManip&           getInstance();
    UnitManip&                  operator=(const UnitManip&) = delete;
    UnitManip(const UnitManip&) = delete;
private:
    UnitManip();

    enum connNodeType : unsigned char { NONE=0, CONNECTER, CONNECTED };
};

// definition inside header file because of ODR


#endif //NODE_WARS_UNITMANIP_H
