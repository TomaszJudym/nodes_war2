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

std::shared_ptr<User> User::spawnUser( const sf::Vector2f& _pos )
{
    std::cout << "spawing user: " << _pos.x << " " << _pos.y << std::endl;
    if (userCount <= 3)
        return std::shared_ptr<User>(new User(_pos));
    else
    {
        std::cerr << "cannot create User unit => Users limit reached" << std::endl;
        return nullptr;
    }
}

std::shared_ptr<User> User::spawnUser( float _x, float _y )
{
    return User::spawnUser( sf::Vector2f(_x, _y) );
}

User::User( const sf::Vector2f& _pos ) :
Node( _pos ),
connectedServerPtr(nullptr)
{
    image.loadFromFile( "img/computer630x630.jpg" );
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