#include <windows.h>
#include "../D2DEngine/D2DEngine.h"
#include "../D2DEngine/Animator.h"
#include "Scene_Average.h"
#include "eObjectDefine.h"
#include "StatBox.h"
#include "StatBox2.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "StageManager.h"
#include "MouseManager.h"
#include "KeyManager.h"
#include "Shop.h"
#include "Inventory.h"
#include "GameMenu.h"
#include "Credit.h"
#include "IWoolClasses.h"
#include "TimerManager.h"

Animator* DanttoOut = new Animator();

Scene_Average::Scene_Average(const int sceneNum, const std::string& sceneName, SceneManager* pSceneManager)
	: IScene(sceneNum, sceneName, pSceneManager), MouseClickOnce(true), changeBox(false), averageCheck(false)
	,m_averagePrice(0), m_averageDurability(0), m_averagePermeability(0), m_averageWarmth(0), m_sumEA(0), 
	m_currentSpc1(WoolSpcAbility::NONE), m_currentSpc2(WoolSpcAbility::NONE), m_currentSpc3(WoolSpcAbility::NONE), m_currentSpc4(WoolSpcAbility::NONE), m_CatOut(false), m_CatTimer(0),
	count(0), m_pAngora(nullptr), m_pBurlap(nullptr), m_pCashmere(nullptr), m_pCotton(nullptr), m_pCredit(nullptr), m_pInventory(nullptr), m_pLambsWool(nullptr),
	m_pShop(nullptr), m_pSpiderWeb(nullptr), m_pStatBox(nullptr), m_pStatBox2(nullptr)
{
	/// 리소스는 여기서 모두 로드한다.
	m_pStageManager = StageManager::GetInstance();
	m_pMouseManager = MouseManager::GetInstance();

	for (int i = 0; i < 8; i++)
	{
		DanttoOut->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_OUT, 700*i, 0, 700, 700, 1));
	}

}

Scene_Average::~Scene_Average()
{

}

