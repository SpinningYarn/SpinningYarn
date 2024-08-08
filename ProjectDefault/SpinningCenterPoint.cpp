#include "SpinningCenterPoint.h"
#include "MouseManager.h"
#include "TimerManager.h"
#include "SpinningGaugeManager.h"
#include "../D2DEngine/D2DEngine.h"
#include "StageManager.h"
#include "SoundManager.h"
#include "SpinningGaugBall.h"

#include <windowsx.h>
#include <atltypes.h>
#include <cmath>

#include "DragAndDrop.h"

SpinningCenterPoint::SpinningCenterPoint(
	const int objectNum, std::string objectName)
	: Object(objectNum, objectName)
	, m_WorldPosX(0)
	, m_WorldPosY(0)
	, m_MousePosX(0)
	, m_MousePosY(0)
	, m_LocalPosX(0)
	, m_LocalPosY(0)
	, m_ObjectTouchState(false)
	, m_ObjectMisTouchState(false)
	, m_ObjectAlphaValue(0)
	, m_AccTime(0)
	, m_CurFrame(0)
	, m_IsSpinningRotate(false)
	, m_PosX(1105), m_PosY(500)
	, m_CurMousePosX(0), m_CurMousePosY(0), m_PevMousePosX(0), m_PevMousePosY(0)
	, m_MousePosState(false)
	, m_NextPosX(0), m_NextPosY(0), m_Speed(0)
	, m_Sin(0), m_Cos(0), m_Tan(0), m_Radian(0), m_Degree(0)
	, m_CountRotate(0)
	, m_IsSpinningWheelRange(false)
	, m_OneSpinningWheelRange(false)
{
	m_pMouseManager = MouseManager::GetInstance();
	m_pSpinningGaugeManager = SpinningGaugeManager::GetInstance();
	m_pStageManager = StageManager::GetInstance();
	m_pDragAndDrop1 = new DragAndDrop();
	m_pDragAndDrop2 = new DragAndDrop();
	m_pDragAndDrop3 = new DragAndDrop();
	Rotate();
}

SpinningCenterPoint::SpinningCenterPoint(
	const int objectNum, std::string objectName,
	const double posX, const double posY)
	: Object(objectNum, objectName)
	, m_WorldPosX(posX)
	, m_WorldPosY(posY)
	, m_MousePosX(0)
	, m_MousePosY(0)
	, m_LocalPosX(0)
	, m_LocalPosY(0)
	, m_ObjectTouchState(false)
	, m_ObjectMisTouchState(false)
	, m_ObjectAlphaValue(0)
	, m_AccTime(0)
	, m_CurFrame(0)
	, m_IsSpinningRotate(false)
	, m_PosX(posX), m_PosY(posY)
	, m_CurMousePosX(0), m_CurMousePosY(0), m_PevMousePosX(0), m_PevMousePosY(0)
	, m_MousePosState(false)
	, m_NextPosX(0), m_NextPosY(0), m_Speed(0)
	, m_Sin(0), m_Cos(0), m_Tan(0), m_Radian(0), m_Degree(0)
	, m_CountRotate(0)
	, m_ObjectSizeX(140), m_ObjectSizeY(140)
	, m_IsSpinningWheelRange(false)
	, m_OneSpinningWheelRange(false)
{
	m_pMouseManager = MouseManager::GetInstance();
	m_pSpinningGaugeManager = SpinningGaugeManager::GetInstance();
	m_pStageManager = StageManager::GetInstance();
	m_pDragAndDrop1 = new DragAndDrop();
	m_pDragAndDrop2 = new DragAndDrop();
	m_pDragAndDrop3 = new DragAndDrop();
	Rotate();
}

SpinningCenterPoint::~SpinningCenterPoint()
{

}

