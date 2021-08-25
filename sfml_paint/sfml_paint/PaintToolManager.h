//-- library includes --/
#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <wingdi.h>
#include "resource.h"

//-- class includes --//
#include "ColorChooserDialog.h"
#include "BrushTool.h"

class PaintToolManager
{

private:
	PaintToolManager();
	void createPointerTextures();
	void updatePointerSprite(BrushType);

	int windowSizeX = 1024;
	int windowSizeY = 720;
	sf::Image* canvas;
	sf::Texture canvasTexture;
	sf::Sprite canvasSprite;
	sf::RenderWindow window;
	BrushTool* brush;
	ColorChooserDialog* colorDialog;

	sf::Texture brushTexture;
	sf::Texture spraycanTexture;
	sf::Texture eraserTexture;
	sf::Sprite currentPointerSprite;

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
	void moveMousePointer(sf::Vector2i);
	void brushDraw(sf::Vector2i, sf::Color*);
	void changeBrushType(BrushType);
	void changeBrushSize(BrushSize);
	void increaseBrushSize();
	void decreaseBrushSize();
	void increaseBrushType();
	void decreaseBrushType();

	void OpenColorDialog(sf::Window*, sf::Color*);



};

