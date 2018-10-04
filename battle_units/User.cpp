//
// Created by Ackan on 17.09.2018.
//

#include "User.h"

const std::map< int, std::wstring > User::names = []
{
    std::map< int, std::wstring > retMap;
    retMap[WOLF] = L"狼";
    retMap[IDIOT] = L"馬鹿";
    retMap[COUNTERPUNCH] = L"馬鹿";
    retMap[DELTA] = L"デルタ";
    retMap[YELLOW] = L"黄";
    retMap[MATILDA] = L"マチルダ";
    return retMap;
}();

size_t User::userCount = 0;

std::shared_ptr<User> User::spawnUser( sf::Vector2f& _pos, sf::RenderWindow& _rw  )
{
    std::cout << "spawing user: " << _pos.x << " " << _pos.y << std::endl;
    if (userCount <= 3)
        return std::shared_ptr<User>(new User(_pos, _rw));
    else
    {
        std::cerr << "cannot create User unit => Users limit reached" << std::endl;
        return nullptr;
    }
}

User::User( sf::Vector2f& _pos, sf::RenderWindow& _rw ) :
Node( _pos, _rw ),
connectedServerPtr(nullptr)
{
    image.loadFromFile( "img/camputer480x480.jpg" );
    initSprite();
    setName( names.at(userCount) );
    initText();
    ++userCount;
}

void User::makeConnection( Node* _target )
{
    if( connectedServerPtr != nullptr )
    {
        connectedServerPtr = reinterpret_cast<Server*>(_target);
    }
    else
    {
        std::wcerr << "ERROR server already assigned to " << name << std::endl;
    }
}

User::~User()
{
    connectedServerPtr = nullptr;
}