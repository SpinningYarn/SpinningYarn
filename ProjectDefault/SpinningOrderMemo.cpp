#include "SpinningOrderMemo.h"
#include "../D2DEngine//D2DEngine.h"
#include "StageManager.h"

SpinningOrderMemo::SpinningOrderMemo(const int objectNum, std::string objectName)
	: Object(objectNum, objectName, 0, 0)
	, m_PosX(0), m_PosY(0)
{
	this->renderOrder = UI_ORDER;
	m_pStageManager = StageManager::GetInstance();
}

SpinningOrderMemo::SpinningOrderMemo(const int objectNum, const std::string& objectName, const double posX, const double posY)
	: Object(objectNum, objectName, posX, posY)
	, m_PosX((float)posX), m_PosY((float)posY)
{
	this->renderOrder = UI_ORDER;
	m_pStageManager = StageManager::GetInstance();
}

SpinningOrderMemo::~SpinningOrderMemo()
{

}

void SpinningOrderMemo::UpdateObject()
{

}

void SpinningOrderMemo::RenderObject()
{
	D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SpinningOrderMemo, m_PosX, m_PosY);

	if (m_pStageManager->GetStageNum() == 1)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SpinningOrderMemoCustomer1, m_PosX, m_PosY);
		D2DEngine::GetInstance()->DrawText((int)m_PosX + 325, (int)m_PosY + 225, (int)m_pStageManager->GetPlayerMisTakeCount());
	}
	else if (m_pStageManager->GetStageNum() == 2)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SpinningOrderMemoCustomer2, m_PosX, m_PosY);
		D2DEngine::GetInstance()->DrawText((int)m_PosX + 325, (int)m_PosY + 225, m_pStageManager->GetPlayerMisTakeCount());
	}
	else if (m_pStageManager->GetStageNum() == 3)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SpinningOrderMemoCustomer3, m_PosX, m_PosY);
		D2DEngine::GetInstance()->DrawText((int)m_PosX + 325, (int)m_PosY + 225, m_pStageManager->GetPlayerMisTakeCount());
	}
	else if (m_pStageManager->GetStageNum() == 4)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SpinningOrderMemoCustomer4, m_PosX, m_PosY);
		D2DEngine::GetInstance()->DrawText((int)m_PosX + 325, (int)m_PosY + 225, m_pStageManager->GetPlayerMisTakeCount());
	}
	else if (m_pStageManager->GetStageNum() == 5)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SpinningOrderMemoCustomer5, m_PosX, m_PosY);
		D2DEngine::GetInstance()->DrawText((int)m_PosX + 325, (int)m_PosY + 225, m_pStageManager->GetPlayerMisTakeCount());
	}
}
