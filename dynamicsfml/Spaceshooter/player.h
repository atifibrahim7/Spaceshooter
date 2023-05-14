
#pragma once 
#include <SFML/Graphics.hpp>
#include<string.h>
#include "bullet.h"
#include "Enemy.h"
#include <iostream>

using namespace sf;
class Player
{
public:
	int bdirection = 0;
	Bullet* b[50]; // Bullet object
	int lives; 
	Texture tex;
	Sprite sprite;
	float speed = 7.5;
	int zz;

	int x, y;
	float timer = 0;

	void move(std::string s)
	{
		float checkDiagonal1 = 0;
		float  checkDiagonal2 = 0;
		float delta_x = 0, delta_y = 0;
		if (s == "l")
		{
			delta_x = -1;
		}

		//move the player left
		else if (s == "r")
		{
			delta_x = 1;

		}
		//move the player right
		if (s == "u")
		{
			delta_y = -1;
		}
		else if (s == "d")
		{
			delta_y = 1;
		}



		delta_x *= speed;
		delta_y *= speed;
		x = sprite.getPosition().x;
		y = sprite.getPosition().y;

		sprite.move(delta_x, delta_y);
	}
	void wraparound()
	{
		if (sprite.getPosition().x < 0)
			sprite.setPosition(sf::Vector2f(900, sprite.getPosition().y));
		else if (sprite.getPosition().x > 900)
			sprite.setPosition(sf::Vector2f(0, sprite.getPosition().y));

		if (sprite.getPosition().y < 0)
			sprite.setPosition(sf::Vector2f(sprite.getPosition().x, 900));
		else if (sprite.getPosition().y > 900)
			sprite.setPosition(sf::Vector2f(sprite.getPosition().x, 0));
	}
	Player(std::string png_path)
	{	
		zz = 0;
		for (int i = 0; i < 50; i++)
		{
		//	std::cout << "Bullet created " << i<<std::endl; 
			b[i] = new Bullet();
			b[i]->x = -100;
			b[i]->y = -100;
			b[i]->sprite.setPosition(b[i]->x, b[i]->y);
		}
		lives = 3;

		tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		x = 340; y = 700;
		sprite.setPosition(x, y);
		sprite.setScale(0.75, 0.75);
		
	}
	
	

	void fire(float time)
	{
		timer += time;
		// Play the sound

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timer > 0.2)
		{
			timer = 0;

			for (int i = 0; i < 50; i++) {
				if (!b[i]->active) {
					b[i]->active = true;
					b[i]->x = sprite.getPosition().x + 55;
					b[i]->y = sprite.getPosition().y;
					b[i]->sprite.setPosition(b[i]->x, b[i]->y);
					break;
				}
			}
		}

		for (int i = 0; i < 50; i++) {
			if (b[i]->active) {
				if (zz == 1) {
					{
						b[i]->move(135);
						b[i]->sprite.setRotation(45);
						// b[i]->sprite.setRotation(135);
					}
				}
				else if (zz == 2) {
					b[i]->move(45);
					b[i]->sprite.setRotation(135);

				//	b[i]->sprite.setRotation(45);
				}
				else if(zz == 0) {
					b[i]->sprite.setRotation(90);

					b[i]->move(90);
				//	b[i]->sprite.setRotation(90);
				}
				if (b[i]->y < 0) {
					b[i]->active = false;
					b[i]->x = -100;
					b[i]->y = -100;
					b[i]->sprite.setPosition(b[i]->x, b[i]->y);
				}
			}
		}
	}

	void rotate()
	{	
		if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Up)) {
			zz = 1; // left move 
			tex.loadFromFile("img/l.png");
			sprite.setTexture(tex);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Up)) {
			zz = 2; // right move  ;
			
				
			tex.loadFromFile("img/r.png");
			sprite.setTexture(tex);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Down)) {
			zz = 0;
			tex.loadFromFile("img/lb.png");
			sprite.setTexture(tex);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Down)) {
			zz = 0;
			tex.loadFromFile("img/rb.png");
			sprite.setTexture(tex);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::Up) )
		{
			zz = 0 ;
			tex.loadFromFile("img/player_ship.png");
			sprite.setTexture(tex);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Right))
		{
			
			tex.loadFromFile("img/player_ship.png");
			sprite.setTexture(tex);
		}
		else {
			
			tex.loadFromFile("img/player_ship.png");
			sprite.setTexture(tex);
		}
	}

};
