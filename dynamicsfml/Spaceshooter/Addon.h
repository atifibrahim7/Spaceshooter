#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf; 


class Addons
{
public  :
	int  randomDrop()
	{
		srand(time(0));
		int x = rand(); 
		std::cout <<x;
		return  x;
	}
	virtual bool apply(Player& player) = 0;
	virtual void drop() = 0;
	virtual void draw(RenderWindow& window) = 0;
	virtual void activate() = 0;
};

class ShieldAddon : public Addons
{	public:
	Texture Tex , shield_Tex;
	Sprite sprite , sprite_shield;
	int x; 
	int y; 
	ShieldAddon()
	{	
		//shield_Tex.loadFromFile("img/PNG/Effects/shield1.png");
	//	sprite_shield.setTexture(shield_Tex);
		if(!Tex.loadFromFile("img/PNG/Power-ups/shield_gold.png"))
			system("pause");
		sprite.setTexture(Tex);
		x = 100;
		y = 100;
		sprite.setPosition(x, y);
		std::cout << "Sheild created at " << x << "x "<< y <<"y \n";

	}
	void activate() override
	{
		
	}
	bool apply(Player& player) override
	{	
		//std::cout << "player " << player.x << " " << player.y <<"       "<<x <<" "<<y<<std::endl;

		
		if (sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds())) 
		{
			std::cout << "Haha Collision \n";
			sprite.setPosition(x, -1800);
			return true;
			
		}
		return false;

		
	}
	void drop() override
	{
		sprite.move(0, 5);
		x = sprite.getPosition().x;
		y = sprite.getPosition().y;
		if (y > 900)
			sprite.setPosition(randomDrop()  % 900, 00);
		
	}
	void draw(RenderWindow& window) override
	{	
		//std::cout << "Drawing sheild drop out";
		window.draw(sprite);
	}
};