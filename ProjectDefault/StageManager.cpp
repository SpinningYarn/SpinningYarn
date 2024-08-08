#include <random>
#include "StageManager.h"
#include "TimerManager.h"
#include "eStageObject.h"
#include "SceneManager.h"
#include "SpinningGaugeManager.h"
#include "Scene_Knitting.h"
#include "Scene_Average.h"

StageManager* StageManager::m_pInstance = nullptr;

StageManager* StageManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new StageManager();
	}

	return m_pInstance;
}

StageManager::StageManager()
	: m_pSceneManager(NULL)
	, m_StageNum(1)
	, m_IsSpiderweb(false), m_IsLambswool(false), m_IsCotton(false)
	, m_IsBurlap(false), m_IsAngoraHair(false), m_IsCashmere(false)
	, m_Elasticity1(eStageObjectDefine::Elasticity)
	, m_Stiff1(eStageObjectDefine::Stiff)
	, m_WarmthFiber(0), m_DurabilityFiber(0), m_BreathabilityFiber(0)
	, m_Softness1(eStageObjectDefine::Softness)
	, m_HairLoss1(eStageObjectDefine::HairLoss)
	, m_Lightness1(eStageObjectDefine::Lightness)
	, m_Rough1(eStageObjectDefine::Rough)
	, m_NoneSpecial1(eStageObjectDefine::NoneSpecial)
	, m_Elasticity(false), m_Stiff(false), m_Softness(false)
	, m_HairLoss(false), m_Lightness(false), m_Rough(false), m_NoneSpecial(false)
	, m_Lowness(false), m_Middle(false), m_High(false)
	, m_PurchaseCount(0), m_Changes(0)
	, m_BudgetCredit(30), m_MisTakeCount(0), m_AveragePrice(0), m_PercentageTip(0)
	, m_Doll(eStageObjectDefine::Doll)
	, m_Muffler(eStageObjectDefine::Muffler)
	, m_Bag(eStageObjectDefine::Bag)
	, m_Gloves(eStageObjectDefine::Gloves)
	, m_Sweater(eStageObjectDefine::Sweater)
	, m_CraftingBall(0), m_StuffPrice(30)
	, m_SpecialNeeds(false)
	, m_TipMoney(0), m_ArbitrageMoney(0)
	, m_SpinningGameStart(true)
	, m_IsStage(false)
	, m_SpinningBallRange(0)
	, m_pKnitting(nullptr)
	, m_pAverage(nullptr)
	, m_SpinningBallObjectState(false)
	, m_IsSpinningGaugBall(false)
	, m_FailAnimation(false)
	, m_SucessAnimation(false)
	, m_BallAnimation(true)
{
	/// ��� ��ġ �ʱ�ȭ
	// �Ź���
	m_Warmth[0] = 10;
	m_Durability[0] = 50;
	m_Breathability[0] = 40;
	m_FiberPrice[0] = 10;
	m_UnlockPrice[0] = 0;
	m_Special1[0] = m_NoneSpecial1;
	m_Special2[0] = m_NoneSpecial1;

	// ������
	m_Warmth[1] = 60;
	m_Durability[1] = 55;
	m_Breathability[1] = 30;
	m_FiberPrice[1] = 50;
	m_UnlockPrice[1] = 40;
	m_Special1[1] = m_Elasticity1;
	m_Special2[1] = m_Rough1;

	// ��ư(��ȭ)
	m_Warmth[2] = 40;
	m_Durability[2] = 80;
	m_Breathability[2] = 60;
	m_FiberPrice[2] = 40;
	m_UnlockPrice[2] = 0;
	m_Special1[2] = m_Stiff1;
	m_Special2[2] = m_NoneSpecial1;

	// �ﺣ��
	m_Warmth[3] = 5;
	m_Durability[3] = 60;
	m_Breathability[3] = 80;
	m_FiberPrice[3] = 20;
	m_UnlockPrice[3] = 55;
	m_Special1[3] = m_NoneSpecial1;
	m_Special2[3] = m_Rough1;

	// �Ӱ����
	m_Warmth[4] = 80;
	m_Durability[4] = 20;
	m_Breathability[4] = 35;
	m_FiberPrice[4] = 60;
	m_UnlockPrice[4] = 90;
	m_Special1[4] = m_NoneSpecial1;
	m_Special2[4] = m_Softness1;

	// ĳ�ù̾�
	m_Warmth[5] = 100;
	m_Durability[5] = 45;
	m_Breathability[5] = 70;
	m_FiberPrice[5] = 70;
	m_UnlockPrice[5] = 120;
	m_Special1[5] = m_NoneSpecial1;
	m_Special2[5] = m_Softness1;

	/// �Ǹ��� ���� ��ġ �ʱ�ȭ
	// �ʿ��� ���
	for (int i = 0; i < 5; i++)
	{
		m_WarmthRating[i] = false;
		m_DurabilityRating[i] = false;
		m_BreathabilityRating[i] = false;
	}

	// Player ������
	m_CurPossessedMoney = m_StartPossessedMoney;
}

