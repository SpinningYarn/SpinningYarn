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
		// Gauge 랜덤 수치 받기
		SetRandomGaugePos();

		// Spinning Gauge 범위 Render 투명도 설정
		m_pSpinningGaugeManger->RandomGaugeAlphaValue(1.0f);

		// 만약 한 바퀴 회전하여 카우팅 됬을 경우 조건 열람
		if (m_pSpinningGaugeManger->GetGauageCount() >= 1)
		{
			m_CountOn = true;
		}

		// 물레가 작동중이라면 실행
		if (m_pStageManager->IsSpinningGaugeBallState() == true)
		{
			m_PosX++;
			m_CountNum++;
		}

		/// 방적 실패
		if (m_PosX >= 1200)
		{
			// 실수 카운터 갱신
			m_pStageManager->AddPlayerMisTakeCount();

			m_PosX = 700;	// 과열되면 원위치로

			m_pStageManager->SetFailAnimation(true);
		}

		// 한 바퀴 회전 시 증가하게 하는 부분
		//if (m_CountOn == true && m_PosX < m_pSpinningGaugeManger->GetMaxGaugeBar())
		//{
		//	// 10%식 증가
		//	if (m_CountNum < m_pSpinningGaugeManger->GetPercent10Gauge())
		//	{
		//		m_PosX += 2.5f;
		//		m_CountNum++;

		//		/// 방적 실패
		//		if (m_PosX >= 1200)
		//		{
		//			// 실수 카운터 갱신
		//			m_pStageManager->AddPlayerMisTakeCount();

		//			m_PosX = 700;	// 과열되면 원위치로

		//			m_pStageManager->SetFailAnimation(true);
		//		}
		//	}

		//	// 회전이 멈췄을 때 계속 증가하지 않게끔 초기화
		//	if (m_CountNum >= m_pSpinningGaugeManger->GetPercent10Gauge())
		//	{
		//		m_CountNum = 0;
		//		m_pSpinningGaugeManger->CountIncrease(0);
		//		m_CountOn = false;
		//	}
		//}

		// 랜덤 범위안에 있을 경우
		if (m_PosX > m_RandomPosX && m_PosX < m_RandomPosX + 130)
		{
			// 범위 안에 있을 경우 Ball 애니메이션 세팅
			m_pStageManager->SetBallAnimation(true);

			m_AccTime2 += (float)TimerManager::GetInstance().GetDeltaTime();
			m_CurFrame2++;	// 1초당 몇 프레임인지 세기

			if (m_AccTime2 >= 1.0f)
			{
				m_pSpinningGaugeManger->RandomPosCounting();	// 1초에 한번씩 카운트
				// 값들 0으로 다시 초기화
				m_AccTime2 = 0;
				m_CurFrame2 = 0;
			}
		}
		else
		{
			m_pSpinningGaugeManger->RandomPosCountInit();	// 상시 초기화
			m_pStageManager->SetBallAnimation(false);	// 애니메이션 초기화
			m_pStageManager->SetSucessAnimation(false);	// 애니메이션 초기화
		}

		/// 얼마만큼의 시간이 지나면 실행
		// 현재 흐르는 시간
		m_AccTime += (float)TimerManager::GetInstance().GetDeltaTime();
		m_CurFrame++;	// 1초당 몇 프레임인지 세기

		if (m_AccTime >= 0.1f)
		{
			m_MinusCount = 10;	// 줄어들 길이

			// 값들 0으로 다시 초기화
			m_AccTime = 0;
			m_CurFrame = 0;
		}

		// 게이지 줄이기
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
	// 미니게임이 종료되는 시점 (성공)
	if (m_pSpinningGaugeManger->GetRandomTimeCount() > 3)
	{
		// 성공 애니메이션 작동
		m_pStageManager->SetSucessAnimation(true);
		
		// 1초당 카운트되던 변수 초기화
		m_pSpinningGaugeManger->RandomPosCountInit();

		// GugeBar 랜덤 수치 초기화
		m_pSpinningGaugeManger->SetRandomPos();
		SetRandomGaugePos();

		// 다시 원위치로
		m_PosX = 700;

		// 랜덤 범위 Render 투명하게
		m_pSpinningGaugeManger->RandomGaugeAlphaValue(0);

		// 게임 동작 못하게
		m_pStageManager->SpinningGameStateChage(false);
		
		// 미니게임 종료
		m_pStageManager->SpinningGameStateChage(false);
	}
}

void SpinningGaugBall::SetRandomGaugePos()
{
	m_RandomPosX = m_pSpinningGaugeManger->GetRandomGaugePosX() - 60;
}
