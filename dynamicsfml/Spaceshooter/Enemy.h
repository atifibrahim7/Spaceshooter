#pragma once 
#include <SFML/Graphics.hpp>
#include<string.h>
#include<iostream>
#include "bullet.h"
#include "bomb.h"
using namespace sf;



class Enemy
{   
private : 
    bool active; 
protected  :
    int health; 
    bool movement = false;
public :
    Texture Tex;
    Sprite sprite;
    Bomb* bomb;
    Enemy ()
    {
        bomb = new Bomb();
        
        if ( randomDrop() % 2  == 1)
        {  
            bomb->setActive(true);
          //  bomb->sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y);
            std::cout << "Bomb created"<<std::endl;
        }
        else
        { 
            bomb->setActive(false);
        }
        active = true;
        health = 100;

        
        
    }
  
    
  int randomDrop() {
        // create an mt19937 generator with a random seed
        std::mt19937 rng(std::random_device{}());

        // create a uniform integer distribution from 0 to 900
        std::uniform_int_distribution<int> dist(0, 900);

        // generate a random number in the range of 0 to 900
        int random_number = dist(rng);

        return random_number;
    }
  virtual  bool  isActive() 
    {
       return  active;
    }
   virtual void setActive(bool s)
    {
        active = s;
    }
        ~Enemy(){}
      virtual  void moving()
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

};

