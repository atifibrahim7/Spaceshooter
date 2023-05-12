#pragma once 
#include "monster.h"
#include <SFML/Graphics.hpp>
#include <time.h>
#include "player.h"
#include "Enemy.h"
#include "Addon.h"
#include "invader.h"
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
public:

    Sprite background, shield; //Game background sprite
    Texture bg_texture, shield_texture;
    Player* p; //player 
    Addons** Addon_;
    bool cflag = false;
    int enemy_killed = 0;
    bool isMonsteractive = 0;
    bool monsterkilled = 0;
    // add other game attributes
    Enemy** enemy; //Enemy object

    bool isShieldActive = false;
    bool isBombActive = false;


    Game()
    {

        enemy = new  Enemy * [4];
        enemy[0] = new Alpha[5];
        enemy[1] = new Beta[5];
        enemy[2] = new Gamma[5];
        enemy[3] = new Monster();

        Addon_ = new Addons * [4] {new ShieldAddon(), new LivesAddon(), new DangerAddon(), new FireAddon()};
        shield_texture.loadFromFile("img/PNG/Effects/shield1.png");
        shield.setTexture(shield_texture);
        p = new Player("img/player_ship.png");
        bg_texture.loadFromFile("img/bg.jpg");
        // Addones loading sprites 

        background.setTexture(bg_texture);
        background.setScale(1.0, 1.0);
        background.setPosition(0, 00);

    }

    void timeclock(Enemy ** & enemy , float & mtimer , RenderWindow & window , float &time )
    {
        if (enemy_killed == 0)
        {
            setDiamod(enemy);


        }
        else if (enemy_killed == 15)
        {
            setRectangle(enemy);
        }
        else if (enemy_killed == 29 && !monsterkilled && mtimer == 0)
        {
            enemy[3]->sprite.setPosition(400, 100);
            window.draw(enemy[3]->sprite);
            mtimer += time;
            enemy[3]->setActive(1);
          //  std::cout << enemy[3]->sprite.getPosition().x << " " << enemy[3]->sprite.getPosition().y << "\n";
        }
        else if (enemy_killed == 29 && monsterkilled )
            setCross(enemy);
        else if (enemy_killed == 43)
            setHeart(enemy);
        else if (enemy_killed == (43 + 14))
            setTriangle(enemy);
        else if (enemy_killed == 72)
            setCircle(enemy);
        //else if (enemy_killed == )

    }
    void start_game()
    {
        srand(time(0));
        RenderWindow window(VideoMode(900, 900), title);
        window.setFramerateLimit(60);
        Clock clock, clock1;
        float timer = 0;
        float shieldtimer = 0;
        float firetimer = shieldtimer;
        bool fireaddonflag = false;
        float btimer = 0;
        float mtimer = 0;
        float pausetimer = 0;
            while (window.isOpen())
        {
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;
            btimer += time;
            
            timeclock(enemy, mtimer, window, time);
        
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

            int r1 = Addon_[1]->randomDrop() % 3;
            int r2 = Addon_[1]->randomDrop() % 5;
            

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    checkCollision(p, enemy[i][j].bomb);
                }

            }
          if( checkCollision(p, enemy))
            {}

            p->rotate();
            p->wraparound();
            p->fire(time);
            if (btimer > 10)
            {
                btimer = 0;
               std:: cout << btimer;
            }
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    
                    if (enemy[i][j].bomb->isActive())
                    {
                        if (btimer > 4 && btimer < 4.1 )
                        {
                           
                           
                                enemy[i][j].bomb->sprite.setPosition(enemy[i][j].sprite.getPosition().x, enemy[i][j].sprite.getPosition().y);
                                std::cout << i << j << " " << enemy[i][j].bomb->sprite.getPosition().x << " " << enemy[i][j].bomb->sprite.getPosition().y << "\n";
                               
                           
                        }
                    }
                }
            }

            
            if (Addon_[0]->apply(*p))
            {
                isShieldActive = true;
                //  std::cout << " Collision shield";
            }
            if (fireaddonflag)
            {
                firetimer += time;
            }
            for (int i = 1; i < 4; i++)
            {

                if (Addon_[3]->apply(*p))
                {
                    //  std::cout << "timer start ";
                    fireaddonflag = true;

                    for (int i = 0; i < 50; i++)
                    {

                        p->b[i]->sprite.setScale(1.5, 1.5);

                    }


                }
                else if (Addon_[i]->apply(*p))
                    std::cout << "Addon picked" << p->lives;
            }




            // std::cout << "ENemy at :" << enemy[0][0].sprite.getPosition().x << " " << enemy[0][0].sprite.getPosition().y<<"\n";
          //   std::cout << firetimer << "\n";
            if (firetimer > 5.0f)
            {
                std::cout << "in if statement";
                firetimer = 0;
                fireaddonflag = false;
                for (int i = 0; i < 50; i++)
                {
                    p->b[i]->Tex.loadFromFile("img/PNG/Lasers/laser.png");
                    p->b[i]->sprite.setTexture(p->b[i]->Tex);
                    p->b[i]->sprite.setRotation(90);
                    p->b[i]->sprite.setScale(1, 1);

                }
                //   firetimer = 0;
            }
            for (int i = 0; i < 4; i++)
            {
                Addon_[i]->drop();
            }

            //E->fire();
            //////////////////////////////////////////////

            window.clear(Color::Black); //clears the screen
            window.draw(background);  // setting background
           // window.draw(enemy[0][0].sprite);
            //
           /* enemy->draw(window);
            enemy->moving();*/
            //
            window.draw(p->sprite);   // setting player on screen

            if (isShieldActive)
            {
                shield.setPosition(p->x - 20, p->y - 30);
                window.draw(shield);
                shieldtimer += time;
                //  std::cout << shieldtimer<<"\n";

                if (shieldtimer > 4.0f) {
                    isShieldActive = false;
                    shield.setPosition(-150, -100);
                    shieldtimer = 0;
                }
            }

            for (int i = 0; i < 50; i++)
            {
                if (checkCollision(p->b[i], enemy))
                {
                    std::cout << "Enemy killed";
                    std::cout<<enemy_killed<<"\n";
                    p->b[i]->x = -100;
                    p->b[i]->y = -100;
                    p->b[i]->sprite.setPosition(p->b[i]->x, p->b[i]->y);
                }
            }

            if (p->b)
                for (int j = 0; j < 50; j++)
                    window.draw(p->b[j]->sprite);
            if (Addon_[0])
            {
                for (int i = 0; i < 4; i++)
                    Addon_[i]->draw(window);
            }


            /// Monster ; - -----------------                   
            if (enemy[3]->isActive())
            {
                std::cout << mtimer<<"\n";
                mtimer += time;
                enemy[3]->moving();
                window.draw(enemy[3]->sprite);
                //  std::cout << enemy[3]->sprite.getPosition().x << " " << enemy[3]->sprite.getPosition().y << "\n";
                if (mtimer > 5) {
                    monsterkilled = true;
                    enemy[3]->setActive(0);
                    mtimer = 0;
                    enemy[3]->sprite.setPosition(-900, 300);
                }
            }
            window.draw(enemy[3]->sprite);

          //  ------------------------------------------
            for (int i = 0; i < 5; i++) {
                window.draw(enemy[0][i].sprite);
            }


            for (int i = 0; i < 5; i++) {
                window.draw(enemy[1][i].sprite);
            }

            for (int i = 0; i < 5; i++) {
                window.draw(enemy[2][i].sprite);
            }
            if (enemy_killed >= 0)
            {
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        if (enemy[i][j].bomb->isActive())
                        {
                            enemy[i][j].bomb->sprite.move(0, 2);
                            window.draw(enemy[i][j].bomb->sprite);


                        }

                    }
                }
            }

            window.display();  //Displying all the sprites
        }


    }

    virtual void setRectangle(Enemy**& en) {

        for (int i = 0; i < 5; i++) {
            en[0][i].sprite.setPosition(i * 153.0 + 100, 0);

        }

        for (int i = 0; i < 5; i++) {
            en[1][i].sprite.setPosition(i * 153.0 + 100, 250);
        }

        en[2][0].sprite.setPosition(100.0, 90);

        en[2][1].sprite.setPosition(712.0, 90.0);

        en[2][2].sprite.setPosition(100.f, 180.0);

        en[2][3].sprite.setPosition(712, 180);
        en[2][4].sprite.setPosition(-100, -100);

    }
    virtual void setCross(Enemy**& en) {
        for (int i = 0; i < 5; i++)
            en[0][i].sprite.setPosition(200 + i * 50, i * 50.0);
        en[2][0].sprite.setPosition(450, 250);
        en[2][1].sprite.setPosition(500, 300);

        for (int i = 0; i < 5; i++)
            if (i != 3)
                en[1][i].sprite.setPosition(500 - i * 50, i * 50);
        en[1][3].sprite.setPosition(350, 250);
        en[2][2].sprite.setPosition(250, 250);
        en[2][3].sprite.setPosition(200, 300);


    }

    virtual void setTriangle(Enemy**& en) {
        for (int i = 0; i < 5; i++)
            en[0][i].sprite.setPosition(360 + i * 50, i * 50);
        for (int i = 0; i < 5; i++)
            en[1][i].sprite.setPosition(280 - i * 50, i * 50);
        for (int i = 0; i < 5; i++) {
            en[2][i].sprite.setPosition(95 + 150 * i, 290);
        }
    }

    //--------------------------------//

    virtual void setCircle(Enemy**& en) {
        float a = (2.0 * 3.14159) / 14;
        float angle = 0, x, y;
        for (int i = 0, j = 0, k = 0; i < 15; i++, k++)
        {
            angle = a * i;
            x = std::cos(angle) * 170 + 360;
            y = std::sin(angle) * 170 + 200;
            en[j][k].sprite.setPosition(x, y);
            if (i == 4 || i == 9) {
                j++;
                k = -1;
            }

        }
    }

    virtual void setHeart(Enemy**& en) {

        en[1][0].sprite.setPosition(210, 50);
        en[1][1].sprite.setPosition(340, 100);
        en[1][2].sprite.setPosition(470, 50);
        en[1][3].sprite.setPosition(160, 100);
        en[1][4].sprite.setPosition(520, 100);


        en[0][0].sprite.setPosition(270, 90);
        en[0][1].sprite.setPosition(400, 90);
        en[0][2].sprite.setPosition(190, 160);
        en[0][3].sprite.setPosition(230, 230);
        en[0][4].sprite.setPosition(280, 290);

        en[2][0].sprite.setPosition(340, 330);
        en[2][1].sprite.setPosition(400, 290);
        en[2][2].sprite.setPosition(450, 230);
        en[2][3].sprite.setPosition(490, 160);
        en[2][4].sprite.setPosition(-100, -100);
    }

    virtual void setDiamod(Enemy**& en) {
        for (int i = 0; i < 4; i++)
            en[0][i].sprite.setPosition(400 + i * 70, i * 70);
        for (int i = 0; i < 4; i++)
            en[1][i].sprite.setPosition(350 - i * 70, i * 50);
       en[2][2].sprite.setPosition(500, 320);
        en[2][3].sprite.setPosition(560, 270);

    en[2][0].sprite.setPosition(160, 250);
       en[2][1].sprite.setPosition(210, 310);
        en[0][4].sprite.setPosition(430, 380);
       en[2][4].sprite.setPosition(260, 380);
        en[1][4].sprite.setPosition(350, 410);
    /*  
        */
    }


   bool checkCollision(Bullet* b, Enemy**& en)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (b->sprite.getGlobalBounds().intersects(en[i][j].sprite.getGlobalBounds()))
                {
                    en[i][j].sprite.setPosition(-100, -100);
                    b->sprite.setPosition(p->x, p->y);
                    enemy_killed++;
                    return true;
                }
          
            }
        }
        return false;
        
    }
   void checkCollision(Player* p , Bomb* b)
   {
       for (int i = 0; i < 3; i++)
       {    
           for (int j = 0; j < 5; j++)
           {
               if (b->sprite.getGlobalBounds().intersects(p->sprite.getGlobalBounds()))
               {
                   p->lives--;
                   p->sprite.setPosition(400, 800);
                   b->sprite.setPosition(-100, 900);
                   
               }
           }
       }
   }
   
   bool checkCollision(Player* p, Enemy**& en)
   {
       for (int i = 0; i < 3; i++)
       {
           for (int j  = 0; j < 5; j++)
           {
               if (p->sprite.getGlobalBounds().intersects(en[i][j].sprite.getGlobalBounds()))
               {
                   p->lives--;
                   p->sprite.setPosition(400, 800);
                   return true;
               }
           }
       }
       return false;
   }
};

