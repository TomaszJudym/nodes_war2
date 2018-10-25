//
// Created by Ackan on 17.09.2018.
//

#include "User.h"

const std::map< int, std::wstring > User::names = []
{
    std::map< int, std::wstring > retMap;
    retMap[WOLF] = L"狼";
    retMap[IDIOT] = L"馬鹿";
    retMap[COUNTERPUNCH] = L"カウンターパンチ";
    retMap[DELTA] = L"デルタ";
    retMap[YELLOW] = L"黄";
    retMap[MATILDA] = L"マチルダ";
    return retMap;
}();

size_t User::userCount = 0;

std::shared_ptr<User> User::spawnUser( const sf::Vector2f& _pos, sf::Texture& _texture )
{
    std::cout << "spawing user: " << _pos.x << " " << _pos.y << std::endl;
    if (userCount <= 5)
        return std::shared_ptr<User>(new User(_pos, _texture));
    else
    {
        // TODO -> will be useful with menu to choose units, now its dangerous
        // TODO with testing purposes
        std::cerr << "cannot create User unit => Users limit reached" << std::endl;
        return nullptr;
    }
}

std::shared_ptr<User> User::spawnUser( float _x, float _y, sf::Texture& _texture )
{
    return User::spawnUser( sf::Vector2f(_x, _y), _texture );
}

User::User( const sf::Vector2f& _pos, sf::Texture& _texture ) :
Node( _pos, _texture ),
connectedServerPtr(nullptr)
{
    setName( names.at(userCount) );
    initText();
    userCount++;

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