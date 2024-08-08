#include "../D2DEngine/D2DEngine.h"
#include "DatumPoint.h"
#include "TimerManager.h"
#include "MouseManager.h"
#include "AnswerBoard.h"
#include "Scene_Knitting.h"
#include "TimerManager.h"
#include "DrawBoard.h"
#include "StageManager.h"

DatumPoint::DatumPoint(const int objectNum, std::string objectName)
 	: Object(objectNum, objectName, 1302, 478), m_DatumSpeed(0), m_DatumX(GetPositionX()), m_DatumY(GetPositionY()), m_PrintXposition(0), m_PrintYposition(0), m_Size(25), m_StartTimer(0), m_EndTimer(0), m_StartX(0), m_ReverseX(0), m_OnDraw(false), m_Count(0), m_GoalCount(0), m_Retry(false), m_Wait(true), m_StartFlag(false), m_ClearFlag(false)
{
	this->renderOrder = KNITTING_ORDER+1;
}

DatumPoint::DatumPoint(const int objectNum, const std::string& objectName, const double posX, const double posY)
	: Object(objectNum, objectName, posX, posY), m_DatumSpeed(0), m_DatumX(posX), m_DatumY(posY), m_PrintXposition(0), m_PrintYposition(0), m_Size(25), m_StartTimer(0), m_EndTimer(0), m_StartX(0), m_ReverseX(0), m_OnDraw(false), m_Count(0), m_GoalCount(0), m_Retry(false), m_Wait(true), m_StartFlag(false), m_ClearFlag(false)
{
	this->renderOrder = KNITTING_ORDER+1;
}

DatumPoint::~DatumPoint()
{

}

void DatumPoint::UpdateObject()
{
	UpdateDrawPosition();
	BasicMove();
}

void DatumPoint::RenderObject()
{
	if (m_OnDraw == true)
	{
 		D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::DatumPoint, GetDrawX(), GetDrawY());
	}

	if (m_Count < m_GoalCount)
	{
		if (4 - m_StartTimer >= 3 && m_StartFlag == true)
		{
			D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::Three, 871, 70);
		}
		else if (3 > 4 - m_StartTimer && 4 - m_StartTimer >= 2 && m_StartFlag == true)
		{
			D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::Two, 871, 70);
		}
		else if (2 > 4 - m_StartTimer && 4 - m_StartTimer >= 1 && m_StartFlag == true)
		{
			D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::One, 871, 70);
		}
	}
}

int DatumPoint::GetSize()
{
	return m_Size;
}

void DatumPoint::SetDrawX(double move)
{
	m_PrintXposition += move;
}

double DatumPoint::GetDrawX()
{
	return m_PrintXposition;
}

double DatumPoint::GetDrawY()
{
	return m_PrintYposition;
}

void DatumPoint::UpdateDrawPosition()
{
	m_PrintXposition = m_DatumX - m_Size;
	m_PrintYposition = m_DatumY - m_Size;
}

int DatumPoint::GetCount()
{
	return m_Count;
}

int DatumPoint::GetGoalCount()
{
	return m_GoalCount;
}

void DatumPoint::SetGoalCount(int goal)
{
	m_GoalCount = goal;
}

void DatumPoint::BasicMove()
{
	// 그리기
	if (m_Count < m_GoalCount && m_StartFlag == true && m_ClearFlag == false)
	{

		// 게임 시작되면 타이머를 잼
		m_StartTimer += TimerManager::GetInstance().GetDeltaTime();
		m_OnDraw = true;

		// 정방향 진행
		if (m_Count % 2 == 0)
		{
			// N초가 지나면 그려지면서 출발 (게임 시작 후 게임 진행까지 타이머), 재시작이 아닐 경우
			if (m_StartTimer >= DATUM_START_TIMER && m_Retry == false)
			{
				m_OnDraw = true;
				m_Wait = false;
				m_DatumX -= m_DatumSpeed *TimerManager::GetInstance().GetDeltaTime();
			}

			// 다시하기 시 N초 뒤에 출발
			else if (m_StartTimer >= DATUM_REPLAY_TIMER && m_Retry == true)
			{
				m_OnDraw = true;
				m_Wait = false;
				m_DatumX -= m_DatumSpeed * TimerManager::GetInstance().GetDeltaTime();
			}

			// 정방향 목적지에 도달하면 그리기 종료, 타이머 시작
			if (m_DatumX <= m_ReverseX)
			{
				m_EndTimer += TimerManager::GetInstance().GetDeltaTime();
				m_OnDraw = false;
				m_Wait = true;
				m_DatumX = m_ReverseX - INTERVAL;
				m_PrintXposition = m_DatumX;
			}
		}

		// 역방향 진행
		else if (m_Count % 2 != 0)
		{
			// N초가 지나면 그려지면서 출발 (게임 시작 후 게임 진행까지 타이머), 재시작이 아닐 경우
			if (m_StartTimer >= DATUM_START_TIMER && m_Retry == false)
			{
				m_OnDraw = true;
				m_Wait = false;
				m_DatumX += m_DatumSpeed * TimerManager::GetInstance().GetDeltaTime();
			}

			// 다시하기 시 N초 뒤에 출발
			else if (m_StartTimer >= DATUM_REPLAY_TIMER && m_Retry == true)
			{
				m_OnDraw = true;
				m_Wait = false;
				m_DatumX += m_DatumSpeed * TimerManager::GetInstance().GetDeltaTime();
			}

			// 역방향 목적지에 도달하면 그리기 종료, 타이머 시작
			if (m_DatumX >= m_StartX)
			{
				m_EndTimer += TimerManager::GetInstance().GetDeltaTime();
				m_OnDraw = false;
				m_Wait = true;
				m_DatumX = m_StartX+ INTERVAL;
				m_PrintXposition = m_DatumX;

			}
		}

		// 대기시간 끝날 시 타이머 종료 및 카운트 추가
		if (m_EndTimer >= DATUM_END_TIMER && m_GoalCount > m_Count)
		{
			m_Count++;
			m_EndTimer = 0;
			m_StartTimer = 0;
		}

		// 목적 카운트 달성하면 그리기 중단
		if (m_Count >= m_GoalCount)
		{
			m_Wait = true,
			m_OnDraw = true;
		}

		// OnDraw가 켜져있을때만 그릴 수 있도록 좌표값을 넘겨줌
		if (m_OnDraw == true)
		{
			SetPositionX(m_DatumX);
			SetPositionX(m_DatumY);
		}
	}
	if (m_ClearFlag == true)
	{
		m_OnDraw = false;
	}
}

