#pragma once
#include "game.h"
Game ::Game()
{
    spritebadge = new Sprite[3];
    texbadge = new Texture[3];

    texbadge[0].loadFromFile("img/badgeG.png");
    texbadge[1].loadFromFile("img/badgeS.png");
    texbadge[2].loadFromFile("img/badgeB.png");
    for (int i = 0; i < 3; i++)
    {
        spritebadge[i].setTexture(texbadge[i]);
        spritebadge[i].setScale(0.02, 0.02);
    }
    end_tex.loadFromFile("img/end.png");
    end.setTexture(end_tex);
    ptex.loadFromFile("img/Restart.png");
    pmenu.setTexture(ptex);
    pmenu.setScale(0.9, 0.9);
    stex.loadFromFile("img/PNG/UI/playerLife1_blue.png");
    spaceship.setTexture(stex);
    //spaceship.setScale(.5, .5);
    l_tex.loadFromFile("img/life.png");
    life.setTexture(l_tex);
    life.setScale(0.07, 0.07);
    //menu = new Menu();
    enemy = new  Enemy * [5];
    enemy[0] = new Alpha[5];
    enemy[1] = new Beta[5];
    enemy[2] = new Gamma[5];
    enemy[3] = new Monster();
    enemy[4] = new Dragon();
    m = new Meteors[3];
    m[1].texture.loadFromFile("img/PNG/Meteors/meteorBrown_big4.png");
    m[2].texture.loadFromFile("img/PNG/Meteors/meteorGrey_big2.png");

    Addon_ = new Addons * [5] {new ShieldAddon(), new LivesAddon(), new DangerAddon(), new FireAddon() , new Powerup()};
    shield_texture.loadFromFile("img/PNG/Effects/shield1.png");
    shield.setTexture(shield_texture);
    p = new Player("img/player_ship.png");
    bg_texture.loadFromFile("img/background_1.png");
    // Addones loading sprites 

    background.setTexture(bg_texture);
    background.setScale(1.3, 0.8);
    //background.setPosition(0, 00);
    m[1].sprite.setPosition(-1300, 600);
    m[2].sprite.setPosition(-100, 700);
}
void Game:: start_game(bool& flag)
{
    Font FONTS;
    FONTS.loadFromFile("img/ss.otf");
    bool filesaved = 0;
    menu.display_menu(flag, spritebadge);
    if (flag)
    {

        Text enterNameText;
        enterNameText.setFont(FONTS);
        enterNameText.setCharacterSize(50);
        enterNameText.setFillColor(Color::Yellow);
        enterNameText.setString("Enter Your Name:");
        enterNameText.setPosition(100, 100); // Adjust the position as needed

        Text nameText;
        nameText.setFont(FONTS);
        nameText.setCharacterSize(50);
        nameText.setFillColor(Color::Yellow);
        nameText.setPosition(200, 200); // Adjust the position as needed

        std::string playerName;

        bool enteringName = true;


        srand(time(0));
        RenderWindow window(VideoMode(900, 950), title);
        window.setFramerateLimit(60);
        Clock clock, clock1;
        int bombspeed = 4;
        float timer = 0;
        float shieldtimer = 0;
        float firetimer = shieldtimer;
        bool fireaddonflag = false;
        float btimer = 0;
        float mtimer = 0;
        float dtimer = 0;
        float pausetimer = 0;
        bool animation = 0;
        bool powerup = 0;
        Music gameplay;
        float powertimer = 0;
        bool showSprite1 = false;
        bool showSprite2 = false;
        bool showSprite3 = false;


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
        Event event;
        while (enteringName)
        {
            //std::cout << enterNameText.getPosition().x << enterNameText.getPosition().y << "\n";
            // ...
            window.clear();
            window.draw(enterNameText);
            nameText.setString(playerName);
            window.draw(nameText);
            window.display();
            while (window.pollEvent(event))

            {
                window.clear();
                window.draw(enterNameText);
                nameText.setString(playerName);
                window.draw(nameText);
                window.display();
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                else if (event.type == sf::Event::TextEntered)
                {
                    if (enteringName && event.text.unicode < 128)
                    {
                        if (event.text.unicode == '\b' && !playerName.empty())
                        {
                            // Handle backspace
                            playerName.pop_back();
                        }
                        else if (event.text.unicode == '\r' || event.text.unicode == '\n')
                        {
                            // Handle enter key
                            enteringName = false;
                        }
                        else
                        {
                            // Add the entered character to the name string
                            playerName += static_cast<char>(event.text.unicode);
                        }
                    }
                }
                window.clear();
                window.draw(enterNameText);
                nameText.setString(playerName); // Update the text with the current playerName
                window.draw(nameText);
                window.display();
            }

        }

        // ...



        Texture enemyTexture;
        if (!enemyTexture.loadFromFile("img/enemy_1.png"))
        {
            // Error handling if the texture fails to load
            ;
        }

        sf::Texture animationTexture;
        if (!animationTexture.loadFromFile("img/explosion.png"))
        {
            // Error handling if the texture fails to load
            ;
        }

        // Set up the sprites
        sf::Sprite sprite1(enemyTexture);
        sprite1.setPosition(100, 200);
        sf::Vector2f sprite1Velocity(1.0f, 0.0f);

        sf::Sprite sprite2(enemyTexture);
        sprite2.setPosition(500, 200);
        sf::Vector2f sprite2Velocity(-1.0f, 0.0f);

        bool collisionOccurred = false;
        bool animationComplete = false;

        while (window.isOpen() && !animationComplete)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            // Move the sprites
            sprite1.move(sprite1Velocity);
            sprite2.move(sprite2Velocity);

            // Check for collision
            sf::FloatRect sprite1Bounds = sprite1.getGlobalBounds();
            sf::FloatRect sprite2Bounds = sprite2.getGlobalBounds();
            if (sprite1Bounds.intersects(sprite2Bounds) && !collisionOccurred)
            {
                // Collision occurred, play the animation
                collisionOccurred = true;

                sprite1.setTexture(animationTexture);
                sprite2.setTexture(animationTexture);

                sf::Clock animationClock;
                int animationFrame = 0;

                while (animationFrame < 4)
                {
                    window.clear();

                    // Draw the animation frame
                    sprite1.setTextureRect(sf::IntRect(animationFrame * 138, 0, 138, 138));
                   
                    window.draw(background);
                    window.draw(sprite1);
                    window.draw(sprite2);

                    window.display();

                    // Delay to control the animation speed
                    sf::Time elapsedTime = animationClock.getElapsedTime();
                    if (elapsedTime.asMilliseconds() >= 200)
                    {
                        animationFrame++;
                        animationClock.restart();
                    }
                }

                // Animation completed, exit the loop
                animationComplete = true;
            }

            window.clear();

            // Draw the sprites
            window.draw(background);
            window.draw(sprite1);
            window.draw(sprite2);
            window.display();
        }


        // Bonus

        while (window.isOpen())
        {

            // std::cout << "Level : " << level<<"\n";
            if (level == 2 && !animation)
            {
                bombspeed = 8;
                bg_texture.loadFromFile("img/bg2.jpeg");
                animation = !animation;
            }
            if (level == 3 && animation)
            {
                bombspeed = 12;
                bg_texture.loadFromFile("img/bg3.jpeg");
                animation = !animation;
            }

            if (p->lives < 0)
            {
                if (!filesaved)
                {
                    saveScoreToFile(playerName, score);
                    filesaved = !filesaved;
                }
                // system("pause");
                window.clear();
                window.draw(end);
                window.display();
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    replay = true;
                    p->lives = 3;
                    level = 1;
                    wave = 1;
                    enemy_killed = 0;
                    monsterkilled = 0;
                    p->sprite.setPosition(400, 800);
                    paused = !paused;
                    score = 0;
                    for (int i = 0; i < 50; i++)
                    {
                        p->b[i]->sprite.setPosition(1000, 1000);
                    }
                    for (int i = 0; i < 3; i++)
                    {
                        for (int j = 0; j < 5; j++)
                        {
                            if (enemy[i][j].bomb->isActive())
                                enemy[i][j].bomb->sprite.setPosition(400, 1000);
                        }
                    }
                    btimer = 0;


                    break;
                }
                if (Keyboard::isKeyPressed(Keyboard::E))
                {
                    replay = false;
                    break;
                }
            }
            float time = clock.getElapsedTime().asSeconds();


            clock.restart();
            timer += time;
            btimer += time;
            Event ev;
            while (window.pollEvent(ev))
            {
                // ...

                if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::P)
                {
                    if (!paused)
                    {
                        paused = true;
                        pausetimer = clock.getElapsedTime().asSeconds(); // Store the time at which the game was paused
                    }
                    else
                    {
                        paused = false;
                        float pausetime = clock.getElapsedTime().asSeconds() - pausetimer; // Calculate the time the game was paused
                        timer += pausetime; // Add the paused time to the timer
                    }
                }
                if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::R)
                {
                    if (paused)
                    {
                        // Reset the game state here
                        // ...
                        p->lives = 3;
                        level = 1;
                        wave = 1;
                        enemy_killed = 0;
                        monsterkilled = 0;
                        p->sprite.setPosition(400, 800);
                        paused = !paused;
                        score = 0;
                        for (int i = 0; i < 50; i++)
                        {
                            p->b[i]->sprite.setPosition(1000, 1000);
                        }
                        for (int i = 0; i < 3; i++)
                        {
                            for (int j = 0; j < 5; j++)
                            {
                                if (enemy[i][j].bomb->isActive())
                                    enemy[i][j].bomb->sprite.setPosition(400, 1000);
                            }
                        }
                        btimer = 0;

                    }
                }
                if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Num1)
                {
                    // std::cout << "1 pressed";
                    showSprite1 = true;
                    showSprite2 = false;
                    showSprite3 = false;
                }
                if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Num2)
                {
                    // std::cout << "2 pressed";
                    showSprite1 = false;
                    showSprite2 = true;
                    showSprite3 = false;
                }
                if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Num3)
                {
                    //  std::cout << "2 pressed";
                    showSprite1 = false;
                    showSprite3 = true;
                    showSprite2 = false;
                }
                if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Num4)
                {
                    // std::cout << "2 pressed";
                    showSprite1 = false;
                    showSprite3 = false;
                    showSprite2 = false;
                }



            }







            // window.display();
            if (paused)
            {
                window.clear();
                window.draw(pmenu);
                window.display();  // Display a pause message or menu
                continue; // Skip the game logic and go to the next iteration of the game loop
            }
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
            // Define a Clock object to measure the elapsed time
            static Clock soundClock;

            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                if (soundClock.getElapsedTime().asSeconds() >= 0.5f)
                {
                    soundClock.restart(); // Restart the clock to measure the time again

                    // Play the sound
                    gameplay.stop(); // Stop the sound if it's already playing
                    if (gameplay.getStatus() != Sound::Playing)
                    {
                        gameplay.setVolume(70); // Set the volume to 70%
                        // gameplay.setLoop(true);
                        gameplay.play();
                    }
                }
            }



            if (Keyboard::isKeyPressed(Keyboard::D))
                enemy[4]->setActive(1);
            if (Keyboard::isKeyPressed(Keyboard::X))
                enemy[4]->setActive(0);


            ////////////////////////////////////////////////
            ///  Call your functions here            ///
         

            if (Addon_[4]->apply(*p))
            {
                std::cout << "power up";
                powerup = 1;
            }
            if (powerup)
            {
               
                p->b[0]->move(45);
                p->b[1]->move(60);
                p->b[6]->move(30);
                p->b[5]->move(15);
                p->b[4]->move(55);
                p->b[2]->move(75);
                p->b[3]->move(90);
                powertimer += time;

            }
            if (powertimer > 6)
            {   
                powerup = !powerup;
                powertimer = 0;
            }
               // End // 
            

            int r1 = Addon_[1]->randomDrop() % 3;
            int r2 = Addon_[1]->randomDrop() % 5;


            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    checkCollision(p, enemy[i][j].bomb, window);
                }

            }
            if (checkCollision(p, enemy, window)) {}

            p->rotate();
            p->wraparound();
            p->fire(time);



            if (btimer > 6)
            {
                btimer = 0;
                //  std::cout << btimer;
            }
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 5; j++)
                {

                    if (enemy[i][j].bomb->isActive())
                    {
                        if (btimer > 4 && btimer < 4.1)
                        {


                            enemy[i][j].bomb->sprite.setPosition(enemy[i][j].sprite.getPosition().x, enemy[i][j].sprite.getPosition().y);
                            //   std::cout << i << j << " " << enemy[i][j].bomb->sprite.getPosition().x << " " << enemy[i][j].bomb->sprite.getPosition().y << "\n";


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
                else if (Addon_[i]->apply(*p));
                //  std::cout << "Addon picked" << p->lives;
            }




            // std::cout << "ENemy at :" << enemy[0][0].sprite.getPosition().x << " " << enemy[0][0].sprite.getPosition().y<<"\n";
          //   std::cout << firetimer << "\n";
            if (firetimer > 5.0f)
            {
                // std::cout << "in if statement";
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
            for (int i = 0; i < 5; i++)
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
                    if (checkCollision(shield, shield_texture, enemy[i][j].bomb, window))
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
                    //   std::cout << "Enemy killed";
                  //     std::cout << enemy_killed << "\n";
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
                    if (enemy[k][i].isActive())
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
                            enemy[i][j].bomb->drop(bombspeed);
                            // enemy[i][j].bomb->sprite.move(0, 2);
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
            if (!enemy[4]->getTrigger())
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
                    //  std::cout << dtimer << "\n";
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
                enemy[4]->sprite.setPosition(200, 100);
                enemy[4]->setActive(0);
                score += 50;
                dtimer = 0;
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
                spaceship.setPosition(50 + i * 50, 870);
                window.draw(spaceship);
            }

            // -------------------------------------------------------------------------Meteors _----------------------------------//
            int c = 3;
            for (int i = 0; i < 3; i++)
            {
                if (level == 2)
                    c = 5;

                if (level == 3)
                    c = 7;
                m[i].wraparound(c);
                if (m[i].sprite.getPosition().x > 950)
                {
                    m[i].sprite.setPosition(-1500, m[i].y);
                }
                if (checkCollision(m[i].sprite, p->sprite))
                {
                    m[i].sprite.setPosition(-500, m[i].sprite.getPosition().y);
                    p->sprite.setPosition(400, 800);
                    p->lives--;
                }
                window.draw(m[i].sprite);
            }

            //  std::cout << m->sprite.getPosition().x << " " << m->sprite.getPosition().y << "\n";
              //   m->sprite.setPosition(200, 300);
            nameText.setPosition(800, 10);
            window.draw(nameText);
            window.draw(Addon_[4]->sprite);

            if (showSprite1)
            {
                //spritebadge[0].setPosition(100, 100);
                window.draw(spritebadge[0]);
            }
            else if (showSprite2)
            {
                window.draw(spritebadge[1]);
            }
            else if (showSprite3)
            {
                window.draw(spritebadge[2]);
            }
            else {
                ;
            }

            timeclock(enemy, mtimer, window, time);

            window.display();  //Displying all the sprites


        }

    }
}
bool Game:: checkCollision(const Sprite& sprite1, const Sprite& sprite2) {
    FloatRect bounds1 = sprite1.getGlobalBounds();
    FloatRect bounds2 = sprite2.getGlobalBounds();

    // Check for intersection between the two bounding rectangles
    if (bounds1.left < bounds2.left + bounds2.width &&
        bounds1.left + bounds1.width > bounds2.left &&
        bounds1.top < bounds2.top + bounds2.height &&
        bounds1.top + bounds1.height > bounds2.top) {

        Vector2f sprite1Position = sprite1.getPosition();
        Vector2f sprite2Position = sprite2.getPosition();

        Vector2f sprite1Size = Vector2f(sprite1.getGlobalBounds().width, sprite1.getGlobalBounds().height);
        Vector2f sprite2Size = Vector2f(sprite2.getGlobalBounds().width, sprite2.getGlobalBounds().height);

        // Calculate the minimum and maximum coordinates for both sprites
        Vector2f sprite1Min = sprite1Position - sprite1Size / 2.f;
        Vector2f sprite1Max = sprite1Position + sprite1Size / 2.f;
        Vector2f sprite2Min = sprite2Position - sprite2Size / 2.f;
        Vector2f sprite2Max = sprite2Position + sprite2Size / 2.f;

        // Check for intersection along both axes (x and y)
        if (sprite1Min.x < sprite2Max.x && sprite1Max.x > sprite2Min.x &&
            sprite1Min.y < sprite2Max.y && sprite1Max.y > sprite2Min.y) {
            return true; // Collision detected
        }
    }

    return false; // No collision
}

