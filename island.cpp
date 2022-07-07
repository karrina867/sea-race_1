#include"island.h"
#include"const.h"
Islands::Islands() {
	texture.loadFromFile(IMAGES_FOLDER + ISLAND_1);
	sprite.setTexture(texture);
	spawn();
}
void Islands::update() {
	sprite.move(speedx, speedy);
	sf::FloatRect g_bound = sprite.getGlobalBounds();
	if (sprite.getPosition().x < 0 - g_bound.width ||
		sprite.getPosition().x > WINDOW_WIDTH ||
		sprite.getPosition().y > WINDOW_HEIGHT)
	{
		spawn();
	}
}
void Islands::draw(sf::RenderWindow& window) { window.draw(sprite); }
void Islands::spawn() {
	sf::FloatRect g_bound = sprite.getGlobalBounds();
	float x = rand() % (static_cast<size_t>(1));
	float y = rand() % (static_cast<size_t>(WINDOW_HEIGHT)) - WINDOW_HEIGHT - 200;
	sprite.setPosition(x, y);
	speedx = 0;
	speedy = 4;
}
sf::FloatRect Islands::getHitBox() { return sprite.getGlobalBounds(); }
sf::Vector2f Islands::getPosition() { return sprite.getPosition(); }