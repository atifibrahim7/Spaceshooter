#pragma once 
#include"Enemy.h"


Enemy::Enemy()
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
std::string Enemy::gettype()
{
    return type;
}
void Enemy::setType(std::string s)
{
    type = s;
}
void Enemy::setTrigger(bool s) { trigger = s; }
bool Enemy::getTrigger() { return trigger; }
int Enemy::randomDrop() {
    // create an mt19937 generator with a random seed
    std::mt19937 rng(std::random_device{}());

    // create a uniform integer distribution from 0 to 900
    std::uniform_int_distribution<int> dist(0, 900);

    // generate a random number in the range of 0 to 900
    int random_number = dist(rng);

    return random_number;
}
 bool Enemy::isActive()
{
    return  active;
}
 void Enemy::setActive(bool s)
{
    active = s;
}
Enemy::~Enemy() { delete[] bomb; }