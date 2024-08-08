#include "SpinningGaugeBar.h"
#include "../D2DEngine//D2DEngine.h"
#include "../D2DEngine/Animator.h"
#include "SpinningGaugeManager.h"

SpinningGaugeBar::SpinningGaugeBar(const int objectNum, std::string objectName)
	: Object(objectNum, objectName, 0, 0)
	, m_PosX(0), m_PosY(0)
	, m_IsRandomX(true)
	, m_AlphaValue(1)
{
	this->renderOrder = OBJECT_ORDER;
	m_pSpinningGaugeManager = SpinningGaugeManager::GetInstance();
	m_pSpinningGaugeManager->SetGauageBarPos((int)m_PosX, (int)m_PosY);
	m_pSpinningGaugeManager->RandomIsCountChage(true);
}

SpinningGaugeBar::SpinningGaugeBar(const int objectNum, const std::string& objectName, const double posX, const double posY)
	: Object(objectNum, objectName, posX, posY)
	, m_PosX((float)posX), m_PosY((float)posY)
	, m_IsRandomX(true)
	, m_AlphaValue(1)
{
	this->renderOrder = OBJECT_ORDER;
	m_pSpinningGaugeManager = SpinningGaugeManager::GetInstance();
	m_pSpinningGaugeManager->SetGauageBarPos((int)m_PosX, (int)m_PosY);
	m_pSpinningGaugeManager->RandomIsCountChage(true);
}

SpinningGaugeBar::~SpinningGaugeBar()
{

}

void SpinningGaugeBar::UpdateObject()
{
	if (m_pSpinningGaugeManager->GetRandomIsCount() == true)
	{
		m_pSpinningGaugeManager->SetRandomPos();			// 랜덤 좌표 설정
	}

	m_pSpinningGaugeManager->RandomIsCountChage(false);					// 랜덤 상태 false
	m_AlphaValue = m_pSpinningGaugeManager->GetRandomGaugeAlphaValue();	// 랜덤 범위 Render 투명도 받기 
}

void SpinningGaugeBar::RenderObject()
{
	// GaugeBar 랜더
	D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SpinningGaugeBar, m_PosX, m_PosY);
	
	// GaugeBar 크기 속 랜덤 범위 랜더
	D2DEngine::GetInstance()->DrawSpriteAlpha(eObjectDefine::SpinningGaugeBarRange, m_pSpinningGaugeManager->GetRandomGaugePosX(), m_PosY + 1, m_AlphaValue, 0);
}