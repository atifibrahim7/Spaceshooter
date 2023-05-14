#pragma once 
#include "monster.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "player.h"
#include "Enemy.h"
#include "Addon.h"
#include "dragon.h"
#include "invader.h"
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
public:

    Sprite background, shield , life ; //Game background sprite
    Sprite spaceship;
    
    Texture bg_texture, shield_texture  , stex , l_tex;

    int score;
    Player* p; //player 
    Addons** Addon_;
    bool cflag = false;
    int enemy_killed = 0;
    int wave = 1;
    bool isMonsteractive = 0;
    bool monsterkilled = 0;
    // add other game attributes
    Enemy** enemy; //Enemy object

    bool isShieldActive = false;
    bool isBombActive = false;


    Game()
    {
        stex.loadFromFile("img/PNG/UI/playerLife1_blue.png");
        spaceship.setTexture(stex);
        //spaceship.setScale(.5, .5);
        l_tex.loadFromFile("img/life.png");
        life.setTexture(l_tex);
        life.setScale(0.07, 0.07);
        enemy = new  Enemy * [5];
        enemy[0] = new Alpha[5];
        enemy[1] = new Beta[5];
        enemy[2] = new Gamma[5];
        enemy[3] = new Monster();
        enemy[4] = new Dragon();

        Addon_ = new Addons * [4] {new ShieldAddon(), new LivesAddon(), new DangerAddon(), new FireAddon()};
        shield_texture.loadFromFile("img/PNG/Effects/shield1.png");
        shield.setTexture(shield_texture);
        p = new Player("img/player_ship.png");
        bg_texture.loadFromFile("img/background_1.png");
        // Addones loading sprites 

        background.setTexture(bg_texture);
        background.setScale(1.3, 0.8);
        //background.setPosition(0, 00);

    }

   
    
    void start_game()
    {
        srand(time(0));
        RenderWindow window(VideoMode(900, 950), title);
        window.setFramerateLimit(60);
        Clock clock, clock1;
        int level = 1;
        float timer = 0;
        float shieldtimer = 0;
        float firetimer = shieldtimer;
        bool fireaddonflag = false;
        float btimer = 0;
        float mtimer = 0;
        float dtimer = 0;
        float pausetimer = 0;
        bool animation = 0; 
        Music gameplay;
        if (!gameplay.openFromFile("img/laser.wav"))
            system("pause"); // error
       
        Music gameplay_music;
        if (!gameplay_music.openFromFile("img/joji.wav"))
            system("pause"); // error
        gameplay_music.setVolume(70); // set the volume to 50%
        gameplay_music.setLoop(true);
        gameplay_music.play();

        Music shot_music;
        if (!shot_music.openFromFile("img/laser.wav"))
            ;
       

        Font FONTS;
        FONTS.loadFromFile("img/ss.otf");
      

        // Bonus
       
            while (window.isOpen())
        {   
                p->sprite; 
               
            float time = clock.getElapsedTime().asSeconds();
            

            clock.restart();
            timer += time;
            btimer += time;
        //
           
        // 
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
            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
               
                gameplay.setVolume(70); // set the volume to 50%
               // gameplay.setLoop(true);
                gameplay.play();

            }

            if (Keyboard::isKeyPressed(Keyboard::D))
                enemy[4]->setActive(1);
            if (Keyboard::isKeyPressed(Keyboard::X))
                enemy[4]->setActive(0);

            
            ////////////////////////////////////////////////
            ///  Call your functions here            ///
               
            
            int r1 = Addon_[1]->randomDrop() % 3;
            int r2 = Addon_[1]->randomDrop() % 5;
            

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    checkCollision(p, enemy[i][j].bomb , window);
                }

            }
          if( checkCollision(p, enemy  , window)) {}

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

                        p->b[i]->sprite.setScale(1.5, 2);

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
                Addon_[i]->drop(score);
            }

           
            //////////////////////////////////////////////

            window.clear(Color::Black); //clears the screen
            window.draw(background);  // setting background
           // window.draw(enemy[0][0].sprite);
            //
           /* enemy->draw(window);
            enemy->moving();*/
            //
            window.draw(p->sprite);   // setting player on screen
            // Adding collision for bomb 
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    if(checkCollision(shield, shield_texture, enemy[i][j].bomb , window))
                        ;

                }

            }


            //
            if (isShieldActive)
            {
                shield.setPosition(p->x - 20, p->y - 30);
                window.draw(shield);
                shieldtimer += time;
                //  std::cout << shieldtimer<<"\n";

                if (shieldtimer > 5.0f) {
                    isShieldActive = false;
                    shield.setPosition(-150, -100);
                    shieldtimer = 0;
                }
            }

            for (int i = 0; i < 50; i++)
            {
                if (checkCollision(p->b[i], enemy, window, fireaddonflag))
                {
                    std::cout << "Enemy killed";
                    std::cout<<enemy_killed<<"\n";
                    if (!fireaddonflag)
                    {
                    p->b[i]->x = -100;
                    p->b[i]->y = -100;
                    p->b[i]->sprite.setPosition(p->b[i]->x, p->b[i]->y);

                   }
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
            checkCollision(p, enemy[3][0], window);         //player collision with monster
             
            if (enemy[3]->isActive())
            {
             //   std::cout << mtimer<<"\n";
                mtimer += time;
                enemy[3][0].moving(window);
                window.draw(enemy[3]->sprite);
                //  std::cout << enemy[3]->sprite.getPosition().x << " " << enemy[3]->sprite.getPosition().y << "\n";
                if (mtimer > 5) {
                    monsterkilled = true;
                    enemy[3]->setActive(0);
                    mtimer = 0;
                    enemy[3]->sprite.setPosition(-3000, 900);
                    enemy[3]->beam.setPosition(-3000, 900);
                }
            }
          //  window.draw(enemy[3]->sprite);
            enemy[3][0].draw(window);
           // window.draw(enemy[3]->)

          //  ------------------------------------------
           
            // Enemy Draw 
            for (int k = 0; k < 3; k++)
            {

                for (int i = 0; i < 5; i++)
                {
                    if(enemy[k][i].isActive())
                    window.draw(enemy[k][i].sprite);
                }
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


            // ------------------------------------------------------------- Dragon ---------------------------------------------// 
            
            if (enemy[4]->isActive())
            {
                window.draw(enemy[4]->sprite);
            }
            if(!enemy[4]->getTrigger())
            enemy[4]->moving(window);
                
            if (enemy[4]->isActive())
            {

                for (int i = 0; i < 25; i++)
                {
                    if (checkCollision(p->b[i], enemy[4]))
                        enemy[4]->setTrigger(1);

                }
            }
            if (enemy[4]->isActive())
            {
                if (enemy[4]->getTrigger())
                {
                    dtimer += time;
                    std:: cout << dtimer << "\n";
                    for (int i = 0; i < 3; i++)
                    {
                        for (int j = 0; j < 5; j++)
                        {
                            enemy[i][j].setActive(0);
                        }
                   }
                }
            }
            if (enemy[4]->getTrigger())
            {
                enemy[4]->sprite.setScale(1, 1);
            }
            else  enemy[4]->sprite.setScale(0.25, 0.25);
            if (dtimer > 5)
            {   

                enemy[4]->setTrigger(0);
                enemy[4]->sprite.setScale(0.5, 0.5);
                enemy[4]->setActive(0);
                dtimer = 0;
                score += 50;
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        enemy[i][j].setActive(1);
                    }
                }
            }
            checkCollision(enemy[4], p, window);

            beamdirection(window);
          //  enemy[4]->beamformonster(window);
            // ------------------------------------------------------------- Dragon ---------------------------------------------// 




            
            //Text text1("Lives : " + std::to_string(p->lives), FONTS, 30);
            //text1.setPosition(750, 870);
            //window.draw(text1);
           
           // window.draw(life); 

            for (int i = 0; i < p->lives; i++)
            {
                
                life.setPosition(740 + i * 50, 870);
                window.draw(life);

            }
            
            Text text3("Score : " + std::to_string(score), FONTS, 30);
            text3.setPosition(500, 870);
            window.draw(text3);

            Text text2("Wave : " + std::to_string(wave), FONTS, 30);
            text2.setPosition(650, 870);
            window.draw(text2);

            for (int i = 0; i < p->lives; i++)
            {
                spaceship.setPosition(50 + i*50, 870);
                window.draw(spaceship);
            }

          // std::cout << score << "\n";
            //if (!animation )
            //{
            //    enemy[0][1].sprite.setPosition(200, 400);
            //    enemy[0][2].sprite.setPosition(800, 400);
            //    while (!animation)
            //    {
            //     
            //        window.clear(Color::Blue);
            //        sf::Time delay = sf::seconds(0.2);
            //        sf::sleep(delay);
            //        
            //        window.draw(background);
            //        window.draw(enemy[0][1].sprite);
            //        
            //        window.draw(enemy[0][2].sprite);
            //        enemy[0][1].sprite.move(2, 0);
            //        enemy[0][2].sprite.move(-2, 0);
            //       if (enemy[0][1].sprite.getGlobalBounds().intersects(enemy[0][2].sprite.getGlobalBounds()))
            //        {
            //            for (int k = 2; k <= 5; k++)
            //            {
            //                // Load the explosion texture
            //                std::string filename = "img/explosion" + std::to_string(k) + ".png";
            //                enemy[0][1].Tex.loadFromFile(filename);
            //                enemy[0][1].sprite.setTexture(enemy[0][1].Tex);
            //                enemy[0][2].Tex.loadFromFile(filename);
            //                enemy[0][2].sprite.setTexture(enemy[0][2].Tex);
            //                window.clear(Color::Black);
            //                window.draw(background);
            //                window.draw(enemy[0][1].sprite);
            //                window.draw(enemy[0][2].sprite);
            //                window.display();
            //                // Add a delay to show each frame of the animation
            //                sf::Time delay = sf::seconds(0.1);
            //                sf::sleep(delay);
            //            }
            //            animation = 1;
            //        }
            //       
            //    }
            //}

           
            timeclock(enemy, mtimer, window, time);

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
            en[0][i].sprite.setPosition(200 + 50 + i * 70, i * 70.0);
        en[2][0].sprite.setPosition(650, 400);
        en[2][1].sprite.setPosition(550 + 40, 340);

        for (int i = 0; i < 5; i++)
            if (i != 3)
            {
                en[1][i].sprite.setPosition(700 - i * 50, i * 50+ 30);
                
        }
        en[1][4].sprite.setPosition(550, 180);

        
        en[1][3].sprite.setPosition(370,280);
    en[2][2].sprite.setPosition(590/2 - 10, 340);
  en[2][3].sprite.setPosition(220, 400);
  en[2][4].sprite.setPosition(460, 300);


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
  // bullets with enemy
    bool checkCollision(Bullet* b, Enemy**& en, RenderWindow& window , bool & fireaddonflag)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (b->sprite.getGlobalBounds().intersects(en[i][j].sprite.getGlobalBounds()))
                {   
                    //en[i][j].Tex.loadFromFile("img/PNG/playerShip2_green.png");
                    if (en[i][j].gettype() == "alpha")
                        score+=10;
                    else if (en[i][j].gettype() == "beta")
                        score += 20;
                    else if  (en[i][j].gettype() == "gamma")
                        score += 30;
                    en[i][j].sprite.setTexture(en[i][j].Tex);
                    // Show the explosion animation
                    for (int k = 2; k <= 5; k++)
                    {
                        // Load the explosion texture
                       std:: string filename = "img/explosion" + std::to_string(k) + ".png";
                        en[i][j].Tex.loadFromFile(filename);
                        en[i][j].sprite.setTexture(en[i][j].Tex);
                        window.draw(en[i][j].sprite);
                        window.display();

                        // Add a delay to show each frame of the animation
                        sf::Time delay = sf::seconds(0.01);
                        sf::sleep(delay);
                    }

                    // Update the enemy sprite and position
                    if (i == 0)
                    {
                        en[i][j].Tex.loadFromFile("img/enemy_1.png");
                    }
                    else if (i == 1)
                    {
                        en[i][j].Tex.loadFromFile("img/enemy_2.png");
                    }
                    else if (i == 2)
                    {
                        en[i][j].Tex.loadFromFile("img/enemy_3.png");
                    }
                    en[i][j].sprite.setTexture(en[i][j].Tex);
                    en[i][j].sprite.setPosition(-300, 2000);
                    enemy[i][j].setActive(0) ; 
                    // Update the bullet position and count the enemy as killed
                    
                    if(!fireaddonflag)
                    b->sprite.setPosition(p->x, p->y);
                    enemy_killed++;

                    return true;
                }
            }
        }
        return false;
    }
    //player ship contact with enemy bomb 
    void checkCollision(Player* p , Bomb* b , RenderWindow &  window)
   {
       for (int i = 0; i < 3; i++)
       {    
           for (int j = 0; j < 5; j++)
           {
               if (b->sprite.getGlobalBounds().intersects(p->sprite.getGlobalBounds()))
               {
                   window.clear(Color::Black);
                   // Show the explosion animation
                   for (int i = 1; i <= 3; i++)
                   {
                       // Load the explosion texture
                       std::string filename = "img/PNG/Damage/playerShip1_damage" + std::to_string(i) + ".png";
                       window.draw(background);
                       p->tex.loadFromFile(filename);
                       p->sprite.setTexture(p->tex);

                       // Update the window to show the animation
                      // window.clear();
                       window.draw(p->sprite);
                       window.display();

                       // Add a delay to show each frame of the animation
                       sf::Time delay = sf::seconds(0.1);
                       sf::sleep(delay);
                   }
                   p->tex.loadFromFile("img/player_ship.png");
                   p->sprite.setTexture(p->tex);
                   p->lives--;
                   p->sprite.setPosition(400, 800);
                   b->sprite.setPosition(-500, 900);
                   
               }
           }
       }
   }
  // player ship in contact with enemy ship
   bool checkCollision(Player* p, Enemy**& en, RenderWindow & window)
   {
       for (int i = 0; i < 3; i++)
       {
           for (int j  = 0; j < 5; j++)
           {
               if (p->sprite.getGlobalBounds().intersects(en[i][j].sprite.getGlobalBounds()))
               {
                   window.clear(Color::Black);
                   // Show the explosion animation
                   for (int i = 1; i <= 3; i++)
                   {
                       // Load the explosion texture
                       std::string filename = "img/PNG/Damage/playerShip1_damage" + std::to_string(i) + ".png";
                       window.draw(background);
                       p->tex.loadFromFile(filename);
                       p->sprite.setTexture(p->tex);

                       // Update the window to show the animation
                      // window.clear();
                       window.draw(p->sprite);
                       window.display();

                       // Add a delay to show each frame of the animation
                       sf::Time delay = sf::seconds(0.1);
                       sf::sleep(delay);
                   }

                   // Reset the player sprite and position
                   p->tex.loadFromFile("img/player_ship.png");
                   p->sprite.setTexture(p->tex);
                   p->sprite.setPosition(400, 800);
                   p->lives--;
                   p->sprite.setPosition(400, 800);
                   return true;
               }
           }
       }
       return false;
   }
  
   // Monster collision ;
   bool checkCollision(Player* p, Enemy& e, RenderWindow& window)
   {
       if (p->sprite.getGlobalBounds().intersects(e.sprite.getGlobalBounds()) || p->sprite.getGlobalBounds().intersects(e.beam.getGlobalBounds()))
       {
           // Show the explosion animation
           for (int i = 1; i <= 3; i++)
           {
               // Load the explosion texture
               std::string filename = "img/PNG/Damage/playerShip1_damage" + std::to_string(i) + ".png";
               p->tex.loadFromFile(filename);
               p->sprite.setTexture(p->tex);

               // Update the window to show the animation
              // window.clear();
               window.draw(p->sprite);
               window.display();

               // Add a delay to show each frame of the animation
               sf::Time delay = sf::seconds(0.1);
               sf::sleep(delay);
           }

           // Reset the player sprite and position
           p->tex.loadFromFile("img/player_ship.png");
           p->sprite.setTexture(p->tex);
           p->sprite.setPosition(400, 800);

           // Reset the enemy sprite position
          e.sprite.setPosition(50, 100);

           // Decrease the player's lives and return true to indicate a collision
           p->lives--;
           return true;
       }
       return false;
   }
   void timeclock(Enemy**& enemy, float& mtimer, RenderWindow& window, float& time)
   {
       int count = 0;
       for (int i = 0; i < 3; i++)
       {
           for (int j = 0; j < 5; j++)
           {
               if (enemy[i][j].isActive() == 0 )
               {
                   count++;
               }
           }
       }

       if (enemy_killed == 0)
       {
           wave = 1;
           setDiamod(enemy);
           for (int i = 0; i < 3; i++)
           {
               for (int j = 0; j < 5; j++)
               {
                   enemy[i][j].setActive(1);
               }
           }


       }
       else if (enemy_killed == 15)
       {
           wave = 2;
           setRectangle(enemy);
           for (int i = 0; i < 3; i++)
           {
               for (int j = 0; j < 5; j++)
               {
                   enemy[i][j].setActive(1);
               }
           }
       }
       else if (enemy_killed == 29 && !monsterkilled && mtimer == 0)
       {    

           enemy[3]->sprite.setPosition(400, 100);
           window.draw(enemy[3]->sprite);
           mtimer += time;
           enemy[3]->setActive(1);
           //  std::cout << enemy[3]->sprite.getPosition().x << " " << enemy[3]->sprite.getPosition().y << "\n";
       }
       else if (enemy_killed == 29 && monsterkilled)
       {    
           if (wave == 2)
           {
               score += 60;
           wave = 3;
           }
           enemy[3]->sprite.setPosition(-22222, -2222);
           for (int i = 0; i < 3; i++)
           {
               for (int j = 0; j < 5; j++)
               {
                   enemy[i][j].setActive(1);
               }
           }
           setCross(enemy);

       }
       else if (enemy_killed == 43)
       {
           wave = 4;
           setHeart(enemy);
           for (int i = 0; i < 3; i++)
           {
               for (int j = 0; j < 5; j++)
               {
                   enemy[i][j].setActive(1);
               }
           }
       }
       else if (enemy_killed == (43 + 14))
       {
           setTriangle(enemy);

           wave = 5;
           for (int i = 0; i < 3; i++)
           {
               for (int j = 0; j < 5; j++)
               {
                   enemy[i][j].setActive(1);
               }
           }
       }
       else if (enemy_killed == 72)
       {
           wave = 6;
           setCircle(enemy);
           for (int i = 0; i < 3; i++)
           {
               for (int j = 0; j < 5; j++)
               {
                   enemy[i][j].setActive(1);
               }
           }
       }
       //else if (enemy_killed == )

   }
 
   //           Shield collision
   bool checkCollision(Sprite &shield,Texture & shield_texture , Bomb* b , RenderWindow & window )
   {    
       if (isShieldActive)
       {
       if (shield.getGlobalBounds().intersects(b->sprite.getGlobalBounds()))
       {    
           for (int i = 1; i <= 3; i++)
           {
               // Load the explosion texture
               std::string filename = "img/PNG/Effects/shield" + std::to_string(i) + ".png";
               shield_texture.loadFromFile(filename);
               shield.setTexture(shield_texture);

               // Update the window to show the animation
              // window.clear();
               window.draw(background);
               window.draw(shield);
               window.display();

               // Add a delay to show each frame of the animation
               sf::Time delay = sf::seconds(0.03);
               sf::sleep(delay);
           }

           b->sprite.setPosition(-1000, -1000);
           shield_texture.loadFromFile("img/PNG/Effects/shield1.png");
           shield.setTexture(shield_texture);
           return 1;
       }

       }
       return 0;
   }
  
   
   //Dragon collision/
   bool checkCollision(Bullet* b, Enemy *en)
   {
       if (b->sprite.getGlobalBounds().intersects(en->sprite.getGlobalBounds()))
       {    
           b->sprite.setPosition(-200, 1100);
           return true;
       }
       return false;
   }
   bool checkCollision(Enemy* en, Player* p ,RenderWindow & window)
   {
       if (p->sprite.getGlobalBounds().intersects(en->sprite.getGlobalBounds()) || p->sprite.getGlobalBounds().intersects(en->beam.getGlobalBounds()))
       {
           window.clear(Color::Black);
           // Show the explosion animation
           for (int i = 1; i <= 3; i++)
           {
               // Load the explosion texture
               std::string filename = "img/PNG/Damage/playerShip1_damage" + std::to_string(i) + ".png";
               window.draw(background);
               p->tex.loadFromFile(filename);
               p->sprite.setTexture(p->tex);

               // Update the window to show the animation
              // window.clear();
               window.draw(p->sprite);
               window.display();

               // Add a delay to show each frame of the animation
               sf::Time delay = sf::seconds(0.1);
               sf::sleep(delay);
           }

           // Reset the player sprite and position
           p->tex.loadFromFile("img/player_ship.png");
           p->sprite.setTexture(p->tex);
           p->sprite.setPosition(400, 800);
           p->lives--;
           p->sprite.setPosition(400, 800);
           return true;
       }
       return false;
   }


 void beamdirection(RenderWindow & window)
   {
       if(enemy[4]->getTrigger())
       {
          enemy[4]-> sprite.setPosition(300, 100);
           enemy[4]->beam.setPosition(enemy[4][0].sprite.getPosition().x + 75, enemy[4][0].sprite.getPosition().y + 250);
           if (p->x > 0 && p->x < 300)
           {
               std::cout << "AAAAAAZAZAZAZAAZ";
               enemy[4]->beam.setRotation(45);
               enemy[4]->draw(window);
           }
           if (p->x > 400 && p->x < 550)
           {
               enemy[4]->beam.setRotation(0);
               enemy[4]->draw(window);
           }
           if (p->x > 600 && p->x < 900)
           {    
              enemy[4]->beam.setPosition(enemy[4][0].sprite.getPosition().x +75, enemy[4][0].sprite.getPosition().y + 300);
               enemy[4]->beam.setRotation(-45);
               enemy[4]->draw(window);
           }

       }
       
   }
       
   
};

