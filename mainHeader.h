//
// Created by Ackan on 11.07.2018.
//

#ifndef ABSEIL_MAINHEADER_H
#define ABSEIL_MAINHEADER_H

#include <iostream>
#include <iterator>
#include <string>
#include <memory>
#include <random>
#include <algorithm>
#include <vector>
#include <map>
#include "abseiltToTW.h"
#include "chili_STD_gems.h"



long hex2int( const std::string& hexStr ){
    if( hexStr.length() > 2 ){
        if( hexStr[0] == '0' && hexStr[1] == 'x' ){
            return strtol( hexStr.c_str(), nullptr, 0 );
        }
    }
    return strtol( hexStr.c_str(), nullptr, 16 );
}

void stringToNumeric()
{
    std::string str1 = "0x12AB";
    std::cout << hex2int( str1 ) << std::endl;
    std::string str2 = "12AB";
    std::cout << hex2int( str2 ) << std::endl;
    std::string str3 = "QAFG";
    std::cout << hex2int( str3 ) << std::endl;
}

#endif //ABSEIL_MAINHEADER_H
