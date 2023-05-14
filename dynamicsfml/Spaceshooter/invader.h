#pragma once

#include "Enemy.h"
class Invader : public Enemy
{
public : 
	void moving(RenderWindow& window)
	{

	}
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
	void moving(RenderWindow& window)
	{

	}
	Alpha()
	{
		Tex.loadFromFile("img/enemy_1.png");
			sprite.setTexture(Tex);
			setType("alpha");
			sprite.setPosition(200, 200);
			sprite.setScale(0.5, 0.5);
	}
};

class Beta : public Invader
{
public : 
	void moving(RenderWindow& window)
	{}
	Beta()
	{
		setType("beta");
		Tex.loadFromFile("img/enemy_2.png");
		sprite.setTexture(Tex);
		sprite.setPosition(200, 200);
		sprite.setScale(0.5, 0.5);


	}
};

class Gamma : public Invader
{
public:
	void moving(RenderWindow& window){}

	Gamma()
	{
		setType("gamma");

		Tex.loadFromFile("img/enemy_3.png");
		sprite.setTexture(Tex);
		sprite.setPosition(200, 200);
		sprite.setScale(0.35, 0.35);

	}
};