#include "GamesEngineeringBase.h"
#include "FixedWorld.h"
#include "InfiniteWorld.h"
#include "RepeatingFixedWorld.h"
#include "Camera.h"
#include "InputHandler.h"
#include "FollowCamera.h"
#include <iostream>
#include "TimedSurvivalManager.h"
#include "StressTester.h"

#include "Button.h"

int main() {
	GamesEngineeringBase::Window window;
	window.create(1024, 768, "Game");
	bool running = true;

	Tile::LoadTiles();

	//UNCOMMENT FOR INFINITE WORLD

	InfiniteWorld* world = new InfiniteWorld({ 384497, 1235 });

	//UNCOMMENT FOR FINITE WORLD

	//FixedWorld* world = new FixedWorld(50, 50, 123);
	//world->SaveWorld("Saves/World1.dat");

	//UNCOMMENT FOR FINITE WORLD WITH FIXED FILL

	//FixedWorld* world = new FixedWorld(50, 50, (char)0);
	//world->SaveWorld("Saves/World1.dat");

	//UNCOMMENT FOR REPEATING FINITE WORLD

	//RepeatingFixedWorld* world = new RepeatingFixedWorld(50, 50, 123);
	//world->SaveWorld("Saves/World1.dat");

	//UNCOMMENT FOR REPEATING FINITE WORLD WITH FIXED FILL

	//RepeatingFixedWorld* world = new RepeatingFixedWorld(50, 50, (char)0);
	//world->SaveWorld("Saves/World1.dat");

	InputHandler inputHandler = InputHandler(window);
#ifdef enableDrawOutsideBounds
	Canvas canvas = Canvas(window, window.getWidth() / 2, window.getHeight() / 2, window.getWidth() / 4, window.getHeight() / 4);
#else
	Canvas canvas = Canvas(window, window.getWidth(), window.getHeight(), 0, 0);
#endif

	int accumulator = 0;
	float timer = 0;
	int fps = 0;

	TimedSurvivalManager gameManager{ canvas };

	//CHANGE 120 TO DESIRED GAME DURATION
	gameManager.Setup(world, 120);

	while (running)
	{
		// Check for input (key presses or window events)
		inputHandler.Update();

		// If the Escape key is pressed, exit the loop and close the window
		if (inputHandler.KeyHeld(VK_ESCAPE))
		{
			running = false;
			break; // Exits the game loop
		}

		if (inputHandler.KeyHeld('P'))
		{
			gameManager.Save("Saves/test.dat");
		}
		else if (inputHandler.KeyHeld('L'))
		{
			gameManager.Load("Saves/test.dat");
		}

		gameManager.RunTick(inputHandler);
		gameManager.Draw(inputHandler);

		accumulator += 1;
		timer += inputHandler.GetDT();

		if (timer > 1)
		{
			fps = round(accumulator / timer);
			accumulator = 0;
			timer = 0;
		}
		
		canvas.DrawFont(std::to_string(fps), { 0, 0 });
		window.present();
	}

	//Button start = Button(std::string("Start"), (Vector<int>)canvas.GetSize() / 2, Vector<int>(300, 60), Colour(150, 150, 150), Colour(50, 50, 50), UIElement::Centre);
	//Button editor = Button(std::string("Level Editor"), (Vector<int>)canvas.GetSize() / 2, Vector<int>(300, 60), Colour(150, 150, 150), Colour(50, 50, 50), UIElement::Centre);

	//while (true)
	//{
	//	inputHandler.Update();
	//	start.Update(inputHandler, canvas);
	//	canvas.clear();
	//	start.Draw(canvas);
	//	window.present();
	//}

	return 0;
}