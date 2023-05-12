#pragma once

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <iostream>
class Monster : public Enemy
{   
    bool movement = false;
public:
    
    bool active = false;

    Monster()
    {   
        setActive(0);
        Tex.loadFromFile("img/monster.png");
        sprite.setTexture(Tex);
        sprite.setPosition(-100,1150);
        sprite.setScale(0.25, 0.25);
        std::cout << "Monster created at " << sprite.getPosition().x << " " << sprite.getPosition().y;


    }
    void moving()
    {
        // Check if sprite has reached the left or right edge of the screen
        if (sprite.getPosition().x < 0 || sprite.getPosition().x > 830)
        {
            // Reverse direction of movement
            movement = !movement;
        }

        // Move sprite in the appropriate direction
        if (movement)
        {
            sprite.move(4, 0);
        }
        else
        {
            sprite.move(-4, 0);
        }
    }
   

    void draw(RenderWindow& window)
    {
        window.draw(sprite);
    }


};