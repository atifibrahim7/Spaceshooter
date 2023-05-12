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
	
	void drop()
	{	

		sprite.move(0, 2);
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

