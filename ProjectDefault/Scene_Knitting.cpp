#include <random>
#include "../D2DEngine/D2DEngine.h"
#include "../D2DEngine/Animator.h"
#include "Scene_Knitting.h"
#include "SceneManager.h"
#include "StartButton.h"
#include "DatumPoint.h"
#include "AnswerBoard.h"
#include "ResultProduct.h"
#include "eObjectDefine.h"
#include "MouseManager.h"
#include "KeyManager.h"
#include "TimerManager.h"
#include "Shop.h"
#include "Inventory.h"
#include "IWoolClasses.h"
#include "Credit.h"
#include "GameMenu.h"
#include "Needle.h"
#include "Dantto.h"
#include "StageManager.h"
#include "DrawBoard.h"
#include "SoundManager.h"
#include "KeyManager.h"

Animator* knit_Success = new Animator();

Scene_Knitting::Scene_Knitting(const int sceneNum, const std::string& sceneName, SceneManager* pSceneManager)
	: IScene(sceneNum, sceneName, pSceneManager), m_pStartButton(nullptr), m_pDatumPoint(nullptr), m_pAnswerBoard(nullptr),
	m_pShop(nullptr), m_pCredit(nullptr), m_SpinningWrongCount(0), m_Timer(0), m_SuccessDrawFlag (false), m_AniFlag(false)
{
	for (int i = 0; i < 8; i++)
	{
		knit_Success->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::SucessAnim, 1920 * i, 0, 1920, 1080, 1));
	}
	knit_Success->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::SucessAnim, 1920 * 7, 0, 1920, 1080, 1));
	knit_Success->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::SucessAnim, 1920 * 7, 0, 1920, 1080, 1));
	knit_Success->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::SucessAnim, 1920 * 7, 0, 1920, 1080, 1));
	knit_Success->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::SucessAnim, 1920 * 7, 0, 1920, 1080, 1));
	knit_Success->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::SucessAnim, 1920 * 7, 0, 1920, 1080, 1));
}

Scene_Knitting::~Scene_Knitting()
{
}
static bool fail = false;
static bool knittingO = false;
static bool knittingX = false;

