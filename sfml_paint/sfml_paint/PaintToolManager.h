//-- library includes --/
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <wingdi.h>
#include <iostream>

//-- class includes --//
#include "ColorChooserDialog.h"
#include "BrushTool.h"

class PaintToolManager
{

private:
	PaintToolManager();

	int windowSizeX = 1024;
	int windowSizeY = 720;
	sf::Image* canvas;
	sf::Texture canvasTexture;
	sf::Sprite canvasSprite;
	sf::RenderWindow window;
	BrushTool* brush;
	ColorChooserDialog* colorDialog;

	static PaintToolManager* instance;
	
	
public:
	static PaintToolManager* getInstance() {
		if (!instance)
			instance = new PaintToolManager;
		return instance;
	}

	void drawAll(sf::RenderWindow* window);
	void brushDraw(sf::Vector2i _mousePos, sf::Color* _currentColor);
	void OpenColorDialog(sf::Window* _windowRef, sf::Color* _colorRef);



};