void Game :: timeclock(Enemy**& enemy, float& mtimer, RenderWindow& window, float& time)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (enemy[i][j].isActive() == 0)
            {
                count++;
            }
        }
    }


    if (enemy_killed == 0)
    {
        wave = 1;
        // setCross(enemy);
        setCircle(enemy);
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
    else if (enemy_killed == 30 && !monsterkilled && mtimer == 0)
    {

        enemy[3]->sprite.setPosition(400, 100);
        window.draw(enemy[3]->sprite);
        mtimer += time;
        enemy[3]->setActive(1);
        //  std::cout << enemy[3]->sprite.getPosition().x << " " << enemy[3]->sprite.getPosition().y << "\n";
    }
    else if (enemy_killed == 30 && monsterkilled)
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
        //setDiamod(enemy);
        setTriangle(enemy);


    }
    else if (enemy_killed == 45)
    {
        level = 2;
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
    else if (enemy_killed == (60))
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
    else if (enemy_killed == 75)
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
    else  if (enemy_killed == 90)
    {
        level = 3;
        setCross(enemy);
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                enemy[i][j].setActive(1);
            }
        }
        wave = 7;
    }
    else if (enemy_killed == 105)
    {
        wave = 8;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                enemy[i][j].setActive(1);
            }
        }
        setRectangle(enemy);
    }
    else if (enemy_killed == 120)
    {
        wave = 9;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                enemy[i][j].setActive(1);
            }
        }
        setCross(enemy);
    }
}

