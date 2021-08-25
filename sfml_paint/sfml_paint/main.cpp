#include "PaintToolManager.h"

int windowXSize = 1024;
int windowYSize = 720;

sf::Color currentPenColor;

PaintToolManager* PaintToolManager::instance = 0;
PaintToolManager* ptm = PaintToolManager::getInstance();

int main() {

	sf::RenderWindow window(sf::VideoMode(windowXSize, windowYSize), "SFML works!");

	sf::Vector2i currentMousePos;
	sf::Event event;
	while (window.isOpen())
	{
		currentMousePos.x = sf::Mouse::getPosition(window).x;
		currentMousePos.y = sf::Mouse::getPosition(window).y;


		//wait for close event to close window
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if ( (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::W) ) {
				ptm->increaseBrushSize();
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::S)) {
				ptm->decreaseBrushSize();
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::D)) {
				ptm->increaseBrushType();
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::A)) {
				ptm->decreaseBrushType();
			}
		}




		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			ptm->OpenColorDialog(&window, &currentPenColor);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			ptm->brushDraw(currentMousePos, &currentPenColor);

		}
		

		window.clear();
		ptm->drawAll(&window);
		window.display();

	}


}