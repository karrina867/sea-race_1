#pragma once
#include "SFML/Graphics.hpp"
class Bonus {
public:
	Bonus();
	void update();
	void draw(sf::RenderWindow&);
	void spawn();
	sf::FloatRect getHitBox();
	sf::Vector2f getPosition();
private:
	sf::Texture texture;
	sf::Sprite sprite;
	float speedx, speedy;
};