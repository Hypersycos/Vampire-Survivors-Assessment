#include "GamesEngineeringBase.h"
#include "World.cpp"
#include "Camera.cpp"
#include <iostream>

int main() {
	GamesEngineeringBase::Window canvas;
	canvas.create(1024, 768, "Game");
	bool running = true;

	GamesEngineeringBase::Timer timer;

	World* world = new TestWorld();
	Camera camera = Camera(world, canvas);

	while (running)
	{
		// Check for input (key presses or window events)
		canvas.checkInput();

		// If the Escape key is pressed, exit the loop and close the window
		if (canvas.keyPressed(VK_ESCAPE))
		{
			running = false;
			break; // Exits the game loop
		}

		float dt = timer.dt();

		Vector<float> movement = Vector<float>();

		if (canvas.keyPressed('W'))
		{
			movement.y -= 1;
		}
		if (canvas.keyPressed('A'))
		{
			movement.x -= 1;
		}
		if (canvas.keyPressed('S'))
		{
			movement.y += 1;
		}
		if (canvas.keyPressed('D'))
		{
			movement.x += 1;
		}

		if (movement.x != 0 || movement.y != 0)
		{
			movement *= 500 * dt;
			if (movement.x != 0 && movement.y != 0)
				movement *= 0.7071;

			camera.Move(movement);
		}

		camera.Clear();
		canvas.present();
	}
	return 0;
}