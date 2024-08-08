#include "Cashmere.h"
#include "../D2DEngine/D2DEngine.h"
#include "MouseManager.h"

Cashmere::Cashmere(const int& objectNum, std::string objectName)
	:IWool(objectNum, objectName, 100, 45, 70, 70, 120, 1, false, eObjectDefine::CASHMERE, WoolSpcAbility::LIGHTNESS, WoolSpcAbility::SOFTNESS),
	returnItemBox(false), returnStatBox(false)
{
}

Cashmere::Cashmere(int objectNum, std::string objectName, double posX, double posY)
	:IWool(objectNum, objectName, posX, posY, 100, 45, 70, 70, 120, 1, false, eObjectDefine::CASHMERE, WoolSpcAbility::LIGHTNESS, WoolSpcAbility::SOFTNESS),
	returnItemBox(false), returnStatBox(false)
{
}

Cashmere::~Cashmere()
{
}

void Cashmere::UpdateObject()
{
}

void Cashmere::RenderObject()
{
}

bool Cashmere::SendImage()
{
	return false;
}

bool Cashmere::SendStat()
{
	return false;
}
