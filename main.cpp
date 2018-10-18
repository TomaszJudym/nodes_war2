
#include <thread>
#include <chrono>
#include <fstream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Thread.hpp>


#include <string>
#include <fstream>
#include <streambuf>
#include <conio.h>
#include <iostream>
#include <thread>

#include "battle_units/Server.h"
#include "battle_units/User.h"
#include "Terminal.h"
#include "LoadRing.h"
#include "Tools/ThicknessLine.h"
#include "battle_units/units_utilities/UnitManip.h"
#include "mainHeader.h"
#include "NodesBattlefield.h"

using std::cout;
using std::endl;
using std::thread;

using milisec = std::chrono::milliseconds;

void initialize_log( std::string& );

int main()
{
    NodesBattlefield& battlefield = NodesBattlefield::getInstance();
    battlefield.run();

    return 0;
}