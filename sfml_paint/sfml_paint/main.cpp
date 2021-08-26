#include "PaintToolManager.h"

int windowXSize = 1024;
int windowYSize = 720;

sf::Color currentPenColor;

PaintToolManager* PaintToolManager::instance = 0;
PaintToolManager* ptm = PaintToolManager::getInstance();

HINSTANCE g_hInstance;

sf::RenderWindow window;

std::vector<sf::Shape*> shapes;

int circRadius = 0;
int rectWidth = 0;
int rectHeight = 0;

enum class PaintMode {BRUSH, CIRCLE, RECTANGLE};

PaintMode mode = PaintMode::BRUSH;




LRESULT CALLBACK OnEvent(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam)
{
	// Handle is the current window handle, Message is the contents of the event,
	// WParam and LParam return different info based on the Message that is sent. 

	switch (Message) // switch based on that message. 
	{
	case WM_COMMAND: // there's a bunch of different case WM_ options, feel free to use em.
	{
		int wmId = LOWORD(WParam); // wmId is basically a wide message id - just for clarity. 
		switch (wmId)
		{
		case ID_MAIN_EXIT: // if i click the exit button on the toolbar, under main?
			PostQuitMessage(0);
			break;
		case ID_EDIT_COLORCHOOSER:
			ptm->OpenColorDialog(&window, &currentPenColor);
		
		case ID_BRUSHTYPES_STANDARDBRUSH:
			ptm->changeBrushType(BrushType::BRUSH);
			mode = PaintMode::BRUSH;
			break;
		case ID_BRUSHTYPES_SPRAYCAN:
			ptm->changeBrushType(BrushType::SPRAYCAN);
			mode = PaintMode::BRUSH;
			break;
		case ID_BRUSHTYPES_ERASER:
			ptm->changeBrushType(BrushType::ERASER);
			mode = PaintMode::BRUSH;
			break;
		case ID_BRUSHSIZE_SMALL:
			ptm->changeBrushSize(BrushSize::SMALL);
			mode = PaintMode::BRUSH;
			break;
		case ID_BRUSHSIZE_MEDIUM:
			ptm->changeBrushSize(BrushSize::MEDIUM);
			mode = PaintMode::BRUSH;
			break;
		case ID_BRUSHSIZE_LARGE:
			ptm->changeBrushSize(BrushSize::LARGE);
			mode = PaintMode::BRUSH;
			break;
		case ID_BRUSHSIZE_EXTRALARGE:
			ptm->changeBrushSize(BrushSize::XLARGE);
			mode = PaintMode::BRUSH;
			break;

		case ID_CIRCLE_SMALL:
			ptm->changeBrushType(BrushType::POLYGON);
			circRadius = 10;
			mode = PaintMode::CIRCLE;
			break;
		case ID_CIRCLE_MEDIUM:
			ptm->changeBrushType(BrushType::POLYGON);
			circRadius = 20;
			mode = PaintMode::CIRCLE;
			break;
		case ID_CIRCLE_LARGE:
			ptm->changeBrushType(BrushType::POLYGON);
			circRadius = 40;
			mode = PaintMode::CIRCLE;
			break;
		case ID_CIRCLE_EXTRALARGE:
			ptm->changeBrushType(BrushType::POLYGON);
			circRadius = 65;
			mode = PaintMode::CIRCLE;
			break;
		case ID_RECTANGLE_SMALL:
			ptm->changeBrushType(BrushType::POLYGON);
			rectWidth = 20;
			rectHeight = 10;
			mode = PaintMode::RECTANGLE;
			break;
		case ID_RECTANGLE_MEDIUM:
			ptm->changeBrushType(BrushType::POLYGON);
			rectWidth = 30;
			rectHeight = 10;
			mode = PaintMode::RECTANGLE;
			break;
		case ID_RECTANGLE_LARGE:
			ptm->changeBrushType(BrushType::POLYGON);
			rectWidth = 40;
			rectHeight = 20;
			mode = PaintMode::RECTANGLE;
			break;
		case ID_RECTANGLE_EXTRALARGE:
			ptm->changeBrushType(BrushType::POLYGON);
			rectWidth = 60;
			rectHeight = 30;
			mode = PaintMode::RECTANGLE;
			break;


		default: // need the default here otherwise it breaks. 
			return DefWindowProc(Handle, Message, WParam, LParam); // default: do nothing basically 
		}
	}
	break; // need to avoid the infinite loop

	// Quit when we close the main window
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	}

	return DefWindowProc(Handle, Message, WParam, LParam); // always do default behaviour. 
}






