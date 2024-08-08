#include "AverageObject.h"
#include "../D2DEngine/D2DEngine.h"



AverageObject::AverageObject(const int& objectNum, std::string objectName)
	:Object(objectNum, objectName)
{
	this->renderOrder = OBJECT_ORDER;
}

AverageObject::AverageObject(int objectNum, std::string objectName, double posX, double posY)
	:Object(objectNum, objectName, posX, posY)
{
	this->renderOrder = OBJECT_ORDER;
}

AverageObject::~AverageObject()
{
}

void AverageObject::UpdateObject()
{
}

void AverageObject::RenderObject()
{
	if (this->GetPositionX() < 1000)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::EMPTYBOX1, GetPositionX(), GetPositionY());
	}
	else
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::AVERAGEBOX_NOCOUNT, GetPositionX(), GetPositionY());
	}
	//D2DEngine::GetInstance()->DrawRect(GetPositionX(), GetPositionY(), GetPositionX() + 256, GetPositionY() + 256);
}




