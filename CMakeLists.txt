cmake_minimum_required(VERSION 3.7)
set(PROJECT_NAME node_wars)

file(GLOB SOURCES
        main.cpp
        mainHeader.h
        Terminal.h
        Terminal.cpp
        LoadRing.h
        LoadRing.cpp
        Tools/ThicknessLine.h
        Tools/ThicknessLine.cpp
        battle_units/Node.h
        battle_units/Node.cpp
        battle_units/User.h
        battle_units/User.cpp
        battle_units/Server.h
        battle_units/Server.cpp
        battle_units/units_utilities/UnitManip.h
        battle_units/units_utilities/UnitManip.cpp
        NodesBattlefield.h
        NodesBattlefield.cpp
        )

project(${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -static")
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Tools/SFML_my/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics)
add_executable(${PROJECT_NAME} ${SOURCES} )
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-system)

set(CMAKE_CXX_STANDARD 17)