int main() {
	WNDCLASS WindowClass; // creating the windowclass variable - 
	WindowClass.style = 0; // style options aren't needed
	/*
		setting the wndproc here is important - this lets us listen for
		toolbar events, so it's the most important thing here.
	*/
	WindowClass.lpfnWndProc = &OnEvent;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;

	// handle to the instance is needed as well here. 
	WindowClass.hInstance = g_hInstance;
	WindowClass.hIcon = NULL; // we can swap this later but don't really need a new icon. 
	WindowClass.hCursor = 0; // we can create a new cursor with this system, but currently we don't need it. 

	// v that selects the background of the window, which isn't really needed because we're going to 
	// nest an sfml window within. 
	WindowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);

	// attach this menu - you can find the name in the resource.h file. If you create one in your own 
	// project, the prefix for that will likely be IDR_MENU1 as well.
	WindowClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	// the name of the window. The L in front of this is necessary, and is a weird win32 formatting thing. 
	WindowClass.lpszClassName = L"SFML and Win32 Toolbar Example Project";

	// make sure that this is called. 
	RegisterClass(&WindowClass);

	/* the 0,0 is the origin (top left), and the 800,600 is the max width / height of the window. */
	HWND Window = CreateWindow(WindowClass.lpszClassName, L"SFML with Toolbars", WS_OVERLAPPEDWINDOW  | WS_VISIBLE | WS_THICKFRAME, 0, 0, windowXSize, windowYSize, NULL, NULL, g_hInstance, NULL);
	// a way to improve the above and below code for createwindow is to replace the 800 and 600 values with g_WindowWidth and g_WindowHeight. 
	// If you then change the window height and width, you should be good to go. 

	// Let's create an SFML view
	// NOTE - the stuff below is for a dual-screen kinda setup, which interferes with the event layer of SFML and basically stops input from working with the way it was set up.
	// Don't bother with this at this stage.  
	//DWORD Style = WS_CHILD | WS_VISIBLE; //| WS_CLIPSIBLINGS; - add the siblings option to complete the dual-screen operation. 
	//HWND  View1 = CreateWindow(L"STATIC", NULL, Style, 0, 0, 800, 600, Window, NULL, g_hInstance, NULL); 
	// this allows you to create a second screen, but i have commented this as it isn't useful. 
	//HWND  View2 = CreateWindow(L"STATIC", NULL, Style, 400, 100, 300, 400, Window, NULL, g_hInstance, NULL);

	sf::RenderWindow window(Window); // we're using pseudo-views for this, because that's the best way to create a sub-region for the window. 
	//sf::RenderWindow SFMLView2(View2);

	MSG Message; // an MSG is a structure that holds data relevant to things that have happened to the window, such as a toolbar click 
				//or you hitting the X button to close the window.

	Message.message = ~WM_QUIT; // while the window isnt closed:


	//sf::RenderWindow window(sf::VideoMode(windowXSize, windowYSize), "SFML works!");


	sf::Vector2i currentMousePos;
	sf::Event event;

	while (Message.message != WM_QUIT)
	{
		ptm->moveMousePointer(sf::Mouse::getPosition(window));

		currentMousePos.x = sf::Mouse::getPosition(window).x;
		currentMousePos.y = sf::Mouse::getPosition(window).y;


		//wait for close event to close window
		event = *new sf::Event();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
				ptm->updateCanvasSize(event.size.width, event.size.height);
			}

			if (mode == PaintMode::BRUSH) {
				//mouse pointer paint
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					ptm->brushDraw(currentMousePos, &currentPenColor);
				}
			}
			else if (mode == PaintMode::CIRCLE) {
				if ((event.type == sf::Event::MouseButtonPressed) && (event.key.code == sf::Mouse::Button::Left)) {
					
						sf::CircleShape* circ = new sf::CircleShape();
						circ->setRadius(circRadius);
						circ->setOrigin(circ->getLocalBounds().width / 2, circ->getLocalBounds().height / 2);
						circ->setPosition(currentMousePos.x, currentMousePos.y);
						circ->setFillColor(currentPenColor);

						shapes.push_back(circ);
					
				}
			}
			else if (mode == PaintMode::RECTANGLE) {
				if ((event.type == sf::Event::MouseButtonPressed) && (event.key.code == sf::Mouse::Button::Left)) {
					sf::RectangleShape* rect = new sf::RectangleShape();
					rect->setSize(sf::Vector2f(rectWidth, rectHeight));
					rect->setOrigin(rect->getLocalBounds().width / 2, rect->getLocalBounds().height / 2);
					rect->setPosition(currentMousePos.x, currentMousePos.y);
					rect->setFillColor(currentPenColor);

					shapes.push_back(rect);

				}
			}
			

		}

		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			// If a message was waiting in the message queue, process it
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{

			window.clear();
			ptm->drawAll(&window);
			for (int i = 0; i < shapes.size(); i++) {
				window.draw(*shapes[i]);
			};
			window.display();


		}




	}


}