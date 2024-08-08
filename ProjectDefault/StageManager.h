#pragma once
#include "eStageObject.h"
#include <vector>

class SceneManager;
class Scene_Knitting;
class Scene_Average;

/// <summary>
/// 스테이지를 관리할 클래스
/// 1~5 Stage 존재
/// 
/// 2023.02.19 KDW
/// </summary>
class StageManager
{
public:
	static StageManager* GetInstance();

private:
	static StageManager* m_pInstance;

	 StageManager();
	~StageManager();

	SceneManager* m_pSceneManager;

private:
	/// 스테이지 관리
	int m_StageNum;			// Stage Number 명시
	bool m_IsStage;			// Stage가 시작되고 있는지 체크하기 위한 변수

	/// 섬유
	bool m_IsSpiderweb;		// 거미줄		// 1~5 Stage (기본 해금)
	bool m_IsLambswool;		// 램스울		// 2~5 Stage 
	bool m_IsCotton;		// 코튼(목화)	// 3~5 Stage (자동 해금)
	bool m_IsBurlap;		// 삼베실		// 3~5 Stage
	bool m_IsAngoraHair;	// 앙고라털		// 3~5 Stage
	bool m_IsCashmere;		// 캐시미어		// 3~5 Stage

	/// 섬유 스펙
	int m_Warmth[6];			// 보온성
	int m_Durability[6];		// 내구성
	int m_Breathability[6];		// 통기성
	int m_FiberPrice[6];		// 가격
	int m_UnlockPrice[6];		// 해금 가격
	eStageObjectDefine m_Special1[6];	// 특수1
	eStageObjectDefine m_Special2[6];	// 특수2

	int m_WarmthFiber;			// 보온성
	int m_DurabilityFiber;		// 내구성
	int m_BreathabilityFiber;	// 통기성

	// 특수
	eStageObjectDefine m_Elasticity1;	// 탄력
	eStageObjectDefine m_Stiff1;		// 뻣뻣
	eStageObjectDefine m_Softness1;		// 부드러움
	eStageObjectDefine m_HairLoss1;		// 털빠짐 (탈모)
	eStageObjectDefine m_Lightness1;	// 가벼움
	eStageObjectDefine m_Rough1;		// 까끌
	eStageObjectDefine m_NoneSpecial1;	// 특수상태 없음

	bool m_Elasticity;		// 탄력
	bool m_Stiff;			// 뻣뻣
	bool m_Softness;		// 부드러움
	bool m_HairLoss;		// 털빠짐 (탈모)
	bool m_Lightness;		// 가벼움
	bool m_Rough;			// 까끌
	bool m_NoneSpecial;		// 특수상태 없음

	/// 섬유 스펙 등급 (필요한가?)
	const int m_MinLowness	= 0;	// 낮은 등급 최소 0
	const int m_MaxLowness	= 30;	// 낮은 등급 최대 30
	const int m_MinMiddle	= 31;	// 중간 등급 최소 31
	const int m_MaxMiddle	= 70;	// 중간 등급 최대 70
	const int m_MinHigh		= 71;	// 높음 등급 최소 71
	const int m_MaxHigh		= 100;	// 높음 등급 최대 100

	// 등급 상태
	bool m_Lowness;		// 낮음 0~30
	bool m_Middle;		// 중간 31~70
	bool m_High;		// 높음 71~100

	/// Player
	const int m_StartPossessedMoney = 50;	// 시작 소지금
	int m_CurPossessedMoney;				// 현재 소지금
	int m_BudgetCredit;						// 예산 (의뢰금)
	const int m_RethinkMax = 10;			// 한도 수량
	int m_PurchaseCount;					// 구입 count
	int m_Changes;							// 남은 돈(잔돈)
	int m_MisTakeCount;						// 실수 횟수
	int m_AveragePrice;						// 소득 평균
	int m_PercentageTip;					// 팁 감소해야 할 % 크기
	//eStageObjectDefine m_SpecialList[6];

	/// 제작해야 하는 물건
	eStageObjectDefine m_Doll;				// 인형
	eStageObjectDefine m_Muffler;			// 목도리
	eStageObjectDefine m_Bag;				// 가방
	eStageObjectDefine m_Gloves;			// 장갑
	eStageObjectDefine m_Sweater;			// 스웨터

	/// 주문 제작시 필요한 것들
	bool m_WarmthRating[5];				// 필요한 보온성 등급
	bool m_DurabilityRating[5];			// 필요한 내구성 등급
	bool m_BreathabilityRating[5];		// 필요한 통기성 등급
	// Stage마다 다른 값
	int m_CraftingBall;					// 필요한 ball 개수
	int m_StuffPrice;					// 판매가
	bool m_SpecialNeeds;				// 특별한 요구
	int m_ArbitrageMoney;				// 차익
	int m_TipMoney;						// 팁

	/// Scene 미니게임 활성화 변수
	bool m_SpinningGameStart;

	/// Spinning 관련
	int m_SpinningBallRange;		// Spinning 게이지 볼 랜덤 범위 초기화하기 위한 변수
	bool m_SpinningBallObjectState;	// Spinning Ball Object 상태
	bool m_IsSpinningGaugBall;
	// 애니메이션 판단
	bool m_FailAnimation;
	bool m_SucessAnimation;
	bool m_BallAnimation;


	/// 직조 씬 초기화 위한 변수
	Scene_Knitting* m_pKnitting;

	/// 평균 씬 초기화용
	Scene_Average* m_pAverage;
public:
	/// 스테이지당 초기화
	void StageInitialization(int stageNum);
	
