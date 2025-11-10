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

World* LoadWorld(std::string path)
{
	return nullptr;
}

World* Create()
{
	char in;
	std::cout << "(F)ixed, (I)nfinite, (R)epeatingFixed" << std::endl;
	std::cin >> in;
	World* world = nullptr;
	switch (in)
	{
	case 'F':
	{
		int width;
		int height;
		std::cout << "Width: " << std::endl;
		std::cin >> width;
		std::cout << "Height: " << std::endl;
		std::cin >> height;

		std::cout << "(S)eed or (F)ill" << std::endl;
		std::cin >> in;
		int answer = 0;
		std::cout << in << ": ";
		std::cin >> answer;
		switch (in)
		{
		case 'S':
			world = new FixedWorld(width, height, answer);
			break;
		case 'F':
			world = new FixedWorld(width, height, (char)answer);
			break;
		}
		break;
	}
	case 'R':
	{
		int width;
		int height;
		std::cout << "Width: " << std::endl;
		std::cin >> width;
		std::cout << "Height: " << std::endl;
		std::cin >> height;

		std::cout << "(S)eed or (F)ill" << std::endl;
		std::cin >> in;
		int answer = 0;
		std::cout << in << ": ";
		std::cin >> answer;
		switch (in)
		{
		case 'S':
			world = new RepeatingFixedWorld(width, height, answer);
			break;
		case 'F':
			world = new RepeatingFixedWorld(width, height, (char)answer);
			break;
		}
		break;
	}
	case 'I':
	{
		std::cout << "Seed 1: ";
		double answer = 0;
		std::cin >> answer;
		std::cout << "Seed 2: ";
		double answer2 = 0;
		std::cin >> answer2;
		world = new InfiniteWorld(Vector<double>(answer, answer2));
		break;
	}
	}
	return world;
}

void LoadGame(std::string path, Canvas& canvas, InputHandler& inputHandler, GamesEngineeringBase::Window& window)
{
	int accumulator = 0;
	float timer = 0;
	int fps = 0;

	TimedSurvivalManager gameManager{ canvas };

	gameManager.Load(path);

	bool running = true;
	inputHandler.Update();

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
			gameManager.Save("Saves/temp.dat");
		}
		else if (inputHandler.KeyHeld('L'))
		{
			gameManager.Load("Saves/temp.dat");
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
}

void Play(World* world, float duration, Canvas& canvas, InputHandler& inputHandler, GamesEngineeringBase::Window& window)
{
	int accumulator = 0;
	float timer = 0;
	int fps = 0;

	TimedSurvivalManager gameManager{ canvas };

	gameManager.Setup(world, duration);

	bool running = true;
	inputHandler.Update();

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
			gameManager.Save("Saves/tempsave.dat");
		}
		else if (inputHandler.KeyHeld('L'))
		{
			gameManager.Load("Saves/tempsave.dat");
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
}

void MainMenu(Canvas& canvas, InputHandler& input, GamesEngineeringBase::Window& window)
{
	char in;
	std::cout << "(P)lay, (L)oad Game, (E)dit" << std::endl;
	std::cin >> in;

	World* world = nullptr;

	if (in != 'L')
	{
		std::cout << "(L)oad, (C)reate";
		char loadOrC;
		std::cin >> loadOrC;

		switch (loadOrC)
		{
		case 'C':
			world = Create();
			break;
		case 'L':
		{
			std::string path;
			std::cout << "Path: Saves/";
			std::cin >> path;
			switch (in)
			{
			case 'E':
			{
				world = LoadWorld("Saves/" + path);
				break;
			}
			case 'P':
			{
				char type;
				std::cout << "(R)epeating, (F)ixed";
				std::cin >> type;
				FixedWorld* w;
				if (type == 'R')
					w = new RepeatingFixedWorld();
				else
					w = new FixedWorld();
				w->LoadMap(path);
				world = w;
				break;
			}
			}
		}
		}
	}

	switch (in)
	{
	case 'P':
		float duration;
		std::cout << "Runtime: ";
		std::cin >> duration;
		Play(world, duration, canvas, input, window);
		break;
	case 'E':
		//Edit(world);
		break;
	case 'L':
	{
		std::string path;
		std::cout << "Path: Saves/";
		std::cin >> path;
		LoadGame("Saves/" + path, canvas, input, window);
		break;
	}
	}
}

int main() {
	GamesEngineeringBase::Window window;
	window.create(1024, 768, "Game");

	InputHandler inputHandler = InputHandler(window);
#ifdef enableDrawOutsideBounds
	Canvas canvas = Canvas(window, window.getWidth() / 2, window.getHeight() / 2, window.getWidth() / 4, window.getHeight() / 4);
#else
	Canvas canvas = Canvas(window, window.getWidth(), window.getHeight(), 0, 0);
#endif

	Tile::LoadTiles();

	bool running = true;
	while (running)
	{
		MainMenu(canvas, inputHandler, window);
	}

	/*
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

	//UNCOMMENT FOR NORMAL GAME. P AND L TO SAVE & LOAD
	TimedSurvivalManager gameManager{ canvas };

	//CHANGE 120 TO DESIRED GAME DURATION
	gameManager.Setup(world, 120);

	//UNCOMMENT FOR STRESS TESTER. T AND G TO MODIFY SPRITE COUNT

	//StressTester gameManager{ canvas };
	//gameManager.Setup(world);

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
	*/
	return 0;
}