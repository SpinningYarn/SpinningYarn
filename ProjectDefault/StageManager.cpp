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
	/// 재료 수치 초기화
	// 거미줄
	m_Warmth[0] = 10;
	m_Durability[0] = 50;
	m_Breathability[0] = 40;
	m_FiberPrice[0] = 10;
	m_UnlockPrice[0] = 0;
	m_Special1[0] = m_NoneSpecial1;
	m_Special2[0] = m_NoneSpecial1;

	// 램스울
	m_Warmth[1] = 60;
	m_Durability[1] = 55;
	m_Breathability[1] = 30;
	m_FiberPrice[1] = 50;
	m_UnlockPrice[1] = 40;
	m_Special1[1] = m_Elasticity1;
	m_Special2[1] = m_Rough1;

	// 코튼(목화)
	m_Warmth[2] = 40;
	m_Durability[2] = 80;
	m_Breathability[2] = 60;
	m_FiberPrice[2] = 40;
	m_UnlockPrice[2] = 0;
	m_Special1[2] = m_Stiff1;
	m_Special2[2] = m_NoneSpecial1;

	// 삼베실
	m_Warmth[3] = 5;
	m_Durability[3] = 60;
	m_Breathability[3] = 80;
	m_FiberPrice[3] = 20;
	m_UnlockPrice[3] = 55;
	m_Special1[3] = m_NoneSpecial1;
	m_Special2[3] = m_Rough1;

	// 앙고라털
	m_Warmth[4] = 80;
	m_Durability[4] = 20;
	m_Breathability[4] = 35;
	m_FiberPrice[4] = 60;
	m_UnlockPrice[4] = 90;
	m_Special1[4] = m_NoneSpecial1;
	m_Special2[4] = m_Softness1;

	// 캐시미어
	m_Warmth[5] = 100;
	m_Durability[5] = 45;
	m_Breathability[5] = 70;
	m_FiberPrice[5] = 70;
	m_UnlockPrice[5] = 120;
	m_Special1[5] = m_NoneSpecial1;
	m_Special2[5] = m_Softness1;

	/// 판매할 물건 수치 초기화
	// 필요한 등급
	for (int i = 0; i < 5; i++)
	{
		m_WarmthRating[i] = false;
		m_DurabilityRating[i] = false;
		m_BreathabilityRating[i] = false;
	}

	// Player 소지금
	m_CurPossessedMoney = m_StartPossessedMoney;
}

StageManager::~StageManager()
{

}

