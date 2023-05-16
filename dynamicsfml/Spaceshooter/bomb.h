#pragma once
#include "Enemy.h"
#include <random>
class Bomb
{
	bool active;
public  : 
	Texture tex;
	Sprite sprite;
	int damage;
	int x; int y;

	Bomb()
	{
		tex.loadFromFile("img/enemy_laser.png");
		sprite.setTexture(tex);
		setActive(1);
		sprite.setPosition(-299, -299);

		
	}
	void setActive( bool s)
	{
		active = s; 
	}
	
	void drop(int x)
	{	
		
		sprite.move(0, x);
		/*if (sprite.getPosition().y > 900)
		{
			delete this;
			
		}*/
		
	}
	bool isActive()
	{
		return active;
	}
};

