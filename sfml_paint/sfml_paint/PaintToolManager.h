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

	int brushTypeIndex = 0;
	int brushSizeIndex = 0;
	BrushSize sizes[4] = { BrushSize::SMALL, BrushSize::MEDIUM, BrushSize::LARGE, BrushSize::XLARGE };
	BrushType types[3] = { BrushType::BRUSH, BrushType::SPRAYCAN, BrushType::ERASER };

	static PaintToolManager* instance;
	
	
public:
	static PaintToolManager* getInstance() {
		if (!instance)
			instance = new PaintToolManager;
		return instance;
	}

	void drawAll(sf::RenderWindow*);
	void brushDraw(sf::Vector2i, sf::Color*);
	void changeBrushType(BrushType);
	void changeBrushSize(BrushSize);
	void increaseBrushSize();
	void decreaseBrushSize();
	void increaseBrushType();
	void decreaseBrushType();

	void OpenColorDialog(sf::Window*, sf::Color*);



};

