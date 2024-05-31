//to run ./sfmlgametest
//to compile g++ main.cpp -I /opt/homebrew/Cellar/sfml/2.6.1/include -o sfmlgametest -std=c++17 -L /opt/homebrew/Cellar/sfml/2.6.1/lib  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
#include <SFML/Graphics.hpp>
#include <string.h>
#include "Game.h"
#include <iostream>
// #include "Vec2.h"
// #include "Vec2.cpp"
//for testing

int main(){

    Vec2 v1(1,2);
    Vec2 v2(5,7);

    Vec2 v3 = v1 + v2;

    std::cout << v3.x <<" "<<v3.y;
    
    Game g("config.txt");
    g.run();
   
    return 0;
    

}