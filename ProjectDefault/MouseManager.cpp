#include "MouseManager.h"
#include "TimerManager.h"
#include "SoundManager.h"

#include <windowsx.h>
#include <math.h>

// 클래스의 static 변수를 초기화하는 방법
MouseManager* MouseManager::m_pInstance = nullptr;

MouseManager* MouseManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MouseManager();
	}

	return m_pInstance;
}

MouseManager::MouseManager()
	: m_PosX()
	, m_PosY()
	, m_PevPosX()
	, m_PevPosY()
	, m_Speed()
	, m_DeltaTime()
	, m_Distance()
	, m_EveX()
	, m_EveY()
	, m_InputTimeCount()
	, m_LeftUpClick(false)
	, m_LeftDownClick(false)
	, m_LeftDownDoubleClick(false)
	, m_RightUpClick(false)
	, m_RightDownClick(false)
	, m_RightDownDoubleClick(false)
	, m_LParam(NULL)
	, m_OneClickOn(false)
	, m_ObjectTouchState(false)
	, m_ObjectMisTouchState(false)
	, m_oneClickCount(0)
	, m_IsOneClickUp(false)
	, m_ObjectNextPosIsState(false)
{
	
}

MouseManager::~MouseManager()
{

}

void MouseManager::Initialize(LPARAM lParam)
{
	m_LParam = lParam;
}

void MouseManager::SetPevMousePos()
{
	m_PevPosX = GET_X_LPARAM(m_LParam);
	m_PevPosY = GET_Y_LPARAM(m_LParam);
}

void MouseManager::Update()
{
	// 실시간 좌표 받기
	m_PosX = GET_X_LPARAM(m_LParam);
	m_PosY = GET_Y_LPARAM(m_LParam);

	ClickSound();

	// 좌클릭 중이라면
	if (GetLeftButtonDownState() == true)
	{
		SpeedCalc();
		InputCount();
	}
	else
	{
		m_InputTimeCount = 0;
	}
}

void MouseManager::GetLeftButtonUpChangeState(bool state)
{
	m_LeftUpClick = state;
}

void MouseManager::GetLeftButtonDownChangeState(bool state)
{
	m_LeftDownClick = state;
}

void MouseManager::GetRightButtonUpChangeState(bool state)
{
	m_RightUpClick = state;
}

void MouseManager::GetRightButtonDownChangeState(bool state)
{
	m_RightDownClick = state;
}

bool MouseManager::GetLeftButtonUpState()
{
	return m_LeftUpClick;
}

bool MouseManager::GetLeftButtonDownState()
{
	return m_LeftDownClick;
}

bool MouseManager::GetLeftDoubleButtonState()
{
	return m_LeftDownDoubleClick;
}

bool MouseManager::GetRightButtonUpState()
{
	return m_RightUpClick;
}

bool MouseManager::GetRightButtonDownState()
{
	return m_RightDownClick;
}

bool MouseManager::GetRightDoubleButtonState()
{
	return m_RightDownDoubleClick;
}

float MouseManager::GetXPos()
{
	return m_PosX;
}

float MouseManager::GetYPos()
{
	return m_PosY;
}

int MouseManager::GetPevXpos()
{
	return m_PevPosX;
}

int MouseManager::GetPevYpos()
{
	return m_PevPosY;
}

double MouseManager::GetSpeed()
{
	return m_Speed;
}

int MouseManager::GetInputTime()
{
	return m_InputTimeCount;
}

void MouseManager::EvePosUpdate()
{
	m_EveX = m_PosX;
	m_EveY = m_PosY;
}

void MouseManager::SpeedCalc()
{
	m_Distance = abs(m_PosX - m_EveX) + abs(m_PosY - m_EveY);	// 현재 마우스 위치 - 직전 마우스 위치

	m_DeltaTime = TimerManager::GetInstance().GetDeltaTime();
	m_Speed = (double)m_Distance / m_DeltaTime * m_DPI;
	EvePosUpdate();
}

void MouseManager::InputCount()
{
	if (TimerManager::GetInstance().GetFPS() >= 1)
	{
		m_InputTimeCount++;
	}
}