void Scene_Average::UpdateScene()
{
	// 씬 강제로 넘기기 'P'
	if (m_pShop->GetActivated() == false && m_pGameMenu->GetActivated() == false)
	{
		if (KeyManager::GetInstance().GetKeyAndState(Key::P) == KeyState::TAP)
		{
			m_pSceneManager->SetNowScene("SpinningScene");
		}
	}

	if (m_pInventory->GetItemListSize() <= 0)
	{
		m_pInventory->AddObject((IWool*)m_pSpiderWeb);
		m_pInventory->UpdateShowList();
	}

	if (m_pShop->GetActivated() == false && m_pGameMenu->GetActivated() == false)
	{
		OnUpdate();

		// 1번쨰 박스에 아무것도 없을떄
		StopWhen1stZero();

		// 2번쨰 박스에 아무것도 없을때
		StopWhen2ndZero();
		//Confirm();
		CalcAveragePrice();
		InactivateButton();
		UpdateCurrentSpc();
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

	if (m_CatOut == false)
	{
		m_CatTimer += TimerManager::GetInstance().GetDeltaTime();

		if (m_CatTimer >= 4)
		{
			m_CatOut = true;
		}
	}
}

void Scene_Average::RenderScene()
{
	/// 뜨개질 씬을 그리기 위해서만 존재하는 리소스 등 처리
	OnRender();

	//D2DEngine::GetInstance()->DrawRect(1550, 582, 1650, 632);
	// 첫번째 박스가 채워져 있으면 2번째 박스로 간다
	PrintStat();

	// 스탯 평균값을 텍스트로 보여준다
	// 2개의 오브젝트의 합이 10이 넘어가면 멈추게 한다(변경해야함)
	if (m_pStatBox->targetQuantity * m_pStatBox->MouseCount + m_pStatBox2->targetQuantity2 * m_pStatBox2->MouseCount2 > 11)
	{
		//D2DEngine::GetInstance()->DrawText(1400, 500, "더 이상 집어 넣을 수 없다");
	}
	else
	{
		GetAverage();
	}
	
	if (m_CatOut == false)
	{
		DanttoOut->PlayAnimation(1250, 280, 5, 25);
	}
	/// 뜨개질 씬을 그린다. (공통 코드)

	m_pShop->RenderObject();
	m_pGameMenu->RenderObject();
}


void Scene_Average::Initialize()
{
	m_pStatBox = (StatBox*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("스탯박스");
	m_pStatBox2 = (StatBox2*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("스탯박스2");
	m_pShop = (Shop*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("상점");
	m_pCredit = (Credit*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("소지금");

	m_pInventory = (Inventory*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("인벤토리");
	m_pGameMenu = (GameMenu*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("메뉴");

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

	if (m_pInventory->GetItemListSize() <= 0)
	{
		m_pInventory->AddObject((IWool*)m_pSpiderWeb);
		m_pInventory->UpdateShowList();
	}

	StageManager::GetInstance()->InitializeAverageScene(this);

	/// 스테이지 +될때 이 이니셜라이즈 함수를 한번 불러주면 됟듯? 요기서 다 초기화시키고
	m_CatOut = false;
	m_CatTimer = 0;
}

void Scene_Average::PrintStat()
{
	if (m_pShop->GetActivated() == false)
	{
		/// 1번째 박스에 아직 아무것도 안들어 있는 상태고,
		/// TestWool의 Sendimage가 true이고(사실 아무 의미 없는 것이다) 상자위치 누르면 발동
		/// statbox2의 mousecount가 10 미만일때

		if (m_pInventory->GetSendIWool() != nullptr)
		{
			if (m_pStatBox->IsEmpty() == false && m_pStatBox2->MouseCount2 < 10)
			{
				m_pStatBox->UpdateStat(m_pInventory->GetSendIWool());
				m_pStatBox->changeBox = true;
				averageCheck = true;
				m_pInventory->EmptySendIWool();
			}
		}

		if (m_pInventory->GetSendIWool2() != nullptr)
		{
			if (m_pStatBox2->IsEmpty() == false && m_pStatBox->MouseCount < 10)
			{
				m_pStatBox2->UpdateStat2(m_pInventory->GetSendIWool2());
				m_pStatBox2->changeBox = true;
				averageCheck = true;
				m_pInventory->EmptySendIWool2();
			}
		}

		/// <summary>
		/// 1번째 박스가 채워져 있으면 2번째 박스로 넘어간다
		/// </summary>

	}
}


/// <summary>
/// 각각의 상황에 따른 평균값 구하는 로직을 바꾼다
/// </summary>
void Scene_Average::GetAverage()
{
	/// averageCheck가 true일때(즉 어느박스에라도 오브젝트가 들어가 있을때)
	if (averageCheck == true && m_pStatBox->MouseCount > 0 && m_pStatBox2->MouseCount2 > 0)
	{
		// 오브젝트가 첫번째에만 들어가 있을 때
		if (m_pStatBox->returnTestWool == true && m_pStatBox2->returnTestWool2 == false )
		{
			D2DEngine::GetInstance()->DrawTextInt(1453, 507, m_averageWarmth);

			D2DEngine::GetInstance()->DrawTextInt(1453, 540, m_averageDurability);

			D2DEngine::GetInstance()->DrawTextInt(1453, 573, m_averagePermeability);

			D2DEngine::GetInstance()->DrawTextInt(1453, 606, (m_averagePrice));

			D2DEngine::GetInstance()->DrawTextInt(1575, 613, (m_pStatBox->targetQuantity * m_pStatBox->MouseCount));
		}
		// 오브젝트가 2개 들어가 있을 때
		else if (m_pStatBox->returnTestWool == true && m_pStatBox2->returnTestWool2 == true)
		{
			D2DEngine::GetInstance()->DrawTextInt(1453, 507, m_averageWarmth);

			D2DEngine::GetInstance()->DrawTextInt(1453, 540, m_averageDurability);

			D2DEngine::GetInstance()->DrawTextInt(1453, 573, m_averagePermeability);

			D2DEngine::GetInstance()->DrawTextInt(1453, 606, m_averagePrice);

			D2DEngine::GetInstance()->DrawTextInt(1575, 613, (m_pStatBox->targetQuantity * m_pStatBox->MouseCount + m_pStatBox2->targetQuantity2 * m_pStatBox2->MouseCount2));
		}
		// 첫번째 오브젝트가 빠지고 두번째 오브젝트에만 들어있을 때
		else if (m_pStatBox->returnTestWool == false && m_pStatBox2->returnTestWool2 == true)
		{
			D2DEngine::GetInstance()->DrawTextInt(1453, 507, m_averageWarmth);

			D2DEngine::GetInstance()->DrawTextInt(1453, 540, m_averageDurability);

			D2DEngine::GetInstance()->DrawTextInt(1453, 573, m_averagePermeability);

			D2DEngine::GetInstance()->DrawTextInt(1453, 606, m_averagePrice);

			D2DEngine::GetInstance()->DrawTextInt(1575, 613, (m_pStatBox2->targetQuantity2 * m_pStatBox2->MouseCount2));
		}
	}
	// 오브젝트가 하나도 없을때
	if (m_pStatBox->returnTestWool == false && m_pStatBox2->returnTestWool2 == false || m_pStatBox2->MouseCount2 == 0 || m_pStatBox->MouseCount == 0)
	{
		D2DEngine::GetInstance()->DrawTextInt(1453, 507, m_averageWarmth);

		D2DEngine::GetInstance()->DrawTextInt(1453, 540, m_averageDurability);

		D2DEngine::GetInstance()->DrawTextInt(1453, 573, m_averagePermeability);

		D2DEngine::GetInstance()->DrawTextInt(1453, 606, m_averagePrice);

		D2DEngine::GetInstance()->DrawTextInt(1575, 613, (m_pStatBox2->targetQuantity2 * 0));	
	}
}

void Scene_Average::CalcAveragePrice()
{
	//m_sumEA = m_pStatBox->MouseCount + m_pStatBox2->MouseCount2;

	//스탯박스1이 비어있지 않고 스탯박스2가 비어있을때
	if (m_pStatBox->IsEmpty() && !m_pStatBox2->IsEmpty())
	{
		m_averageWarmth = m_pStatBox->targetWarmth * m_pStatBox->MouseCount / m_pStatBox->MouseCount; 
		m_averageDurability = m_pStatBox->targetAbsoptivity * m_pStatBox->MouseCount / m_pStatBox->MouseCount;
		m_averagePermeability = m_pStatBox->targetAeration * m_pStatBox->MouseCount / m_pStatBox->MouseCount;
		m_averagePrice = m_pStatBox->targetPrice * m_pStatBox->MouseCount;
		m_sumEA = m_pStatBox->MouseCount;
		m_pStageManager->SetAveragePrice(m_averagePrice);
	}
	//스탯박스1이 비어있고 스탯박스2가 비어있지 않을때
	else if (!m_pStatBox->IsEmpty() && m_pStatBox2->IsEmpty())
	{
		m_averageWarmth = m_pStatBox2->targetWarmth2 * m_pStatBox2->MouseCount2 / m_pStatBox2->MouseCount2;
		m_averageDurability = m_pStatBox2->targetAbsoptivity2 * m_pStatBox2->MouseCount2 / m_pStatBox2->MouseCount2;
		m_averagePermeability = m_pStatBox2->targetAeration2 * m_pStatBox2->MouseCount2 / m_pStatBox2->MouseCount2;
		m_averagePrice = m_pStatBox2->targetPrice2 * m_pStatBox2->MouseCount2;
		m_sumEA = m_pStatBox2->MouseCount2;
		m_pStageManager->SetAveragePrice(m_averagePrice);	
	}
	//둘 다 비어있지 않으면
	else if (m_pStatBox->IsEmpty() && m_pStatBox2->IsEmpty())
	{
		m_averageWarmth = (m_pStatBox->targetWarmth * m_pStatBox->MouseCount + m_pStatBox2->targetWarmth2 * m_pStatBox2->MouseCount2) / m_sumEA;
		m_averageDurability = (m_pStatBox->targetAbsoptivity * m_pStatBox->MouseCount + m_pStatBox2->targetAbsoptivity2 * m_pStatBox2->MouseCount2) / m_sumEA;
		m_averagePermeability = (m_pStatBox->targetAeration * m_pStatBox->MouseCount + m_pStatBox2->targetAeration2 * m_pStatBox2->MouseCount2) / m_sumEA;
		m_averagePrice = m_pStatBox->targetPrice * m_pStatBox->MouseCount + m_pStatBox2->targetPrice2 * m_pStatBox2->MouseCount2;
		m_sumEA = m_pStatBox->MouseCount + m_pStatBox2->MouseCount2;
		m_pStageManager->SetAveragePrice(m_averagePrice);
	}
	//둘 다 비어있으면
	else if (!m_pStatBox->IsEmpty() && !m_pStatBox2->IsEmpty())
	{
		m_averageWarmth = 0;
		m_averageDurability = 0;
		m_averagePermeability = 0;
		m_averagePrice = 0;
		m_sumEA = 0;
		m_pStageManager->SetAveragePrice(m_averagePrice);	
	}
}

/// <summary>
/// 1번째 박스의 오브젝트에 감소버튼을 눌러서 mousecount가 0 이 되면 Statbox의 Undo함수를 실행한다
/// </summary>
void Scene_Average::StopWhen1stZero()
{
	if (m_pStatBox->MouseCount == 0)
	{
		// StatBox의 Undo 함수를 불러온다
		m_pStatBox->EmptyStatBox();
	}
}

/// <summary>
/// 2번째 박스의 오브젝트에 감소버튼을 눌러서 mousecount2가 0 이 되면 Statbox2의 Undo2함수를 실행한다
/// </summary>
void Scene_Average::StopWhen2ndZero()
{
	if (m_pStatBox2->MouseCount2 == 0)
	{
		m_pStatBox2->EmptyStatBox();
	}
}

/// <summary>
/// 카운트 합이 10이 될때 증가버튼을 못누르게 막는다
/// </summary>
void Scene_Average::InactivateButton()
{
	if (m_pStatBox->returnTestWool == false && m_pStatBox2->MouseCount2 < 10)
	{
		m_pStatBox->InactivateButton = true;

		m_pStatBox2->InactivateButton2 = false;
	}
	else if (m_pStatBox2->returnTestWool2 == false && m_pStatBox->MouseCount < 10)
	{
		m_pStatBox->InactivateButton = false;

		m_pStatBox2->InactivateButton2 = true;
	}
	else if (m_pStatBox->MouseCount +  m_pStatBox2->MouseCount2 >= 10)
	{
		m_pStatBox->InactivateButton = true;

		m_pStatBox2->InactivateButton2 = true;
	}
	else
	{
		m_pStatBox->InactivateButton = false;

		m_pStatBox2->InactivateButton2 = false;
	}
}

//평균값 반환 함수들
int Scene_Average::GetAverageWarmth()
{
	return this->m_averageWarmth;
}

int Scene_Average::GetAverageDurability()
{
	return this->m_averageDurability;
}

int Scene_Average::GetAveragePermeability()
{
	return this->m_averagePermeability;
}

int Scene_Average::GetAveragePrice()
{
	return this->m_averagePrice;
}

int Scene_Average::GetSum()
{
	return this->m_sumEA;
}

//평균값에 나타난 섬유재료들의 특수 능력 상태를 업데이트 해줌
void Scene_Average::UpdateCurrentSpc()
{
	//둘 다 비어있으면 아무것도 하지마		//NONE 유지
	if (!m_pStatBox->IsEmpty() && !m_pStatBox2->IsEmpty())
	{
		return;
	}

	//첫번째 박스가 비어있지 않고 두번째 박스가 비어있으면
	if (m_pStatBox->IsEmpty() && !m_pStatBox2->IsEmpty())
	{
		this->m_currentSpc1 = m_pStatBox->m_spcAbil1;
		this->m_currentSpc2 = m_pStatBox->m_spcAbil2;
	}
	//첫번째 박스가 비어있고 두번째 박스가 비어있지 않으면
	else if (!m_pStatBox->IsEmpty() && m_pStatBox2->IsEmpty())
	{
		this->m_currentSpc1 = m_pStatBox2->m_spcAbil1;
		this->m_currentSpc2 = m_pStatBox2->m_spcAbil2;
	}
	//둘 다 뭔가 들어있으면
	else if (m_pStatBox->IsEmpty() && m_pStatBox2->IsEmpty())
	{
		//지옥의 시작
		if (m_pStatBox->eOD == eObjectDefine::SPIDERWEB)
		{
			if (m_pStatBox2->eOD == eObjectDefine::SPIDERWEB)
			{
				this->m_currentSpc1 = WoolSpcAbility::NONE;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::LAMBSWOOL)
			{
				this->m_currentSpc1 = WoolSpcAbility::ELASTICITY;
				this->m_currentSpc2 = WoolSpcAbility::ROUGH;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::COTTON)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::HEMP)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::ROUGH;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::ANGORA)
			{
				this->m_currentSpc1 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc2 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::CASHMERE)
			{
				this->m_currentSpc1 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc2 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
		}
		else if (m_pStatBox->eOD == eObjectDefine::LAMBSWOOL)
		{
			if (m_pStatBox2->eOD == eObjectDefine::SPIDERWEB)
			{
				this->m_currentSpc1 = WoolSpcAbility::ELASTICITY;
				this->m_currentSpc2 = WoolSpcAbility::ROUGH;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::LAMBSWOOL)
			{
				this->m_currentSpc1 = WoolSpcAbility::ELASTICITY;
				this->m_currentSpc2 = WoolSpcAbility::ROUGH;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::COTTON)
			{
				this->m_currentSpc1 = WoolSpcAbility::ROUGH;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::HEMP)
			{
				this->m_currentSpc1 = WoolSpcAbility::ROUGH;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::ANGORA)
			{
				this->m_currentSpc1 = WoolSpcAbility::ELASTICITY;
				this->m_currentSpc2 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::CASHMERE)
			{
				this->m_currentSpc1 = WoolSpcAbility::ELASTICITY;
				this->m_currentSpc2 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
		}
		else if (m_pStatBox->eOD == eObjectDefine::COTTON)
		{
			if (m_pStatBox2->eOD == eObjectDefine::SPIDERWEB)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::LAMBSWOOL)
			{
				this->m_currentSpc1 = WoolSpcAbility::ROUGH;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::COTTON)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::HEMP)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::ROUGH;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::ANGORA)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc3 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::CASHMERE)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc3 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
		}
		else if (m_pStatBox->eOD == eObjectDefine::COTTON)
		{
			if (m_pStatBox2->eOD == eObjectDefine::SPIDERWEB)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::LAMBSWOOL)
			{
				this->m_currentSpc1 = WoolSpcAbility::ROUGH;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::COTTON)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::HEMP)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::ROUGH;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::ANGORA)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc3 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::CASHMERE)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc3 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
		}
		else if (m_pStatBox->eOD == eObjectDefine::HEMP)
		{
			if (m_pStatBox2->eOD == eObjectDefine::SPIDERWEB)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::ROUGH;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::LAMBSWOOL)
			{
				this->m_currentSpc1 = WoolSpcAbility::ROUGH;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::COTTON)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::ROUGH;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::HEMP)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::ROUGH;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::ANGORA)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::CASHMERE)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
		}
		else if (m_pStatBox->eOD == eObjectDefine::ANGORA)
		{
			if (m_pStatBox2->eOD == eObjectDefine::SPIDERWEB)
			{
				this->m_currentSpc1 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc2 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::LAMBSWOOL)
			{
				this->m_currentSpc1 = WoolSpcAbility::ELASTICITY;
				this->m_currentSpc2 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::COTTON)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc3 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::HEMP)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::ANGORA)
			{
				this->m_currentSpc1 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc2 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::CASHMERE)
			{
				this->m_currentSpc1 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc2 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc3 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
		}
		else if (m_pStatBox->eOD == eObjectDefine::CASHMERE)
		{
			if (m_pStatBox2->eOD == eObjectDefine::SPIDERWEB)
			{
				this->m_currentSpc1 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc2 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::LAMBSWOOL)
			{
				this->m_currentSpc1 = WoolSpcAbility::ELASTICITY;
				this->m_currentSpc2 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::COTTON)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc3 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::HEMP)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::ANGORA)
			{
				this->m_currentSpc1 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc2 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc3 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox2->eOD == eObjectDefine::CASHMERE)
			{
				this->m_currentSpc1 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc2 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
		}

		//
		if (m_pStatBox2->eOD == eObjectDefine::SPIDERWEB)
		{
			if (m_pStatBox->eOD == eObjectDefine::SPIDERWEB)
			{
				this->m_currentSpc1 = WoolSpcAbility::NONE;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::LAMBSWOOL)
			{
				this->m_currentSpc1 = WoolSpcAbility::ELASTICITY;
				this->m_currentSpc2 = WoolSpcAbility::ROUGH;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::COTTON)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::HEMP)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::ROUGH;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::ANGORA)
			{
				this->m_currentSpc1 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc2 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::CASHMERE)
			{
				this->m_currentSpc1 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc2 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
		}
		else if (m_pStatBox2->eOD == eObjectDefine::LAMBSWOOL)
		{
			if (m_pStatBox->eOD == eObjectDefine::SPIDERWEB)
			{
				this->m_currentSpc1 = WoolSpcAbility::ELASTICITY;
				this->m_currentSpc2 = WoolSpcAbility::ROUGH;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::LAMBSWOOL)
			{
				this->m_currentSpc1 = WoolSpcAbility::ELASTICITY;
				this->m_currentSpc2 = WoolSpcAbility::ROUGH;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::COTTON)
			{
				this->m_currentSpc1 = WoolSpcAbility::ROUGH;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::HEMP)
			{
				this->m_currentSpc1 = WoolSpcAbility::ROUGH;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::ANGORA)
			{
				this->m_currentSpc1 = WoolSpcAbility::ELASTICITY;
				this->m_currentSpc2 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::CASHMERE)
			{
				this->m_currentSpc1 = WoolSpcAbility::ELASTICITY;
				this->m_currentSpc2 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
		}
		else if (m_pStatBox2->eOD == eObjectDefine::COTTON)
		{
			if (m_pStatBox->eOD == eObjectDefine::SPIDERWEB)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::LAMBSWOOL)
			{
				this->m_currentSpc1 = WoolSpcAbility::ROUGH;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::COTTON)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::HEMP)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::ROUGH;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::ANGORA)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc3 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::CASHMERE)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc3 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
		}
		else if (m_pStatBox2->eOD == eObjectDefine::COTTON)
		{
			if (m_pStatBox->eOD == eObjectDefine::SPIDERWEB)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::LAMBSWOOL)
			{
				this->m_currentSpc1 = WoolSpcAbility::ROUGH;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::COTTON)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::HEMP)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::ROUGH;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::ANGORA)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc3 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::CASHMERE)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc3 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
		}
		else if (m_pStatBox2->eOD == eObjectDefine::HEMP)
		{
			if (m_pStatBox->eOD == eObjectDefine::SPIDERWEB)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::ROUGH;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::LAMBSWOOL)
			{
				this->m_currentSpc1 = WoolSpcAbility::ROUGH;
				this->m_currentSpc2 = WoolSpcAbility::NONE;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::COTTON)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::ROUGH;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::HEMP)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::ROUGH;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::ANGORA)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::CASHMERE)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
		}
		else if (m_pStatBox2->eOD == eObjectDefine::ANGORA)
		{
			if (m_pStatBox->eOD == eObjectDefine::SPIDERWEB)
			{
				this->m_currentSpc1 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc2 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::LAMBSWOOL)
			{
				this->m_currentSpc1 = WoolSpcAbility::ELASTICITY;
				this->m_currentSpc2 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::COTTON)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc3 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::HEMP)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::ANGORA)
			{
				this->m_currentSpc1 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc2 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::CASHMERE)
			{
				this->m_currentSpc1 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc2 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc3 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
		}
		else if (m_pStatBox2->eOD == eObjectDefine::CASHMERE)
		{
			if (m_pStatBox->eOD == eObjectDefine::SPIDERWEB)
			{
				this->m_currentSpc1 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc2 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::LAMBSWOOL)
			{
				this->m_currentSpc1 = WoolSpcAbility::ELASTICITY;
				this->m_currentSpc2 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::COTTON)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc3 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::HEMP)
			{
				this->m_currentSpc1 = WoolSpcAbility::STIFF;
				this->m_currentSpc2 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::ANGORA)
			{
				this->m_currentSpc1 = WoolSpcAbility::HAIRLOSS;
				this->m_currentSpc2 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc3 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
			else if (m_pStatBox->eOD == eObjectDefine::CASHMERE)
			{
				this->m_currentSpc1 = WoolSpcAbility::LIGHTNESS;
				this->m_currentSpc2 = WoolSpcAbility::SOFTNESS;
				this->m_currentSpc3 = WoolSpcAbility::NONE;
				this->m_currentSpc4 = WoolSpcAbility::NONE;
			}
		}
	}
}

