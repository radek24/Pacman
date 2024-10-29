#include "Button.h"

void InitButton(Button* button, char* text, SDL_Color color, Vec2i loc, LevelManager* manager, ButtonPressedCallback callback)
{
	InitText((&button->text), color, text, loc, manager);
	button->callback = callback;
	button->state = deselected;
}

void AppendButton(Button* button, Button* previous, char* text, LevelManager* manager, ButtonPressedCallback callback)
{
	button->previousButton = previous;
	button->previousButton->nextButton = button;
	Vec2i loc = (Vec2i){ previous->text.location.x,previous->text.location.y + TILE_SIZE*2 };
	InitText((&button->text), previous->text.color, text, loc, manager);
	button->callback = callback;
	button->state = deselected;
}

/* Please only pass prefixes and postfixes of lenght 2. I know, very generic function indeed.*/
char* ReplacePrefix(char* str, const char* oldPrefix, const char* newPrefix) {
	size_t prefixLen = 2;
	if (strncmp(str, oldPrefix, prefixLen) == 0) {
		memcpy(str, newPrefix, prefixLen);
	}
	return str;
}

void UpdateButton(Button* button, LevelManager* manager)
{
	if (button->state != selected) return;
	if (!manager->isInputActive) return;
	SDL_Event event = manager->inputEvent;
	if (event.type != SDL_KEYDOWN) return;

	switch (event.key.keysym.sym)
	{
	case SDLK_UP: {
		button->previousButton->state = selected;
		button->state = deselected;
		UpdateText(&(button->text), ReplacePrefix(button->text.text,"> ", "  "), manager);
		UpdateText(&(button->previousButton->text), ReplacePrefix(button->previousButton->text.text, "  ", "> "), manager);
	}break;
	case SDLK_DOWN: {
		button->nextButton->state = selected;
		button->state = deselected;
		UpdateText(&(button->text), ReplacePrefix(button->text.text, "> ", "  "), manager);
		UpdateText(&(button->nextButton->text), ReplacePrefix(button->nextButton->text.text, "  ", "> "), manager);
	}break;
	case SDLK_KP_ENTER:
	case SDLK_RETURN: {
		button->callback(manager);
	}break;
	}
}

void RenderButton(Button* button,SDL_Renderer* renderer)
{
	RenderText(&(button->text), renderer);
}

void DestroyButton(Button* button)
{
	DestroyText(&(button->text));
}
