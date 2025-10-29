#include "GamesEngineeringBase.h"
#include "TestWorld.cpp"
#include "Camera.h"
#include "InputHandler.h"
#include "FollowCamera.h"
#include <iostream>

int main() {
	GamesEngineeringBase::Window window;
	window.create(1024, 768, "Game");
	bool running = true;

	World* world = new TestWorld();
	InputHandler inputHandler = InputHandler(window);
	Canvas canvas = Canvas(window, window.getWidth(), window.getHeight(), 0, 0);
	Camera camera = Camera(world, canvas, new FollowCamera(world->GetPlayer()));

	float accumulator = 0;
	int frames = 0;

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

		accumulator += inputHandler.GetDT();
		frames++;

		if (accumulator >= 1)
		{
			std::cout << frames << std::endl;
			frames = 0;
			accumulator = 0;
		}

		if (inputHandler.MouseDown(GamesEngineeringBase::MouseLeft))
		{
			camera.ChangeZoom(0.25);
		}
		else if (inputHandler.MouseDown(GamesEngineeringBase::MouseRight))
		{
			camera.ChangeZoom(-0.25);
		}

		world->Update(inputHandler);
		camera.UpdatePosition(inputHandler);
		camera.Redraw();
		window.present();
	}
	return 0;
}