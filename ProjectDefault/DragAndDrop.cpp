#include "DragAndDrop.h"
#include "MouseManager.h"
#include "SoundManager.h"

DragAndDrop::DragAndDrop()
	: m_ObjectMisTouchState(false)
	, m_ObjectTouchState(false)
	, m_ObjectNextPosIsState(false)
{
	m_pMouseManager = MouseManager::GetInstance();
}

DragAndDrop::~DragAndDrop()
{

}

void DragAndDrop::SetDragAndDrop(
	std::function<void()> ojbectEvent,
	std::function<void()> objectSecondEvent,
	std::function<void()> startEvent,
	std::function<void()> endEvent,
	std::function<void()> exceptionEvent,
	int localPosX, int localPosY,
	int firstStratPosX, int firstStartPosY, int firstEndPosX, int firstEndPosY, 
	int secondStratPosX, int secondStartPosY, int secondEndPosX, int secondEndPosY)
{
	static bool drag = false;
	static bool drop = false;

	// 눌렀을 경우
	if (m_pMouseManager->GetLeftButtonDownState() == true)
	{
		//drop = false;

		// 첫번째 상호작용 이벤트 발생 범위에 있을 경우
		if (localPosX > firstStratPosX && localPosY > firstStartPosY
			&& localPosX < firstEndPosX && localPosY < firstEndPosY
			&& this->m_ObjectMisTouchState == false)
		{
			// 터치 상태 True 변경
			this->m_ObjectTouchState = true;

			///
			if (drag == false)
			{
				SoundManager::GetInstance().PlaySounds(Drag);
				drag = true;
			}

			// 기능구현
			startEvent();
		}	

		// 두번째 상호작용 이벤트 발생 범위에 있을 경우
		if (localPosX > secondStratPosX && localPosY > secondStartPosY
			&& localPosX < secondEndPosX && localPosY < secondEndPosY
			&& this->m_ObjectTouchState == true)
		{
			// 두번째 좌표에 있으면서 마우스를 땠을 때 작동되는 기능을 위한 상태변경
			this->m_ObjectNextPosIsState = true;

			// 기능구현
			endEvent();
		}
		else	// 예외상황 이벤트 발생 시
		{
			// 기능구현
			exceptionEvent();
		}

		// 첫번째 Object 상호작용
		if (this->m_ObjectTouchState == true)
		{
			// 기능구현
			ojbectEvent();
		}

	}	// 버튼을 떼고 범위안에 있을 경우에만 EndEvent 발생
	else if (m_pMouseManager->GetLeftButtonUpState() == true
		&& localPosX > secondStratPosX && localPosY > secondStartPosY
		&& localPosX < secondEndPosX && localPosY < secondEndPosY)
	{
		// 터치 실수 안함 false
		this->m_ObjectTouchState = false;

		// 두번째 Object 상호작용
		if (m_ObjectNextPosIsState == true)
		{
			// 기능구현
			objectSecondEvent();

			///
			if (drop == false)
			{
				SoundManager::GetInstance().PlaySounds(Drop);
				drop = true;
			}

			// 다시 false로 중복 기능 막기
			this->m_ObjectNextPosIsState = false;
		}
	}
	else if (m_pMouseManager->GetLeftButtonUpState() == true)
	{
		// 상태 초기화
		this->m_ObjectNextPosIsState = false;
		this->m_ObjectMisTouchState = false;
		this->m_ObjectTouchState = false;

	}

	if (m_pMouseManager->GetLeftButtonDownState())
	{
		drop = false;
	}

	if (m_pMouseManager->GetLeftButtonUpState())
	{
		drag = false;
	}
}
