#ifndef PARTICLEENGINE_H
#define PARTICLEENGINE_H

#include "Player.h"

#include <vector>
using namespace std;

//Number of particles to render.
const int NUMBER_OF_PARTICLES = 10;
//Pixel limit X value of particles
const int PARTICLE_LIMIT_X = 0;
//Pixel limit Y value of particles.
const int PARTICLE_LIMIT_Y = 0;
//Random value of particles movement.
const int PARTICLE_LIMIT_RAND = 1;
//Frames of life per particle.
const int FRAME_LIMIT = 10;
//How often particles flicker per frame.
const int FLICKER_PER_FRAME = 7;

//Contains info of a particles location.
struct Particle
{
	//X position.
	int x;
	//Y position.
	int y;
	//xVelocity of the particle.
	int xVel;
	//yVelocity of the particle.
	int yVel;
	//How many frames the particle is alive for.
	int frame;
	//Type or color of the particle.
	SDL_Surface* type;
};

class ParticleEngine
{
public:
	//Default constructor.
	ParticleEngine();
	//Intializes the particleEngine.
	//@param int x - x value to begin.
	//@param int y - y value to begin.
	//@return bool - true if successful.
	bool Initialize(int x, int y);
	void SetX(int x){goalX = x;};
	void SetY(int y){goalY = y;};
	//UpdateMazeGoal - updates the particle engine if it were the gaol on the maze.
	//@param SDL_Surface* - pointer to the screen.
	void UpdateMazeGoal(SDL_Surface* screen);
	//Updates the particle Engine.
	//@param SDL_Surface* - screen to render to.
	//@param int - x value of deviation.
	//@param int - y value of deviation.
	//@param int - xVel of deviation.
	//@param int - yVel of deviation.
	void Update(SDL_Surface* screen, int x, int y, int xVel, int yVel);
	//Shutsdown the engine.
	void Shutdown();
	//Default destructor.
	~ParticleEngine();
private:
	//Pointer to red particle.
	SDL_Surface* red;
	//Pointer to blue particle.
	SDL_Surface* blue;
	//Pointer to green particle.
	SDL_Surface* green;
	//Pointer to shimmer effect.
	SDL_Surface* shimmer;
	//Vector of particle structs.
	std::vector<Particle*> particleVector;
	//Previous particleX
	int prevX;
	//Previous particleY
	int prevY;
	//Alpha value for keying
	int alpha;
	//HARDCODED FOR MAZE GOAL USAGE
	int goalX;
	int goalY;
	int goalXVel;
	int goalYVel;

private:
	//KillAndReplace - Readjusts particle values.
	//@param Particle* dying - particle to exchange.
	//@param int x - x value to init calculations.
	//@param int y - y value to init calculatons.
	//@param int xVel - xVel to init calculations.
	//@param int yVel - yVel to init calcualations.
	//@return Particle* returns the new particle.
	Particle* KillAndReplace(Particle* dying, int x, int y, int xVel, int yVel);
	//Render - Renders the particle on screen.
	//@param SDL_Surface* - particle to render.
	//@param int - x value to render to.
	//@param int - y value to render to.
	//@param SDL_Surface* - screen to render to.
	//@param Uint8 - alpha value of keying.
	void Render(SDL_Surface* particle, int x, int y, SDL_Surface* screen, Uint8 alpha);
	//CalculatePosition - calculates the particle's movement.
	//@param Particle* - particle to calculate.
	void CalculatePosition(Particle* p);
};

#endif