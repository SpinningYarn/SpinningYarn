#include "Angora.h"
#include "../D2DEngine/D2DEngine.h"
#include "MouseManager.h"

Angora::Angora(const int& objectNum, std::string objectName)
	:IWool(objectNum, objectName, 80, 20, 35, 60, 90, 1, false, eObjectDefine::ANGORA, WoolSpcAbility::SOFTNESS, WoolSpcAbility::HAIRLOSS),
	returnItemBox(false), returnStatBox(false)
{

}

Angora::Angora(int objectNum, std::string objectName, double posX, double posY)
	:IWool(objectNum, objectName, posX, posY, 80, 20, 35, 60, 90, 1, false, eObjectDefine::ANGORA, WoolSpcAbility::SOFTNESS, WoolSpcAbility::HAIRLOSS),
	returnItemBox(false), returnStatBox(false)
{

}

Angora::~Angora()
{
}

void Angora::UpdateObject()
{
}

void Angora::RenderObject()
{
}

bool Angora::SendImage()
{
	return false;
}

bool Angora::SendStat()
{
	return false;
}
