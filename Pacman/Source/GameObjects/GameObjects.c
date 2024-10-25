#include "GameObjects.h"
#include "../Core/Log.h"
#include "../SDL_Wrapper.h"

void RenderSprite(SpriteComponent* sprite, SDL_Renderer* renderer)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, sprite->sprite);
    if (texture == NULL) {
        PAC_WARN("Failed to load texture! IMG_Error: %s\n", IMG_GetError());
        return;
    }
    SDL_RenderClear(renderer);
    Rect2Di spritetransofrm = sprite->transform;
    SDL_RenderCopy(renderer, texture, NULL, &(SDL_Rect){
        spritetransofrm.position.x,
            spritetransofrm.position.y,
            spritetransofrm.size.x,
            spritetransofrm.size.y
    });
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}
