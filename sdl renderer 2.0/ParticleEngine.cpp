#include "ParticleEngine.h"

ParticleEngine::ParticleEngine()
{
	red = NULL;
	blue = NULL;
	green = NULL;
	shimmer = NULL;
}

bool ParticleEngine::Initialize(int x, int y)
{
	srand(SDL_GetTicks());
	goalX = x;
	goalY = y;
	red = SDL_LoadBMP("redParticle.bmp");
	if(red == NULL)
	{
		std::cerr << "Unable to load redParticle." << std::endl;
		return false;
	}
	blue = SDL_LoadBMP("blueParticle.bmp");
	if(blue == NULL)
	{
		std::cerr << "Unable to load blueParticle." << std::endl;
		return false;
	}
	green = SDL_LoadBMP("greenParticle.bmp");
	if(green == NULL)
	{
		std::cerr << "Unable to load greenParticle." << std::endl;
		return false;
	}
	shimmer = SDL_LoadBMP("shimmerParticle.bmp");
	if(shimmer == NULL)
	{
		std::cerr << "Unable to load shimmerParticle." << std::endl;
		return false;
	}

	for(int i = 0; i < NUMBER_OF_PARTICLES; i++)
	{
		Particle* p = new Particle();
		p->frame = rand() % 5;
		p->x = x - 5 + (rand() % 25);
		p->y = y - 5 + (rand() % 25);
		p->xVel = 0;
		p->yVel = 0;
		switch(rand() % 3)
		{
		case 0: p->type = red; break;
		case 1: p->type = green; break;
		case 2: p->type = blue; break;
		}
		particleVector.push_back(p);
	}

	return true;
}

void ParticleEngine::UpdateMazeGoal(SDL_Surface* screen)
{
	goalXVel = rand() % 1;
	goalYVel = rand() % 1;
	for(int i = 0; i < NUMBER_OF_PARTICLES; i++)
	{
		particleVector[i]->frame += 1;
		alpha = particleVector[i]->frame * (255 / FRAME_LIMIT);
		if(particleVector[i]->frame % FLICKER_PER_FRAME == 2)
		{
			Render(shimmer, particleVector[i]->x, particleVector[i]->y, screen, alpha);
		}
		else
		{
			Render(particleVector[i]->type, particleVector[i]->x, particleVector[i]->y, screen, alpha);
		}
		CalculatePosition(particleVector[i]);
		if(particleVector[i]->frame > FRAME_LIMIT)
		{
			particleVector.push_back(KillAndReplace(particleVector[i], goalX, goalY, goalXVel, goalYVel));
			particleVector[i] = particleVector.back();
			particleVector.pop_back();
		}
	}
}

void ParticleEngine::Update(SDL_Surface* screen, int x, int y, int xVel, int yVel)
{
	prevX = x;
	prevY = y;
	for(int i = 0; i < NUMBER_OF_PARTICLES; i++)
	{
		if(prevX == x)
		{
			particleVector[i]->xVel /= 2;
		}
		if(prevY == y)
		{
			particleVector[i]->yVel /= 2;
		}
		particleVector[i]->frame += 1;
		alpha = particleVector[i]->frame * (255 / FRAME_LIMIT);
		if(particleVector[i]->frame % FLICKER_PER_FRAME == 2)
		{
			Render(shimmer, particleVector[i]->x, particleVector[i]->y, screen, alpha);
		}
		else
		{
			Render(particleVector[i]->type, particleVector[i]->x, particleVector[i]->y, screen, alpha);
		}
		CalculatePosition(particleVector[i]);
		if(particleVector[i]->frame > FRAME_LIMIT)
		{
			particleVector.push_back(KillAndReplace(particleVector[i], x, y, xVel, yVel));
			particleVector[i] = particleVector.back();
			particleVector.pop_back();
		}
	}
}

void ParticleEngine::CalculatePosition(Particle* p)
{
	p->x = p->x + p->xVel / 2;
	if(p->x > p->x + PARTICLE_LIMIT_X)
	{
		p->x = p->x + PARTICLE_LIMIT_X + rand() % PARTICLE_LIMIT_RAND;
	}
	if(p->x < p->x - PARTICLE_LIMIT_X)
	{
		p->x = p->x - PARTICLE_LIMIT_X - rand() % PARTICLE_LIMIT_RAND;
	}
	p->y = p->y + p->yVel / 2;
	if(p->y > p->y + PARTICLE_LIMIT_Y)
	{
		p->y = p->y + PARTICLE_LIMIT_Y + rand() % PARTICLE_LIMIT_RAND;
	}
	if(p->y < p->y - PARTICLE_LIMIT_Y)
	{
		p->y =p-> y + PARTICLE_LIMIT_Y + rand() % PARTICLE_LIMIT_RAND;
	}
}

Particle* ParticleEngine::KillAndReplace(Particle* dying, int x, int y, int xVel, int yVel)
{
	dying->x = x - 5 + (rand() % 25);
	dying->y = y - 5 + (rand() % 25);
	dying->frame = rand() % 5;
	dying->xVel = xVel;
	dying->yVel = yVel;
	switch(rand() % 3)
	{
	case 0: 
		dying->type = red; 
		break;
	case 1: 
		dying->type = green; 
		break;
	case 2: 
		dying->type = blue; 
		break;
	}
	return dying;
}

void ParticleEngine::Shutdown()
{
	for(int i = 0; i < NUMBER_OF_PARTICLES; i++)
	{
		delete particleVector[i];
	}
	red = NULL;
	blue = NULL;
	green = NULL;
	shimmer = NULL;
}

ParticleEngine::~ParticleEngine()
{
	ParticleEngine::Shutdown();
}

void ParticleEngine::Render(SDL_Surface* particle, int x, int y, SDL_Surface* screen, Uint8 alpha)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;
	//color key turqoise
	SDL_SetColorKey(particle, SDL_SRCCOLORKEY, SDL_MapRGB(particle->format, 0, 255, 255));
	SDL_SetAlpha(particle, SDL_SRCALPHA, alpha);
	SDL_BlitSurface(particle, NULL, screen, &offset);
}