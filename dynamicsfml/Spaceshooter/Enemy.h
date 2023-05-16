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

    Enemy();
    std::string gettype();
    void setType(std::string s);
    void setTrigger(bool s);
    bool getTrigger();
    int randomDrop();
    virtual  bool  isActive();
    virtual void setActive(bool s);
    ~Enemy();
    virtual  void moving(RenderWindow& window) = 0;
    virtual  void draw(RenderWindow& window) {};
    virtual void beamformonster(RenderWindow& window) {}
   


};

