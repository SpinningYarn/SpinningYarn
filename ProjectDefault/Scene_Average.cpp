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
	/// ���ҽ��� ���⼭ ��� �ε��Ѵ�.
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
	// �� ������ �ѱ�� 'P'
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

		// 1���� �ڽ��� �ƹ��͵� ������
		StopWhen1stZero();

		// 2���� �ڽ��� �ƹ��͵� ������
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
	/// �߰��� ���� �׸��� ���ؼ��� �����ϴ� ���ҽ� �� ó��
	OnRender();

	//D2DEngine::GetInstance()->DrawRect(1550, 582, 1650, 632);
	// ù��° �ڽ��� ä���� ������ 2��° �ڽ��� ����
	PrintStat();

	// ���� ��հ��� �ؽ�Ʈ�� �����ش�
	// 2���� ������Ʈ�� ���� 10�� �Ѿ�� ���߰� �Ѵ�(�����ؾ���)
	if (m_pStatBox->targetQuantity * m_pStatBox->MouseCount + m_pStatBox2->targetQuantity2 * m_pStatBox2->MouseCount2 > 11)
	{
		//D2DEngine::GetInstance()->DrawText(1400, 500, "�� �̻� ���� ���� �� ����");
	}
	else
	{
		GetAverage();
	}
	
	if (m_CatOut == false)
	{
		DanttoOut->PlayAnimation(1250, 280, 5, 25);
	}
	/// �߰��� ���� �׸���. (���� �ڵ�)

	m_pShop->RenderObject();
	m_pGameMenu->RenderObject();
}


