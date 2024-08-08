#include "SpiderWeb.h"
#include "../D2DEngine/D2DEngine.h"
#include "MouseManager.h"

SpiderWeb::SpiderWeb(const int& objectNum, std::string objectName)
	:IWool(objectNum, objectName, 10, 35, 40, 10, 0, 1, false, eObjectDefine::SPIDERWEB, WoolSpcAbility::NONE, WoolSpcAbility::NONE),
	returnItemBox(false), returnStatBox(false)
{
}

SpiderWeb::SpiderWeb(int objectNum, std::string objectName, double posX, double posY)
	:IWool(objectNum, objectName,posX, posY, 10, 35, 40, 10, 0, 1, false, eObjectDefine::SPIDERWEB, WoolSpcAbility::NONE, WoolSpcAbility::NONE),
	returnItemBox(false), returnStatBox(false)
{
}

SpiderWeb::~SpiderWeb()
{
}

void SpiderWeb::UpdateObject()
{
}

void SpiderWeb::RenderObject()
{
}

bool SpiderWeb::SendImage()
{
	return false;
}

bool SpiderWeb::SendStat()
{
	return false;
}
