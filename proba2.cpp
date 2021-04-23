// EGC_Bresenham.cpp : Defines the entry point for the console application.
//
//  Created by CGIS on 13/04/2020.
//  Copyright © 2020 CGIS. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <thread>
#include "include/SDL.h"
#include "bresenham.h"

using namespace std;

//define window dimensions
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

//The window
SDL_Window *window = NULL;
//The window renderer
SDL_Renderer* renderer = NULL;
SDL_Event currentEvent;

bool quit = false;
int mouseX, mouseY;
bool pressed = false;

BresenhamCircle myCircle;

int lineY, lineX1, lineX2;

bool initWindow()
{
	bool success = true;

	myCircle.centerX = 270;
	myCircle.centerY = 230;
	myCircle.radius = 50;

	lineX1 = 0;
	lineX2 = 650;
	lineY = 450;

	//Try to initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL initialization failed" << std::endl;
		success = false;
	}
	else {
		//Try to create the window
		window = SDL_CreateWindow("Proba2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

		if (window == NULL)
		{
			std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}
	return success;
}

void destroyWindow()
{
	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	//Quit SDL
	SDL_Quit();
}

void gravity() {
	//while (!quit) {
		//if (!pressed) {
			float time = 0;
			float speed = 0;
			int y = myCircle.centerY;
			while (y + myCircle.radius < 450) {
				speed += 0.098 * time;
				y += floor(speed * time + 0.098 * time * time / 2);
				myCircle.centerY = y;
				time += 1e-4;
				//chrono::milliseconds timespan(1);
				//this_thread::sleep_for(timespan);
			}
		//}
	//}
}

void handleMouseEvents()
{
	//Mouse event -> pressed button
	if (currentEvent.type == SDL_MOUSEBUTTONDOWN)
	{
		if (currentEvent.button.button == SDL_BUTTON_LEFT)
		{
			SDL_GetMouseState(&mouseX, &mouseY);
			myCircle.centerX = mouseX;
			myCircle.centerY = mouseY;
		}
	}

	//Mouse event -> mouse movement
	if (currentEvent.type == SDL_MOUSEMOTION)
	{
		if (currentEvent.button.button & SDL_BUTTON_LMASK)
		{
			SDL_GetMouseState(&mouseX, &mouseY);
			if (mouseX > myCircle.centerX - myCircle.radius && mouseX < myCircle.centerX + myCircle.radius &&
				mouseY > myCircle.centerY - myCircle.radius && mouseY < myCircle.centerY + myCircle.radius &&
				mouseY < lineY - myCircle.radius && mouseX < lineX2 - myCircle.radius && mouseX > lineX1 + myCircle.radius && mouseY > myCircle.radius) {
				myCircle.centerX = mouseX;
				myCircle.centerY = mouseY;
			}
			//pressed = true;
		}
		else gravity();// pressed = false;
	}
}

void app() {	
	if (!initWindow())
	{
		std::cout << "Failed to initialize" << std::endl;
		return;
	}

	while (!quit) {
		//Handle events on queue
		while (SDL_PollEvent(&currentEvent) != 0)
		{
			//User requests quit
			if (currentEvent.type == SDL_QUIT)
			{
				quit = true;
			}

			handleMouseEvents();

			//Clear screen
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(renderer);

			//Draw Bresenham circle
			SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0x00);

			BresenhamDraw(myCircle, renderer);
			SDL_RenderDrawLine(renderer, lineX1, lineY, lineX2, lineY);

			//Update screen
			SDL_RenderPresent(renderer);
		}
	}
	destroyWindow();
}

int main(int argc, char * argv[]) {


	//thread th(gravity);
	//thread th0(app);

	//th0.join();
	//th.join();
	app();
	gravity();

	return 0;
}