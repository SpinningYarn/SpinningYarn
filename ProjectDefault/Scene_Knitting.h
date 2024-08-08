#pragma once
#include "IScene.h"

// 사용할 정답 Define
const int UP = 1;
const int DOWN = 2;
const int LEFT = 3;
const int RIGHT = 4;

const int NONE = 21;
const int O = 22;
const int X = 23;

class StartButton;
class DatumPoint;
class AnswerBoard;
class Needle;
class Dantto;
class ResultProduct;
class Shop;
class Inventory;
class Credit;
class GameMenu;
class DrawBoard;

class IWool;
class SpiderWeb;
class LambsWool;
class Cotton;
class Burlap;
class Angora;
class Cashmere;

/// <summary>
/// 
/// 뜨개질 씬
/// 
/// 기준점, 정답판, 다시하기 버튼
/// 각자 처리할 수 있는 로직들은 최대한 오브젝트 안에서 처리하였으며
/// 상호간에 유기적으로 처리해야 하는 로직들은 이 안에서 처리하였음
/// 
/// 2023.02.11 YJH
/// </summary>

class Scene_Knitting : public IScene
{
public:
	Scene_Knitting(const int sceneNum, const std::string& sceneName, SceneManager* pSceneManager);
	virtual ~Scene_Knitting();

	virtual void UpdateScene() override;
	virtual void RenderScene() override;
	virtual void Initialize() override;	// Scene내의 오브젝트들을 포인터로 받아오기 위한 초기화

	void GameStartLogic();			// 첫 게임스타트 로직
	void RetryLogic();				// 다시하기 버튼 로직
	void AnswerLogic();				// 정답 버튼 로직
	void AnswerChooseLogic();		// 정답 칸 선택 로직
	int GetAnswer();				// 정답 가져오기
	void SetAnswer(int num);		// 정답 설정
	void SetRandom();				// 랜덤 뜨개질 종류 설정
	int GetGoal();					// 게임 시행 횟수 가져오기
	void SetGoal(int stage);		// 게임 시행횟수 설정	
	int GetAnswerCount(int round);	// 라운드 별 정답 횟수 가져오기
	void SetAnswerCount(int index, int num);	// 라운듭 별 정답 횟수 설정
	int GetTotalAnswer();			// 총 정답 횟수 가져오기
	void TotalAnswerCountLogic();	// 정답 산출
	void SetWrongCount(int index, int num);
	void GotoNextStage();			// 목표치 - 총 정답이 5보다 작다면 다음게임으로 넘어가도록~
	void UpdateResultProd();
	void UpdateShopAndCredits(); 
	void WrongCountCheck();
	void SetSpinningWrongCount(int count);

private:
	StartButton* m_pStartButton;
	DatumPoint* m_pDatumPoint;
	ResultProduct* m_pResultProduct;
	Needle* m_pNeedle;
	Dantto* m_pDantto;
	DrawBoard* m_pDrawBoard;

	AnswerBoard* m_pAnswerBoard;
	AnswerBoard* m_PBoard1st;		// 이전 정답칸 저장을 위한 변수
	AnswerBoard* m_pBoard2nd;		// 이전 정답칸 저장을 위한 변수
	AnswerBoard* m_pBoard3rd;		// 이전 정답칸 저장을 위한 변수
	AnswerBoard* m_pBoard4th;		// 이전 정답칸 저장을 위한 변수
	AnswerBoard* m_pBoard5th;		// 이전 정답칸 저장을 위한 변수
	AnswerBoard* m_pBoard6th;		// 이전 정답칸 저장을 위한 변수
	AnswerBoard* m_pBoard7th;		// 이전 정답칸 저장을 위한 변수
	AnswerBoard* m_pBoard8th;		// 이전 정답칸 저장을 위한 변수
	AnswerBoard* m_pPrviousBoard;	// 이전 정답칸 저장을 위한 변수

	AnswerBoard* m_pSetAnswer;		// 정답 지정을 위한 포인터
	int m_Answer;
	int m_TotalAnserCount;			// 총 정답 카운트
	int m_AnswerCount[7];			// 1~7라까지 각 라운드별 정답횟수
	int m_TotalWrongCount;			// 총 오답 카운트
	int m_WrongCount[7];			// 틀렸을때 카운트
	int m_GoalCount;				// 게임 시행 횟수

	int m_temp = 0;						//틀린거 카운트 서포트용

	// 정답 5행 7열 -> 5가지의 뜨개질 종류별로 MAX 7까지의 라운드를 담아놓을 예정
	int m_AnswerBook[7][8];			// 인형 정답 담아놓을 것
	int m_SpinningWrongCount;
	double m_Timer;
	bool m_SuccessDrawFlag;
	bool m_AniFlag;

private:
	Shop* m_pShop;
	Inventory* m_pInventory;
	Credit* m_pCredit;
	GameMenu* m_pGameMenu;
private:
	//재료들
	SpiderWeb* m_pSpiderWeb;
	LambsWool* m_pLambsWool;
	Cotton* m_pCotton;
	Burlap* m_pBurlap;
	Angora* m_pAngora;
	Cashmere* m_pCashmere;
	std::vector<IWool*> m_iwools;
};
