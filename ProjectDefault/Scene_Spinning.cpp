#include "Scene_Spinning.h"
#include "../D2DEngine/D2DEngine.h"
#include "../D2DEngine/Animator.h"
#include "SceneManager.h"
#include "MouseManager.h"
#include "Shop.h"
#include "Credit.h"
#include "GameMenu.h"
#include "KeyManager.h"
#include "SpinningWheel.h"
#include "SpinningCenterPoint.h"
#include "SpinningOrderMemo.h"
#include "SpinningGaugeManager.h"
#include "StageManager.h"
#include "TimerManager.h"
#include "Scene_Knitting.h"

#include <windows.h>

Animator* g_Fail = new Animator();
Animator* g_Sucess = new Animator();

Animator* g_Ball1 = new Animator();
Animator* g_Ball2 = new Animator();
Animator* g_Ball3 = new Animator();

Scene_Spinning::Scene_Spinning(const int sceneNum, const std::string& sceneName, SceneManager* pSceneManager)
	: IScene(sceneNum, sceneName, pSceneManager)
	, m_pD2DEngine(nullptr)
	, m_pShop(nullptr)
	, m_pCredit(nullptr)
	, m_pWheel(nullptr)
	, m_pCenterPoint(nullptr)
	, m_AnimationTime(0)
	, m_SpriteTime(0)
	, m_OnSucessFlag(false)
	, m_OnSucessFlag1(false)
	, m_OnFailFlag(false)
	, m_OnFailFlag1(false)
	, m_OutSucessFlag(false)
	, m_OutFailFlag(false)
	, m_OnGaugeBall1(false)
	, m_OnGaugeBall2(false)
	, m_OnGaugeBall3(false)
	, m_OnGaugeBall4(false)
	, m_OutGaugeBall1(false)
	, m_OutGaugeBall2(false)
	, m_OutGaugeBall3(false)
{
	/// (이 씬에서만 사용되는) 리소스는 여기서 모두 로드한다.
	/// D2D엔진은 싱글턴이어도 될 것 같다.
	SpinningCount = 3;

	m_pD2DEngine = D2DEngine::GetInstance();
	m_pMouserManager = MouseManager::GetInstance();
	m_SpinningGaugeManager = SpinningGaugeManager::GetInstance();
	m_pStageManager = StageManager::GetInstance();

	// 애니메이션 생성
	for (int i = 0; i < 8; i++)
	{
		g_Fail->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::FailAnim, 1920 * i, 0, 1920, 1080, 1));
		g_Sucess->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::SucessAnim, 1920 * i, 0, 1920, 1080, 1));
	}

	for (int i = 0; i < 6; i++)
	{
		g_Ball1->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::SpinningBallAnim1, 120 * i, 0, 120, 80, 1));
		g_Ball2->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::SpinningBallAnim2, 120 * i, 0, 120, 80, 1));
		g_Ball3->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::SpinningBallAnim3, 120 * i, 0, 120, 80, 1));
	}
}

Scene_Spinning::~Scene_Spinning()
{
	/// (이 씬에서만 사용되는) 리소스는 모두 여기서 지워라

	///delete m_pResource;
	SpinningCount = 0;
}

void Scene_Spinning::Initialize()
{
	m_pShop = (Shop*)m_pSceneManager->GetScene("SpinningScene")->GetSceneObject("상점");
	m_pCredit = (Credit*)m_pSceneManager->GetScene("SpinningScene")->GetSceneObject("소지금");
	m_pWheel = (SpinningWheel*)m_pSceneManager->GetScene("SpinningScene")->GetSceneObject("방직 물레");
	m_pCenterPoint = (SpinningCenterPoint*)m_pSceneManager->GetScene("SpinningScene")->GetSceneObject("물레기준점");
	m_pSpinningOrderMemo = (SpinningOrderMemo*)m_pSceneManager->GetScene("SpinningScene")->GetSceneObject("메모장");

	m_pInventory = (Inventory*)m_pSceneManager->GetScene("SpinningScene")->GetSceneObject("인벤토리");
	m_pGameMenu = (GameMenu*)m_pSceneManager->GetScene("SpinningScene")->GetSceneObject("메뉴");

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

	m_pKntting = (Scene_Knitting*)m_pSceneManager->GetScene("KnittingScene");
}

