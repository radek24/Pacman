#pragma once
#include "GameObjects/Text.h"

typedef enum {
	deselected,selected,pressed
}ButtonState;

typedef void (*ButtonPressedCallback)(LevelManager*);

typedef struct Button Button;

typedef struct Button {
    Button* nextButton;
    Button* previousButton;
    Text text;
    ButtonState state;
    ButtonPressedCallback callback;
} Button;

void InitButton(Button* button, char* text, SDL_Color color, Vec2i loc,LevelManager* manager, ButtonPressedCallback callback);
void AppendButton(Button* button, Button* previous, char* text,LevelManager* manager, ButtonPressedCallback callback);
void UpdateButton(Button* button, LevelManager* manager);
void RenderButton(Button* button, SDL_Renderer* renderer);
void DestroyButton(Button* button);
