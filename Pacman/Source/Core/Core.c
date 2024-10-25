#include "Core.h"

int getSpriteIndexFromTime(float time, int sprites)
{
     return ((int)(time * 10) % sprites);
}