StageManager::~StageManager()
{

}

void StageManager::StageInitialization(int stageNum)
{
	if (stageNum == 1)
	{
		// ���Ż���
		m_IsSpiderweb = true;		// �Ź���	
		m_IsLambswool = false;		// ������	
		m_IsCotton = false;			// ��ư(��ȭ)
		m_IsBurlap = false;			// �ﺣ��	
		m_IsAngoraHair = false;		// �Ӱ����	
		m_IsCashmere = false;		// ĳ�ù̾�	

		// �Ǹŵ� ����
		m_CraftingBall = 1;				// �ʿ��� ball ����
		m_StuffPrice = 30;				// �ǸŰ�
		m_SpecialNeeds = true;			// Ư���� �䱸
		m_ArbitrageMoney = 20;			// ����
		m_TipMoney = 0;					// ��

		// ���� ���� �ʱ�ȭ
		m_Elasticity	= false;	// ź��
		m_Stiff			= false;	// ����
		m_Softness		= false;	// �ε巯��
		m_HairLoss		= false;	// �к��� (Ż��)
		m_Lightness		= false;	// ������
		m_Rough			= false;	// ���
		m_NoneSpecial	= false;	// Ư������ ����

		// Player ���� �ʱ�ȭ
		m_MisTakeCount = 0;			// �Ǽ� count
		m_CurPossessedMoney = 0;
		m_CurPossessedMoney = m_StartPossessedMoney;

		// Scene �̴ϰ��� Ȱ��ȭ �ʱ�ȭ
		m_SpinningGameStart = true;
		m_SpinningBallObjectState = false;
		m_FailAnimation = false;
		m_SucessAnimation = false;
		m_BallAnimation = true;
		m_pKnitting->GotoNextStage();
	}
	else if (stageNum == 2)
	{
		// ���Ż���
		m_IsSpiderweb = true;		// �Ź���	
		m_IsLambswool = false;		// ������	
		m_IsCotton = false;			// ��ư(��ȭ)
		m_IsBurlap = false;			// �ﺣ��	
		m_IsAngoraHair = false;		// �Ӱ����	
		m_IsCashmere = false;		// ĳ�ù̾�	

		// �Ǹŵ� ����
		m_CraftingBall = 2;				// �ʿ��� ball ����
		m_StuffPrice = 80;				// �ǸŰ�
		m_SpecialNeeds = true;			// Ư���� �䱸
		m_ArbitrageMoney = 20;			// ����
		m_TipMoney = 50;				// ��

		// ���� ���� �ʱ�ȭ
		m_Elasticity = false;	// ź��
		m_Stiff = false;	// ����
		m_Softness = false;	// �ε巯��
		m_HairLoss = false;	// �к��� (Ż��)
		m_Lightness = false;	// ������
		m_Rough = false;	// ���
		m_NoneSpecial = false;	// Ư������ ����

		// Player ���� �ʱ�ȭ
		m_MisTakeCount = 0;			// �Ǽ� count

		// Scene �̴ϰ��� Ȱ��ȭ �ʱ�ȭ
		m_SpinningGameStart = true;
		m_SpinningBallObjectState = false;
		m_FailAnimation = false;
		m_SucessAnimation = false;
		m_BallAnimation = true;
		m_pKnitting->GotoNextStage();
	}
	else if (stageNum == 3)
	{
		// ���Ż���
		m_IsSpiderweb = true;		// �Ź���	
		m_IsLambswool = false;		// ������	
		m_IsCotton = true;			// ��ư(��ȭ)
		m_IsBurlap = false;			// �ﺣ��	
		m_IsAngoraHair = false;		// �Ӱ����	
		m_IsCashmere = false;		// ĳ�ù̾�

		// �Ǹŵ� ����
		m_CraftingBall = 4;			// �ʿ��� ball ����
		m_StuffPrice = 150;			// �ǸŰ�
		m_SpecialNeeds = false;		// Ư���� �䱸
		m_TipMoney = 50;			// ��

		srand(time(NULL) * TimerManager::GetInstance().GetDeltaTime());
		m_ArbitrageMoney = rand() % 45 + 5;		// ����

		// ���� ���� �ʱ�ȭ
		m_Elasticity = false;	// ź��
		m_Stiff = false;	// ����
		m_Softness = false;	// �ε巯��
		m_HairLoss = false;	// �к��� (Ż��)
		m_Lightness = false;	// ������
		m_Rough = false;	// ���
		m_NoneSpecial = false;	// Ư������ ����

		// Player ���� �ʱ�ȭ
		m_MisTakeCount = 0;			// �Ǽ� count

		// Scene �̴ϰ��� Ȱ��ȭ �ʱ�ȭ
		m_SpinningGameStart = true;
		m_SpinningBallObjectState = false;
		m_FailAnimation = false;
		m_SucessAnimation = false;
		m_BallAnimation = true;
		m_pKnitting->GotoNextStage();
	}
	else if (stageNum == 4)
	{
		// ���Ż���
		m_IsSpiderweb = true;		// �Ź���	
		m_IsLambswool = false;		// ������	
		m_IsCotton = true;			// ��ư(��ȭ)
		m_IsBurlap = false;			// �ﺣ��	
		m_IsAngoraHair = false;		// �Ӱ����	
		m_IsCashmere = false;		// ĳ�ù̾�	

		// �Ǹŵ� ����
		m_CraftingBall = 4;				// �ʿ��� ball ����
		m_StuffPrice = 270;				// �ǸŰ�
		m_SpecialNeeds = false;			// Ư���� �䱸
		m_TipMoney = 70;				// ��

		srand(time(NULL) * TimerManager::GetInstance().GetDeltaTime());
		m_ArbitrageMoney = rand() % 45 + 5;		// ����

		// ���� ���� �ʱ�ȭ
		m_Elasticity = false;	// ź��
		m_Stiff = false;	// ����
		m_Softness = false;	// �ε巯��
		m_HairLoss = false;	// �к��� (Ż��)
		m_Lightness = false;	// ������
		m_Rough = false;	// ���
		m_NoneSpecial = false;	// Ư������ ����

		// Player ���� �ʱ�ȭ
		m_MisTakeCount = 0;			// �Ǽ� count

		// Scene �̴ϰ��� Ȱ��ȭ �ʱ�ȭ
		m_SpinningGameStart = true;
		m_SpinningBallObjectState = false;
		m_FailAnimation = false;
		m_SucessAnimation = false;
		m_BallAnimation = true;
		m_pKnitting->GotoNextStage();
	}
	else if (stageNum == 5)
	{
		// ���Ż���
		m_IsSpiderweb = true;		// �Ź���	
		m_IsLambswool = false;		// ������	
		m_IsCotton = true;			// ��ư(��ȭ)
		m_IsBurlap = false;			// �ﺣ��	
		m_IsAngoraHair = false;		// �Ӱ����	
		m_IsCashmere = false;		// ĳ�ù̾�	

		// �Ǹŵ� ����
		m_CraftingBall = 5;				// �ʿ��� ball ����
		m_StuffPrice = 350;				// �ǸŰ�
		m_SpecialNeeds = false;			// Ư���� �䱸
		m_TipMoney = 100;				// ��

		srand(time(NULL) * TimerManager::GetInstance().GetDeltaTime());
		m_ArbitrageMoney = rand() % 45 + 5;		// ����

		// ���� ���� �ʱ�ȭ
		m_Elasticity = false;	// ź��
		m_Stiff = false;	// ����
		m_Softness = false;	// �ε巯��
		m_HairLoss = false;	// �к��� (Ż��)
		m_Lightness = false;	// ������
		m_Rough = false;	// ���
		m_NoneSpecial = false;	// Ư������ ����

		// Player ���� �ʱ�ȭ
		m_MisTakeCount = 0;			// �Ǽ� count

		// Scene �̴ϰ��� Ȱ��ȭ �ʱ�ȭ
		m_SpinningGameStart = true;
		m_SpinningBallObjectState = false;
		m_FailAnimation = false;
		m_SucessAnimation = false;
		m_BallAnimation = true;
		m_pKnitting->GotoNextStage();
	}
}

