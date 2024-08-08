#include "SpinningGaugBall.h"
#include "../D2DEngine//D2DEngine.h"
#include "SpinningGaugeManager.h"
#include "TimerManager.h"
#include "StageManager.h"

SpinningGaugBall::SpinningGaugBall(const int objectNum, std::string objectName)
	: Object(objectNum, objectName, 0, 0)
	,m_PosX(0), m_PosY(0)
	, m_CountOn(false), m_MinusCount(0), m_CountNum(0)
	, m_AccTime(0), m_CurFrame(0)
	, m_AccTime2(0), m_CurFrame2(0)
	, m_RandomPosX(0)
	, m_IsGameStart(true)
	, m_AlphaValue(1)
{
	this->renderOrder = OBJECT_ORDER;
	m_pSpinningGaugeManger = SpinningGaugeManager::GetInstance();
	m_pStageManager = StageManager::GetInstance();
	m_pSpinningGaugeManger->SetGauageBallPos((int)m_PosX, (int)m_PosY);
}

SpinningGaugBall::SpinningGaugBall(const int objectNum, const std::string& objectName, const double posX, const double posY)
	: Object(objectNum, objectName, posX, posY)
	, m_PosX((int)posX), m_PosY((int)posY)
	, m_CountOn(false), m_MinusCount(0), m_CountNum(0)
	, m_AccTime(0), m_CurFrame(0)
	, m_AccTime2(0), m_CurFrame2(0)
	, m_RandomPosX(0)
	, m_IsGameStart(true)
	, m_AlphaValue(1)
{
	this->renderOrder = OBJECT_ORDER;
	m_pSpinningGaugeManger = SpinningGaugeManager::GetInstance();
	m_pStageManager = StageManager::GetInstance();
	m_pSpinningGaugeManger->SetGauageBallPos((int)m_PosX, (int)m_PosY);
}

SpinningGaugBall::~SpinningGaugBall()
{

}

