#pragma once 

#include <SFML/Graphics.hpp>
#include"Enemy.h"
#include<string.h>
using namespace sf;

class Bullet
{   
protected:
    int bullet_damage;
public:
    Sprite sprite;
    Texture Tex;
    int x;
    int y;
    bool active;
    friend class Enemy;
    Bullet()
    {   
        active = true;
        Tex.loadFromFile("img/PNG/Lasers/laser.png");
        sprite.setTexture(Tex);
      sprite.setRotation(90); 
        sprite.setScale(1, 1);
        x = 0;
        y = 0;
        bullet_damage = 100;
    }
    int getBulletdamage()
    {
        return bullet_damage;
    }
    void move()
    {
        y -= 7;
        sprite.setPosition(x, y);
    }
    void move_down()
    {
        y  += 10; 
        sprite.setPosition(x, y);
    }
    
    ~Bullet(){}
    bool isActive()
    {
        return active;
    }

  
};