void StageManager::SpinningGaugeBallRangeInit()
{
	m_SpinningBallRange = (int)SpinningGaugeManager::GetInstance()->GetRandomGaugePosX() - 60;
}

void StageManager::SetSpinningBallObjectState(bool state)
{
	m_SpinningBallObjectState = state;
}

void StageManager::SetSpinningGaugeState(bool state)
{
	m_IsSpinningGaugBall = state;
}

void StageManager::SetFailAnimation(bool state)
{
	m_FailAnimation = state;
}

void StageManager::SetSucessAnimation(bool state)
{
	m_SucessAnimation = state;
}

void StageManager::SetBallAnimation(bool state)
{
	m_BallAnimation = state;
}

void StageManager::LambswoolUnlock(int stageNum, int money)
{
	if (m_UnlockPrice[stageNum] <= money)
	{
		m_IsLambswool = true;
		m_CurPossessedMoney -= money;
	}
}

void StageManager::BurlapUnlock(int stageNum, int money)
{
	if (m_UnlockPrice[stageNum] <= money)
	{
		m_IsBurlap = true;
		m_CurPossessedMoney -= money;
	}
}

void StageManager::AngoraHairUnlock(int stageNum, int money)
{
	if (m_UnlockPrice[stageNum] <= money)
	{
		m_IsAngoraHair = true;
		m_CurPossessedMoney -= money;
	}
}