void Scene_Average::Initialize()
{
	m_pStatBox = (StatBox*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("���ȹڽ�");
	m_pStatBox2 = (StatBox2*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("���ȹڽ�2");
	m_pShop = (Shop*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("����");
	m_pCredit = (Credit*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("������");

	m_pInventory = (Inventory*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("�κ��丮");
	m_pGameMenu = (GameMenu*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("�޴�");

	m_pSpiderWeb = (SpiderWeb*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("�Ź���");
	m_pLambsWool = (LambsWool*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("������");
	m_pCotton = (Cotton*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("��ư");
	m_pBurlap = (Burlap*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("�ﺣ��");
	m_pAngora = (Angora*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("�Ӱ����");
	m_pCashmere = (Cashmere*)m_pSceneManager->GetScene("AverageScene")->GetSceneObject("ĳ�ù̾�");

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

	/// �������� +�ɶ� �� �̴ϼȶ����� �Լ��� �ѹ� �ҷ��ָ� �޵�? ��⼭ �� �ʱ�ȭ��Ű��
	m_CatOut = false;
	m_CatTimer = 0;
}

void Scene_Average::PrintStat()
{
	if (m_pShop->GetActivated() == false)
	{
		/// 1��° �ڽ��� ���� �ƹ��͵� �ȵ�� �ִ� ���°�,
		/// TestWool�� Sendimage�� true�̰�(��� �ƹ� �ǹ� ���� ���̴�) ������ġ ������ �ߵ�
		/// statbox2�� mousecount�� 10 �̸��϶�

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
		/// 1��° �ڽ��� ä���� ������ 2��° �ڽ��� �Ѿ��
		/// </summary>

	}
}


/// <summary>
/// ������ ��Ȳ�� ���� ��հ� ���ϴ� ������ �ٲ۴�
/// </summary>
void Scene_Average::GetAverage()
{
	/// averageCheck�� true�϶�(�� ����ڽ����� ������Ʈ�� �� ������)
	if (averageCheck == true && m_pStatBox->MouseCount > 0 && m_pStatBox2->MouseCount2 > 0)
	{
		// ������Ʈ�� ù��°���� �� ���� ��
		if (m_pStatBox->returnTestWool == true && m_pStatBox2->returnTestWool2 == false )
		{
			D2DEngine::GetInstance()->DrawTextInt(1453, 507, m_averageWarmth);

			D2DEngine::GetInstance()->DrawTextInt(1453, 540, m_averageDurability);

			D2DEngine::GetInstance()->DrawTextInt(1453, 573, m_averagePermeability);

			D2DEngine::GetInstance()->DrawTextInt(1453, 606, (m_averagePrice));

			D2DEngine::GetInstance()->DrawTextInt(1575, 613, (m_pStatBox->targetQuantity * m_pStatBox->MouseCount));
		}
		// ������Ʈ�� 2�� �� ���� ��
		else if (m_pStatBox->returnTestWool == true && m_pStatBox2->returnTestWool2 == true)
		{
			D2DEngine::GetInstance()->DrawTextInt(1453, 507, m_averageWarmth);

			D2DEngine::GetInstance()->DrawTextInt(1453, 540, m_averageDurability);

			D2DEngine::GetInstance()->DrawTextInt(1453, 573, m_averagePermeability);

			D2DEngine::GetInstance()->DrawTextInt(1453, 606, m_averagePrice);

			D2DEngine::GetInstance()->DrawTextInt(1575, 613, (m_pStatBox->targetQuantity * m_pStatBox->MouseCount + m_pStatBox2->targetQuantity2 * m_pStatBox2->MouseCount2));
		}
		// ù��° ������Ʈ�� ������ �ι�° ������Ʈ���� ������� ��
		else if (m_pStatBox->returnTestWool == false && m_pStatBox2->returnTestWool2 == true)
		{
			D2DEngine::GetInstance()->DrawTextInt(1453, 507, m_averageWarmth);

			D2DEngine::GetInstance()->DrawTextInt(1453, 540, m_averageDurability);

			D2DEngine::GetInstance()->DrawTextInt(1453, 573, m_averagePermeability);

			D2DEngine::GetInstance()->DrawTextInt(1453, 606, m_averagePrice);

			D2DEngine::GetInstance()->DrawTextInt(1575, 613, (m_pStatBox2->targetQuantity2 * m_pStatBox2->MouseCount2));
		}
	}
	// ������Ʈ�� �ϳ��� ������
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

	//���ȹڽ�1�� ������� �ʰ� ���ȹڽ�2�� ���������
	if (m_pStatBox->IsEmpty() && !m_pStatBox2->IsEmpty())
	{
		m_averageWarmth = m_pStatBox->targetWarmth * m_pStatBox->MouseCount / m_pStatBox->MouseCount; 
		m_averageDurability = m_pStatBox->targetAbsoptivity * m_pStatBox->MouseCount / m_pStatBox->MouseCount;
		m_averagePermeability = m_pStatBox->targetAeration * m_pStatBox->MouseCount / m_pStatBox->MouseCount;
		m_averagePrice = m_pStatBox->targetPrice * m_pStatBox->MouseCount;
		m_sumEA = m_pStatBox->MouseCount;
		m_pStageManager->SetAveragePrice(m_averagePrice);
	}
	//���ȹڽ�1�� ����ְ� ���ȹڽ�2�� ������� ������
	else if (!m_pStatBox->IsEmpty() && m_pStatBox2->IsEmpty())
	{
		m_averageWarmth = m_pStatBox2->targetWarmth2 * m_pStatBox2->MouseCount2 / m_pStatBox2->MouseCount2;
		m_averageDurability = m_pStatBox2->targetAbsoptivity2 * m_pStatBox2->MouseCount2 / m_pStatBox2->MouseCount2;
		m_averagePermeability = m_pStatBox2->targetAeration2 * m_pStatBox2->MouseCount2 / m_pStatBox2->MouseCount2;
		m_averagePrice = m_pStatBox2->targetPrice2 * m_pStatBox2->MouseCount2;
		m_sumEA = m_pStatBox2->MouseCount2;
		m_pStageManager->SetAveragePrice(m_averagePrice);	
	}
	//�� �� ������� ������
	else if (m_pStatBox->IsEmpty() && m_pStatBox2->IsEmpty())
	{
		m_averageWarmth = (m_pStatBox->targetWarmth * m_pStatBox->MouseCount + m_pStatBox2->targetWarmth2 * m_pStatBox2->MouseCount2) / m_sumEA;
		m_averageDurability = (m_pStatBox->targetAbsoptivity * m_pStatBox->MouseCount + m_pStatBox2->targetAbsoptivity2 * m_pStatBox2->MouseCount2) / m_sumEA;
		m_averagePermeability = (m_pStatBox->targetAeration * m_pStatBox->MouseCount + m_pStatBox2->targetAeration2 * m_pStatBox2->MouseCount2) / m_sumEA;
		m_averagePrice = m_pStatBox->targetPrice * m_pStatBox->MouseCount + m_pStatBox2->targetPrice2 * m_pStatBox2->MouseCount2;
		m_sumEA = m_pStatBox->MouseCount + m_pStatBox2->MouseCount2;
		m_pStageManager->SetAveragePrice(m_averagePrice);
	}
	//�� �� ���������
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
/// 1��° �ڽ��� ������Ʈ�� ���ҹ�ư�� ������ mousecount�� 0 �� �Ǹ� Statbox�� Undo�Լ��� �����Ѵ�
/// </summary>
void Scene_Average::StopWhen1stZero()
{
	if (m_pStatBox->MouseCount == 0)
	{
		// StatBox�� Undo �Լ��� �ҷ��´�
		m_pStatBox->EmptyStatBox();
	}
}

/// <summary>
/// 2��° �ڽ��� ������Ʈ�� ���ҹ�ư�� ������ mousecount2�� 0 �� �Ǹ� Statbox2�� Undo2�Լ��� �����Ѵ�
/// </summary>
void Scene_Average::StopWhen2ndZero()
{
	if (m_pStatBox2->MouseCount2 == 0)
	{
		m_pStatBox2->EmptyStatBox();
	}
}

/// <summary>
/// ī��Ʈ ���� 10�� �ɶ� ������ư�� �������� ���´�
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

//��հ� ��ȯ �Լ���
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

//��հ��� ��Ÿ�� ���������� Ư�� �ɷ� ���¸� ������Ʈ ����
void Scene_Average::UpdateCurrentSpc()
{
	//�� �� ��������� �ƹ��͵� ������		//NONE ����
	if (!m_pStatBox->IsEmpty() && !m_pStatBox2->IsEmpty())
	{
		return;
	}

	//ù��° �ڽ��� ������� �ʰ� �ι�° �ڽ��� ���������
	if (m_pStatBox->IsEmpty() && !m_pStatBox2->IsEmpty())
	{
		this->m_currentSpc1 = m_pStatBox->m_spcAbil1;
		this->m_currentSpc2 = m_pStatBox->m_spcAbil2;
	}
	//ù��° �ڽ��� ����ְ� �ι�° �ڽ��� ������� ������
	else if (!m_pStatBox->IsEmpty() && m_pStatBox2->IsEmpty())
	{
		this->m_currentSpc1 = m_pStatBox2->m_spcAbil1;
		this->m_currentSpc2 = m_pStatBox2->m_spcAbil2;
	}
	//�� �� ���� ���������
	else if (m_pStatBox->IsEmpty() && m_pStatBox2->IsEmpty())
	{
		//������ ����
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

//�������� Ŭ���� ���ǿ�
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
/// Ȯ����ư
/// ���߿� ���ǵ��� �� �߰��ؾ��Ѵ�
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

//���� �κ��丮 �ʱ�ȭ		//�߸�
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

//������ ũ���� ����
void Scene_Average::UpdateShopAndCredits()
{
	m_pShop->UpdateCredits(m_pCredit);
	m_pShop->UnlockItems(m_pCredit, m_iwools, m_pInventory);
}




