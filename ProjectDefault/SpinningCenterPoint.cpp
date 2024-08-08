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
	// �ǽð� ���콺 ��ǥ ����
	m_MousePosX = m_pMouseManager->GetXPos();
	m_MousePosY = m_pMouseManager->GetYPos();

	// ����, ���� ���콺 ��ǥ ����
	m_CurMousePosX = (int)m_pMouseManager->GetXPos();
	m_CurMousePosY = (int)m_pMouseManager->GetYPos();

	m_PevMousePosX = m_pMouseManager->GetPevXpos();
	m_PevMousePosY = m_pMouseManager->GetPevYpos();

	// ���� �帣�� �ð�
	m_AccTime += (float)TimerManager::GetInstance().GetDeltaTime();

	// ���콺 �ӵ� ��
	m_Speed = m_pMouseManager->GetSpeed();

	// 1�ʴ� �� ���������� ����
	m_CurFrame++;

	if (m_AccTime >= 0.1)
	{
		// ���� 0���� �ٽ� �ʱ�ȭ
		m_AccTime = 0;
		m_CurFrame = 0;

		// ���� ���콺 ��ǥ ����
		MouseManager::GetInstance()->SetPevMousePos();
	}

	// �� ���� �������� ī����
	if (m_Degree >= 360)
	{
		m_CountRotate++;	// �ѹ����� ī��Ʈ ����
		m_pSpinningGaugeManager->CountIncrease(m_CountRotate);	// SpinningBall�� ����� ī��Ʈ ����
		m_CountRotate = 0;	// ī��Ʈ �ʱ�ȭ	
		m_Degree = 0;		// ���� �ʱ�ȭ
	}

	static bool spin = false;

	if (m_pStageManager->GetSpinningGameState() == true)
	{
		// ���콺(��) Ŭ�� �ÿ��� �۵�
		if (m_pMouseManager->GetLeftButtonDownState() == true
			&& m_OneSpinningWheelRange == true)
		{

			/// �߽������� ��ǥ�� 4��� ��Ų �����̴�.
			// ������ ��
			if (m_PosX <= m_pMouseManager->GetXPos() && m_PosY > m_pMouseManager->GetYPos()
				&& m_CurMousePosX > m_PevMousePosX && m_CurMousePosY > m_PevMousePosY)
			{
				// ���� ���� �ȿ� ���� ���
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
			// ������ �Ʒ�
			else if (m_PosX <= m_pMouseManager->GetXPos() && m_PosY <= m_pMouseManager->GetYPos()
				&& m_CurMousePosX <= m_PevMousePosX && m_CurMousePosY > m_PevMousePosY)
			{
				// ���� ���� �ȿ� ���� ���
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
			// ���� �Ʒ�
			else if (m_PosX > m_pMouseManager->GetXPos() && m_PosY <= m_pMouseManager->GetYPos()
				&& m_CurMousePosX <= m_PevMousePosX && m_CurMousePosY <= m_PevMousePosY)
			{
				// ���� ���� �ȿ� ���� ���
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
			// ���� ��
			else if (m_PosX > m_pMouseManager->GetXPos() && m_PosY > m_pMouseManager->GetYPos()
				&& m_CurMousePosX > m_PevMousePosX && m_CurMousePosY <= m_PevMousePosY)
			{
				// ���� ���� �ȿ� ���� ���
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

	// ���콺�� ���� ���
	if (m_pMouseManager->GetLeftButtonDownState() == false)
	{
		// �������� false
		m_pStageManager->SetSpinningGaugeState(false);

		SoundManager::GetInstance().StopBGM(MerryGoRound);

		m_Degree = 0;
		m_IsSpinningWheelRange = false;
		m_OneSpinningWheelRange = true;
	}

	// ���콺 ���¿� ��ǥ ���°� ��� ���� ��� ���� ���� ��ȯ
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
	/// �߽� ��ǥ ǥ�� (��ǥ ����׿�)
	//// �߽� x, y ��ǥ ǥ��, �ѹ��� ī����
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

	/// ����� ������ �ǽð� ���콺 ��ǥ�� ǥ�� (��ǥ ����׿�)
	//// ���� ���콺 ��ǥ
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

	//// ���� ���콺 ��ǥ
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

	/// Spinning Wheel ���߾� ��ǥ Render (��ǥ ������)
	//D2DEngine::GetInstance()->DrawLine((int)m_NextPosX, (int)m_NextPosY, (int)m_PosX, (int)m_PosY, 1);
	//D2DEngine::GetInstance()->DrawRect((int)m_PosX, (int)m_PosY, (int)m_NextPosX, (int)m_NextPosY);

	/// �ǽð� ���콺 ��ǥ Render (��ǥ ������)
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

	/// ��ǥ ���� ������ �������� ���� m_Degree�� ȸ���Ǵ� �� (PrevPos x,y)�� ���� (NectPos x,y) ���
	// �̵��� ��ǥ = width ��ǥ * cosR (-+) Hight ��ǥ * sinR + �߽���ǥ
	m_NextPosX = (m_ObjectSizeX * m_Cos) - (m_ObjectSizeY * m_Sin) + m_PosX;
	m_NextPosY = (m_ObjectSizeX * m_Sin) + (m_ObjectSizeY * m_Cos) + m_PosY;

	// �������� true
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