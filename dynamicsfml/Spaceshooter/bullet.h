#pragma once 

#include <SFML/Graphics.hpp>

#include<string.h>
using namespace sf;

class Bullet
{   
    int bullet_damage;
public:
    Sprite sprite;
    Texture Tex;
    int x;
    int y;

    Bullet()
    {
        Tex.loadFromFile("img/PNG/Lasers/laserBlue12.png");
        sprite.setTexture(Tex);
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
        y -= 10;
        sprite.setPosition(x, y);
    }
    void move_down()
    {
        y  += 10; 
        sprite.setPosition(x, y);
    }
    
    ~Bullet(){}

};