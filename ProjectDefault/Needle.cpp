#include "../D2DEngine/D2DEngine.h"
#include "Needle.h"

Needle::Needle(const int objectNum, std::string objectName)
	:Object(objectNum, objectName, 332, 387), m_NeedleX(GetPositionX()), m_NeedleY(GetPositionY())
{
	this->renderOrder = KNITTING_ORDER;
}

Needle::Needle(const int objectNum, const std::string& objectName, const double posX, const double posY)
	:Object(objectNum, objectName, posX, posY), m_NeedleX(GetPositionX()), m_NeedleY(GetPositionY())
{
	this->renderOrder = KNITTING_ORDER;
}

Needle::~Needle()
{

}

void Needle::UpdateObject()
{

}

void Needle::RenderObject()
{
	D2DEngine::GetInstance()->DrawSprite(eObjectDefine::Needle, GetNeedleX(), GetPositionY());
}

void Needle::MoveNeedleX(double MoveSize)
{
	m_NeedleX += MoveSize;
}

void Needle::MoveNeedleY(double MoveSize)
{
	m_NeedleY += MoveSize;
}

double Needle::GetNeedleX()
{
	return m_NeedleX;
}

void Needle::SetOriginX()
{
	m_NeedleX = GetPositionX();
}
