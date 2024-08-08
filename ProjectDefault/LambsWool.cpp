#include "LambsWool.h"
#include "../D2DEngine/D2DEngine.h"
#include "MouseManager.h"

LambsWool::LambsWool(const int& objectNum, std::string objectName)
	:IWool(objectNum, objectName, 60, 55, 30, 50, 40, 1, false, eObjectDefine::LAMBSWOOL, WoolSpcAbility::ELASTICITY, WoolSpcAbility::ROUGH),
	returnItemBox(false), returnStatBox(false)
{

}

LambsWool::LambsWool(int objectNum, std::string objectName, double posX, double posY)
	:IWool(objectNum, objectName, posX, posY, 60, 55, 30, 50, 40, 1, false, eObjectDefine::LAMBSWOOL, WoolSpcAbility::ELASTICITY, WoolSpcAbility::ROUGH),
	returnItemBox(false), returnStatBox(false)
{

}

LambsWool::~LambsWool()
{
}

void LambsWool::UpdateObject()
{
}

void LambsWool::RenderObject()
{
}

bool LambsWool::SendImage()
{
	return false;
}

bool LambsWool::SendStat()
{
	return false;
}
