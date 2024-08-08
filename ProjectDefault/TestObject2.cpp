#include "TestObject2.h"
#include "../D2DEngine/D2DEngine.h"
#include "../D2DEngine/Animator.h"
#include "KeyManager.h"

/// <summary>
/// �� ������Ʈ�� ���� ���岨��
/// ���� ������ ö�� 3�� �����ϵ���
/// </summary>

Animator* ani = new Animator();

TestObject2::TestObject2(const int& objectNum, std::string objectName)
	: Object(objectNum, objectName), playingAnimation(false), localD2D(nullptr),
	m_raindowReady(false)
{
	this->renderOrder = OBJECT_ORDER + 9999;
	localD2D = D2DEngine::GetInstance();
}

TestObject2::TestObject2(int objectNum, std::string objectName, double posX, double posY)
	: Object(objectNum, objectName, posX, posY), playingAnimation(false), localD2D(nullptr)		// X,Y��ǥ �������ֱ�
	, m_raindowReady(false)
{	
	this->renderOrder = OBJECT_ORDER + 9999;
	localD2D = D2DEngine::GetInstance();

	
}

TestObject2::~TestObject2()
{
	
}

void TestObject2::UpdateObject()
{
	/*if (KeyManager::GetInstance().GetKeyAndState(Key::A) == KeyState::TAP && this->m_raindowReady == true)
	{
		if (this->playingAnimation == false) this->playingAnimation = true;
		else if (this->playingAnimation == true) this->playingAnimation = false;
	}

	if (KeyManager::GetInstance().GetKeyAndState(Key::S) == KeyState::TAP)
	{
		this->m_raindowReady = true;
	}

	rot += 10;
	if (rot >= 360)
	{
		rot = 0;
	}
	����++;
	if (���� >= 16)
	{
		���� = 1;
	}*/
}

void TestObject2::RenderObject()
{
	/*if (this->playingAnimation == true)
	{
		localD2D->DrawSprite(eObjectDefine::CAT_WALKK, 700, 140, rot);

		if (���� == 1 || ���� == 5 || ���� == 9 || ���� == 13)
		{
			localD2D->DrawSpriteAlpha(eObjectDefine::BACK_RED, 0, 0, 0.5f);
		}
		else if (���� == 2 || ���� == 6 || ���� == 10 || ���� == 14)
		{
			localD2D->DrawSpriteAlpha(eObjectDefine::BACK_BLUE, 0, 0, 0.5f);
		}
		else if (���� == 3 || ���� == 7 || ���� == 11 || ���� == 15)
		{
			localD2D->DrawSpriteAlpha(eObjectDefine::BACK_GREEN, 0, 0, 0.5f);
		}
		else if (���� == 4 || ���� == 8 || ���� == 12 || ���� == 16)
		{
			localD2D->DrawSpriteAlpha(eObjectDefine::BACK_YELLOW, 0, 0, 0.5f);
		}
	}*/
}
