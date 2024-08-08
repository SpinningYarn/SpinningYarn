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
	// �׸���
	if (m_Count < m_GoalCount && m_StartFlag == true && m_ClearFlag == false)
	{

		// ���� ���۵Ǹ� Ÿ�̸Ӹ� ��
		m_StartTimer += TimerManager::GetInstance().GetDeltaTime();
		m_OnDraw = true;

		// ������ ����
		if (m_Count % 2 == 0)
		{
			// N�ʰ� ������ �׷����鼭 ��� (���� ���� �� ���� ������� Ÿ�̸�), ������� �ƴ� ���
			if (m_StartTimer >= DATUM_START_TIMER && m_Retry == false)
			{
				m_OnDraw = true;
				m_Wait = false;
				m_DatumX -= m_DatumSpeed *TimerManager::GetInstance().GetDeltaTime();
			}

			// �ٽ��ϱ� �� N�� �ڿ� ���
			else if (m_StartTimer >= DATUM_REPLAY_TIMER && m_Retry == true)
			{
				m_OnDraw = true;
				m_Wait = false;
				m_DatumX -= m_DatumSpeed * TimerManager::GetInstance().GetDeltaTime();
			}

			// ������ �������� �����ϸ� �׸��� ����, Ÿ�̸� ����
			if (m_DatumX <= m_ReverseX)
			{
				m_EndTimer += TimerManager::GetInstance().GetDeltaTime();
				m_OnDraw = false;
				m_Wait = true;
				m_DatumX = m_ReverseX - INTERVAL;
				m_PrintXposition = m_DatumX;
			}
		}

		// ������ ����
		else if (m_Count % 2 != 0)
		{
			// N�ʰ� ������ �׷����鼭 ��� (���� ���� �� ���� ������� Ÿ�̸�), ������� �ƴ� ���
			if (m_StartTimer >= DATUM_START_TIMER && m_Retry == false)
			{
				m_OnDraw = true;
				m_Wait = false;
				m_DatumX += m_DatumSpeed * TimerManager::GetInstance().GetDeltaTime();
			}

			// �ٽ��ϱ� �� N�� �ڿ� ���
			else if (m_StartTimer >= DATUM_REPLAY_TIMER && m_Retry == true)
			{
				m_OnDraw = true;
				m_Wait = false;
				m_DatumX += m_DatumSpeed * TimerManager::GetInstance().GetDeltaTime();
			}

			// ������ �������� �����ϸ� �׸��� ����, Ÿ�̸� ����
			if (m_DatumX >= m_StartX)
			{
				m_EndTimer += TimerManager::GetInstance().GetDeltaTime();
				m_OnDraw = false;
				m_Wait = true;
				m_DatumX = m_StartX+ INTERVAL;
				m_PrintXposition = m_DatumX;

			}
		}

		// ���ð� ���� �� Ÿ�̸� ���� �� ī��Ʈ �߰�
		if (m_EndTimer >= DATUM_END_TIMER && m_GoalCount > m_Count)
		{
			m_Count++;
			m_EndTimer = 0;
			m_StartTimer = 0;
		}

		// ���� ī��Ʈ �޼��ϸ� �׸��� �ߴ�
		if (m_Count >= m_GoalCount)
		{
			m_Wait = true,
			m_OnDraw = true;
		}

		// OnDraw�� ������������ �׸� �� �ֵ��� ��ǥ���� �Ѱ���
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

// �ٽ��ϱ� ���� �� �ʱ�ȭ
void DatumPoint::InitialzieGame(Scene_Knitting* pKnitting, AnswerBoard* pAnswerBoar, AnswerBoard* p_FirstBoard, DrawBoard* p_DrawBoard)
{
	// ���� ���� �� ī��Ʈ�� ¦���� ��� �������̴� ���� �ٽ� �����ϵ���
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

	// ���� ���� �� ī��Ʈ�� Ȧ���� ��� �������̴� ���� �ٽ� �����ϵ���
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

	// ���� ��� ������ �� �� �� �ܰ� �������� ���ư�����
	else if (m_Wait == true && m_Count > 0 && m_OnDraw == true)
	{
		// ī��Ʈ�� ¦���� ���
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

		// ī��Ʈ�� Ȧ���� ���
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
