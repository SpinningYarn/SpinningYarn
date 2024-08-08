#include "Cotton.h"
#include "../D2DEngine/D2DEngine.h"
#include "MouseManager.h"

Cotton::Cotton(const int& objectNum, std::string objectName)
	:IWool(objectNum, objectName, 40, 80, 60, 40, 0, 1, false, eObjectDefine::COTTON, WoolSpcAbility::NONE, WoolSpcAbility::STIFF),
	returnItemBox(false), returnStatBox(false)
{
}

Cotton::Cotton(int objectNum, std::string objectName, double posX, double posY)
	:IWool(objectNum, objectName, posX, posY, 40, 80, 60, 40, 0, 1, false, eObjectDefine::COTTON, WoolSpcAbility::NONE, WoolSpcAbility::STIFF),
	returnItemBox(false), returnStatBox(false)
{
}

Cotton::~Cotton()
{
}

void Cotton::UpdateObject()
{
}

void Cotton::RenderObject()
{
}

bool Cotton::SendImage()
{
	return false;
}

bool Cotton::SendStat()
{
	return false;
}