void Game:: beamdirection(RenderWindow& window)
{
    if (enemy[4]->getTrigger())
    {
        enemy[4]->sprite.setPosition(300, 100);
        enemy[4]->beam.setPosition(enemy[4][0].sprite.getPosition().x + 75, enemy[4][0].sprite.getPosition().y + 250);
        if (p->x > 0 && p->x < 300)
        {
            //  std::cout << "AAAAAAZAZAZAZAAZ";
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
            enemy[4]->beam.setPosition(enemy[4][0].sprite.getPosition().x + 75, enemy[4][0].sprite.getPosition().y + 300);
            enemy[4]->beam.setRotation(-45);
            enemy[4]->draw(window);
        }

    }

}

bool    Game:: checkCollision(Enemy* en, Player* p, RenderWindow& window)
{
    if (en->isActive())
        if (p->sprite.getGlobalBounds().intersects(en->sprite.getGlobalBounds()) || p->sprite.getGlobalBounds().intersects(en->beam.getGlobalBounds()))
        {
            // std::cout << " dragon collided";
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

bool Game::checkCollision(Bullet* b, Enemy* en)
{
    if (en->isActive())
    {

        if (b->sprite.getGlobalBounds().intersects(en->sprite.getGlobalBounds()))
        {
            b->sprite.setPosition(-200, 1100);
            en->beam.setPosition(-200, 1100);
            // std::cout << "collision with Dragon";
            return true;
        }
    }
    return false;
}

bool Game::checkCollision(Sprite& shield, Texture& shield_texture, Bomb* b, RenderWindow& window)
{
    if (isShieldActive)
    {
        if (checkCollision(shield, b->sprite))
        {
            // std::cout << "Collision with shoeld";
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

bool Game::checkCollision(Player* p, Enemy& e, RenderWindow& window)
{
    if (checkCollision(p->sprite, e.sprite) || p->sprite.getGlobalBounds().intersects(e.beam.getGlobalBounds()))
    {
        // std::cout << "monster collides";
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


bool Game::checkCollision(Player* p, Enemy**& en, RenderWindow& window)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (p->sprite.getGlobalBounds().intersects(en[i][j].sprite.getGlobalBounds()))
            {
                //  std::cout << "Collision with enemyship";
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


void Game:: checkCollision(Player* p, Bomb* b, RenderWindow& window)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (checkCollision(b->sprite, p->sprite))
            {
                //std::cout << "Collision with enemy bomb";

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


bool Game::checkCollision(Bullet* b, Enemy**& en, RenderWindow& window, bool& fireaddonflag)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (en[i][j].isActive())
                if (b->sprite.getGlobalBounds().intersects(en[i][j].sprite.getGlobalBounds()))
                {

                    //en[i][j].Tex.loadFromFile("img/PNG/playerShip2_green.png");
                    if (en[i][j].gettype() == "alpha")
                        score += 10;
                    else if (en[i][j].gettype() == "beta")
                        score += 20;
                    else if (en[i][j].gettype() == "gamma")
                        score += 30;
                    en[i][j].sprite.setTexture(en[i][j].Tex);
                    // Show the explosion animation
                    for (int k = 2; k <= 5; k++)
                    {
                        // Load the explosion texture
                        std::string filename = "img/explosion" + std::to_string(k) + ".png";
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
                    enemy[i][j].setActive(0);
                    // Update the bullet position and count the enemy as killed

                    if (!fireaddonflag)
                        b->sprite.setPosition(p->x, p->y);
                    enemy_killed++;

                    return true;
                }
        }
    }
    return false;
}

 void Game::setCircle(Enemy**& en) {
    float a = (2.0 * 3.14159) / 14;
    float angle = 0, x, y;
    for (int i = 0; i < 15; i++) {
        angle = a * i;
        x = std::cos(angle) * 170 + 360;
        y = std::sin(angle) * 170 + 200 + 30;
        en[i / 5][i % 5].sprite.setPosition(x, y);
    }

}
void Game::setHeart(Enemy**& en) {

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
 void Game:: setDiamod(Enemy**& en) {
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

}

 void Game:: setRectangle(Enemy**& en) {

     for (int i = 0; i < 5; i++) {
         en[0][i].sprite.setPosition(i * 153.0 + 100, 50);

     }

     for (int i = 0; i < 5; i++) {
         en[1][i].sprite.setPosition(i * 153.0 + 100, 250);
     }

     en[2][0].sprite.setPosition(100.0, 90);

     en[2][1].sprite.setPosition(712.0, 90.0);

     en[2][2].sprite.setPosition(100.f, 180.0);

     en[2][3].sprite.setPosition(712, 180);
     en[2][4].sprite.setPosition(400, 150);

 }
 void Game::setCross(Enemy**& en) {
     for (int i = 0; i < 5; i++)
         en[0][i].sprite.setPosition(200 + 50 + i * 70, i * 70.0);
     en[2][0].sprite.setPosition(650, 400);
     en[2][1].sprite.setPosition(550 + 40, 340);

     for (int i = 0; i < 5; i++)
         if (i != 3)
         {
             en[1][i].sprite.setPosition(700 - i * 50, i * 50 + 30);

         }
     en[1][4].sprite.setPosition(550, 180);


     en[1][3].sprite.setPosition(370, 280);
     en[2][2].sprite.setPosition(590 / 2 - 10, 340);
     en[2][3].sprite.setPosition(220, 400);
     en[2][4].sprite.setPosition(460, 300);


 }
  void Game::setTriangle(Enemy**& en) {
     for (int i = 0; i < 5; i++)
         en[0][i].sprite.setPosition(360 + i * 50, i * 50);
     for (int i = 0; i < 5; i++)
         en[1][i].sprite.setPosition(280 - i * 50, i * 50);
     for (int i = 0; i < 5; i++) {
         en[2][i].sprite.setPosition(95 + 150 * i, 290);
     }
 }


  bool Game::compareScores(const std::string& score1, const std::string& score2) {
      // Extract the score values from the score strings
      int scoreValue1 = extractScoreValue(score1);
      int scoreValue2 = extractScoreValue(score2);

      // Compare the score values in descending order
      return scoreValue1 > scoreValue2;
  }

  int Game ::extractScoreValue(const std::string& score) {
      // Find the position of the last occurrence of "Score: " in the score string
      size_t scorePosition = score.rfind("Score: ");
      if (scorePosition != std::string::npos) {
          // Extract the score value substring
          std::string scoreValueStr = score.substr(scorePosition + 7);

          // Convert the score value string to an integer
          try {
              return std::stoi(scoreValueStr);
          }
          catch (const std::exception& e) {
              // Handle any conversion errors here
          }
      }

      // Return a default value if the score value extraction fails
      return 0;
  }

  std::string Game::extractPlayerName(const std::string& score) {
      // Find the position of the first occurrence of " - Score: " in the score string
      size_t playerNameEnd = score.find(" - Score: ");
      if (playerNameEnd != std::string::npos) {
          // Extract the player name substring
          return score.substr(13, playerNameEnd - 13);
      }

      // Return an empty string if the player name extraction fails
      return "";
  }


  void Game:: saveScoreToFile(const std::string& playerName, int score)
  {
      std::vector<std::string> scores;

      // Read all the existing scores from the file into a vector
      std::ifstream inputFile("scores.txt");
      if (inputFile.is_open())
      {
          std::string line;
          while (std::getline(inputFile, line))
          {
              scores.push_back(line);
          }

          inputFile.close();
      }
      else
      {
          std::cout << "Error: Unable to open the scores file." << std::endl;
          return;
      }

      bool playerFound = false;

      // Find and update the player's score
      for (auto& existingScore : scores)
      {
          std::string existingPlayerName = extractPlayerName(existingScore);
          int existingScoreValue = extractScoreValue(existingScore);

          if (existingPlayerName == playerName)
          {
              playerFound = true;

              if (score > existingScoreValue)
              {
                  existingScore = "Player Name: " + playerName + " - Score: " + std::to_string(score);
                  std::cout << "Score updated successfully." << std::endl;
              }
              else
              {
                  std::cout << "The current score is not higher than the previous score." << std::endl;
              }

              break;
          }
      }

      // If the player's score is not found, add a new entry
      if (!playerFound)
      {
          scores.push_back("Player Name: " + playerName + " - Score: " + std::to_string(score));
          std::cout << "New entry added successfully." << std::endl;
      }

      // Manually sort the scores in ascending order
      for (size_t i = 0; i < scores.size() - 1; i++) {
          for (size_t j = i + 1; j < scores.size(); j++) {
              if (compareScores(scores[j], scores[i])) {
                  std::swap(scores[i], scores[j]);
              }
          }
      }

      // Write the updated scores back to the file
      std::ofstream outputFile("scores.txt");
      if (outputFile.is_open())
      {
          for (const auto& score : scores)
          {
              outputFile << score << std::endl;
          }
          outputFile.close();
      }
      else
      {
          std::cout << "Error: Unable to open the scores file." << std::endl;
      }
  }

