#include "GamesEngineeringBase.h"
#include "TestWorld.cpp"
#include "Camera.h"
#include <iostream>

int main() {
	GamesEngineeringBase::Window window;
	window.create(1024, 768, "Game");
	bool running = true;
	bool debounce = false;

	GamesEngineeringBase::Timer timer;

	World* world = new TestWorld();
	Canvas canvas = Canvas(window, window.getWidth() / 2, window.getHeight() / 2, window.getWidth() / 4, window.getHeight() / 4);
	Camera camera = Camera(world, canvas);

	float accumulator = 0;
	int frames = 0;

	while (running)
	{
		// Check for input (key presses or window events)
		window.checkInput();

		// If the Escape key is pressed, exit the loop and close the window
		if (window.keyPressed(VK_ESCAPE))
		{
			running = false;
			break; // Exits the game loop
		}

		float dt = timer.dt();
		accumulator += dt;
		frames++;

		if (accumulator >= 1)
		{
			std::cout << frames << std::endl;
			frames = 0;
			accumulator = 0;
		}

		Vector<float> movement = Vector<float>();

		if (window.keyPressed('W'))
		{
			movement.y -= 1;
		}
		if (window.keyPressed('A'))
		{
			movement.x -= 1;
		}
		if (window.keyPressed('S'))
		{
			movement.y += 1;
		}
		if (window.keyPressed('D'))
		{
			movement.x += 1;
		}

		if (movement.x != 0 || movement.y != 0)
		{
			movement *= dt * (window.keyPressed(VK_SHIFT) ? 2000 : 100);
			if (movement.x != 0 && movement.y != 0)
				movement *= 0.7071;

			camera.Move(movement);
		}

		if (!debounce)
		{
			if (window.mouseButtonPressed(GamesEngineeringBase::MouseLeft))
			{
				camera.ChangeZoom(0.25);
				debounce = true;
			}
			else if (window.mouseButtonPressed(GamesEngineeringBase::MouseRight))
			{
				camera.ChangeZoom(-0.25);
				debounce = true;
			}
		}
		else
		{
			if (!window.mouseButtonPressed(GamesEngineeringBase::MouseLeft)
				&& !window.mouseButtonPressed(GamesEngineeringBase::MouseRight))
			{
				debounce = false;
			}
		}

		camera.Redraw();
		window.present();
	}
	return 0;
}