void StageManager::CashmereUnlock(int stageNum, int money)
{
	if (m_UnlockPrice[stageNum] <= money)
	{
		m_IsCashmere = true;
		m_CurPossessedMoney -= money;
	}
}

void StageManager::IsStageChage(bool state)
{
	m_IsStage = state;
}

void StageManager::AddStage()
{
	m_StageNum++;

	if (m_StageNum > 5)
	{
		m_StageNum = 1;
	}

	/// ���⿡ ���� �� �ʱ�ȭ �ڵ� ������ �ɵ�
	if (m_StageNum > 1)
	{
		m_pAverage->ToStage2();			//2���������϶� �κ��丮�� ��ư�� �� ��������� �־���
	}
	m_pAverage->ResetInfos();			//��վ����� ���ȹڽ� �ʱ�ȭ
	m_pKnitting->GotoNextStage();
}

void StageManager::SpinningGameStateChage(bool state)
{
	m_SpinningGameStart = state;
}

void StageManager::BuyFiber()
{
	if (m_StageNum == 1)
	{
		if (m_PurchaseCount < 10)
		{
			m_Warmth[0] += 10;
			m_PurchaseCount++;
		}
	}
}

void StageManager::FiberJudgeRating()
{

}

void StageManager::SpecialOffset(eStageObjectDefine special1, eStageObjectDefine special2)
{
	if (m_Elasticity1 == special1 && m_Stiff1 == special2)
	{

	}
}

void StageManager::DecreaseMoney(int money)
{
	m_CurPossessedMoney -= money;
	
	if (m_CurPossessedMoney < 0)
	{
		m_CurPossessedMoney = 0;
	}
}

void StageManager::IncreaseMoney(int stageNum, int tipMoney)
{
	// ������ ����			//��						//����
	m_CurPossessedMoney += tipMoney + (m_StuffPrice - m_AveragePrice);
}

void StageManager::SetPlayerMisTakeCount(int count)
{
	m_MisTakeCount = count;
}

void StageManager::AddPlayerMisTakeCount()
{
	m_MisTakeCount++;
}

void StageManager::AddPlayerMisTakeCount(int count)
{
	m_MisTakeCount += count;
}

void StageManager::SetAveragePrice(int value)
{
	m_AveragePrice = value;
}

void StageManager::DecreaseTipMoney(int money)
{
	m_TipMoney -= money;
}

void StageManager::SetTimMoneyDecreaseRate(int percentage)
{
	m_PercentageTip = percentage;
}

