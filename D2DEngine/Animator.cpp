#include "Animator.h"
#include "../ProjectDefault/TimerManager.h"

Animator::Animator()
	: animationList(), timeCheck(0), m_deltaTime(0), m_CurFrame(0)
{

}

Animator::~Animator()
{

}

void Animator::AddAnimation(D2DSprite* sprite)
{
	animationList.push_back(sprite);
}

void Animator::PlayAnimation(int posX, int posY, float duration, int divide)
{
	static int count = 0;

	if (animationList.empty())
	{
		return;
	}

	m_deltaTime += (float)TimerManager::GetInstance().GetDeltaTime();
	m_CurFrame++;

	count = m_CurFrame / divide;

	if (m_deltaTime >= duration)
	{
		// 값들 0으로 다시 초기화
		m_deltaTime = 0;
		m_CurFrame = 0;
	}


	if (count < animationList.size())
	{
		D2DEngine::GetInstance()->DrawSprite(count, posX, posY, animationList);
	}

	if (count >= animationList.size())
	{
		return;
	}

	//D2DEngine::GetInstance()->DrawText(400, 400, count);

}

void Animator::ClearAnimation()
{
	animationList.clear();
}
