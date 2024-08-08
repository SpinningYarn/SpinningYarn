#pragma once
#include "eStageObject.h"
#include <vector>

class SceneManager;
class Scene_Knitting;
class Scene_Average;

/// <summary>
/// ���������� ������ Ŭ����
/// 1~5 Stage ����
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
	/// �������� ����
	int m_StageNum;			// Stage Number ���
	bool m_IsStage;			// Stage�� ���۵ǰ� �ִ��� üũ�ϱ� ���� ����

	/// ����
	bool m_IsSpiderweb;		// �Ź���		// 1~5 Stage (�⺻ �ر�)
	bool m_IsLambswool;		// ������		// 2~5 Stage 
	bool m_IsCotton;		// ��ư(��ȭ)	// 3~5 Stage (�ڵ� �ر�)
	bool m_IsBurlap;		// �ﺣ��		// 3~5 Stage
	bool m_IsAngoraHair;	// �Ӱ����		// 3~5 Stage
	bool m_IsCashmere;		// ĳ�ù̾�		// 3~5 Stage

	/// ���� ����
	int m_Warmth[6];			// ���¼�
	int m_Durability[6];		// ������
	int m_Breathability[6];		// ��⼺
	int m_FiberPrice[6];		// ����
	int m_UnlockPrice[6];		// �ر� ����
	eStageObjectDefine m_Special1[6];	// Ư��1
	eStageObjectDefine m_Special2[6];	// Ư��2

	int m_WarmthFiber;			// ���¼�
	int m_DurabilityFiber;		// ������
	int m_BreathabilityFiber;	// ��⼺

	// Ư��
	eStageObjectDefine m_Elasticity1;	// ź��
	eStageObjectDefine m_Stiff1;		// ����
	eStageObjectDefine m_Softness1;		// �ε巯��
	eStageObjectDefine m_HairLoss1;		// �к��� (Ż��)
	eStageObjectDefine m_Lightness1;	// ������
	eStageObjectDefine m_Rough1;		// ���
	eStageObjectDefine m_NoneSpecial1;	// Ư������ ����

	bool m_Elasticity;		// ź��
	bool m_Stiff;			// ����
	bool m_Softness;		// �ε巯��
	bool m_HairLoss;		// �к��� (Ż��)
	bool m_Lightness;		// ������
	bool m_Rough;			// ���
	bool m_NoneSpecial;		// Ư������ ����

	/// ���� ���� ��� (�ʿ��Ѱ�?)
	const int m_MinLowness	= 0;	// ���� ��� �ּ� 0
	const int m_MaxLowness	= 30;	// ���� ��� �ִ� 30
	const int m_MinMiddle	= 31;	// �߰� ��� �ּ� 31
	const int m_MaxMiddle	= 70;	// �߰� ��� �ִ� 70
	const int m_MinHigh		= 71;	// ���� ��� �ּ� 71
	const int m_MaxHigh		= 100;	// ���� ��� �ִ� 100

	// ��� ����
	bool m_Lowness;		// ���� 0~30
	bool m_Middle;		// �߰� 31~70
	bool m_High;		// ���� 71~100

	/// Player
	const int m_StartPossessedMoney = 50;	// ���� ������
	int m_CurPossessedMoney;				// ���� ������
	int m_BudgetCredit;						// ���� (�Ƿڱ�)
	const int m_RethinkMax = 10;			// �ѵ� ����
	int m_PurchaseCount;					// ���� count
	int m_Changes;							// ���� ��(�ܵ�)
	int m_MisTakeCount;						// �Ǽ� Ƚ��
	int m_AveragePrice;						// �ҵ� ���
	int m_PercentageTip;					// �� �����ؾ� �� % ũ��
	//eStageObjectDefine m_SpecialList[6];

	/// �����ؾ� �ϴ� ����
	eStageObjectDefine m_Doll;				// ����
	eStageObjectDefine m_Muffler;			// �񵵸�
	eStageObjectDefine m_Bag;				// ����
	eStageObjectDefine m_Gloves;			// �尩
	eStageObjectDefine m_Sweater;			// ������

	/// �ֹ� ���۽� �ʿ��� �͵�
	bool m_WarmthRating[5];				// �ʿ��� ���¼� ���
	bool m_DurabilityRating[5];			// �ʿ��� ������ ���
	bool m_BreathabilityRating[5];		// �ʿ��� ��⼺ ���
	// Stage���� �ٸ� ��
	int m_CraftingBall;					// �ʿ��� ball ����
	int m_StuffPrice;					// �ǸŰ�
	bool m_SpecialNeeds;				// Ư���� �䱸
	int m_ArbitrageMoney;				// ����
	int m_TipMoney;						// ��

	/// Scene �̴ϰ��� Ȱ��ȭ ����
	bool m_SpinningGameStart;

	/// Spinning ����
	int m_SpinningBallRange;		// Spinning ������ �� ���� ���� �ʱ�ȭ�ϱ� ���� ����
	bool m_SpinningBallObjectState;	// Spinning Ball Object ����
	bool m_IsSpinningGaugBall;
	// �ִϸ��̼� �Ǵ�
	bool m_FailAnimation;
	bool m_SucessAnimation;
	bool m_BallAnimation;


	/// ���� �� �ʱ�ȭ ���� ����
	Scene_Knitting* m_pKnitting;

	/// ��� �� �ʱ�ȭ��
	Scene_Average* m_pAverage;
