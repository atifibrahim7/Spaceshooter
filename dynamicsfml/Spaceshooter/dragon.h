#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <iostream>

class Dragon : public Enemy
{
        bool movement = false;
    public:

        bool active = false;

        Dragon()
        {
            setType( "dragon");
           
            setActive(0);
            Tex.loadFromFile("img/dragon.png");
            sprite.setTexture(Tex);
            b.loadFromFile("img/fire.png");
            beam.setTexture(b);
            sprite.setPosition(500, 150);
            beam.setPosition(-300, 500);
            beam.setRotation(0);
            beam.setScale(1, 2);
            sprite.setScale(0.5, 0.5);
            std::cout << "Dragon created at " << sprite.getPosition().x << " " << sprite.getPosition().y;


        }
        void moving(RenderWindow& window)
        {
            float y = sprite.getPosition().y;
            float x = sprite.getPosition().x;

            if (isActive())
            {
                if (y < 500 && x == 500)
                {
                    // Move down until y=700
                    sprite.move(0, 1);
                }
                else if (y >= 500 && x > 100)
                {
                    // Move left until x=100
                    sprite.move(-1, 0);
                }
                else if (x <= 100 && y > 100)
                {
                    // Move up until y=100
                    sprite.move(0, -1);
                }
                else if (y <= 100 && x < 500)
                {
                    // Move right until x=500
                    sprite.move(1, 0);
                }
            }
        }
        void beamformonster(RenderWindow & window) override
        {
            if (getTrigger())
            {       
                sprite.setPosition(300, 100);
                std::cout << "AAAAAAAAAAAAAAAAAAAAAA";
               
                beam.setPosition(sprite.getPosition().x-75, sprite.getPosition().y+ 150);
                draw(window);

            
                
            }
        }
       
        void draw(RenderWindow& window) override
        {
            window.draw(beam);
            window.draw(sprite);
        }


   
};
