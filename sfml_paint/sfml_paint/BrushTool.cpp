#include "BrushTool.h"
#include <iostream>

BrushTool::BrushTool() {
	if (!brushImage.loadFromFile("images/brush_small.bmp")) {
		std::cout << "image failed to load" << std::endl;
	}
}

void BrushTool::draw(sf::Image* canvas, sf::Vector2i mousePos, sf::Color* currentPenColor) {
	int sizeX = canvas->getSize().x;
	int sizeY = canvas->getSize().y;
	int row = 0;
	int col = 0;
	for (int i = mousePos.x - 5; i < mousePos.x + 5; i++) {

		for (int j = mousePos.y - 5; j < mousePos.y + 5; j++) {

			if ((i < 0 || i > sizeX || j < 0 || j > sizeY) == false) {

				if (brushImage.getPixel(row, col).r == 0) {
					canvas->setPixel(i, j, *currentPenColor);
				}
			}
			col = (col + 1) % 10;
		}

		row++;
	}

}