public:
	/// ���������� �ʱ�ȭ
	void StageInitialization(int stageNum);
	
	/// Spinning ����
	void SpinningGaugeBallRangeInit();		// Spinning ������ �� ���� �ʱ�ȭ
	void SetSpinningBallObjectState(bool state);
	void SetSpinningGaugeState(bool state);
	void SetFailAnimation(bool state);		// ���� Object �ִϸ��̼� ����
	void SetSucessAnimation(bool state);		// ���� Object �ִϸ��̼� ����
	void SetBallAnimation(bool state);		// Ball Object �ִϸ��̼� ����

public:
	/// ��ɵ�
	/// ���� �ر� ����
	// Stage ��ȣ, ���� money
	void LambswoolUnlock(int stageNum, int money);	// ������ �ر�
	// Stage ��ȣ, ���� money
	void BurlapUnlock(int stageNum, int money);		// �ﺣ�� �ر�
	// Stage ��ȣ, ���� money
	void AngoraHairUnlock(int stageNum, int money);	// �Ӱ���� �ر�
	// Stage ��ȣ, ���� money
	void CashmereUnlock(int stageNum, int money);	// ĳ�ù̾� �ر�

	/// Stage ����
	void IsStageChage(bool state);				// �������� �۵� ���� ����
	void AddStage();							// �������� �ѱ��
	void SpinningGameStateChage(bool state);	// Spinning �������� ���� ��ȯ

	/// ���� ����
	void BuyFiber();

	/// ��� �Ǵ�
	void FiberJudgeRating();

	/// Ư�� ���
	void SpecialOffset(eStageObjectDefine special1, eStageObjectDefine special2);

	/// Player ����
	void DecreaseMoney(int money);		// ������ ����
	void IncreaseMoney(int stageNum, int tipMoney);		// ������ ����
	void SetPlayerMisTakeCount(int count);
	void AddPlayerMisTakeCount();		// Player �Ǽ� ī���� ����
	void AddPlayerMisTakeCount(int count);
	void SetAveragePrice(int value);	// Player ���� ��հ� ����
	void DecreaseTipMoney(int money);	// Tip Money ���̱�
	void SetTimMoneyDecreaseRate(int percentage);	// Tip Percentage ����
	void StageEndPlayerMoneyCalculate();	// �������� ������ player ������ ����
	void TipMoneyCalc();				// Tip ���

	/// ���� ����
	/// ���� ���� �ٲٱ�
	void SetElasticity(bool state);		// ź��
	bool SetStiff(bool state);			// ����
	bool SetSoftness(bool state);		// �ε巯��
	bool SetHairLoss(bool state);		// �к���
	bool SetLightness(bool state);		// ������
	bool SetRough(bool state);			// ���
	bool SetNoneSpecial(bool state);	// Ư������ ����

	/// <summary>
	/// Stage Ŭ���� ����
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
	/// ������ ��ȯ

	/// Player ����
	int GetStageNum();				// �������� Number ��ȣ
	int GetStartPossessedMoney();	// Player ���� ������
	int GetCurPossessedMoney();		// Player ���� ������
	int GetPlayerMisTakeCount();	// Player �Ǽ� Count
	int GetPlayerAveragePrice();	// Player ���� ��հ�
	int GetTipMoney();				// TipMoney ��ȯ
	int GetTimMoneyDecreaseRate();	// TipMoney ���ҵ� �ݾ� ��ȯ

	int GetCraftingBall();				// �ʿ��� ball ����
	bool isLownessRange(int object);	// ���� ���� 0~30
	bool isMiddleRange(int object);	// �߰� ���� 31~70
	bool isHighRange(int object);		// ���� ���� 71~

	/// ���� ����
	bool GetSpiderwebUnlockState();		// �Ź��� �ر� ����
	bool GetLambswoolUnlockState();		// ������ �ر� ����
	bool GetCottonUnlockState();		// ��ư �ر� ����
	bool GetBurlapUnlockState();		// �ﺣ�� �ر� ����
	bool GetAngoraHairUnlockState();	// �Ӱ���� �ر� ����
	bool GetCashmereUnlockState();		// ĳ�ù̾� �ر� ����

	int GetWarmthFiber();				// ���¼� ��ġ
	int GetDurabilityFiber();			// ������ ��ġ
	int GetBreathabilityFiber();		// ��⼺ ��ġ

	bool GetElasticity();				// ź��
	bool GetStiff();					// ����
	bool GetSoftness();					// �ε巯��
	bool GetHairLoss();					// �к���
	bool GetLightness();				// ������
	bool GetRough();					// ���
	bool GetNoneSpecial();				// Ư������ ����

	/// Stage ����
	bool GetIsStageState();				// ���� �������� �۵� ����

	/// Spinning ����
	bool GetSpinningGameState();		// Spinning ���� Ȱ��ȭ ����
	int GetSpinningGaugeBallRange();	// Spinning ������ �� ����
	bool IsSpinningBallObjectState();	// Spinning Ball object ����
	bool IsSpinningGaugeBallState();	// Spinning Gauge Ball ����
	bool IsFailAnimation();			// ���� Object �ִϸ��̼�
	bool IsSucessAnimation();			// ���� Object �ִϸ��̼�
	bool IsBallAnimation();		// Ball Object �ִϸ��̼�

	void InitialKnittingScene(Scene_Knitting* p_knitting);
	void InitializeAverageScene(Scene_Average* p_average);

	void SetStage(int stage);
	void InitialShop();
};