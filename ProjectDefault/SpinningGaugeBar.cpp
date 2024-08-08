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
		m_pSpinningGaugeManager->SetRandomPos();			// ���� ��ǥ ����
	}

	m_pSpinningGaugeManager->RandomIsCountChage(false);					// ���� ���� false
	m_AlphaValue = m_pSpinningGaugeManager->GetRandomGaugeAlphaValue();	// ���� ���� Render ���� �ޱ� 
}

void SpinningGaugeBar::RenderObject()
{
	// GaugeBar ����
	D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SpinningGaugeBar, m_PosX, m_PosY);
	
	// GaugeBar ũ�� �� ���� ���� ����
	D2DEngine::GetInstance()->DrawSpriteAlpha(eObjectDefine::SpinningGaugeBarRange, m_pSpinningGaugeManager->GetRandomGaugePosX(), m_PosY + 1, m_AlphaValue, 0);
}