void SpinningGaugBall::UpdateObject()
{
	if (m_pStageManager->GetSpinningGameState() == true)
	{
		// Gauge ���� ��ġ �ޱ�
		SetRandomGaugePos();

		// Spinning Gauge ���� Render ���� ����
		m_pSpinningGaugeManger->RandomGaugeAlphaValue(1.0f);

		// ���� �� ���� ȸ���Ͽ� ī���� ���� ��� ���� ����
		if (m_pSpinningGaugeManger->GetGauageCount() >= 1)
		{
			m_CountOn = true;
		}

		// ������ �۵����̶�� ����
		if (m_pStageManager->IsSpinningGaugeBallState() == true)
		{
			m_PosX++;
			m_CountNum++;
		}

		/// ���� ����
		if (m_PosX >= 1200)
		{
			// �Ǽ� ī���� ����
			m_pStageManager->AddPlayerMisTakeCount();

			m_PosX = 700;	// �����Ǹ� ����ġ��

			m_pStageManager->SetFailAnimation(true);
		}

		// �� ���� ȸ�� �� �����ϰ� �ϴ� �κ�
		//if (m_CountOn == true && m_PosX < m_pSpinningGaugeManger->GetMaxGaugeBar())
		//{
		//	// 10%�� ����
		//	if (m_CountNum < m_pSpinningGaugeManger->GetPercent10Gauge())
		//	{
		//		m_PosX += 2.5f;
		//		m_CountNum++;

		//		/// ���� ����
		//		if (m_PosX >= 1200)
		//		{
		//			// �Ǽ� ī���� ����
		//			m_pStageManager->AddPlayerMisTakeCount();

		//			m_PosX = 700;	// �����Ǹ� ����ġ��

		//			m_pStageManager->SetFailAnimation(true);
		//		}
		//	}

		//	// ȸ���� ������ �� ��� �������� �ʰԲ� �ʱ�ȭ
		//	if (m_CountNum >= m_pSpinningGaugeManger->GetPercent10Gauge())
		//	{
		//		m_CountNum = 0;
		//		m_pSpinningGaugeManger->CountIncrease(0);
		//		m_CountOn = false;
		//	}
		//}

		// ���� �����ȿ� ���� ���
		if (m_PosX > m_RandomPosX && m_PosX < m_RandomPosX + 130)
		{
			// ���� �ȿ� ���� ��� Ball �ִϸ��̼� ����
			m_pStageManager->SetBallAnimation(true);

			m_AccTime2 += (float)TimerManager::GetInstance().GetDeltaTime();
			m_CurFrame2++;	// 1�ʴ� �� ���������� ����

			if (m_AccTime2 >= 1.0f)
			{
				m_pSpinningGaugeManger->RandomPosCounting();	// 1�ʿ� �ѹ��� ī��Ʈ
				// ���� 0���� �ٽ� �ʱ�ȭ
				m_AccTime2 = 0;
				m_CurFrame2 = 0;
			}
		}
		else
		{
			m_pSpinningGaugeManger->RandomPosCountInit();	// ��� �ʱ�ȭ
			m_pStageManager->SetBallAnimation(false);	// �ִϸ��̼� �ʱ�ȭ
			m_pStageManager->SetSucessAnimation(false);	// �ִϸ��̼� �ʱ�ȭ
		}

		/// �󸶸�ŭ�� �ð��� ������ ����
		// ���� �帣�� �ð�
		m_AccTime += (float)TimerManager::GetInstance().GetDeltaTime();
		m_CurFrame++;	// 1�ʴ� �� ���������� ����

		if (m_AccTime >= 0.1f)
		{
			m_MinusCount = 10;	// �پ�� ����

			// ���� 0���� �ٽ� �ʱ�ȭ
			m_AccTime = 0;
			m_CurFrame = 0;
		}

		// ������ ���̱�
		//if (m_MinusCount >= 0 && m_PosX > 700)
		//{
		//	m_PosX -= 1;
		//	m_MinusCount--;
		//}
		//else
		//{
		//	m_MinusCount = 0;
		//}

		if (m_pStageManager->IsSpinningGaugeBallState() == false && m_PosX > 700)
		{
			m_PosX -= 1;
			m_MinusCount--;
		}
		else
		{
			m_MinusCount = 0;
		}
	}

	if (m_pStageManager->GetSpinningGameState() == false)
	{
		m_PosX = 700;
	}

	EndGame();
}

void SpinningGaugBall::RenderObject()
{
	D2DEngine::GetInstance()->DrawSpriteAlpha(eObjectDefine::SpinningGaugeBall, (float)m_PosX, (float)m_PosY, 1, 0);
}

void SpinningGaugBall::EndGame()
{
	// �̴ϰ����� ����Ǵ� ���� (����)
	if (m_pSpinningGaugeManger->GetRandomTimeCount() > 3)
	{
		// ���� �ִϸ��̼� �۵�
		m_pStageManager->SetSucessAnimation(true);
		
		// 1�ʴ� ī��Ʈ�Ǵ� ���� �ʱ�ȭ
		m_pSpinningGaugeManger->RandomPosCountInit();

		// GugeBar ���� ��ġ �ʱ�ȭ
		m_pSpinningGaugeManger->SetRandomPos();
		SetRandomGaugePos();

		// �ٽ� ����ġ��
		m_PosX = 700;

		// ���� ���� Render �����ϰ�
		m_pSpinningGaugeManger->RandomGaugeAlphaValue(0);

		// ���� ���� ���ϰ�
		m_pStageManager->SpinningGameStateChage(false);
		
		// �̴ϰ��� ����
		m_pStageManager->SpinningGameStateChage(false);
	}
}

void SpinningGaugBall::SetRandomGaugePos()
{
	m_RandomPosX = m_pSpinningGaugeManger->GetRandomGaugePosX() - 60;
}
