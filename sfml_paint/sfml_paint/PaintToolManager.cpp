#include "PaintToolManager.h"

PaintToolManager::PaintToolManager() {

	brush = new BrushTool();
	colorDialog = new ColorChooserDialog();

	canvas = new sf::Image();
	canvas->create(windowSizeX, windowSizeY, sf::Color::White);

	canvasTexture.loadFromImage(*canvas);

	canvasSprite.setTexture(canvasTexture);
	canvasSprite.setOrigin(windowSizeX / 2.0f, windowSizeY / 2.0f);
	canvasSprite.setPosition(windowSizeX / 2.0f, windowSizeY / 2.0f);
	canvasSprite.setColor(sf::Color::White);


}	


void PaintToolManager::OpenColorDialog(sf::Window* _windowRef, sf::Color* _colorRef) {
	colorDialog->Open(_windowRef,_colorRef);
}

void PaintToolManager::drawAll(sf::RenderWindow* window) {
	window->draw(canvasSprite);
}


void PaintToolManager::brushDraw(sf::Vector2i _mousePos, sf::Color* _currentColor) {
	brush->draw(canvas, _mousePos, _currentColor);
	canvasTexture.loadFromImage(*canvas);
}

