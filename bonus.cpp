#include "bonus.h"
#include "const.h"
Bonus::Bonus() {
	texture.loadFromFile(IMAGES_FOLDER + PILL_1);
	sprite.setTexture(texture);
	spawn();
}
void Bonus::update() {
	sprite.move(0,6); 
	sf::FloatRect g_bound = sprite.getGlobalBounds();
	if (sprite.getPosition().x < 0 - g_bound.width ||
		sprite.getPosition().x > WINDOW_WIDTH ||
		sprite.getPosition().y > WINDOW_HEIGHT)
	{
		spawn();
	}
}
void Bonus::draw(sf::RenderWindow& window) { window.draw(sprite); }
void Bonus::spawn() {
		sf::FloatRect g_bound = sprite.getGlobalBounds();
		float x = rand() % 500 + 130;
		float y = rand() % (static_cast<size_t>(WINDOW_HEIGHT)) - WINDOW_HEIGHT - 100;
		sprite.setPosition(x, y);
	}
sf::FloatRect Bonus::getHitBox() { return sprite.getGlobalBounds(); }
sf::Vector2f Bonus::getPosition() { return sprite.getPosition(); }