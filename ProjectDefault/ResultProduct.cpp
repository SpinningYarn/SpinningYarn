#include "ResultProduct.h"
#include "StageManager.h"
#include "../D2DEngine/D2DEngine.h"

ResultProduct::ResultProduct(const int objectNum, string objectName)
	:Object(objectNum, objectName, 632, 519), m_DivideAmount(0), m_CurrentDivide(0), m_CurrentY(0)
{
	this->renderOrder = OBJECT_ORDER;
}

ResultProduct::ResultProduct(const int objectNum, const string& objectName, const double posX, const double posY)
	:Object(objectNum, objectName, posX, posY), m_DivideAmount(0), m_CurrentDivide(0), m_CurrentY(0)
{
	this->renderOrder = OBJECT_ORDER;
}

ResultProduct::~ResultProduct()
{

}

void ResultProduct::UpdateObject()
{

}

void ResultProduct::RenderObject()
{
if (m_CurrentDivide > 0)
	switch (StageManager::GetInstance()->GetStageNum())
	{
		case 1:
			D2DEngine::GetInstance()->LoadSpriteFromSheet(eObjectDefine::KnittingWork_1, 0, 480 - m_CurrentY, 640, 480, 1);
			D2DEngine::GetInstance()->DrawSpriteCut(eObjectDefine::KnittingWork_1, this->GetPositionX(), this->GetPositionY(), m_CurrentY);
			break;

		case 2:
			D2DEngine::GetInstance()->LoadSpriteFromSheet(eObjectDefine::KnittingWork_2, 0, 400 - m_CurrentY, 640, 400, 1);
			D2DEngine::GetInstance()->DrawSpriteCut(eObjectDefine::KnittingWork_2, this->GetPositionX(), this->GetPositionY(), m_CurrentY);
			break;

		case 3:
			D2DEngine::GetInstance()->LoadSpriteFromSheet(eObjectDefine::KnittingWork_3, 0, 400 - m_CurrentY, 640, 400, 1);
			D2DEngine::GetInstance()->DrawSpriteCut(eObjectDefine::KnittingWork_3, this->GetPositionX(), this->GetPositionY(), m_CurrentY);
			break;

		case 4:
			D2DEngine::GetInstance()->LoadSpriteFromSheet(eObjectDefine::KnittingWork_4, 0, 400 - m_CurrentY, 640, 400, 1);
			D2DEngine::GetInstance()->DrawSpriteCut(eObjectDefine::KnittingWork_4, this->GetPositionX(), this->GetPositionY(), m_CurrentY);
			break;

		case 5:
			D2DEngine::GetInstance()->LoadSpriteFromSheet(eObjectDefine::KnittingWork_5, 0, 400 - m_CurrentY, 640, 400, 1);
			D2DEngine::GetInstance()->DrawSpriteCut(eObjectDefine::KnittingWork_5, this->GetPositionX(), this->GetPositionY(), m_CurrentY);
			break;

		default:
			break;
	}
}

void ResultProduct::SetCurrentDivide(double divide, int Amount)
{
	if (StageManager::GetInstance()->GetStageNum() == 1)
	{
		m_CurrentDivide = divide;
		m_DivideAmount = Amount;
		if (m_CurrentDivide > 0)
		{
			m_CurrentY = 480 * (m_CurrentDivide / m_DivideAmount);
		}
	}
	else if (StageManager::GetInstance()->GetStageNum() > 1)
	{
		m_CurrentDivide = divide;
		m_DivideAmount = Amount;
		if (m_CurrentDivide > 0)
		{
			m_CurrentY = 400 * (m_CurrentDivide / m_DivideAmount);
		}
	}
}
