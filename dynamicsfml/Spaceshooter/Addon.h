#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>
#include <random>
using namespace sf; 


class Addons
{
public  :
	int randomDrop() {
		// create an mt19937 generator with a random seed
		std::mt19937 rng(std::random_device{}());

		// create a uniform integer distribution from 0 to 900
		std::uniform_int_distribution<int> dist(0, 900);

		// generate a random number in the range of 0 to 900
		int random_number = dist(rng);

		return random_number;
	}
	virtual bool apply(Player& player) = 0;
	virtual void drop() = 0;
	virtual void draw(RenderWindow& window) = 0;
	//virtual void activate() = 0;
};

class ShieldAddon : public Addons
{	public:
	Texture Tex;
	Sprite sprite ;
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
	/*void activate() override
	{
		
	}*/
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


class LivesAddon : public Addons
{	
public : 
	Sprite sprite;
	Texture Tex;
	int x, y;
	
	LivesAddon()
	{	
		Tex.loadFromFile("img/PNG/Power-ups/star_bronze.png");
		sprite.setTexture(Tex);
		x = 100;
		y = 1900;
		sprite.setPosition(x, y);
	}
	bool apply(Player& player) override
	{
		//std::cout << "player " << player.x << " " << player.y <<"       "<<x <<" "<<y<<std::endl;


		if (sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds()))
		{
			std::cout << "Haha Collision \n";
			sprite.setPosition(randomDrop() % 900, -1800);
			if (player.lives < 10)
				player.lives += 1;
			sprite.setPosition(randomDrop() % 900, -2000);
			return true;

		}
		return false;
	}
	
	void drop() override
	{
		sprite.move(0, 2);
		x = sprite.getPosition().x;
		y = sprite.getPosition().y;
		if (y > 900)
			sprite.setPosition(randomDrop() % 900, -2000);

	}
	void draw(RenderWindow& window)
	{
		window.draw(sprite);
	}
};

class DangerAddon : public Addons
{
protected  : 
	Texture Tex;
	Sprite sprite;
	int x;
	int y;

public : 
	DangerAddon()
	{	
		Tex.loadFromFile("img/PNG/Power-ups/bolt_bronze.png");
		sprite.setTexture(Tex);
		x = 200;
		y = 2000;
		sprite.setPosition(x, y);
	}
	void drop() override
	{
		sprite.move(0, 4);
		x = sprite.getPosition().x;
		y = sprite.getPosition().y;
		if (y > 900)
			sprite.setPosition(randomDrop() % 900, -2000);

	}
	bool apply(Player& player) override
	{
		//std::cout << "player " << player.x << " " << player.y <<"       "<<x <<" "<<y<<std::endl;


		if (sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds()))
		{
			std::cout << "Haha Collision \n";
			sprite.setPosition(randomDrop() % 900, -1800);
			if (player.lives > 0)
				player.lives -= 1;
			sprite.setPosition(randomDrop() % 900, -2000);
			
			player.sprite.setPosition(450, 800);
			return true;

		}
		return false;
	}
	void draw(RenderWindow& window)
	{
		window.draw(sprite);
	}
};

class FireAddon : public Addons
{
protected:
	Texture Tex;
	Sprite sprite;
	int x;
	int y;

public:
	FireAddon()
	{
		Tex.loadFromFile("img/PNG/Power-ups/things_gold.png");
		sprite.setTexture(Tex);
		x = 300;
		y = 2500;
		sprite.setPosition(x, y);
	}
	void drop() override
	{
		sprite.move(0, 6);
		x = sprite.getPosition().x;
		y = sprite.getPosition().y;
		if (y > 900)
			sprite.setPosition(randomDrop() % 900, -2500);

	}
	bool apply(Player& player) override
	{
		//std::cout << "player " << player.x << " " << player.y <<"       "<<x <<" "<<y<<std::endl;


		if (sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds()))
		{
			std::cout << "Lol Collision \n";
			sprite.setPosition(randomDrop() % 900, -1800);
			
			sprite.setPosition(randomDrop() % 900, -2000);

			return true;

		}
		return false;
	}
	void draw(RenderWindow& window)
	{
		window.draw(sprite);
	}
};