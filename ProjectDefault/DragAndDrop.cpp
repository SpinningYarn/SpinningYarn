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

	// ������ ���
	if (m_pMouseManager->GetLeftButtonDownState() == true)
	{
		//drop = false;

		// ù��° ��ȣ�ۿ� �̺�Ʈ �߻� ������ ���� ���
		if (localPosX > firstStratPosX && localPosY > firstStartPosY
			&& localPosX < firstEndPosX && localPosY < firstEndPosY
			&& this->m_ObjectMisTouchState == false)
		{
			// ��ġ ���� True ����
			this->m_ObjectTouchState = true;

			///
			if (drag == false)
			{
				SoundManager::GetInstance().PlaySounds(Drag);
				drag = true;
			}

			// ��ɱ���
			startEvent();
		}	

		// �ι�° ��ȣ�ۿ� �̺�Ʈ �߻� ������ ���� ���
		if (localPosX > secondStratPosX && localPosY > secondStartPosY
			&& localPosX < secondEndPosX && localPosY < secondEndPosY
			&& this->m_ObjectTouchState == true)
		{
			// �ι�° ��ǥ�� �����鼭 ���콺�� ���� �� �۵��Ǵ� ����� ���� ���º���
			this->m_ObjectNextPosIsState = true;

			// ��ɱ���
			endEvent();
		}
		else	// ���ܻ�Ȳ �̺�Ʈ �߻� ��
		{
			// ��ɱ���
			exceptionEvent();
		}

		// ù��° Object ��ȣ�ۿ�
		if (this->m_ObjectTouchState == true)
		{
			// ��ɱ���
			ojbectEvent();
		}

	}	// ��ư�� ���� �����ȿ� ���� ��쿡�� EndEvent �߻�
	else if (m_pMouseManager->GetLeftButtonUpState() == true
		&& localPosX > secondStratPosX && localPosY > secondStartPosY
		&& localPosX < secondEndPosX && localPosY < secondEndPosY)
	{
		// ��ġ �Ǽ� ���� false
		this->m_ObjectTouchState = false;

		// �ι�° Object ��ȣ�ۿ�
		if (m_ObjectNextPosIsState == true)
		{
			// ��ɱ���
			objectSecondEvent();

			///
			if (drop == false)
			{
				SoundManager::GetInstance().PlaySounds(Drop);
				drop = true;
			}

			// �ٽ� false�� �ߺ� ��� ����
			this->m_ObjectNextPosIsState = false;
		}
	}
	else if (m_pMouseManager->GetLeftButtonUpState() == true)
	{
		// ���� �ʱ�ȭ
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