void SpinningCenterPoint::UpdateObject()
{
	// 실시간 마우스 좌표 저장
	m_MousePosX = m_pMouseManager->GetXPos();
	m_MousePosY = m_pMouseManager->GetYPos();

	// 현재, 이전 마우스 좌표 저장
	m_CurMousePosX = (int)m_pMouseManager->GetXPos();
	m_CurMousePosY = (int)m_pMouseManager->GetYPos();

	m_PevMousePosX = m_pMouseManager->GetPevXpos();
	m_PevMousePosY = m_pMouseManager->GetPevYpos();

	// 현재 흐르는 시간
	m_AccTime += (float)TimerManager::GetInstance().GetDeltaTime();

	// 마우스 속도 값
	m_Speed = m_pMouseManager->GetSpeed();

	// 1초당 몇 프레임인지 세기
	m_CurFrame++;

	if (m_AccTime >= 0.1)
	{
		// 값들 0으로 다시 초기화
		m_AccTime = 0;
		m_CurFrame = 0;

		// 이전 마우스 좌표 세팅
		MouseManager::GetInstance()->SetPevMousePos();
	}

	// 한 바퀴 돌때마다 카운팅
	if (m_Degree >= 360)
	{
		m_CountRotate++;	// 한바퀴당 카운트 갱신
		m_pSpinningGaugeManager->CountIncrease(m_CountRotate);	// SpinningBall에 사용할 카운트 저장
		m_CountRotate = 0;	// 카운트 초기화	
		m_Degree = 0;		// 각도 초기화
	}

	static bool spin = false;

	if (m_pStageManager->GetSpinningGameState() == true)
	{
		// 마우스(좌) 클릭 시에만 작동
		if (m_pMouseManager->GetLeftButtonDownState() == true
			&& m_OneSpinningWheelRange == true)
		{

			/// 중심점에서 좌표를 4등분 시킨 상태이다.
			// 오른쪽 위
			if (m_PosX <= m_pMouseManager->GetXPos() && m_PosY > m_pMouseManager->GetYPos()
				&& m_CurMousePosX > m_PevMousePosX && m_CurMousePosY > m_PevMousePosY)
			{
				// 물레 범위 안에 있을 경우
					SoundManager::GetInstance().PlayBGM(MerryGoRound);
				if (1300 > m_pMouseManager->GetXPos() &&
					300 < m_pMouseManager->GetYPos())
				{
					m_IsSpinningWheelRange = true;

				}

				if (m_IsSpinningWheelRange == false)
				{
					m_OneSpinningWheelRange = false;
				}

				m_MousePosState = true;
			}
			// 오른쪽 아래
			else if (m_PosX <= m_pMouseManager->GetXPos() && m_PosY <= m_pMouseManager->GetYPos()
				&& m_CurMousePosX <= m_PevMousePosX && m_CurMousePosY > m_PevMousePosY)
			{
				// 물레 범위 안에 있을 경우
				if (1300 > m_pMouseManager->GetXPos() &&
					700 > m_pMouseManager->GetYPos())
				{
					m_IsSpinningWheelRange = true;
				}

				if (m_IsSpinningWheelRange == false)
				{
					m_OneSpinningWheelRange = false;
				}

				m_MousePosState = true;
			}
			// 왼쪽 아래
			else if (m_PosX > m_pMouseManager->GetXPos() && m_PosY <= m_pMouseManager->GetYPos()
				&& m_CurMousePosX <= m_PevMousePosX && m_CurMousePosY <= m_PevMousePosY)
			{
				// 물레 범위 안에 있을 경우
				if (910 < m_pMouseManager->GetXPos() &&
					700 > m_pMouseManager->GetYPos())
				{
					m_IsSpinningWheelRange = true;
				}

				if (m_IsSpinningWheelRange == false)
				{
					m_OneSpinningWheelRange = false;
				}

				m_MousePosState = true;
			}
			// 왼쪽 위
			else if (m_PosX > m_pMouseManager->GetXPos() && m_PosY > m_pMouseManager->GetYPos()
				&& m_CurMousePosX > m_PevMousePosX && m_CurMousePosY <= m_PevMousePosY)
			{
				// 물레 범위 안에 있을 경우
				if (910 < m_pMouseManager->GetXPos() &&
					300 < m_pMouseManager->GetYPos())
				{
					m_IsSpinningWheelRange = true;
				}

				if (m_IsSpinningWheelRange == false)
				{
					m_OneSpinningWheelRange = false;
				}

				m_MousePosState = true;
			}
			else
			{
				m_MousePosState = false;
			}
		}
	}

	// 마우스를 뗐을 경우
	if (m_pMouseManager->GetLeftButtonDownState() == false)
	{
		// 게이지볼 false
		m_pStageManager->SetSpinningGaugeState(false);

		SoundManager::GetInstance().StopBGM(MerryGoRound);

		m_Degree = 0;
		m_IsSpinningWheelRange = false;
		m_OneSpinningWheelRange = true;
	}

	// 마우스 상태와 좌표 상태가 모두 같을 경우 물레 각도 변환
	if (m_MousePosState == true && m_IsSpinningWheelRange == true)
	{
		m_Degree = m_Degree + 3 * (int)m_Speed;
		Rotate();
		m_pSpinningGaugeManager->m_GauageBallPosX++;

		m_MousePosState = false;
	}
}