void Scene_Spinning::UpdateScene()
{
	UpdateWrongCount();

	// 씬 강제로 넘기기 'P'
	if (m_pShop->GetActivated() == false && m_pGameMenu->GetActivated() == false)
	{
		if (KeyManager::GetInstance().GetKeyAndState(Key::P) == KeyState::TAP)
		{
			m_pSceneManager->SetNowScene("KnittingScene");
			m_pKntting->Initialize();
		}

		UpdateRotation();
		OnUpdate();
	}

	if (m_pShop->GetActivated() == true)
	{
		m_pCredit->UpdateObject();
		m_pShop->RotateIcon();
		m_pShop->CloseStore();
		UpdateShopAndCredits();
	}
	if (m_pGameMenu->GetActivated() == true)
	{
		m_pGameMenu->onClickHowToPlay();
		m_pGameMenu->ReturnToMain();
		m_pGameMenu->CloseMenu();
	}

	/// 애니메이션, Sprite 관련
	// 성공, 실패 애니메이션 활성
	if (m_pStageManager->IsSucessAnimation() == true)
	{
		m_OnSucessFlag = true;
		m_AnimationTime += TimerManager::GetInstance().GetDeltaTime();
	}
	else if (m_pStageManager->IsFailAnimation() == true)
	{
		m_OnFailFlag = true;
		m_AnimationTime += TimerManager::GetInstance().GetDeltaTime();
		m_pStageManager->SpinningGameStateChage(false);
	}

	if (m_OnSucessFlag == true && m_AnimationTime >= 0.5)
	{
		m_OnSucessFlag1 = true;
	}
	else if (m_OnFailFlag == true && m_AnimationTime >= 0.5)
	{
		m_OnFailFlag1 = true;
	}

	if (m_OnSucessFlag1 == true)
	{
		m_SpriteTime += TimerManager::GetInstance().GetDeltaTime();
	}
	else if (m_OnFailFlag1 == true)
	{
		m_SpriteTime += TimerManager::GetInstance().GetDeltaTime();
		m_pStageManager->SpinningGameStateChage(true);
	}

	if (m_SpriteTime >= 1)
	{
		m_OnSucessFlag = false;
		m_OnSucessFlag1 = false;
		
		m_OnFailFlag = false;
		m_OnFailFlag1 = false;

		m_pStageManager->SetSucessAnimation(false);
		m_pStageManager->SetFailAnimation(false);

		m_AnimationTime = 0;
		m_SpriteTime = 0;
	}

	// Gauge Ball 애니메이션 활성 & 비활성
	if (m_pStageManager->IsBallAnimation() == true)
	{
		if (m_SpinningGaugeManager->GetRandomTimeCount() == 1)
		{
			m_OnGaugeBall1 = true;
			m_OnGaugeBall2 = false;
			m_OnGaugeBall3 = false;
		}

		if (m_SpinningGaugeManager->GetRandomTimeCount() == 2)
		{
			m_OnGaugeBall1 = false;
			m_OnGaugeBall2 = true;
			m_OnGaugeBall3 = false;
		}

		if (m_SpinningGaugeManager->GetRandomTimeCount() == 3)
		{
			m_OnGaugeBall1 = false;
			m_OnGaugeBall2 = false;
			m_OnGaugeBall3 = true;
			m_pStageManager->SetBallAnimation(true);
		}
	}

	if (m_SpinningGaugeManager->GetRandomTimeCount() == 0)
	{
		m_OnGaugeBall1 = false;
		m_OnGaugeBall2 = false;
		m_OnGaugeBall3 = false;
	}
}

void Scene_Spinning::RenderScene()
{
	/// 물레방아씬을 그린다. (공통 코드)
	OnRender();

	/// 뜨개질 씬을 그리기 위해서만 존재하는 리소스 등 처리
	// 미니게임 성공시 애니메이션
	if (m_OnSucessFlag == true)
	{
		g_Sucess->PlayAnimation(0, 0, 1, 10);
	}
	
	if (m_OnSucessFlag1 == true)
	{
		// 애니메이션 종료 후 이미지로 교체
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::Sucess, 0, 0);
	}

	// 미니게임 실패시 애니메이션
	if (m_OnFailFlag == true)
	{
		g_Fail->PlayAnimation(0, 0, 1, 10);
	}
	
	if (m_OnFailFlag1 == true && m_pStageManager->IsSpinningBallObjectState() == true)
	{
		// 애니메이션 종료 후 이미지로 교체
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::Fail, 0, 0);
	}

	/// 물레 한바퀴당 Ball 생성 애니메이션
	if (m_OnGaugeBall1 == true)
	{
		g_Ball1->PlayAnimation(m_SpinningGaugeManager->GetRandomGaugePosX(), 50, 1, 13.5);
	}
	if (m_OnGaugeBall2 == true)
	{
		g_Ball2->PlayAnimation(m_SpinningGaugeManager->GetRandomGaugePosX(), 50, 1, 13.5);
	}
	if (m_OnGaugeBall3 == true)
	{
		g_Ball3->PlayAnimation(m_SpinningGaugeManager->GetRandomGaugePosX(), 50, 1, 13.5);
	}

	//if (m_OutGaugeBall1 == true)
	//{
	//	D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SpinningBall, 680, 50);
	//}

	//D2DEngine::GetInstance()->DrawText(150, 150, m_SpinningGaugeManager->GetRandomTimeCount());

	m_pShop->RenderObject();
	m_pGameMenu->RenderObject();
}

//계산된 회전값을 SpinningWheel에 넣어주는 함수
void Scene_Spinning::UpdateRotation()
{
	m_pWheel->SetRotateScale(m_pCenterPoint->GetDegree());
}

//상점과 크레딧 연동
void Scene_Spinning::UpdateShopAndCredits()
{
	m_pShop->UpdateCredits(m_pCredit);
	m_pShop->UnlockItems(m_pCredit, m_iwools, m_pInventory);
}

void Scene_Spinning::UpdateWrongCount()
{
	m_pKntting->SetSpinningWrongCount(StageManager::GetInstance()->GetPlayerMisTakeCount());
}
