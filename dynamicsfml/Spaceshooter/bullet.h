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
    bool active;
    int angle;
    int zz = 0;
    int x;
    int y;
    Bullet()
    {   
        active = true;
        angle = 90;
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
   /* void move()
    {
        y -= 15;
        sprite.setPosition(x, y);
    }*/
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

    void move() {
        // use the stored angle instead of the current angle
        float radians = angle * 3.14159265 / 180;
        x += std::cos(radians) * 10;
        y -= std::sin(radians) * 10;
        sprite.setPosition(x, y);
    }

    // overload the move function to take an angle argument
    void move(float newAngle) {
        angle = newAngle;
        move();
    }
    int getx()
    {
        return x;
    }
    int gety()
    {
        return y;
    }

};