void StageManager::StageEndPlayerMoneyCalculate()
{
	m_CurPossessedMoney = m_AveragePrice + m_TipMoney;
}

void StageManager::TipMoneyCalc()
{
	// 3�� �̻� �������� ���
	if (GetPlayerMisTakeCount() >= 16)
	{
		// �� 100% ����
		SetTimMoneyDecreaseRate(100);
	}
	else if (GetPlayerMisTakeCount() >= 13)
	{
		// �� 80%
		SetTimMoneyDecreaseRate(80);
	}
	else if (GetPlayerMisTakeCount() >= 10)
	{
		// �� 60%
		SetTimMoneyDecreaseRate(60);
	}
	else if (GetPlayerMisTakeCount() >= 7)
	{
		// �� 40%
		SetTimMoneyDecreaseRate(40);
	}
	else if (GetPlayerMisTakeCount() >= 4)
	{
		// �� 20%
		SetTimMoneyDecreaseRate(20);
	}
}

void StageManager::SetElasticity(bool state)
{
	m_Elasticity = state;
}

bool StageManager::SetStiff(bool state)
{
	return m_Stiff = state;
}

bool StageManager::SetSoftness(bool state)
{
	return m_Softness = state;
}

bool StageManager::SetHairLoss(bool state)
{
	return m_HairLoss = state;
}

bool StageManager::SetLightness(bool state)
{
	return m_Lightness = state;
}

bool StageManager::SetRough(bool state)
{
	return m_Rough = state;
}

bool StageManager::SetNoneSpecial(bool state)
{
	return m_NoneSpecial = state;
}

void StageManager::StageClearCondition1(int craftingBall, int warmth, int durability, int breathability)
{
	// �ʿ� �� 1, ���¼� : ����, ������, �߰�
	if (m_CraftingBall < craftingBall &&
		m_MinLowness >= warmth && m_MaxLowness < warmth &&
		m_MinMiddle >= durability && m_MaxMiddle <= durability)
	{
		// ���� ���� ���ͺ��� ���ٸ� ���� �����ݿ� ���ϱ�
		if (m_CurPossessedMoney > m_ArbitrageMoney)
		{
			m_CurPossessedMoney += m_ArbitrageMoney + m_TipMoney;
		}
	}
}

void StageManager::StageClearCondition2(int craftingBall, int warmth, int durability, int breathability)
{
	// �ʿ� �� 3��, ���¼� : �߰�, ������ �߰�
	if (m_CraftingBall <= craftingBall &&
		m_MinMiddle >= warmth && m_MaxMiddle <= warmth &&
		m_MinMiddle >= durability && m_MaxMiddle <= durability)
	{
		// ���� ���� ���ͺ��� ���ٸ� ���� �����ݿ� ���ϱ�
		if (m_CurPossessedMoney > m_ArbitrageMoney)
		{
			m_CurPossessedMoney += m_ArbitrageMoney + m_TipMoney;
		}
	}
}

void StageManager::StageClearCondition3(int craftingBall, int warmth, int durability, int breathability)
{
	// �ʿ� �� 4��, ������ : ����, ��⼺ : �߰�, Ư�� : ����
	if (m_CraftingBall <= craftingBall &&
		m_MinHigh >= durability && m_MaxHigh <= durability &&
		m_MinMiddle >= breathability && m_MaxMiddle <= breathability)
	{
		// ���� ���� ���ͺ��� ���ٸ� ���� �����ݿ� ���ϱ�
		if (m_CurPossessedMoney > m_ArbitrageMoney)
		{
			m_CurPossessedMoney += m_ArbitrageMoney + m_TipMoney;
		}
	}
}

void StageManager::StageClearCondition4(int craftingBall, int warmth, int durability, int breathability)
{
	// �ʿ� �� 4��, ���¼� : �߰�, ������ : �߰�, ��⼺ : �߰�, Ư�� : ��� x
	if (m_CraftingBall < craftingBall &&
		m_MinMiddle >= warmth && m_MaxMiddle <= warmth &&
		m_MinMiddle >= durability && m_MaxMiddle <= durability &&
		m_MinMiddle >= breathability && m_MaxMiddle <= breathability)
	{
		// ���� ���� ���ͺ��� ���ٸ� ���� �����ݿ� ���ϱ�
		if (m_CurPossessedMoney > m_ArbitrageMoney)
		{
			m_CurPossessedMoney += m_ArbitrageMoney + m_TipMoney;
		}
	}
}