//스테이지 클리어 조건용
bool Scene_Average::isStiff()
{
	if (m_currentSpc1 == WoolSpcAbility::STIFF
		|| m_currentSpc2 == WoolSpcAbility::STIFF
		|| m_currentSpc3 == WoolSpcAbility::STIFF
		|| m_currentSpc4 == WoolSpcAbility::STIFF
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Scene_Average::isRough()
{
	if (m_currentSpc1 == WoolSpcAbility::ROUGH
		|| m_currentSpc2 == WoolSpcAbility::ROUGH
		|| m_currentSpc3 == WoolSpcAbility::ROUGH
		|| m_currentSpc4 == WoolSpcAbility::ROUGH
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Scene_Average::isSoftness()
{
	if (m_currentSpc1 == WoolSpcAbility::SOFTNESS
		|| m_currentSpc2 == WoolSpcAbility::SOFTNESS
		|| m_currentSpc3 == WoolSpcAbility::SOFTNESS
		|| m_currentSpc4 == WoolSpcAbility::SOFTNESS
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// 확정버튼
/// 나중에 조건들을 더 추가해야한다
/// </summary>
void Scene_Average::Confirm()
{
	if (m_pMouseManager->GetLeftOneDownClickState() == true
		&& 1550 <= m_pMouseManager->GetXPos()
		&& 1650 >= m_pMouseManager->GetXPos()
		&& 582 <= m_pMouseManager->GetYPos()
		&& 632 >= m_pMouseManager->GetYPos())
	{
	

	}
	if (m_pMouseManager->GetLeftOneUpClickState() == true
		&& 1550 <= m_pMouseManager->GetXPos()
		&& 1650 >= m_pMouseManager->GetXPos()
		&& 582 <= m_pMouseManager->GetYPos()
		&& 632 >= m_pMouseManager->GetYPos())
	{
		//MouseClickOnce = true;

		m_pSceneManager->SetNowScene("SpinningScene");
	}
}

void Scene_Average::ResetInfos()
{
	//m_pShop->ResetInfos();
	//m_pInventory->ResetInfos();
	m_pInventory->EmptySendIWool();
	m_pInventory->EmptySendIWool2();
	m_pStatBox->EmptyStatBox();
	m_pStatBox2->EmptyStatBox();
}

//상점 인벤토리 초기화		//야매
void Scene_Average::ResetShopInven()
{
	m_pShop->ResetInfos();
	m_pInventory->ResetInfos();
}

void Scene_Average::ToStage2()
{
	if (!m_pInventory->CheckItem(eObjectDefine::COTTON))
	{
		m_pInventory->AddObject(m_pCotton);
		m_pInventory->UpdateShowList();
	}
}

//상점과 크레딧 연동
void Scene_Average::UpdateShopAndCredits()
{
	m_pShop->UpdateCredits(m_pCredit);
	m_pShop->UnlockItems(m_pCredit, m_iwools, m_pInventory);
}




