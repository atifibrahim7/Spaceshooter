#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
using namespace sf;

class Menu {
public:
    
    Sprite menu, instruction;
    Texture menu_texture, instruction_tex;

    // Add menu attributes here
    Menu();
    void display_menu(bool& flag, Sprite* s);
    void displayHighScores(RenderWindow& window, Event& event, Sprite* s);

};
