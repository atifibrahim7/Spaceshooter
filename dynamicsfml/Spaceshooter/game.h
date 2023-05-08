#pragma once 
#include "dragon.h"
#include <SFML/Graphics.hpp>
#include <time.h>
#include "player.h"
#include "Enemy.h"
#include "Addon.h"
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
public:

    Sprite background, shield; //Game background sprite
    Texture bg_texture , shield_texture;
    Player* p; //player 
    Addons** Addon_;
    bool isShieldActive = false;
    //Enemy* E; //Enemy object
    // add other game attributes
    // Menu * m; //Menu object


    Game()
    {   
       
        Addon_ = new Addons * [5] {new ShieldAddon() , new LivesAddon() , new DangerAddon()};
     
        shield_texture.loadFromFile("img/PNG/Effects/shield1.png");
        shield.setTexture(shield_texture);
        p = new Player("img/player_ship.png");
        bg_texture.loadFromFile("img/background.jpg");
            // Addones loading sprites 
        
      //  E = new Enemy();
        background.setTexture(bg_texture);
        background.setScale(2.0, 1.75);

    }
    void start_game()
    {
        srand(time(0));
        RenderWindow window(VideoMode(900, 900), title);
        window.setFramerateLimit(60);
        Clock clock, clock1;
        float timer = 0;
        float shieldtimer = 0;
        

        while (window.isOpen())
        {
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;

           
            // clock1.restart();
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                    window.close(); //close the game                        	    
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();

            if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
                p->move("l");    // Player will move to left
            if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
                p->move("r");  //player will move to right
            if (Keyboard::isKeyPressed(Keyboard::Up)) //If up key is pressed
                p->move("u");    //playet will move upwards
            if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
                p->move("d");  //player will move downwards

            ////////////////////////////////////////////////
            ///  Call your functions here            ///

            p->rotate();
            p->wraparound();
            p->fire(time);
            
            if (Addon_[0]->apply(*p))
            {
                isShieldActive = true;
                std::cout << " Collision shield";
            }
            for(int i = 1 ; i < 3 ; i++)
            if (Addon_[i]->apply(*p))
                std::cout << "Addon picked" <<p->lives;
            for (int i = 0; i < 3; i++)
            {
                Addon_[i]->drop();
            }
            
            //E->fire();
            //////////////////////////////////////////////

            window.clear(Color::Black); //clears the screen
            window.draw(background);  // setting background
            window.draw(p->sprite);   // setting player on screen
            if (isShieldActive)
            { 
                shield.setPosition(p->x -20,p->y-30);
                window.draw(shield);
                shieldtimer += time;
              //  std::cout << shieldtimer<<"\n";
                
                if (shieldtimer > 4.0f) {
                    isShieldActive = false;
                    shield.setPosition(-150, -100);
                    shieldtimer = 0;
                }
            }
   
            if (p->b)
                for (int j = 0; j < 50; j++)
                    window.draw(p->b[j]->sprite);
            if (Addon_[0])
            {
              for(int i = 0 ; i < 3 ; i++)
                Addon_[i]->draw(window);
            }
                /* if(timer >2 )
            {
                window.draw(E->sprite);
            }*/
            //window.draw(E->sprite);   // setting enemy on screen

            window.display();  //Displying all the sprites
        }


    }



};

