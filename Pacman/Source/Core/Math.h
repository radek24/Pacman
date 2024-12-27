#pragma once

typedef struct {
	int x;
	int y;
}Vec2i;

typedef struct {
	float x;
	float y;
}Vec2f;

typedef struct {
	Vec2f position;
	float rotation; // In degrees
	Vec2f scale;
} Transform2Df;

typedef struct {
	Vec2i position;
	Vec2i size;
}Rect2Di;

typedef enum{Right,Left,Up,Down}Orientation;

int Vec2iEqual(Vec2i* a, Vec2i* b);