void Scene_Knitting::UpdateScene()
{
	if (m_pDatumPoint->GetCount() == 0)
	{
		StageManager::GetInstance()->SetPlayerMisTakeCount(m_SpinningWrongCount);
	}
	else if (m_pDatumPoint->GetCount() == 1)
	{
		StageManager::GetInstance()->SetPlayerMisTakeCount(m_SpinningWrongCount + (8-m_AnswerCount[0]));
	}
	else if (m_pDatumPoint->GetCount() == 2)
	{
		StageManager::GetInstance()->SetPlayerMisTakeCount(m_SpinningWrongCount + (8 - m_AnswerCount[0]) +(8 - m_AnswerCount[1]));
	}
	else if (m_pDatumPoint->GetCount() == 3)
	{
		StageManager::GetInstance()->SetPlayerMisTakeCount(m_SpinningWrongCount + (8 - m_AnswerCount[0]) +(8 - m_AnswerCount[1]) + (8 - m_AnswerCount[2]));
	}
	else if (m_pDatumPoint->GetCount() == 4)
	{
		StageManager::GetInstance()->SetPlayerMisTakeCount(m_SpinningWrongCount + (8 - m_AnswerCount[0]) + +(8 - m_AnswerCount[1]) + (8 - m_AnswerCount[2]) + (8 - m_AnswerCount[3]));
	}
	else if (m_pDatumPoint->GetCount() == 5)
	{
		StageManager::GetInstance()->SetPlayerMisTakeCount(m_SpinningWrongCount + (8 - m_AnswerCount[0]) + +(8 - m_AnswerCount[1]) + (8 - m_AnswerCount[2]) + (8 - m_AnswerCount[3]) +(8 - m_AnswerCount[4]));
	}
	else if (m_pDatumPoint->GetCount() == 6)
	{
		StageManager::GetInstance()->SetPlayerMisTakeCount(m_SpinningWrongCount + (8 - m_AnswerCount[0]) + +(8 - m_AnswerCount[1]) + (8 - m_AnswerCount[2]) + (8 - m_AnswerCount[3]) +(8 - m_AnswerCount[4]) + (8 - m_AnswerCount[5]));
	}


	//static bool knittingX = false;
	//static bool undo = false;

	// 씬 강제로 넘기기 'P'
	if (m_pShop->GetActivated() == false && m_pGameMenu->GetActivated() == false)
	{
		if (KeyManager::GetInstance().GetKeyAndState(Key::P) == KeyState::TAP)
		{
			m_pSceneManager->SetNowScene("TalkingScene2");
		}
	}

	// 게임 로직
	if (m_pShop->GetActivated() == false && m_pGameMenu->GetActivated() == false)
	{
		m_pAnswerBoard->GetDatumPoint(m_pDatumPoint->GetCount());
		m_pDatumPoint->SetStartX(m_pBoard8th->GetXposPlusSize() + 30);
		m_pDatumPoint->SetReverseX(m_PBoard1st->GetXpos() - 30);
		GameStartLogic();
		RetryLogic();
		AnswerChooseLogic();
		AnswerLogic();
		WrongCountCheck();
		UpdateResultProd();
		TotalAnswerCountLogic();
		// 오브젝트들 업데이트
		OnUpdate();
	}

	if (m_pShop->GetActivated() == true)
	{
		m_pCredit->UpdateObject();
		m_pShop->CloseStore();
		m_pShop->RotateIcon();
		UpdateShopAndCredits();
	}

	if (m_pGameMenu->GetActivated() == true)
	{
		m_pGameMenu->onClickHowToPlay();
		m_pGameMenu->ReturnToMain();
		m_pGameMenu->CloseMenu();
	}
	if (m_pDatumPoint->GetCount() < m_GoalCount)
	{
		m_SuccessDrawFlag = false;
		m_AniFlag = false;
		m_Timer = 0;
	}

	if (m_pDatumPoint->GetCount() == m_GoalCount && m_GoalCount * 8 - m_TotalAnserCount <= 10)
	{
		m_pDatumPoint->SetClearFlag(true);
	}

	// 정답시 
	if (m_pDatumPoint->GetCount() == m_GoalCount && m_GoalCount * 8 - m_TotalAnserCount <= 10 && m_AniFlag == false)
	{
		m_SuccessDrawFlag = true;
		m_Timer += TimerManager::GetInstance().GetDeltaTime();
	}

	if (m_SuccessDrawFlag == true && m_Timer >= 3)
	{
		m_SuccessDrawFlag = false;	
		m_AniFlag = true;
	}
}

void Scene_Knitting::RenderScene()
{
	/// 뜨개질 씬을 그리기 위해서만 존재하는 리소스 등 처리


	// 오브젝트들 그리기
	OnRender();
	//static bool knittingX = false;
	D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::KeyNum, 450, 320);
	// 한줄씩 정답 보여주기
	if (m_pDatumPoint->GetCount() < m_GoalCount)
	{
		m_PBoard1st->DrawAnswer(m_AnswerBook[m_pDatumPoint->GetCount()][0]);
		m_pBoard2nd->DrawAnswer(m_AnswerBook[m_pDatumPoint->GetCount()][1]);
		m_pBoard3rd->DrawAnswer(m_AnswerBook[m_pDatumPoint->GetCount()][2]);
		m_pBoard4th->DrawAnswer(m_AnswerBook[m_pDatumPoint->GetCount()][3]);
		m_pBoard5th->DrawAnswer(m_AnswerBook[m_pDatumPoint->GetCount()][4]);
		m_pBoard6th->DrawAnswer(m_AnswerBook[m_pDatumPoint->GetCount()][5]);
		m_pBoard7th->DrawAnswer(m_AnswerBook[m_pDatumPoint->GetCount()][6]);
		m_pBoard8th->DrawAnswer(m_AnswerBook[m_pDatumPoint->GetCount()][7]);
	}
	m_pShop->RenderObject();
	m_pGameMenu->RenderObject();
	m_pDantto->RenderDantto();

	if (m_pDatumPoint->GetCount() == m_GoalCount && m_GoalCount * 8 - m_TotalAnserCount <= 10 && m_SuccessDrawFlag == true)
	{
		knit_Success->PlayAnimation(0, 0, 3, 10);
	}

	/// 디버깅용