void StageManager::StageClearCondition5(int craftingBall, int warmth, int durability, int breathability)
{
	// �ʿ� �� 5��, ���¼� : ����, ������ : �߰�, Ư�� : �ε巯��
	if (m_CraftingBall < craftingBall &&
		m_MinLowness >= warmth && m_MaxLowness < warmth &&
		m_MinMiddle >= durability && m_MaxMiddle <= durability)
	{
	}
}

int StageManager::GetStageNum()
{
	return m_StageNum;
}

int StageManager::GetStartPossessedMoney()
{
	return m_StartPossessedMoney;
}

int StageManager::GetCurPossessedMoney()
{
	return m_CurPossessedMoney;
}

int StageManager::GetPlayerMisTakeCount()
{
	return m_MisTakeCount;
}

int StageManager::GetPlayerAveragePrice()
{
	return m_AveragePrice;
}

int StageManager::GetTipMoney()
{
	return m_TipMoney;
}

int StageManager::GetTimMoneyDecreaseRate()
{
	return m_TipMoney * m_PercentageTip / 100;
}

int StageManager::GetCraftingBall()
{
	return m_CraftingBall;
}

bool StageManager::isLownessRange(int object)
{
	if (0 <= object && object <= 30)
	{
		return true;
	}
	return false;
}

bool StageManager::isMiddleRange(int object)
{
	if (31 <= object && object <= 70)
	{
		return true;
	}
	return false;
}

bool StageManager::isHighRange(int object)
{
	if (71 <= object && object <= 100)
	{
		return true;
	}
	return false;
}

bool StageManager::GetSpiderwebUnlockState()
{
	return m_IsSpiderweb;
}

bool StageManager::GetLambswoolUnlockState()
{
	return m_IsLambswool;
}

bool StageManager::GetCottonUnlockState()
{
	return m_IsCotton;
}

bool StageManager::GetBurlapUnlockState()
{
	return m_IsBurlap;
}

bool StageManager::GetAngoraHairUnlockState()
{
	return m_IsAngoraHair;
}

bool StageManager::GetCashmereUnlockState()
{
	return m_IsCashmere;
}

int StageManager::GetWarmthFiber()
{
	return m_WarmthFiber;
}

int StageManager::GetDurabilityFiber()
{
	return m_DurabilityFiber;
}

int StageManager::GetBreathabilityFiber()
{
	return m_BreathabilityFiber;
}

bool StageManager::GetElasticity()
{
	return m_Elasticity;
}

bool StageManager::GetStiff()
{
	return m_Stiff;
}

bool StageManager::GetSoftness()
{
	return m_Softness;
}

bool StageManager::GetHairLoss()
{
	return m_HairLoss;
}

bool StageManager::GetLightness()
{
	return m_Lightness;
}

bool StageManager::GetRough()
{
	return m_Rough;
}

bool StageManager::GetNoneSpecial()
{
	return m_NoneSpecial;
}

bool StageManager::GetIsStageState()
{
	return m_IsStage;
}

bool StageManager::GetSpinningGameState()
{
	return m_SpinningGameStart;
}
int StageManager::GetSpinningGaugeBallRange()
{
	return m_SpinningBallRange;
}

bool StageManager::IsSpinningBallObjectState()
{
	return m_SpinningBallObjectState;
}

bool StageManager::IsSpinningGaugeBallState()
{
	return m_IsSpinningGaugBall;
}

bool StageManager::IsFailAnimation()
{
	return m_FailAnimation;
}

bool StageManager::IsSucessAnimation()
{
	return m_SucessAnimation;
}

bool StageManager::IsBallAnimation()
{
	return m_BallAnimation;
}

void StageManager::InitialKnittingScene(Scene_Knitting* p_knitting)
{
	m_pKnitting = p_knitting;
}

void StageManager::InitializeAverageScene(Scene_Average* p_average)
{
	m_pAverage = p_average;
}

void StageManager::SetStage(int stage)
{
	m_StageNum = stage;
}

void StageManager::InitialShop()
{
	m_pAverage->ResetShopInven();
}
