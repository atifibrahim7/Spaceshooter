#pragma once 
#include <SFML/Graphics.hpp>
#include<string.h>
#include<iostream>
#include "bullet.h"
#include "bomb.h"
using namespace sf;



class Enemy
{
private:
    bool active;
    std::string type;
protected:
    int x, y;
    int health;
    bool movement = false;
    bool trigger;
public:
    Texture Tex;
    Sprite sprite;
    Bomb* bomb;
    Sprite beam;
    Texture b, b1, b2, b3;

    Enemy()
    {
        bomb = new Bomb();
        type = " ";
        if (randomDrop() % 2 == 1)
        {
            bomb->setActive(true);
            //  bomb->sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y);
          //  std::cout << "Bomb created" << std::endl;
        }
        else
        {
            bomb->setActive(false);
        }
        active = true;
        health = 100;



    }
    std::string gettype()
    {
        return type;
    }
    void setType(std::string s)
    {
        type = s;
    }
    void setTrigger(bool s) { trigger = s; }
    bool getTrigger() { return trigger; }
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
    ~Enemy() { delete[] bomb; }
    virtual  void moving(RenderWindow& window) = 0;
    virtual  void draw(RenderWindow& window) {};
    virtual void beamformonster(RenderWindow& window) {}
   


};

