#pragma once 

#include <SFML/Graphics.hpp>

using namespace sf;

class Meteors
{
protected : 
public : 
	int x, y;
	Sprite sprite;
	Texture texture;
	int randomDrop() {
		// create an mt19937 generator with a random seed
		std::mt19937 rng(std::random_device{}());

		// create a uniform integer distribution from 0 to 900
		std::uniform_int_distribution<int> dist(0, 900);

		// generate a random number in the range of 0 to 900
		int random_number = dist(rng);

		return random_number;
	}
		
	Meteors()
	{
		texture.loadFromFile("img/PNG/Meteors/meteorBrown_big2.png");
		sprite.setTexture(texture);
		sprite.setPosition(-1000, 800);
		x = sprite.getPosition().x;
		y = sprite.getPosition().y;
	}

	void wraparound(int c)
	{
		x = sprite.getPosition().x;
		y = sprite.getPosition().y;
		sprite.move(c, 0);
		
	}
	
};
