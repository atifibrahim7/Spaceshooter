#pragma once 
#include <SFML/Graphics.hpp>
#include<string.h>
#include "bullet.h"

using namespace sf;

class Enemy
{
    int enemy_health;
public:
    Texture tex;
    Sprite sprite;
    int x, y;
    float  speed = 5;
    Bullet* eBullet[10];


    Enemy()
    {
        for (int i = 0; i < 10; i++)
            eBullet[i] = new Bullet();
        enemy_health = 100;
        tex.loadFromFile("img/enemy_3.png");

        sprite.setTexture(tex);
        x = 300; y = 300;
        sprite.setPosition(sf::Vector2f(x, y));
        sprite.setScale(0.5, 0.5);
    }
    int getEnemyHealth()
    {
        return enemy_health;
    }
    virtual void fire() = 0;

    
   
};