void StageManager::StageInitialization(int stageNum)
{
	if (stageNum == 1)
	{
		// 구매상태
		m_IsSpiderweb = true;		// 거미줄	
		m_IsLambswool = false;		// 램스울	
		m_IsCotton = false;			// 코튼(목화)
		m_IsBurlap = false;			// 삼베실	
		m_IsAngoraHair = false;		// 앙고라털	
		m_IsCashmere = false;		// 캐시미어	

		// 판매될 물건
		m_CraftingBall = 1;				// 필요한 ball 개수
		m_StuffPrice = 30;				// 판매가
		m_SpecialNeeds = true;			// 특별한 요구
		m_ArbitrageMoney = 20;			// 차익
		m_TipMoney = 0;					// 팁

		// 섬유 상태 초기화
		m_Elasticity	= false;	// 탄력
		m_Stiff			= false;	// 뻣뻣
		m_Softness		= false;	// 부드러움
		m_HairLoss		= false;	// 털빠짐 (탈모)
		m_Lightness		= false;	// 가벼움
		m_Rough			= false;	// 까끌
		m_NoneSpecial	= false;	// 특수상태 없음

		// Player 관련 초기화
		m_MisTakeCount = 0;			// 실수 count
		m_CurPossessedMoney = 0;
		m_CurPossessedMoney = m_StartPossessedMoney;

		// Scene 미니게임 활성화 초기화
		m_SpinningGameStart = true;
		m_SpinningBallObjectState = false;
		m_FailAnimation = false;
		m_SucessAnimation = false;
		m_BallAnimation = true;
		m_pKnitting->GotoNextStage();
	}
	else if (stageNum == 2)
	{
		// 구매상태
		m_IsSpiderweb = true;		// 거미줄	
		m_IsLambswool = false;		// 램스울	
		m_IsCotton = false;			// 코튼(목화)
		m_IsBurlap = false;			// 삼베실	
		m_IsAngoraHair = false;		// 앙고라털	
		m_IsCashmere = false;		// 캐시미어	

		// 판매될 물건
		m_CraftingBall = 2;				// 필요한 ball 개수
		m_StuffPrice = 80;				// 판매가
		m_SpecialNeeds = true;			// 특별한 요구
		m_ArbitrageMoney = 20;			// 차익
		m_TipMoney = 50;				// 팁

		// 섬유 상태 초기화
		m_Elasticity = false;	// 탄력
		m_Stiff = false;	// 뻣뻣
		m_Softness = false;	// 부드러움
		m_HairLoss = false;	// 털빠짐 (탈모)
		m_Lightness = false;	// 가벼움
		m_Rough = false;	// 까끌
		m_NoneSpecial = false;	// 특수상태 없음

		// Player 관련 초기화
		m_MisTakeCount = 0;			// 실수 count

		// Scene 미니게임 활성화 초기화
		m_SpinningGameStart = true;
		m_SpinningBallObjectState = false;
		m_FailAnimation = false;
		m_SucessAnimation = false;
		m_BallAnimation = true;
		m_pKnitting->GotoNextStage();
	}
	else if (stageNum == 3)
	{
		// 구매상태
		m_IsSpiderweb = true;		// 거미줄	
		m_IsLambswool = false;		// 램스울	
		m_IsCotton = true;			// 코튼(목화)
		m_IsBurlap = false;			// 삼베실	
		m_IsAngoraHair = false;		// 앙고라털	
		m_IsCashmere = false;		// 캐시미어

		// 판매될 물건
		m_CraftingBall = 4;			// 필요한 ball 개수
		m_StuffPrice = 150;			// 판매가
		m_SpecialNeeds = false;		// 특별한 요구
		m_TipMoney = 50;			// 팁

		srand(time(NULL) * TimerManager::GetInstance().GetDeltaTime());
		m_ArbitrageMoney = rand() % 45 + 5;		// 차익

		// 섬유 상태 초기화
		m_Elasticity = false;	// 탄력
		m_Stiff = false;	// 뻣뻣
		m_Softness = false;	// 부드러움
		m_HairLoss = false;	// 털빠짐 (탈모)
		m_Lightness = false;	// 가벼움
		m_Rough = false;	// 까끌
		m_NoneSpecial = false;	// 특수상태 없음

		// Player 관련 초기화
		m_MisTakeCount = 0;			// 실수 count

		// Scene 미니게임 활성화 초기화
		m_SpinningGameStart = true;
		m_SpinningBallObjectState = false;
		m_FailAnimation = false;
		m_SucessAnimation = false;
		m_BallAnimation = true;
		m_pKnitting->GotoNextStage();
	}
	else if (stageNum == 4)
	{
		// 구매상태
		m_IsSpiderweb = true;		// 거미줄	
		m_IsLambswool = false;		// 램스울	
		m_IsCotton = true;			// 코튼(목화)
		m_IsBurlap = false;			// 삼베실	
		m_IsAngoraHair = false;		// 앙고라털	
		m_IsCashmere = false;		// 캐시미어	

		// 판매될 물건
		m_CraftingBall = 4;				// 필요한 ball 개수
		m_StuffPrice = 270;				// 판매가
		m_SpecialNeeds = false;			// 특별한 요구
		m_TipMoney = 70;				// 팁

		srand(time(NULL) * TimerManager::GetInstance().GetDeltaTime());
		m_ArbitrageMoney = rand() % 45 + 5;		// 차익

		// 섬유 상태 초기화
		m_Elasticity = false;	// 탄력
		m_Stiff = false;	// 뻣뻣
		m_Softness = false;	// 부드러움
		m_HairLoss = false;	// 털빠짐 (탈모)
		m_Lightness = false;	// 가벼움
		m_Rough = false;	// 까끌
		m_NoneSpecial = false;	// 특수상태 없음

		// Player 관련 초기화
		m_MisTakeCount = 0;			// 실수 count

		// Scene 미니게임 활성화 초기화
		m_SpinningGameStart = true;
		m_SpinningBallObjectState = false;
		m_FailAnimation = false;
		m_SucessAnimation = false;
		m_BallAnimation = true;
		m_pKnitting->GotoNextStage();
	}
	else if (stageNum == 5)
	{
		// 구매상태
		m_IsSpiderweb = true;		// 거미줄	
		m_IsLambswool = false;		// 램스울	
		m_IsCotton = true;			// 코튼(목화)
		m_IsBurlap = false;			// 삼베실	
		m_IsAngoraHair = false;		// 앙고라털	
		m_IsCashmere = false;		// 캐시미어	

		// 판매될 물건
		m_CraftingBall = 5;				// 필요한 ball 개수
		m_StuffPrice = 350;				// 판매가
		m_SpecialNeeds = false;			// 특별한 요구
		m_TipMoney = 100;				// 팁

		srand(time(NULL) * TimerManager::GetInstance().GetDeltaTime());
		m_ArbitrageMoney = rand() % 45 + 5;		// 차익

		// 섬유 상태 초기화
		m_Elasticity = false;	// 탄력
		m_Stiff = false;	// 뻣뻣
		m_Softness = false;	// 부드러움
		m_HairLoss = false;	// 털빠짐 (탈모)
		m_Lightness = false;	// 가벼움
		m_Rough = false;	// 까끌
		m_NoneSpecial = false;	// 특수상태 없음

		// Player 관련 초기화
		m_MisTakeCount = 0;			// 실수 count

		// Scene 미니게임 활성화 초기화
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

	/// 여기에 각종 씬 초기화 코드 넣으면 될듯
	if (m_StageNum > 1)
	{
		m_pAverage->ToStage2();			//2스테이지일때 인벤토리에 코튼이 안 들어있으면 넣어줌
	}
	m_pAverage->ResetInfos();			//평균씬에서 스탯박스 초기화
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
	// 소지금 증가			//팁						//차익
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
	// 3번 이상 실패했을 경우
	if (GetPlayerMisTakeCount() >= 16)
	{
		// 팁 100% 까임
		SetTimMoneyDecreaseRate(100);
	}
	else if (GetPlayerMisTakeCount() >= 13)
	{
		// 팁 80%
		SetTimMoneyDecreaseRate(80);
	}
	else if (GetPlayerMisTakeCount() >= 10)
	{
		// 팁 60%
		SetTimMoneyDecreaseRate(60);
	}
	else if (GetPlayerMisTakeCount() >= 7)
	{
		// 팁 40%
		SetTimMoneyDecreaseRate(40);
	}
	else if (GetPlayerMisTakeCount() >= 4)
	{
		// 팁 20%
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
	// 필요 볼 1, 보온성 : 낮음, 내구성, 중간
	if (m_CraftingBall < craftingBall &&
		m_MinLowness >= warmth && m_MaxLowness < warmth &&
		m_MinMiddle >= durability && m_MaxMiddle <= durability)
	{
		// 현재 돈이 차익보다 높다면 다음 소지금에 더하기
		if (m_CurPossessedMoney > m_ArbitrageMoney)
		{
			m_CurPossessedMoney += m_ArbitrageMoney + m_TipMoney;
		}
	}
}

void StageManager::StageClearCondition2(int craftingBall, int warmth, int durability, int breathability)
{
	// 필요 볼 3개, 보온성 : 중간, 내구성 중간
	if (m_CraftingBall <= craftingBall &&
		m_MinMiddle >= warmth && m_MaxMiddle <= warmth &&
		m_MinMiddle >= durability && m_MaxMiddle <= durability)
	{
		// 현재 돈이 차익보다 높다면 다음 소지금에 더하기
		if (m_CurPossessedMoney > m_ArbitrageMoney)
		{
			m_CurPossessedMoney += m_ArbitrageMoney + m_TipMoney;
		}
	}
}

void StageManager::StageClearCondition3(int craftingBall, int warmth, int durability, int breathability)
{
	// 필요 볼 4개, 내구성 : 높음, 통기성 : 중간, 특수 : 뻣뻣
	if (m_CraftingBall <= craftingBall &&
		m_MinHigh >= durability && m_MaxHigh <= durability &&
		m_MinMiddle >= breathability && m_MaxMiddle <= breathability)
	{
		// 현재 돈이 차익보다 높다면 다음 소지금에 더하기
		if (m_CurPossessedMoney > m_ArbitrageMoney)
		{
			m_CurPossessedMoney += m_ArbitrageMoney + m_TipMoney;
		}
	}
}

void StageManager::StageClearCondition4(int craftingBall, int warmth, int durability, int breathability)
{
	// 필요 볼 4개, 보온성 : 중간, 내구성 : 중간, 통기성 : 중간, 특수 : 까끌 x
	if (m_CraftingBall < craftingBall &&
		m_MinMiddle >= warmth && m_MaxMiddle <= warmth &&
		m_MinMiddle >= durability && m_MaxMiddle <= durability &&
		m_MinMiddle >= breathability && m_MaxMiddle <= breathability)
	{
		// 현재 돈이 차익보다 높다면 다음 소지금에 더하기
		if (m_CurPossessedMoney > m_ArbitrageMoney)
		{
			m_CurPossessedMoney += m_ArbitrageMoney + m_TipMoney;
		}
	}
}

void StageManager::StageClearCondition5(int craftingBall, int warmth, int durability, int breathability)
{
	// 필요 볼 5개, 보온성 : 높음, 내구성 : 중간, 특수 : 부드러움
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
