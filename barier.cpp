#include "barier.h"
#include"const.h"
std::string Barier::barier_file_names[] = {
		SHIP_FILE_NAME_1,
		SHIP_FILE_NAME_2,
		SHIP_FILE_NAME_3,
		SHIP_FILE_NAME_4,
		SHIP_FILE_NAME_5
};
Barier::Barier() {
	size_t num = rand() % BARIER_TYPE;
	texture.loadFromFile(IMAGES_FOLDER + barier_file_names[num]);
	sprite.setTexture(texture);
	spawn();
}
void Barier::update() {
	sprite.move(speedx, speedy);
	sf::FloatRect g_bound = sprite.getGlobalBounds();
	if (sprite.getPosition().x < 0 - g_bound.width ||
		sprite.getPosition().x > WINDOW_WIDTH ||
		sprite.getPosition().y > WINDOW_HEIGHT)
	{
		spawn();
	}
}
void Barier::draw(sf::RenderWindow& window) { window.draw(sprite); }
void Barier::spawn() {
	sf::FloatRect g_bound = sprite.getGlobalBounds();
	float x = rand() % 500 + 130;
	float y = rand() % (static_cast<size_t>(WINDOW_HEIGHT)) - WINDOW_HEIGHT-100;
	sprite.setPosition(x, y);
	speedx = 0;
	speedy = 6;
}
sf::FloatRect Barier::getHitBox() { return sprite.getGlobalBounds(); }
sf::Vector2f Barier::getPosition() { return sprite.getPosition(); }