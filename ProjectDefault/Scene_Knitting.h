#pragma once
#include "IScene.h"

// ����� ���� Define
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
/// �߰��� ��
/// 
/// ������, ������, �ٽ��ϱ� ��ư
/// ���� ó���� �� �ִ� �������� �ִ��� ������Ʈ �ȿ��� ó���Ͽ�����
/// ��ȣ���� ���������� ó���ؾ� �ϴ� �������� �� �ȿ��� ó���Ͽ���
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
	virtual void Initialize() override;	// Scene���� ������Ʈ���� �����ͷ� �޾ƿ��� ���� �ʱ�ȭ

	void GameStartLogic();			// ù ���ӽ�ŸƮ ����
	void RetryLogic();				// �ٽ��ϱ� ��ư ����
	void AnswerLogic();				// ���� ��ư ����
	void AnswerChooseLogic();		// ���� ĭ ���� ����
	int GetAnswer();				// ���� ��������
	void SetAnswer(int num);		// ���� ����
	void SetRandom();				// ���� �߰��� ���� ����
	int GetGoal();					// ���� ���� Ƚ�� ��������
	void SetGoal(int stage);		// ���� ����Ƚ�� ����	
	int GetAnswerCount(int round);	// ���� �� ���� Ƚ�� ��������
	void SetAnswerCount(int index, int num);	// ���� �� ���� Ƚ�� ����
	int GetTotalAnswer();			// �� ���� Ƚ�� ��������
	void TotalAnswerCountLogic();	// ���� ����
	void SetWrongCount(int index, int num);
	void GotoNextStage();			// ��ǥġ - �� ������ 5���� �۴ٸ� ������������ �Ѿ����~
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
	AnswerBoard* m_PBoard1st;		// ���� ����ĭ ������ ���� ����
	AnswerBoard* m_pBoard2nd;		// ���� ����ĭ ������ ���� ����
	AnswerBoard* m_pBoard3rd;		// ���� ����ĭ ������ ���� ����
	AnswerBoard* m_pBoard4th;		// ���� ����ĭ ������ ���� ����
	AnswerBoard* m_pBoard5th;		// ���� ����ĭ ������ ���� ����
	AnswerBoard* m_pBoard6th;		// ���� ����ĭ ������ ���� ����
	AnswerBoard* m_pBoard7th;		// ���� ����ĭ ������ ���� ����
	AnswerBoard* m_pBoard8th;		// ���� ����ĭ ������ ���� ����
	AnswerBoard* m_pPrviousBoard;	// ���� ����ĭ ������ ���� ����

	AnswerBoard* m_pSetAnswer;		// ���� ������ ���� ������
	int m_Answer;
	int m_TotalAnserCount;			// �� ���� ī��Ʈ
	int m_AnswerCount[7];			// 1~7����� �� ���庰 ����Ƚ��
	int m_TotalWrongCount;			// �� ���� ī��Ʈ
	int m_WrongCount[7];			// Ʋ������ ī��Ʈ
	int m_GoalCount;				// ���� ���� Ƚ��

	int m_temp = 0;						//Ʋ���� ī��Ʈ ����Ʈ��

	// ���� 5�� 7�� -> 5������ �߰��� �������� MAX 7������ ���带 ��Ƴ��� ����
	int m_AnswerBook[7][8];			// ���� ���� ��Ƴ��� ��
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
	//����
	SpiderWeb* m_pSpiderWeb;
	LambsWool* m_pLambsWool;
	Cotton* m_pCotton;
	Burlap* m_pBurlap;
	Angora* m_pAngora;
	Cashmere* m_pCashmere;
	std::vector<IWool*> m_iwools;
};
