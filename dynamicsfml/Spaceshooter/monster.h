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
        b.loadFromFile("img/PNG/Lasers/laserblue12.png");
        beam.setTexture(b);
        setActive(0);
        Tex.loadFromFile("img/monster.png");
        sprite.setTexture(Tex);
        sprite.setPosition(-100,1150);
        beam.setPosition(-300, 500);
        beam.setRotation(0);
        beam.setScale(1, 15);
        sprite.setScale(0.25, 0.25);
      //  std::cout << "Monster created at " << sprite.getPosition().x << " " << sprite.getPosition().y;


    }
    void moving(RenderWindow & window) override
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
            beam.setPosition(sprite.getPosition().x + 150, sprite.getPosition().y);
           // window.draw(beam);
           // std::cout << beam.getPosition().x + 100 << " " << beam.getPosition().y;
           
        }
        else
        {
            sprite.move(-4, 0);
           // 
         beam.setPosition(sprite.getPosition().x+150, sprite.getPosition().y);
          /*
          window.draw(beam);
            */
          //  std::cout << beam.getPosition().x +50<< " " << beam.getPosition().y;
            draw(window);


            
        }
    }
   
    
    void draw(RenderWindow& window) override
    {
        window.draw(beam);
        window.draw(sprite);
    }


};