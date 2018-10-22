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
};

struct UnitManip
{
private:
    std::map< ConnectionData*, ThicknessLine* > connectionsMap;

public:
    static ThicknessLine* connect2Units( Node* _connecter, Node* _connected, sf::Color _color = sf::Color(118, 56, 100) );
    MemorisUnit*          memorisUnit;

    void                  addConnection(Node* _connecter, Node* _connected);
    const                 std::map< ConnectionData*, ThicknessLine* >* getConnectionsMap();
    void                  updateTransitions(Node* _changedNode);


    static UnitManip&     getInstance();
    UnitManip&            operator=(const UnitManip&) = delete;
    UnitManip(const UnitManip&) = delete;
private:
    UnitManip();

    enum connNodeType : unsigned char { NONE=0, CONNECTER, CONNECTED };
};

// definition inside header file because of ODR


#endif //NODE_WARS_UNITMANIP_H