	/// Spinning 관련
	void SpinningGaugeBallRangeInit();		// Spinning 게이지 볼 범위 초기화
	void SetSpinningBallObjectState(bool state);
	void SetSpinningGaugeState(bool state);
	void SetFailAnimation(bool state);		// 실패 Object 애니메이션 세팅
	void SetSucessAnimation(bool state);		// 성공 Object 애니메이션 세팅
	void SetBallAnimation(bool state);		// Ball Object 애니메이션 세팅

public:
	/// 기능들
	/// 섬유 해금 조건
	// Stage 번호, 현재 money
	void LambswoolUnlock(int stageNum, int money);	// 램스울 해금
	// Stage 번호, 현재 money
	void BurlapUnlock(int stageNum, int money);		// 삼베실 해금
	// Stage 번호, 현재 money
	void AngoraHairUnlock(int stageNum, int money);	// 앙고라털 해금
	// Stage 번호, 현재 money
	void CashmereUnlock(int stageNum, int money);	// 캐시미어 해금

	/// Stage 관련
	void IsStageChage(bool state);				// 스테이지 작동 상태 변경
	void AddStage();							// 스테이지 넘기기
	void SpinningGameStateChage(bool state);	// Spinning 스테이지 상태 변환

	/// 섬유 구입
	void BuyFiber();

	/// 등급 판단
	void FiberJudgeRating();

	/// 특수 상쇄
	void SpecialOffset(eStageObjectDefine special1, eStageObjectDefine special2);

	/// Player 관련
	void DecreaseMoney(int money);		// 소지금 감소
	void IncreaseMoney(int stageNum, int tipMoney);		// 소지금 증가
	void SetPlayerMisTakeCount(int count);
	void AddPlayerMisTakeCount();		// Player 실수 카운터 증가
	void AddPlayerMisTakeCount(int count);
	void SetAveragePrice(int value);	// Player 수익 평균값 세팅
	void DecreaseTipMoney(int money);	// Tip Money 줄이기
	void SetTimMoneyDecreaseRate(int percentage);	// Tip Percentage 세팅
	void StageEndPlayerMoneyCalculate();	// 스테이지 끝나고 player 소지금 정산
	void TipMoneyCalc();				// Tip 계산

	/// 섬유 관련
	/// 섬유 상태 바꾸기
	void SetElasticity(bool state);		// 탄력
	bool SetStiff(bool state);			// 뻣뻣
	bool SetSoftness(bool state);		// 부드러움
	bool SetHairLoss(bool state);		// 털빠짐
	bool SetLightness(bool state);		// 가벼움
	bool SetRough(bool state);			// 까끌
	bool SetNoneSpecial(bool state);	// 특수상태 없음

	/// <summary>
	/// Stage 클리어 조건
	/// </summary>
	/// <param name="craftingBall"></param>
	/// <param name="warmth"></param>
	/// <param name="durability"></param>
	/// <param name="breathability"></param>
	void StageClearCondition1(int craftingBall, int warmth, int durability, int breathability);
	void StageClearCondition2(int craftingBall, int warmth, int durability, int breathability);
	void StageClearCondition3(int craftingBall, int warmth, int durability, int breathability);
	void StageClearCondition4(int craftingBall, int warmth, int durability, int breathability);
	void StageClearCondition5(int craftingBall, int warmth, int durability, int breathability);

public:
	/// 데이터 반환

	/// Player 관련
	int GetStageNum();				// 스테이지 Number 번호
	int GetStartPossessedMoney();	// Player 시작 소지금
	int GetCurPossessedMoney();		// Player 현재 소지금
	int GetPlayerMisTakeCount();	// Player 실수 Count
	int GetPlayerAveragePrice();	// Player 수익 평균값
	int GetTipMoney();				// TipMoney 반환
	int GetTimMoneyDecreaseRate();	// TipMoney 감소된 금액 반환

	int GetCraftingBall();				// 필요한 ball 개수
	bool isLownessRange(int object);	// 낮은 범위 0~30
	bool isMiddleRange(int object);	// 중간 범위 31~70
	bool isHighRange(int object);		// 높음 범위 71~

	/// 섬유 관련
	bool GetSpiderwebUnlockState();		// 거미줄 해금 상태
	bool GetLambswoolUnlockState();		// 램스울 해금 상태
	bool GetCottonUnlockState();		// 코튼 해금 상태
	bool GetBurlapUnlockState();		// 삼베실 해금 상태
	bool GetAngoraHairUnlockState();	// 앙고라털 해금 상태
	bool GetCashmereUnlockState();		// 캐시미어 해금 상태

	int GetWarmthFiber();				// 보온성 수치
	int GetDurabilityFiber();			// 내구성 수치
	int GetBreathabilityFiber();		// 통기성 수치

	bool GetElasticity();				// 탄력
	bool GetStiff();					// 뻣뻣
	bool GetSoftness();					// 부드러움
	bool GetHairLoss();					// 털빠짐
	bool GetLightness();				// 가벼움
	bool GetRough();					// 까끌
	bool GetNoneSpecial();				// 특수상태 없음

	/// Stage 관련
	bool GetIsStageState();				// 현재 스테이지 작동 상태

	/// Spinning 관련
	bool GetSpinningGameState();		// Spinning 게임 활성화 상태
	int GetSpinningGaugeBallRange();	// Spinning 게이지 볼 범위
	bool IsSpinningBallObjectState();	// Spinning Ball object 상태
	bool IsSpinningGaugeBallState();	// Spinning Gauge Ball 상태
	bool IsFailAnimation();			// 실패 Object 애니메이션
	bool IsSucessAnimation();			// 성공 Object 애니메이션
	bool IsBallAnimation();		// Ball Object 애니메이션

	void InitialKnittingScene(Scene_Knitting* p_knitting);
	void InitializeAverageScene(Scene_Average* p_average);

	void SetStage(int stage);
	void InitialShop();
};