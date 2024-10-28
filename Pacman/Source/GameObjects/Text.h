#pragma once
#include <string.h>
#include "Core/Core.h"
#include "SDL_Wrapper.h"
#include "LevelManager.h"

typedef struct {
	SDL_Color color;
	char text[256];
	Vec2i location;
	
	/*Private variable*/
	Vec2i _textDimensions;
	/*Private variable*/
	SDL_Texture* _currentTexture;
}Text;

/*Text lenght should be less than 256 characters*/
void InitText(Text* text, SDL_Color color, char* textToRender, Vec2i location, LevelManager* manager);
void UpdateText(Text* text, char* textToRender, LevelManager* manager);
void UpdateTextColor(Text* text, SDL_Color color, LevelManager* manager);
void RenderText(Text* text, SDL_Renderer* renderer);
void DestroyText(Text* text);