// 다시하기 누를 시 초기화
void DatumPoint::InitialzieGame(Scene_Knitting* pKnitting, AnswerBoard* pAnswerBoar, AnswerBoard* p_FirstBoard, DrawBoard* p_DrawBoard)
{
	// 게임 진행 중 카운트가 짝수일 경우 진행중이던 게임 다시 시작하도록
	if (m_Count % 2 == 0 && m_Wait == false && m_OnDraw == true)
	{
		pKnitting->SetAnswerCount(m_Count, 0);
		pKnitting->SetWrongCount(m_Count, 0);
		m_DatumX = m_StartX + INTERVAL;
		m_StartTimer = 0;
		m_OnDraw = false;
		m_Retry = true;
		m_Wait = true;

		p_DrawBoard->SetXflagArray(m_Count);
		while (p_FirstBoard != nullptr)
		{
			p_FirstBoard->SetXdrawFlag(m_Count, false);
			p_FirstBoard = p_FirstBoard->GetNextBoard();
		}
	}

	// 게임 진행 중 카운트가 홀수일 경우 진행중이던 게임 다시 시작하도록
	else if (m_Count % 2 != 0 && m_Wait == false && m_OnDraw == true)
	{
		pKnitting->SetAnswerCount(m_Count, 0);
		pKnitting->SetWrongCount(m_Count, 0);
		m_DatumX = m_ReverseX - INTERVAL;
		m_StartTimer = 0;
		m_OnDraw = false;
		m_Retry = true;
		m_Wait = true;

		p_DrawBoard->SetXflagArray(m_Count);
		while (p_FirstBoard != nullptr)
		{
			p_FirstBoard->SetXdrawFlag(m_Count, false);
			p_FirstBoard = p_FirstBoard->GetNextBoard();
		}
	}

	// 게임 대기 상태일 때 그 전 단계 게임으로 돌아가도록
	else if (m_Wait == true && m_Count > 0 && m_OnDraw == true)
	{
		// 카운트가 짝수일 경우
		if (m_Count % 2 == 0)
		{
			m_DatumX = m_ReverseX - INTERVAL;
			m_StartTimer = 0;
			m_OnDraw = false;
			m_Retry = true;
			m_Wait = true;
			m_Count--;
			pKnitting->SetAnswerCount(m_Count, 0);
			pKnitting->SetWrongCount(m_Count, 0);
			if (m_Count >= 0)
			{
				p_DrawBoard->SetXflagArray(m_Count);
				while (p_FirstBoard != nullptr)
				{
					p_FirstBoard->SetXdrawFlag(m_Count, false);
					p_FirstBoard = p_FirstBoard->GetNextBoard();
				}
			}

		}

		// 카운트가 홀수일 경우
		else if (m_Count % 2 != 0)
		{
			m_DatumX = m_StartX + INTERVAL;
			m_StartTimer = 0;
			m_OnDraw = false;
			m_Retry = true;
			m_Wait = true;
			m_Count--;
			pKnitting->SetAnswerCount(m_Count, 0);
			pKnitting->SetWrongCount(m_Count, 0);
			if (m_Count >= 0)
			{
				p_DrawBoard->SetXflagArray(m_Count);
				while (p_FirstBoard != nullptr)
				{
					p_FirstBoard->SetXdrawFlag(m_Count, false);
					p_FirstBoard = p_FirstBoard->GetNextBoard();
				}
			}
		}
	}
}

double DatumPoint::GetDatumX()
{
	return m_DatumX;
}

void DatumPoint::SetDatumX(double num)
{
	m_DatumX += num;
}

void DatumPoint::SetStartX(double num)
{
	m_StartX = num;
}

void DatumPoint::SetReverseX(double move)
{
	m_ReverseX = move;
}

bool DatumPoint::GetWaitState()
{
	return m_Wait;
}

void DatumPoint::Initialize()
{
	m_DatumX = 1302+ INTERVAL;
	m_DatumY = 478;
	m_StartX = 1302;
	m_ReverseX = 502;
	m_StartTimer = 0, m_EndTimer = 0, m_OnDraw = false, m_Count = 0, m_GoalCount = 0, m_Retry = false, m_Wait = true;
	m_StartFlag = false;
	m_ClearFlag = false;

	m_DatumSpeed = DATUM_GAME_SPEED + DATUM_GAME_SPEED * ((SPEED_INCREASE_PERCENT * (StageManager::GetInstance()->GetStageNum() - 1) * 0.01));
}

void DatumPoint::SetStartTimer(double time)
{
	m_StartTimer = time;
}

void DatumPoint::SetStartFlag(bool OX)
{
	m_StartFlag = OX;
}

bool DatumPoint::GetStartFlag()
{
	return m_StartFlag;
}

void DatumPoint::SetOriginX()
{
	m_DatumX = 1302 + INTERVAL;
}

void DatumPoint::SetClearFlag(bool OX)
{
	m_ClearFlag = OX;
}
