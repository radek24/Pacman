#include "TestLevel.h"

typedef struct
{
	int x;
}TestLevelData;


void TestLevel_Init(LevelManager* manager)
{
	manager->data = malloc(sizeof(TestLevelData));
	PAC_ASSERT(manager && manager->data);
	((TestLevelData*)manager->data)->x = 4;
}

void TestLevel_Update(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	TestLevelData* CurrentLevelData = (TestLevelData*)manager->data;
	CurrentLevelData->x++;
	
}

void TestLevel_Render(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	TestLevelData* CurrentLevelData = (TestLevelData*)manager->data;
	PAC_LOG("%d", CurrentLevelData->x);
}

void TestLevel_Destroy(LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	free(manager->data);
}