#include <SFML/Graphics.hpp>
#include <windows.h>
#include <wingdi.h>
#include <iostream>


class BrushTool
{
public:
	BrushTool();
	void draw(sf::Image* canvas, sf::Vector2i mousePos, sf::Color* currentPenColor);

private:
	sf::Image brushImage;
	std::string filename;
};

