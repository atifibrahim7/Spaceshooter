#pragma once

#include "Enemy.h"
class Invader : public Enemy
{
public : 
	 bool collide(Bullet& bullet)
	{
		if (sprite.getGlobalBounds().intersects(bullet.sprite.getGlobalBounds()))
		{
			return true;
		}
		else return false;
	}

};

class Alpha : public Invader
{
public : 
	Alpha()
	{
		Tex.loadFromFile("img/enemy_1.png");
			sprite.setTexture(Tex);

			sprite.setPosition(200, 200);
			sprite.setScale(0.5, 0.5);
	}
};

class Beta : public Invader
{
public : 
	Beta()
	{
		Tex.loadFromFile("img/enemy_2.png");
		sprite.setTexture(Tex);
		sprite.setPosition(200, 200);
		sprite.setScale(0.5, 0.5);


	}
};

class Gamma : public Invader
{
public:
	Gamma()
	{
		Tex.loadFromFile("img/enemy_3.png");
		sprite.setTexture(Tex);
		sprite.setPosition(200, 200);
		sprite.setScale(0.35, 0.35);

	}
};