// 	D2DEngine::GetInstance()->DrawText(800, 360, m_GoalCount);					// 목표 횟수 출력
// 	D2DEngine::GetInstance()->DrawText(1100, 200, m_pDatumPoint->GetCount());	// 현재 카운트 출력
// 	D2DEngine::GetInstance()->DrawText(900, 200, m_AnswerCount[m_pDatumPoint->GetCount()]);			// 정답 횟수 출력
// 	D2DEngine::GetInstance()->DrawText(900, 100, m_TotalAnserCount);			// 정답 횟수 출력
// 
// 	D2DEngine::GetInstance()->DrawText(1000, 200, m_TotalWrongCount);			// 오답 횟수 출력
// 	D2DEngine::GetInstance()->DrawText(100, 400, m_Answer);						// 오답 횟수 출력
}

void Scene_Knitting::Initialize()
{
	// 만들어져있는 오브젝트를 가져와서 원래의 오브젝트 타입으로 강제 현변환시켜 포인터를 가지고 있음
	m_pStartButton = (StartButton*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("시작하기");
	m_pDatumPoint = (DatumPoint*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("기준점");
	m_pAnswerBoard = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판 대기소");
	m_pNeedle = (Needle*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("바늘");
	m_pDantto = (Dantto*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("고양이");
	m_pResultProduct = (ResultProduct*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("완성품");
	m_pShop = (Shop*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("상점");
	m_pInventory = (Inventory*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("인벤토리");
	m_pCredit = (Credit*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("소지금");
	m_pGameMenu = (GameMenu*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("메뉴");

	m_pSpiderWeb = (SpiderWeb*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("거미줄");
	m_pLambsWool = (LambsWool*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("램스울");
	m_pCotton = (Cotton*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("코튼");
	m_pBurlap = (Burlap*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("삼베실");
	m_pAngora = (Angora*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("앙고라털");
	m_pCashmere = (Cashmere*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("캐시미어");

	m_iwools.push_back((IWool*)m_pSpiderWeb);
	m_iwools.push_back((IWool*)m_pLambsWool);
	m_iwools.push_back((IWool*)m_pCotton);
	m_iwools.push_back((IWool*)m_pBurlap);
	m_iwools.push_back((IWool*)m_pAngora);
	m_iwools.push_back((IWool*)m_pCashmere);

	m_PBoard1st = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판1");
	m_pBoard2nd = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판2");
	m_pBoard3rd = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판3");
	m_pBoard4th = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판4");
	m_pBoard5th = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판5");
	m_pBoard6th = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판6");
	m_pBoard7th = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판7");
	m_pBoard8th = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판8");

	m_PBoard1st->SetIndex(0);
	m_pBoard2nd->SetIndex(1);
	m_pBoard3rd->SetIndex(2);
	m_pBoard4th->SetIndex(3);
	m_pBoard5th->SetIndex(4);
	m_pBoard6th->SetIndex(5);
	m_pBoard7th->SetIndex(6);
	m_pBoard8th->SetIndex(7);

	m_PBoard1st->SetNextBoard(m_pBoard2nd);
	m_pBoard2nd->SetNextBoard(m_pBoard3rd);
	m_pBoard3rd->SetNextBoard(m_pBoard4th);
	m_pBoard4th->SetNextBoard(m_pBoard5th);
	m_pBoard5th->SetNextBoard(m_pBoard6th);
	m_pBoard6th->SetNextBoard(m_pBoard7th);
	m_pBoard7th->SetNextBoard(m_pBoard8th);

	// 기준점 초기화
	m_pDatumPoint->Initialize();

	// 직조 씬의 멤버 변수들 초기화
	m_Answer = 0;
	m_TotalAnserCount = 0;
	m_TotalWrongCount = 0;
	m_GoalCount = 0;
	m_SpinningWrongCount = 0;
	m_Timer = 0;
	m_SuccessDrawFlag = false;
	m_AniFlag = false;

	for (int i = 0; i < 7; i++)
	{
		m_AnswerCount[i] = 0;
		m_WrongCount[i] = 0;
	}

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_AnswerBook[i][j] = 0;
		}
	}
	StageManager::GetInstance()->InitialKnittingScene(this);

	// 새로운 스테이지를 위해 다시 설정
	SetRandom();

	SetGoal(StageManager::GetInstance()->GetStageNum());

	// 시작버튼 초기화
	m_pStartButton->SetDrawFlag(true);

	// 목표치 설정
	m_pDatumPoint->SetGoalCount(m_GoalCount);

	// 출력판 초기화
	m_pDrawBoard = (DrawBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("출력판");
	m_pDrawBoard->Initialize(m_PBoard1st, m_pDatumPoint);

	// 고양이 초기화

	m_pDantto->Initialize(m_pNeedle, m_PBoard1st, m_pDatumPoint, m_pResultProduct, m_pDrawBoard);
}

void Scene_Knitting::GameStartLogic()
{
	if (m_pStartButton->GameStartButtonClick(m_pDantto) == true)
	{
		m_pDatumPoint->SetStartFlag(true);
		m_pStartButton->SetDrawFlag(false);
	}
}

static bool undo = false;
void Scene_Knitting::RetryLogic()
{
	if (m_pStartButton->RetryButtonClick() == true && m_pDantto->GetAttackFlag() == false)
	{
		/// <summary>
		/// 한줄 풀 때 소리
		/// </summary>
		if (undo == false)
		{
			SoundManager::GetInstance().PlaySounds(BackLine);
			undo = true;
		}

		m_pDatumPoint->InitialzieGame(this, m_pAnswerBoard, m_PBoard1st, m_pDrawBoard);
	}
}

void Scene_Knitting::AnswerLogic()
{
	knittingX = false;
	fail = false;

	// 정답 로직
	if (
		(KeyManager::GetInstance().GetKnittingKey() == m_Answer) &&
		(m_pAnswerBoard->GetPositionX() < m_pDatumPoint->GetDatumX() - 25) &&
		(m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize() < m_pAnswerBoard->GetXposPlusSize()) &&
		(m_pAnswerBoard->GetQuestionActivate() == true) &&
		(m_pAnswerBoard->GetCountFlag() == true)
		)
	{
		// 정답카운트 ++


		m_pAnswerBoard->SetOX(O);
		m_pAnswerBoard->SetQuestionActivate(false);		// 정답을 맞추면 비활성화
		m_pAnswerBoard->SetCountFlag(false);			// 정답을 맞추면 카운트 임시변수를 받아옴
		m_pAnswerBoard->SetWrongCountFlag(false);		// 정답 맞추면 오답카운트 비활성화
		m_AnswerCount[m_pDatumPoint->GetCount()]++;		// 정답시 정답 카운트 추가

		/// <summary>
		/// 정답 소리
		/// </summary>
		if (knittingO == false)
		{
			SoundManager::GetInstance().PlaySounds(Knitting1);
			knittingO = true;

		}
	}


	// 연타할 경우
	else if (
		((KeyManager::GetInstance().GetKnittingKey() == UP) ||
			(KeyManager::GetInstance().GetKnittingKey() == DOWN) ||
			(KeyManager::GetInstance().GetKnittingKey() == LEFT) ||
			(KeyManager::GetInstance().GetKnittingKey() == RIGHT)) &&
		(m_pAnswerBoard->GetCountFlag() == true) &&
		(m_pDatumPoint->GetDatumX() - m_pDatumPoint->GetSize() >= 607) &&
		(m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize() <= 1297)
		)
	{
		// 오답카운트 ++
		m_pAnswerBoard->SetOX(X);
		m_pAnswerBoard->SetQuestionActivate(false);
		m_pAnswerBoard->SetWrongCountFlag(true);
		m_pAnswerBoard->SetCountFlag(false);
	}

	// 	else if (
	// 		(KeyManager::GetInstance().GetKnittingKey() == SPACE)
	// 		&& m_pDatumPoint->GetCount() == 0 )
	// 		)
	// 	{
	// 		m_pAnswerBoard->GETNE
	// 	}

		// 정답일때 아무 키도 입력하지 않은 경우 
	else if (
		(KeyManager::GetInstance().GetKnittingKey() != m_Answer) &&
		(m_pAnswerBoard->GetQuestionActivate() == true) &&
		(m_pAnswerBoard->GetCountFlag() == true) &&
		(m_pDatumPoint->GetDatumX() - m_pDatumPoint->GetSize() >= 607) &&
		(m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize() <= 1297)
		)
	{
		// 오답카운트 ++
		m_pAnswerBoard->SetQuestionActivate(true);
		m_pAnswerBoard->SetWrongCountFlag(true);
	}
	undo = false;
}


void Scene_Knitting::AnswerChooseLogic()
{

	knittingO = false;

	/// 정방향일 경우
	if (m_pDatumPoint->GetCount() % 2 == 0)
	{
		// 왼쪽에서 1번째 영역에 접근했을때
		if (
			(m_PBoard1st->GetXposPlusSize() > m_pDatumPoint->GetDatumX() - m_pDatumPoint->GetSize()) &&
			(m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize() > m_PBoard1st->GetXpos())
			)
		{
			m_pAnswerBoard = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판1");
			SetAnswer(0);
		}

		// 왼쪽에서 2번째 영역에 접근했을때
		else if (
			(m_pBoard2nd->GetXposPlusSize() > m_pDatumPoint->GetDatumX() - m_pDatumPoint->GetSize()) &&
			(m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize() > m_pBoard2nd->GetXpos())
			)
		{
			m_pAnswerBoard = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판2");
			SetAnswer(1);
		}

		// 왼쪽에서 3번째 영역에 접근했을때 
		else if (
			(m_pBoard3rd->GetXposPlusSize() > m_pDatumPoint->GetDatumX() - m_pDatumPoint->GetSize()) &&
			(m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize() > m_pBoard3rd->GetXpos())
			)
		{
			m_pAnswerBoard = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판3");
			SetAnswer(2);
		}

		// 왼쪽에서 4번째 영역에 접근했을때 
		else if (
			(m_pBoard4th->GetXposPlusSize() > m_pDatumPoint->GetDatumX() - m_pDatumPoint->GetSize()) &&
			(m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize() > m_pBoard4th->GetXpos())
			)
		{
			m_pAnswerBoard = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판4");
			SetAnswer(3);
		}

		// 왼쪽에서 5번째 영역에 접근했을때
		else if (
			(m_pBoard5th->GetXposPlusSize() > m_pDatumPoint->GetDatumX() - m_pDatumPoint->GetSize()) &&
			(m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize() > m_pBoard5th->GetXpos())
			)
		{
			m_pAnswerBoard = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판5");
			SetAnswer(4);
		}

		// 왼쪽에서 6번째 영역에 접근했을때
		else if (
			(m_pBoard6th->GetXposPlusSize() > m_pDatumPoint->GetDatumX() - m_pDatumPoint->GetSize()) &&
			(m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize() > m_pBoard6th->GetXpos())
			)
		{
			m_pAnswerBoard = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판6");
			SetAnswer(5);
		}

		// 왼쪽에서 7번째 영역에 접근했을때
		else if (
			(m_pBoard7th->GetXposPlusSize() > m_pDatumPoint->GetDatumX() - m_pDatumPoint->GetSize()) &&
			(m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize() > m_pBoard7th->GetXpos())
			)
		{
			m_pAnswerBoard = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판7");
			SetAnswer(6);
		}

		// 왼쪽에서 8번째 영역에 접근했을때
		else if (
			(m_pBoard8th->GetXposPlusSize() > m_pDatumPoint->GetDatumX() - m_pDatumPoint->GetSize()) &&
			(m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize() > m_pBoard8th->GetXpos())
			)
		{
			m_pAnswerBoard = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판8");
			SetAnswer(7);
		}

		// 왼쪽 처음, 오른쪽 처음 시작할때 예외처리를 위해 필요
		else if (
			m_PBoard1st->GetXpos() > m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize() ||
			m_pBoard8th->GetXposPlusSize() < m_pDatumPoint->GetDatumX() - m_pDatumPoint->GetSize()
			)
		{
			m_pAnswerBoard = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판 대기소");
			m_PBoard1st->SetOX(NONE);
			m_pBoard2nd->SetOX(NONE);
			m_pBoard3rd->SetOX(NONE);
			m_pBoard4th->SetOX(NONE);
			m_pBoard5th->SetOX(NONE);
			m_pBoard6th->SetOX(NONE);
			m_pBoard7th->SetOX(NONE);
			m_pBoard8th->SetOX(NONE);
		}
	}

	/// 역방향일 경우
	if (m_pDatumPoint->GetCount() % 2 == 1)
	{
		// 왼쪽에서 1번째 영역에 접근했을때
		if (
			(m_PBoard1st->GetXpos() < m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize()) &&
			(m_PBoard1st->GetXposPlusSize() > m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize())
			)
		{
			m_pAnswerBoard = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판1");
			SetAnswer(0);
		}

		// 왼쪽에서 2번째 영역에 접근했을때
		else if (
			(m_pBoard2nd->GetXpos() < m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize()) &&
			(m_pBoard2nd->GetXposPlusSize() > m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize())
			)
		{
			m_pAnswerBoard = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판2");
			SetAnswer(1);
		}

		// 왼쪽에서 3번째 영역에 접근했을때 
		else if (
			(m_pBoard3rd->GetXpos() < m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize()) &&
			(m_pBoard3rd->GetXposPlusSize() > m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize())
			)
		{
			m_pAnswerBoard = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판3");
			SetAnswer(2);
		}

		// 왼쪽에서 4번째 영역에 접근했을때 
		else if (
			(m_pBoard4th->GetXpos() < m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize()) &&
			(m_pBoard4th->GetXposPlusSize() > m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize())
			)
		{
			m_pAnswerBoard = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판4");
			SetAnswer(3);
		}

		// 왼쪽에서 5번째 영역에 접근했을때
		else if (
			(m_pBoard5th->GetXpos() < m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize()) &&
			(m_pBoard5th->GetXposPlusSize() > m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize())
			)
		{
			m_pAnswerBoard = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판5");
			SetAnswer(4);
		}

		// 왼쪽에서 6번째 영역에 접근했을때
		else if (
			(m_pBoard6th->GetXpos() < m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize()) &&
			(m_pBoard6th->GetXposPlusSize() > m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize())
			)
		{
			m_pAnswerBoard = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판6");
			SetAnswer(5);
		}

		// 왼쪽에서 7번째 영역에 접근했을때
		else if (
			(m_pBoard7th->GetXpos() < m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize()) &&
			(m_pBoard7th->GetXposPlusSize() > m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize())
			)
		{
			m_pAnswerBoard = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판7");
			SetAnswer(6);
		}

		// 왼쪽에서 8번째 영역에 접근했을때
		else if (
			(m_pBoard8th->GetXpos() < m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize()) &&
			(m_pBoard8th->GetXposPlusSize() > m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize())
			)
		{
			m_pAnswerBoard = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판8");
			SetAnswer(7);
		}

		// 왼쪽 처음, 오른쪽 처음 시작할때 예외처리를 위해 필요
		else if (
			m_PBoard1st->GetXpos() > m_pDatumPoint->GetDatumX() + m_pDatumPoint->GetSize() ||
			m_pBoard8th->GetXposPlusSize() < m_pDatumPoint->GetDatumX() - m_pDatumPoint->GetSize()
			)
		{
			m_pAnswerBoard = (AnswerBoard*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판 대기소");
			m_PBoard1st->SetOX(NONE);
			m_pBoard2nd->SetOX(NONE);
			m_pBoard3rd->SetOX(NONE);
			m_pBoard4th->SetOX(NONE);
			m_pBoard5th->SetOX(NONE);
			m_pBoard6th->SetOX(NONE);
			m_pBoard7th->SetOX(NONE);
			m_pBoard8th->SetOX(NONE);
		}
	}
	// 이전 정답판을 다시 정답처리할 수 있도록 되돌려놓는 과정
	if (m_pPrviousBoard != m_pAnswerBoard)
	{
		if (
			m_pPrviousBoard != nullptr &&
			m_pPrviousBoard != m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판 대기소") &&
			m_pPrviousBoard->GetWrongCountFlag() == true &&
			m_pPrviousBoard->GetOX() != O
			)
		{


			m_pPrviousBoard->SetXdrawFlag(m_pDatumPoint->GetCount(), true);
			m_pPrviousBoard->SetOX(X);
			m_pDrawBoard->InitializeFlagArray(m_pDatumPoint->GetCount(), m_pPrviousBoard->GetIndex(), true, m_pPrviousBoard->GetPositionX(), 439);
			m_WrongCount[m_pDatumPoint->GetCount()]++;
			m_pPrviousBoard->SetQuestionActivate(true);
			m_pPrviousBoard->SetCountFlag(true);
			m_pAnswerBoard->SetWrongCountFlag(true);


			/// <summary>
			/// 오답 소리
			/// </summary>
			if (knittingX == false)
			{
				SoundManager::GetInstance().PlaySounds(KnittingFail);
				knittingX = true;
				//m_temp = m_TotalWrongCount;
			}

			if (m_pStartButton->RetryButtonClick() == true)
			{
				m_pPrviousBoard->SetXdrawFlag(m_pDatumPoint->GetCount(), false);
				m_pDrawBoard->SetXflagArray(m_pDatumPoint->GetCount());
			}




		}
		// 정답 위한 예외 처리
		else if (
			m_pPrviousBoard != nullptr &&
			m_pPrviousBoard != m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("정답판 대기소") &&
			m_pPrviousBoard->GetWrongCountFlag() == false
			)
		{
			m_pPrviousBoard->SetQuestionActivate(true);
			m_pPrviousBoard->SetCountFlag(true);
			m_pAnswerBoard->SetWrongCountFlag(true);
		}
		m_pPrviousBoard = m_pAnswerBoard;

	}



// 	if (m_TotalWrongCount > 5 && (m_pDatumPoint->GetCount() == m_GoalCount))
// 	{
// 		/// 실패음
// 
// 		if (fail == false)
// 		{
// 			SoundManager::GetInstance().PlaySounds(Fail);
// 			fail = true;
// 		}
// 	}



	
	
}

int Scene_Knitting::GetAnswer()
{
	return m_Answer;
}

void Scene_Knitting::SetAnswer(int num)
{
	m_Answer = m_AnswerBook[m_pDatumPoint->GetCount()][num];
}


void Scene_Knitting::SetRandom()
{
	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<int> answer(1, 4);
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_AnswerBook[i][j] = answer(gen);
		}
	}
}

int Scene_Knitting::GetGoal()
{
	return m_GoalCount;
}

void Scene_Knitting::SetGoal(int stage)
{
	switch (StageManager::GetInstance()->GetStageNum())
	{
		case 1:		// 인형
			m_GoalCount = 6;
			break;
		case 2:		// 스카프
			m_GoalCount = 5;
			break;
		case 3:		// 가방
			m_GoalCount = 5;
			break;
		case 4:		// 장갑
			m_GoalCount = 5;
			break;
		case 5:		// 스웨터
			m_GoalCount = 5;
			break;

		default:
			break;
	}
}

void Scene_Knitting::UpdateResultProd()
{
	m_pResultProduct->SetCurrentDivide(m_pDatumPoint->GetCount(), m_pDatumPoint->GetGoalCount());
}

int Scene_Knitting::GetAnswerCount(int index)
{
	return m_AnswerCount[index];
}

void Scene_Knitting::SetAnswerCount(int index, int num)
{
	m_AnswerCount[index] = num;
}

int Scene_Knitting::GetTotalAnswer()
{
	return m_TotalAnserCount;
}

void Scene_Knitting::TotalAnswerCountLogic()
{
	m_TotalAnserCount = m_AnswerCount[0] + m_AnswerCount[1] + m_AnswerCount[2] + m_AnswerCount[3] + m_AnswerCount[4] + m_AnswerCount[5] + m_AnswerCount[6];
}

void Scene_Knitting::SetWrongCount(int index, int num)
{
	m_WrongCount[index] = num;
}

void Scene_Knitting::GotoNextStage()
{
	// 직조 씬에서
	Initialize();

	m_PBoard1st->FinishGame();
	m_pBoard2nd->FinishGame();
	m_pBoard3rd->FinishGame();
	m_pBoard4th->FinishGame();
	m_pBoard5th->FinishGame();
	m_pBoard6th->FinishGame();
	m_pBoard7th->FinishGame();
	m_pBoard8th->FinishGame();

}

//상점과 크레딧 연동
void Scene_Knitting::UpdateShopAndCredits()
{
	m_pShop->UpdateCredits(m_pCredit);
	m_pShop->UnlockItems(m_pCredit, m_iwools, m_pInventory);
}

void Scene_Knitting::WrongCountCheck()
{
	m_TotalWrongCount = m_WrongCount[0] + m_WrongCount[1] + m_WrongCount[2] + m_WrongCount[3] + m_WrongCount[4] + m_WrongCount[5] + m_WrongCount[6];

	if (m_pDatumPoint->GetCount() % 2 == 0 && m_pDatumPoint->GetDatumX() == 1322 && m_pDatumPoint->GetWaitState() == true)
	{
		m_WrongCount[m_pDatumPoint->GetCount()] = 0;
	}
	if (m_pDatumPoint->GetCount() % 2 != 0 && m_pDatumPoint->GetDatumX() == 582 && m_pDatumPoint->GetWaitState() == true)
	{
		m_WrongCount[m_pDatumPoint->GetCount()] = 0;
	}
}

void Scene_Knitting::SetSpinningWrongCount(int count)
{
	m_SpinningWrongCount = count;
}
