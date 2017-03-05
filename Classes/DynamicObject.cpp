#include "DynamicObject.h"


DynamicObject::DynamicObject(void):MyObject()
{
	prevPos.set(oPos.x, oPos.y);
}


DynamicObject::~DynamicObject(void)
{
}

void DynamicObject::UpdateMove(float deltaTime){}

void DynamicObject::Update(float deltaTime){}

void DynamicObject::Release(){}
