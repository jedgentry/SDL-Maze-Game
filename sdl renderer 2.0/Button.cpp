#include "Button.h"

Button::Button()
{
	display = true;
	mouseX = 0;
	mouseY = 0;
	buttonTexture = new Texture();
}

Button::Button(int x, int y, int w, int h, char* filename)
{
	display = true;
	mouseX = 0;
	mouseY = 0;
	buttonTexture = new Texture(filename);
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
}

void Button::ToggleRender()
{
	if(display)
	{
		display = false;
	}
	if(!display)
	{
		display = true;
	}
}

bool Button::Update(SDL_Surface* screen, SDL_Event* Event)
{
	if(!buttonTexture->Draw(screen, box.x, box.y))
	{
		std::cerr << "Unable to draw button." << std::endl;
	}
	return HandleEvents(Event);
}

bool Button::UpdateWithKey(SDL_Surface* screen, SDL_Event* Event, Uint8 r, Uint8 g, Uint8 b)
{
	if(!buttonTexture->DrawKey(screen, box.x, box.y, r, g, b))
	{
		std::cerr << "Unable to draw button." << std::endl;
	}
	return HandleEvents(Event);
}

bool Button::SwapTexture(char* filename)
{
	if(!buttonTexture->SwapTexture(filename))
	{
		return false;
	}
	return true;
}

bool Button::HandleEvents(SDL_Event* Event)
{
		switch(Event->type)
			case SDL_MOUSEBUTTONDOWN:
		{
			if(Event->button.button == SDL_BUTTON_LEFT)
			{
				mouseX = Event->button.x;
				mouseY = Event->button.y;

				if((mouseX > box.x) && (mouseX < box.x + box.w) && (mouseY > box.y) && (mouseY < box.y + box.h))
				{
					return true;
				}
			}
		}
	return false;
}

void Button::Shutdown()
{
	buttonTexture->Shutdown();
	buttonTexture = NULL;
}