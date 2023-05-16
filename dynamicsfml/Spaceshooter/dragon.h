#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <iostream>

class Dragon : public Enemy
{
        bool movement = false;
    public:

        bool active = false;

        Dragon();
        void moving(RenderWindow& window);
        void beamformonster(RenderWindow& window) override;
        void draw(RenderWindow& window) override;


   
};
