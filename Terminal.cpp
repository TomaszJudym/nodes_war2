//
// Created by Ackan on 11.09.2018.
//

#include "Terminal.h"

Terminal::Terminal() :
terminalCharacterSize(16),
position(20, 20),
//terminalFontDir( "font/batmfa__.ttf" )
terminalFontDir( "font/Osaka.ttc" )
{
    if( !terminalFont.loadFromFile( terminalFontDir ) )
    {
        std::cerr << "Error loading font file: " << terminalFontDir <<
                  "\nexiting..." << std::endl;
    }

    text.setFont(terminalFont);
    text.setCharacterSize(terminalCharacterSize);
    text.setFillColor( sf::Color::White );
    text.setPosition( position );
}

void Terminal::draw(sf::RenderTarget& _rw, sf::RenderStates) const
{
    _rw.draw(text);
}

void Terminal::update( const char _input_char )
{
    std::cout << "received: " << _input_char << std::endl;
    if( !(terminalCharacterSize % 30) )
        ss += "\n";
    if( _input_char == '\n' ) {
        std::cout << "encountered newline" << std::endl;
    }
    ss += _input_char;
    ++terminalCharacterSize;
    text.setString( ss );
}

bool Terminal::update( short _how_many_delete = 1 )
{
    if( !ss.empty() )
    {
        --terminalCharacterSize;
        ss.pop_back();
        text.setString( ss );
        return true;
    }
    return false;
}

void Terminal::update( const std::string& _str )
{
    for( const auto& x : _str )
    {
        update( x );
    }
}

void Terminal::loadInitLog( std::string& _logFileDir, sf::RenderWindow& _windowRef )
{
    std::fstream fs( _logFileDir );
    if( !fs.good() )
    {
        std::cerr << "Error loading init log file " << _logFileDir
                  << "\nexiting..." << std::flush;
    }

    char c;
    bool exit = false;

    while( fs.get(c) && !exit )
    {
        // if more than 5 lines, scrolling up
        if( c == '\n' && std::count( ss.begin(), ss.end(), '\n' ) > 5 )
        {
            ss.erase( 0, ss.find('\n')+1 ); // erase elements from first line
            text.setString( ss );           // set updated string without first line to display
            //_windowRef.clear(sf::Color::Black);

            _windowRef.draw(text);
            _windowRef.display();
        }
        ++terminalCharacterSize;
        ss += c;
        text.setString( ss );
        std::this_thread::sleep_for( mili( 30 ) );
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::U ) )
        {
            exit = true;
        }

        //_windowRef.clear(sf::Color::Black);
        _windowRef.draw( text );
        _windowRef.display();
    }

    if( exit )
    {
        std::ostringstream os;
        fs.seekg(0, std::ios_base::beg);
        os << fs.rdbuf();
        ss = os.str();
        ss = getLastNLines(5, ss.end());
        text.setString( ss );

        _windowRef.clear(sf::Color::Black);
        _windowRef.draw( text );
        _windowRef.display();
    }

    fs.close();
}

void Terminal::clear()
{
    text.setString("");
}

std::string Terminal::getLastNLines( unsigned int _nLines, std::string::const_iterator _end )
{
    auto beginningIter = _end;
    while( _nLines != 0 )
    {
        --beginningIter;
        if( *beginningIter == '\n' )
            --_nLines;
    }
    // one char after newline
    ++beginningIter;
    return std::string( beginningIter, _end );
}

std::string Terminal::catchCommand(sf::RenderWindow& _windowRef)
{
    update( (char)'\n' );
    text.setString( ss );
    _windowRef.draw( text );
    _windowRef.display();
    std::string commandToExecute;
    if( ss.size() > 30 )
    {
        std::string::iterator beginIter = ss.begin() + ss.find_last_of( '\n' );
        commandToExecute = std::string( beginIter, ss.end() );
    }
    else
    {
        if( !ss.empty() )
            commandToExecute = ss;
        else
            update( (char)'\n' );
    }
    return commandToExecute;
}