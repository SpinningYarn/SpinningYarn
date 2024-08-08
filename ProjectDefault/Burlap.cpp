#include "Burlap.h"
#include "../D2DEngine/D2DEngine.h"
#include "MouseManager.h"

Burlap::Burlap(const int& objectNum, std::string objectName)
	:IWool(objectNum, objectName, 5, 75, 80, 20, 55, 1, false, eObjectDefine::HEMP, WoolSpcAbility::STIFF, WoolSpcAbility::ROUGH),
	returnItemBox(false), returnStatBox(false)
{
}

Burlap::Burlap(int objectNum, std::string objectName, double posX, double posY)
	:IWool(objectNum, objectName, posX, posY, 5, 75, 80, 20, 55, 1 , false, eObjectDefine::HEMP, WoolSpcAbility::STIFF, WoolSpcAbility::ROUGH),
	returnItemBox(false), returnStatBox(false)
{
}

Burlap::~Burlap()
{
}

void Burlap::UpdateObject()
{
}

void Burlap::RenderObject()
{
}

bool Burlap::SendImage()
{
	return false;
}

bool Burlap::SendStat()
{
	return false;
}
