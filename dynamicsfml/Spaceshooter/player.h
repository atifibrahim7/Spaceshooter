
#pragma once 
#include <SFML/Graphics.hpp>
#include<string.h>
#include "bullet.h"
#include <iostream>

using namespace sf;
class Player
{
public:
	Bullet* b[50]; // Bullet object

	Texture tex;
	Sprite sprite;
	float speed = 7.5;

	int x, y;
	float timer = 0;

	Player(std::string png_path)
	{
		for (int i = 0; i < 50; i++)
		{
		//	std::cout << "Bullet created " << i<<std::endl; 
			b[i] = new Bullet();
			b[i]->x = -100;
			b[i]->y = -100;
			b[i]->sprite.setPosition(b[i]->x, b[i]->y);
		}

		tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		x = 340; y = 700;
		sprite.setPosition(x, y);
		sprite.setScale(0.75, 0.75);
		
	}
	


	void fire(float time)
	{
		timer += time;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timer > 0.2)
		{
			timer = 0;

			for (int i = 0; i < 50; i++) {
				if (b[i]->y < 0) {
					b[i]->x = sprite.getPosition().x  + 70;
					b[i]->y = sprite.getPosition().y ;
					b[i]->sprite.setPosition(b[i]->x, b[i]->y);
					break;
				}
			}
		}

		for (int i = 0; i < 50; i++) {
			if (b[i]->y >= 0) {
				b[i]->move();
				if (b[i]->y < 0) {
				//	std::cout << "Bullet out of screen " << i << "\n";
					b[i]->x = -100;
					b[i]->y = -100;
					b[i]->sprite.setPosition(b[i]->x, b[i]->y);
					std::cout << b[i]->x << " " << b[i]->y << "\n";
					
				}
			}
		}
	}

	/* void fire()
	{

		// if(Keyboard::isKeyPressed(Keyboard::Space))
		// {
		// 	b = new Bullet[10];
		// 	b->x = sprite.getPosition().x+35;
		// 	b->y = sprite.getPosition().y -25;
		// 	b->sprite.setPosition(b->x,b->y);
		// }
		//  b->sprite.move(0,-10);
			static int i = 0 ;
		{
		if(Keyboard::isKeyPressed(Keyboard::Space))
			for(int i = 0 ; i < 50 ; i++)
			{
				if(b[i]->sprite.getPosition().y > 0)
				{
					continue ;
				}
				else
				{
					b[i]->x = sprite.getPosition().x+35;
					b[i]->y = sprite.getPosition().y -25;
					b[i]->sprite.setPosition(b[i]->x,b[i]->y);
				}
			}
		}
		b[i]->sprite.move(0,-10);
		//  //if(b->sprite.getPosition().y<0)
	}
	 */
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
	void rotate()
	{
		// std::	cout<<"ssss" ;
		sprite.setRotation(0);
		float checkd1 = 0;
		float checkd2 = 0;
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			checkd1 = 1.1f;
			// std::cout<<"left"<<std::endl;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			checkd1 = 1.2f;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			checkd2 = 1.1f;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			checkd2 = 1.2f;
		}

		if (checkd1 == 1.1f && checkd2 == 1.1f)
		{
			sprite.setRotation(315);
		}
		else if (checkd1 == 1.2f && checkd2 == 1.1f)
		{
			sprite.setRotation(45);
		}
		else if (checkd2 == 1.2f && checkd1 == 1.1f)
		{
			sprite.setRotation(225);
		}
		else if (checkd2 == 1.2f && checkd1 == 1.2f)
		{
			sprite.setRotation(135);
		}

	}

};
