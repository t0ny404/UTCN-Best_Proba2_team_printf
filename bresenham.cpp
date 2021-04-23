#include "bresenham.h"
#include "math.h"

void plot_points(int x, int centerX, int y, int centerY, SDL_Renderer* renderer)
{
	SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
	SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
	SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
	SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
	SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
	SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
	SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
	SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
}

//Draws a new raster circle using Bresenham's algorithm
void BresenhamDraw(BresenhamCircle circle, SDL_Renderer* renderer) {
	int R = circle.radius;
	int currentY = R;
	float d = 1. / 4. - R;
	
	//Go only one eighth of a circle
	for (int currentX = 0; currentX <= ceil(R / sqrt(2)); currentX++) {
		plot_points(currentX, circle.centerX, currentY, circle.centerY, renderer);
		d += 2 * currentX + 1;
		if (d > 0) {
		d += 2 - 2 * currentY;
		currentY--;
		}
	}
}