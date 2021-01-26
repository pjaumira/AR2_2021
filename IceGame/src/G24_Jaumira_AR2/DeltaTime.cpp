#include "DeltaTime.h"

DeltaTime::DeltaTime()
{
	lastTime = clock();
	deltaTime = 0;
}

void DeltaTime::UpdateDeltaTime()
{
	deltaTime = clock() - lastTime;
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
}
