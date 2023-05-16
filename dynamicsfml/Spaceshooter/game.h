#pragma once 
#include "monster.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "player.h"
#include "Enemy.h"
#include "Addon.h"
#include "meteors.h"
#include "dragon.h"
#include "invader.h"
#include "menu.h"
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{   
private:
    public:
    Sprite background, shield , life , end ; //Game background sprite
    Sprite spaceship , pmenu ;
    Sprite* spritebadge; 
    Texture* texbadge;
    Texture bg_texture, shield_texture  , stex , l_tex , ptex , end_tex;
    bool paused = false;
    int score;
    bool cflag = false;
    int enemy_killed = 0;
    int wave = 1;
    int level = 1;
    bool isMonsteractive = 0;
    bool monsterkilled = 0;
    // add other game attributes
    Player* p; //player 
    Enemy** enemy; //Enemy object
    Addons** Addon_;
    Meteors* m;
    Menu menu;
    bool isShieldActive = false;
    bool isBombActive = false;
    bool replay = 0;


    Game();


    bool compareScores(const std::string& score1, const std::string& score2);

    int extractScoreValue(const std::string& score);

    std::string extractPlayerName(const std::string& score);
  

    void saveScoreToFile(const std::string& playerName, int score);

  
    
    void start_game(bool& flag);

    virtual void setRectangle(Enemy**& en);
    virtual void setCross(Enemy**& en);
    virtual void setTriangle(Enemy**& en);
    //--------------------------------//
    virtual void setCircle(Enemy**& en);
    virtual void setHeart(Enemy**& en);
    virtual void setDiamod(Enemy**& en);
  // bullets with enemy
    bool checkCollision(Bullet* b, Enemy**& en, RenderWindow& window, bool& fireaddonflag);
    //player ship contact with enemy bomb 
    void checkCollision(Player* p, Bomb* b, RenderWindow& window);
  // player ship in contact with enemy ship
    bool checkCollision(Player* p, Enemy**& en, RenderWindow& window);
  
   // Monster collision ;
   bool checkCollision(Player* p, Enemy& e, RenderWindow& window);
   //           Shield collision
   bool checkCollision(Sprite& shield, Texture& shield_texture, Bomb* b, RenderWindow& window);
  
   
   //Dragon collision/
   bool checkCollision(Bullet* b, Enemy* en);
   bool checkCollision(Enemy* en, Player* p, RenderWindow& window);


 void beamdirection(RenderWindow& window);


 bool checkCollision(const Sprite& sprite1, const Sprite& sprite2);

 void timeclock(Enemy**& enemy, float& mtimer, RenderWindow& window, float& time);

};

