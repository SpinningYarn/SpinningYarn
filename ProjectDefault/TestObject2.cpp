#include "TestObject2.h"
#include "../D2DEngine/D2DEngine.h"
#include "../D2DEngine/Animator.h"
#include "KeyManager.h"

/// <summary>
/// ÀÌ ¿ÀºêÁ§Æ®´Â ÀÌÁ¦ ÆÀÀå²¨´Ù
/// ÀÌÀÇ ÀÖÀ¸¸é Ã¶±Ç 3¼± µµÀüÇÏµµ·Ï
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
	: Object(objectNum, objectName, posX, posY), playingAnimation(false), localD2D(nullptr)		// X,YÁÂÇ¥ ÁöÁ¤ÇØÁÖ±â
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
	µ¥Çò++;
	if (µ¥Çò >= 16)
	{
		µ¥Çò = 1;
	}*/
}

void TestObject2::RenderObject()
{
	/*if (this->playingAnimation == true)
	{
		localD2D->DrawSprite(eObjectDefine::CAT_WALKK, 700, 140, rot);

		if (µ¥Çò == 1 || µ¥Çò == 5 || µ¥Çò == 9 || µ¥Çò == 13)
		{
			localD2D->DrawSpriteAlpha(eObjectDefine::BACK_RED, 0, 0, 0.5f);
		}
		else if (µ¥Çò == 2 || µ¥Çò == 6 || µ¥Çò == 10 || µ¥Çò == 14)
		{
			localD2D->DrawSpriteAlpha(eObjectDefine::BACK_BLUE, 0, 0, 0.5f);
		}
		else if (µ¥Çò == 3 || µ¥Çò == 7 || µ¥Çò == 11 || µ¥Çò == 15)
		{
			localD2D->DrawSpriteAlpha(eObjectDefine::BACK_GREEN, 0, 0, 0.5f);
		}
		else if (µ¥Çò == 4 || µ¥Çò == 8 || µ¥Çò == 12 || µ¥Çò == 16)
		{
			localD2D->DrawSpriteAlpha(eObjectDefine::BACK_YELLOW, 0, 0, 0.5f);
		}
	}*/
}
