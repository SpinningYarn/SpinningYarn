#include "SpinningGaugeManager.h"
#include <random>
#include <time.h>

#include "TimerManager.h"

// 클래스의 static 변수를 초기화
SpinningGaugeManager* SpinningGaugeManager::m_pInstance = nullptr;

SpinningGaugeManager* SpinningGaugeManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new SpinningGaugeManager();
	}

	return m_pInstance;
}

SpinningGaugeManager::SpinningGaugeManager()
	: m_GaugeBarCount(0)
	, m_GauageBarPosX(0)
	, m_GauageBarPosY(0)
	, m_GauageBallPosX(0)
	, m_GauageBallPosY(0)
	, m_GauageNumCount(0)
	, m_RandomGauge(0)
	, m_RandomGaugeTimeCount(0)
	, m_IsRandomCount(false)
	, m_AlphaValue(1)
	, m_FailAnimation(false)
	, m_SucessAnimation(false)
	, m_BallAnimation(false)
{
}

SpinningGaugeManager::~SpinningGaugeManager()
{

}

void SpinningGaugeManager::SetGauageBarPos(int posX, int posY)
{
	m_GauageBarPosX = posX;
	m_GauageBarPosY = posY;
}

void SpinningGaugeManager::SetGauageBallPos(int posX, int posY)
{
	m_GauageBallPosX = posX;
	m_GauageBallPosY = posY;
}

void SpinningGaugeManager::SetRandomPos()
{
	srand(time(NULL) * TimerManager::GetInstance().GetDeltaTime());
	m_RandomGauge = rand() % (360 - 120) + (700 + m_Preheat);
}

void SpinningGaugeManager::SetFailAnimation(bool state)
{
	m_FailAnimation = state;
}

void SpinningGaugeManager::SetSucessAnimation(bool state)
{
	m_SucessAnimation = state;
}

void SpinningGaugeManager::SetBallAnimation(bool state)
{
	m_BallAnimation = state;
}

void SpinningGaugeManager::CountIncrease(int num)
{
	m_GauageNumCount = num;
}

void SpinningGaugeManager::RandomPosCounting()
{
	m_RandomGaugeTimeCount++;
}

void SpinningGaugeManager::RandomPosCountInit()
{
	m_RandomGaugeTimeCount = 0;
}

void SpinningGaugeManager::RandomIsCountChage(bool isRandom)
{
	m_IsRandomCount = isRandom;
}

void SpinningGaugeManager::RandomGaugeAlphaValue(float value)
{
	m_AlphaValue = value;
}

int SpinningGaugeManager::GetGauageCount()
{
	return m_GauageNumCount;
}

int SpinningGaugeManager::GetMaxGaugeBar()
{
	return m_MaxGaugeBar;
}

int SpinningGaugeManager::GetPreheatSize()
{
	return m_Preheat;
}

int SpinningGaugeManager::GetOverloadSize()
{
	return m_Overload;
}

int SpinningGaugeManager::GetPercent10Gauge()
{
	return m_Percent10Gauge;
}

float SpinningGaugeManager::GetRandomGaugePosX()
{
	return m_RandomGauge;
}

int SpinningGaugeManager::GetRandomTimeCount()
{
	return m_RandomGaugeTimeCount;
}

bool SpinningGaugeManager::GetRandomIsCount()
{
	return m_IsRandomCount;
}

float SpinningGaugeManager::GetRandomGaugeAlphaValue()
{
	return m_AlphaValue;
}

bool SpinningGaugeManager::IsFailAnimation()
{
	return m_FailAnimation;
}

bool SpinningGaugeManager::IsSucessAnimation()
{
	return m_SucessAnimation;
}

bool SpinningGaugeManager::IsBallAnimation()
{
	return m_BallAnimation;
}
