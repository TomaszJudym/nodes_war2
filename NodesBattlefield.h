//
// Created by ezjakko on 16.10.2018.
//

#ifndef NODE_WARS_NODESBATTLEFIELD_H
#define NODE_WARS_NODESBATTLEFIELD_H

#include <memory>
#include <vector>
#include <algorithm>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

#include "Terminal.h"
#include "battle_units/Server.h"
#include "battle_units/User.h"
#include "battle_units/units_utilities/UnitManip.h"

class NodesBattlefield
{
    bool                                      initLoad();

    void                                      processEvents();
    void                                      update();
    void                                      render();

    void                                      handlePlayerInputMouse( sf::Mouse::Button _button, bool _pressed );
    void                                      handlePlayerInputKeyboard( sf::Keyboard::Key _key, bool pressed );
    void                                      handlePlayerMouseMove();
    void                                      handleTerminal(sf::Uint32 _keyCode);

    void                                      handleUnitsAction(Node* _unit, bool _pressed);
    void                                      handleUnitsMove(Node* _unit, bool _pressed);
    inline void                               backToChoosingState();

    Node*                                     containsUnit(const sf::Vector2f& _pos);

    const sf::Vector2f                        getMousePos();

    std::vector<Server> servers;
    std::vector< std::shared_ptr<User> >      users;

    UnitManip&                                unitManipulator;

    std::unique_ptr<Terminal>                 terminal;

    sf::RenderWindow                          window;

    NodesBattlefield(); // we can have only 1 instance of battlefield
public:
    static NodesBattlefield&                   getInstance();

    void                                       run();

    NodesBattlefield(NodesBattlefield const&)  = delete;    // more explicit than declaring
    void operator=(NodesBattlefield const&)    = delete;    // them private - better compiler errors
                                                         // in attempt to copy object
private:
    enum MANIPULATION_STATE : short
    {
        none = 0
      , choosing
      , moving
    } manip_state;
};



#endif //NODE_WARS_NODESBATTLEFIELD_H