void SpinningCenterPoint::RenderObject()
{
	/// 중심 좌표 표시 (좌표 디버그용)
	//// 중심 x, y 좌표 표시, 한바퀴 카운팅
	//D2DEngine::GetInstance()->DrawText(
	//	100 + 10,
	//	300,
	//	(int)m_pMouseManager->GetXPos()
	//);
	//D2DEngine::GetInstance()->DrawText(
	//	100 + 80,
	//	300,
	//	(int)m_NextPosX
	//);
	//D2DEngine::GetInstance()->DrawText(
	//	100 + 150,
	//	300,
	//	(int)m_CountRotate
	//);

	/// 현재와 이전의 실시간 마우스 좌표를 표시 (좌표 디버그용)
	//// 현재 마우스 좌표
	//D2DEngine::GetInstance()->DrawText(
	//	100 + 10,
	//	350,
	//	(int)m_CurMousePosX
	//);
	//D2DEngine::GetInstance()->DrawText(
	//	100 + 80,
	//	350,
	//	(int)m_CurMousePosY
	//);

	//// 이전 마우스 좌표
	//D2DEngine::GetInstance()->DrawText(
	//	100 + 10,
	//	400,
	//	(int)m_PevMousePosX
	//);
	//D2DEngine::GetInstance()->DrawText(
	//	100 + 80,
	//	400,
	//	(int)m_PevMousePosY
	//);

	/// Spinning Wheel 정중앙 좌표 Render (좌표 디버깅용)
	//D2DEngine::GetInstance()->DrawLine((int)m_NextPosX, (int)m_NextPosY, (int)m_PosX, (int)m_PosY, 1);
	//D2DEngine::GetInstance()->DrawRect((int)m_PosX, (int)m_PosY, (int)m_NextPosX, (int)m_NextPosY);

	/// 실시간 마우스 좌표 Render (좌표 디버깅용)
	//D2DEngine::GetInstance()->DrawLine(
	//	m_MousePosX,
	//	m_MousePosY,
	//	(int)m_WorldPosX,
	//	(int)m_WorldPosY,
	//	1.0f);

	//D2DEngine::GetInstance()->DrawText(
	//	m_MousePosX + 10,
	//	m_MousePosY,
	//	m_MousePosX
	//);

	//D2DEngine::GetInstance()->DrawText(
	//	m_MousePosX + 100,
	//	m_MousePosY,
	//	m_MousePosY
	//);
}

void SpinningCenterPoint::Rotate()
{
	double tempRadian = m_Radian;

	Radian();

	/// 좌표 공간 원점을 기준으로 각도 m_Degree로 회전되는 점 (PrevPos x,y)에 대해 (NectPos x,y) 계산
	// 이동할 좌표 = width 좌표 * cosR (-+) Hight 좌표 * sinR + 중심좌표
	m_NextPosX = (m_ObjectSizeX * m_Cos) - (m_ObjectSizeY * m_Sin) + m_PosX;
	m_NextPosY = (m_ObjectSizeX * m_Sin) + (m_ObjectSizeY * m_Cos) + m_PosY;

	// 게이지볼 true
	if (tempRadian < m_Radian)
	{
		m_pStageManager->SetSpinningGaugeState(true);
	}
	else
	{
		m_pStageManager->SetSpinningGaugeState(false);
	}
}

void SpinningCenterPoint::Radian()
{
	m_Radian = m_Degree * (PI / 180);
	m_Sin = std::sin(m_Radian);
	m_Cos = std::cos(m_Radian);
	m_Tan = std::tan(m_Radian);
}

double SpinningCenterPoint::GetPosX()
{
	return m_MousePosX;
}

double SpinningCenterPoint::GetPosY()
{
	return m_MousePosY;
}

void SpinningCenterPoint::EventDraw()
{
	D2DEngine::GetInstance()->DrawSpriteAlpha(
		eObjectDefine::TESTOBJECT, m_MousePosX, m_MousePosY, m_ObjectAlphaValue);
}

void SpinningCenterPoint::StartEvent()
{
	m_ObjectAlphaValue = 1.0f;
}

void SpinningCenterPoint::EndEvent()
{
	m_ObjectAlphaValue = 1.0f;
}

void SpinningCenterPoint::ExceptionEvent()
{
	m_ObjectAlphaValue = 0.5f;
}

bool SpinningCenterPoint::IsSpinningRotate()
{
	return m_IsSpinningRotate;
}

int SpinningCenterPoint::LocalPosX()
{
	m_LocalPosX = (int)m_MousePosX - (int)m_WorldPosX;
	return m_LocalPosX;
}

int SpinningCenterPoint::LocalPosY()
{
	m_LocalPosY = (int)m_WorldPosY - (int)m_MousePosY;
	return m_LocalPosY;
}

double SpinningCenterPoint::GetDegree()
{
	return this->m_Degree;
}