/// 클릭 사운드
void MouseManager::ClickSound()
{
	if (GetLeftOneDownClickState() == true)
	{
		SoundManager::GetInstance().PlaySounds(Click);
	}
}

bool MouseManager::GetLeftOneDownClickState()
{
	if (GetLeftButtonDownState() == false)
	{
		m_OneClickOn = false;
	}

	if (GetLeftButtonDownState() == true)
	{
		if (m_OneClickOn == true && m_oneClickCount == 0)
		{
			return false;
		}
		m_OneClickOn = true;
		m_oneClickCount++;
		return true;
	}
	return false;
}

bool MouseManager::GetLeftOneUpClickState()
{
	if (GetLeftButtonDownState() == true)
	{
		m_IsOneClickUp = false;
	}

	if (GetLeftButtonUpState() == true)
	{
		if (m_IsOneClickUp == true && m_oneClickCount == 0)
		{
			return false;
		}
		m_IsOneClickUp = true;
		m_oneClickCount++;
		return true;
	}
	return false;
}

bool MouseManager::GetRightOneDownClickState()
{
	if (GetRightButtonDownState() == false)
	{
		m_OneClickOn = false;
	}

	if (GetRightButtonDownState() == true)
	{
		if (m_OneClickOn == true && m_oneClickCount == 0)
		{
			return false;
		}
		m_OneClickOn = true;
		m_oneClickCount++;
		return true;
	}
	return false;
}

bool MouseManager::GetRightOneUpClickState()
{
	if (GetRightButtonDownState() == true)
	{
		m_IsOneClickUp = false;
	}

	if (GetRightButtonUpState() == true)
	{
		if (m_IsOneClickUp == true && m_oneClickCount == 0)
		{
			return false;
		}
		m_IsOneClickUp = true;
		m_oneClickCount++;
		return true;
	}
	return false;
}

void MouseManager::OneClickEnd()
{
	m_oneClickCount = 0;
}

void MouseManager::DragAndDrop(
	std::function<void()> ojbectEvent,
	std::function<void()> objectSecondEvent,
	std::function<void()> startEvent,
	std::function<void()> endEvent,
	std::function<void()> exceptionEvent,
	int localPosX, int localPosY,
	int firstStratPosX, int firstStartPosY, int firstEndPosX, int firstEndPosY,
	int secondStratPosX, int secondStartPosY, int secondEndPosX, int secondEndPosY)
{
	// 눌렀을 경우
	if (GetLeftButtonDownState() == true)
	{
		// 첫번째 상호작용 이벤트 발생 범위에 있을 경우
		if (localPosX > firstStratPosX && localPosY > firstStartPosY
			&& localPosX < firstEndPosX && localPosY < firstEndPosY
			&& this->m_ObjectMisTouchState == false)
		{
			this->m_ObjectTouchState = true;
				
			// 기능구현
			startEvent();
		}	// 두번째 상호작용 이벤트 발생 범위에 있을 경우
		else if (localPosX > secondStratPosX && localPosY > secondStartPosY
			&& localPosX < secondEndPosX && localPosY < secondEndPosY
			&& this->m_ObjectTouchState == true)
		{
			// 두번째 좌표에 있으면서 마우스를 땠을 때 작동되는 기능을 위한 상태변경
			this->m_ObjectNextPosIsState = true;

			// 기능구현
			endEvent();
		}
		else										// 예외상황 이벤트 발생 시
		{
			this->m_ObjectMisTouchState = true;

			// 기능구현
			exceptionEvent();
		}

		// 이벤트가 발생했을 경우
		if (this->m_ObjectTouchState == true)
		{
			// 기능구현
			ojbectEvent();
		}
	}
	else if (GetLeftButtonUpState() == true)					// 상호작용 없을 때 상태
	{
		if (m_ObjectNextPosIsState == true)
		{
			objectSecondEvent();
		}

		this->m_ObjectNextPosIsState = false;
		this->m_ObjectMisTouchState = false;
		this->m_ObjectTouchState = false;
	}
}

void MouseManager::ResetMousePoint()
{
	m_PosX = 920.0f;
	m_PosY = 500.0f;
	m_LeftDownClick = true;
	m_LeftUpClick = true;
	m_LeftDownClick = false;
	m_LeftUpClick = false;
}
