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


struct UnitManip
{
private:
    std::map< std::wstring, ThicknessLine* > connectionsMap;
public:

    static ThicknessLine* connect2Units( Node* _connecter, Node* _connected, sf::Color _color = sf::Color(118, 56, 100) );
    void addConnection(Node* _connecter, Node* _connected);
    const std::map< std::wstring, ThicknessLine* >* getConnectionsMap();

    ThicknessLine* currentlyCreatedLine;
    Node*          unitToMakeConnectionFrom;

    static UnitManip& getInstance();

    UnitManip& operator=(const UnitManip&) = delete;
    UnitManip(const UnitManip&) = delete;
private:
    UnitManip();

    enum {
        none,
        unitChosen
      , alreadyChoosing
    };
};



#endif //NODE_WARS_UNITMANIP_H
