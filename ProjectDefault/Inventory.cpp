#include "Inventory.h"
#include "../D2DEngine/D2DEngine.h"
#include "DragAndDrop.h"
#include "MouseManager.h"
#include "SceneManager.h"
#include "Shop.h"
#include "GameMenu.h"
#include "IScene.h"
#include "eObjectDefine.h"
#include "IWool.h"

Inventory::Inventory(const int objectNum, std::string objectName, SceneManager* pSceneManager)
	:Object(objectNum, objectName),
	m_containerSrcX(530), m_containerSrcY(920), m_containerDstX(1433), m_containerDstY(1063),
	m_boxSrcX(745), m_boxSrcY(929), m_boxDstX(873), m_boxDstY(1057),
	m_boxIntervalX(149), m_boxIntervalY(0), m_boxAmount(3),
	m_leftButtonSrcX(660), m_leftButtonSrcY(947), m_leftButtonDstX(724), m_leftButtonDstY(1047),
	m_rightButtonSrcX(1192), m_rightButtonSrcY(947), m_rightButtonDstX(1256), m_rightButtonDstY(1047),
	m_isLocked(false), m_mouseClickOnce(true), m_curPage(0), m_maxPage(1), m_curScene(0),
	m_localSceneManager(pSceneManager), m_DD1(nullptr), m_DD2(nullptr), m_DD3(nullptr), m_DD4(nullptr), m_DD5(nullptr), m_DD6(nullptr),
	m_sendIWool(nullptr), m_sendIWool2(nullptr), m_pShop(nullptr), m_pGameMenu(nullptr)
{
	this->renderOrder = OBJECT_ORDER;
	m_localD2D = D2DEngine::GetInstance();
	m_localMouse = MouseManager::GetInstance();

	m_DD1 = new DragAndDrop();
	m_DD2 = new DragAndDrop();
	m_DD3 = new DragAndDrop();
	m_DD4 = new DragAndDrop();
	m_DD5 = new DragAndDrop();
	m_DD6 = new DragAndDrop();
}

Inventory::Inventory(const int objectNum, const std::string& objectName, SceneManager* pSceneManager, const double posX, const double posY)
	:Object(objectNum, objectName, posX, posY),
	m_containerSrcX(posX), m_containerSrcY(posY), m_containerDstX(1433), m_containerDstY(1063),
	m_boxSrcX(745), m_boxSrcY(929), m_boxDstX(873), m_boxDstY(1057),
	m_boxIntervalX(149), m_boxIntervalY(0), m_boxAmount(3),
	m_leftButtonSrcX(660), m_leftButtonSrcY(947), m_leftButtonDstX(724), m_leftButtonDstY(1047),
	m_rightButtonSrcX(1192), m_rightButtonSrcY(947), m_rightButtonDstX(1256), m_rightButtonDstY(1047),
	m_isLocked(false), m_mouseClickOnce(true), m_curPage(0), m_maxPage(1), m_curScene(0),
	m_localSceneManager(pSceneManager), m_DD1(nullptr), m_DD2(nullptr), m_DD3(nullptr), m_DD4(nullptr), m_DD5(nullptr), m_DD6(nullptr),
	m_sendIWool(nullptr), m_sendIWool2(nullptr), m_pShop(nullptr), m_pGameMenu(nullptr)
{
	this->renderOrder = OBJECT_ORDER;
	m_localD2D = D2DEngine::GetInstance();
	m_localMouse = MouseManager::GetInstance();

	m_DD1 = new DragAndDrop();
	m_DD2 = new DragAndDrop();
	m_DD3 = new DragAndDrop();
	m_DD4 = new DragAndDrop();
	m_DD5 = new DragAndDrop();
	m_DD6 = new DragAndDrop();
}

Inventory::~Inventory()
{
	delete m_DD1;
	delete m_DD2;
	delete m_DD3;
	delete m_DD4;
	delete m_DD5;
	delete m_DD6;
}

void Inventory::UpdateObject()
{
	GetCurrentScene();

	if (m_strCurScene == "AverageScene")		//���� 0�� ��հ�Scene		//���߿� Scene�����Ǹ� �����ؾ��ϴµ� �̸����� ���� �� ������?
	{
		PressButton();
	}
}

//ȭ�鿡 ǥ�õ� ������ ����Ʈ�� ������Ʈ ���ִ� �Լ�
//����/������ ����¡ ��ư�� �����ų� �������� �������� ��� ������Ʈ �ǰ�
void Inventory::UpdateShowList()
{
	m_showItemList.clear();

	if (m_itemList.size() > 0)
	{
		for (int i = 0; i < m_boxAmount; i++)
		{
			if (i + (m_curPage * 3) < m_itemList.size())
			{
				if (m_itemList[i + (m_curPage * 3)] != nullptr)
				{
					m_showItemList.push_back(m_itemList[i + (m_curPage * 3)]);
				}
			}
		}
	}
}

//StatBox�� ������Ʈ ���� �Լ�
//�ڽ��� Ŭ���ϸ� �ش� �������� statbox�� ǥ�õǰ� ���� ����
void Inventory::UpdateStatBox()
{
	if (m_showItemList.empty())
	{
		return;
	}

	if (m_pShop->GetActivated() == false && m_pGameMenu->GetActivated() == false)
	{
		//ù��° �ڽ�
		m_DD1->SetDragAndDrop(
			[this]()->void
			{
				if (m_curPage == 0)
				{
					if (m_showItemList.size() > 0)
						m_localD2D->DrawSpriteAlpha(m_showItemList[0]->GetObjectDefine(), m_localMouse->GetXPos() - 50, m_localMouse->GetYPos() - 50, 0.5f);
				}
				else if (m_curPage == 1)
				{
					if (m_showItemList.size() > 0)
						m_localD2D->DrawSpriteAlpha(m_showItemList[0]->GetObjectDefine(), m_localMouse->GetXPos() - 50, m_localMouse->GetYPos() - 50, 0.5f);
				}
			},
			[this]()->void
			{
				if (m_showItemList.size() > 0)
					UpdateSendIWool(m_showItemList[0]);
			},
				[this]()->void
			{

			},
				[this]()->void
			{

			},
				[this]()->void
			{

			},
				m_localMouse->GetXPos(), m_localMouse->GetYPos(),
				m_boxSrcX, m_boxSrcY, m_boxDstX, m_boxDstY,
				311, 191, 567, 447
				);

		//�ι�° �ڽ�
		m_DD2->SetDragAndDrop(
			[this]()->void
			{
				if (m_curPage == 0)
				{
					if (m_showItemList.size() > 1)
						m_localD2D->DrawSpriteAlpha(m_showItemList[1]->GetObjectDefine(), m_localMouse->GetXPos() - 50, m_localMouse->GetYPos() - 50, 0.5f);
				}
				else if (m_curPage == 1)
				{
					if (m_showItemList.size() > 1)
						m_localD2D->DrawSpriteAlpha(m_showItemList[1]->GetObjectDefine(), m_localMouse->GetXPos() - 50, m_localMouse->GetYPos() - 50, 0.5f);
				}
			},
			[this]()->void
			{
				if (m_showItemList.size() > 1)
					UpdateSendIWool(m_showItemList[1]);
			},
				[this]()->void
			{

			},
				[this]()->void
			{

			},
				[this]()->void
			{

			},
				m_localMouse->GetXPos(), m_localMouse->GetYPos(),
				m_boxSrcX + m_boxIntervalX, m_boxSrcY, m_boxDstX + m_boxIntervalX, m_boxDstY,
				311, 191, 567, 447
				);

		//����° �ڽ�
		m_DD3->SetDragAndDrop(
			[this]()->void
			{
				if (m_curPage == 0)
				{
					if (m_showItemList.size() > 2)
						m_localD2D->DrawSpriteAlpha(m_showItemList[2]->GetObjectDefine(), m_localMouse->GetXPos() - 50, m_localMouse->GetYPos() - 50, 0.5f);
				}
				else if (m_curPage == 1)
				{
					if (m_showItemList.size() > 2)
						m_localD2D->DrawSpriteAlpha(m_showItemList[2]->GetObjectDefine(), m_localMouse->GetXPos() - 50, m_localMouse->GetYPos() - 50, 0.5f);
				}
			},
			[this]()->void
			{
				if (m_showItemList.size() > 2)
					UpdateSendIWool(m_showItemList[2]);
			},
				[this]()->void
			{

			},
				[this]()->void
			{

			},
				[this]()->void
			{

			},
				m_localMouse->GetXPos(), m_localMouse->GetYPos(),
				m_boxSrcX + m_boxIntervalX * 2, m_boxSrcY, m_boxDstX + m_boxIntervalX * 2, m_boxDstY,
				311, 191, 567, 447
				);
	}
}

void Inventory::UpdateStatBox2()
{
	if (m_showItemList.empty())
	{
		return;
	}

	if (m_pShop->GetActivated() == false && m_pGameMenu->GetActivated() == false)
	{
	//ù��° �ڽ�
	m_DD4->SetDragAndDrop(
		[this]()->void
		{
			if (m_curPage == 0)
			{
				if (m_showItemList.size() > 0)
					m_localD2D->DrawSpriteAlpha(m_showItemList[0]->GetObjectDefine(), m_localMouse->GetXPos() - 50, m_localMouse->GetYPos() - 50, 0.5f);
			}
			else if (m_curPage == 1)
			{
				if (m_showItemList.size() > 0)
					m_localD2D->DrawSpriteAlpha(m_showItemList[0]->GetObjectDefine(), m_localMouse->GetXPos() - 50, m_localMouse->GetYPos() - 50, 0.5f);
			}
		},
		[this]()->void
		{
			if (m_showItemList.size() > 0)
				UpdateSendIWool2(m_showItemList[0]);
		},
			[this]()->void
		{

		},
			[this]()->void
		{

		},
			[this]()->void
		{

		},
			m_localMouse->GetXPos(), m_localMouse->GetYPos(),
			m_boxSrcX, m_boxSrcY, m_boxDstX, m_boxDstY,
			311, 588, 567, 854
			);

	//�ι�° �ڽ�
	m_DD5->SetDragAndDrop(
		[this]()->void
		{
			if (m_curPage == 0)
			{
				if (m_showItemList.size() > 1)
					m_localD2D->DrawSpriteAlpha(m_showItemList[1]->GetObjectDefine(), m_localMouse->GetXPos() - 50, m_localMouse->GetYPos() - 50, 0.5f);
			}
			else if (m_curPage == 1)
			{
				if (m_showItemList.size() > 1)
					m_localD2D->DrawSpriteAlpha(m_showItemList[1]->GetObjectDefine(), m_localMouse->GetXPos() - 50, m_localMouse->GetYPos() - 50, 0.5f);
			}
		},
		[this]()->void
		{
			if (m_showItemList.size() > 1)
				UpdateSendIWool2(m_showItemList[1]);
		},
			[this]()->void
		{

		},
			[this]()->void
		{

		},
			[this]()->void
		{

		},
			m_localMouse->GetXPos(), m_localMouse->GetYPos(),
			m_boxSrcX + m_boxIntervalX, m_boxSrcY, m_boxDstX + m_boxIntervalX, m_boxDstY,
			311, 588, 567, 854
			);

	//����° �ڽ�
	m_DD6->SetDragAndDrop(
		[this]()->void
		{
			if (m_curPage == 0)
			{
				if (m_showItemList.size() > 2)
					m_localD2D->DrawSpriteAlpha(m_showItemList[2]->GetObjectDefine(), m_localMouse->GetXPos() - 50, m_localMouse->GetYPos() - 50, 0.5f);
			}
			else if (m_curPage == 1)
			{
				if (m_showItemList.size() > 2)
					m_localD2D->DrawSpriteAlpha(m_showItemList[2]->GetObjectDefine(), m_localMouse->GetXPos() - 50, m_localMouse->GetYPos() - 50, 0.5f);
			}
		},
		[this]()->void
		{
			if (m_showItemList.size() > 2)
				UpdateSendIWool2(m_showItemList[2]);
		},
			[this]()->void
		{

		},
			[this]()->void
		{

		},
			[this]()->void
		{

		},
			m_localMouse->GetXPos(), m_localMouse->GetYPos(),
			m_boxSrcX + m_boxIntervalX * 2, m_boxSrcY, m_boxDstX + m_boxIntervalX * 2, m_boxDstY,
			311, 588, 567, 854
			);
	}
}

//���ȹڽ��� ������ ������ ������Ʈ ���ִ� �Լ�
void Inventory::UpdateSendIWool(IWool* obj)
{
	this->m_sendIWool = obj;
}

void Inventory::UpdateSendIWool2(IWool* obj)
{
	this->m_sendIWool2 = obj;
}

void Inventory::EmptySendIWool()
{
	this->m_sendIWool = nullptr;
}

void Inventory::EmptySendIWool2()
{
	this->m_sendIWool2 = nullptr;
}

IWool* Inventory::GetSendIWool()
{
	return this->m_sendIWool;
}

IWool* Inventory::GetSendIWool2()
{
	return this->m_sendIWool2;
}

//��ư ������ ������ �ٲٴ� �Լ�
void Inventory::PressButton()
{
	//���ʹ�ư ��������
	if (m_localMouse->GetLeftOneDownClickState() == true
		&& m_leftButtonSrcX <= m_localMouse->GetXPos()
		&& m_leftButtonSrcY <= m_localMouse->GetYPos()
		&& m_leftButtonDstX >= m_localMouse->GetXPos()
		&& m_leftButtonDstY >= m_localMouse->GetYPos()
		)
	{
		//�������� 1���� ������ �� �����ϱ�		//0�� 1������
		if (m_curPage > 0)
		{
			m_curPage--;
		}
		UpdateShowList();
	}

	//�����ʹ�ư ��������
	if (m_localMouse->GetLeftOneDownClickState() == true
		&& m_rightButtonSrcX <= m_localMouse->GetXPos()
		&& m_rightButtonSrcY <= m_localMouse->GetYPos()
		&& m_rightButtonDstX >= m_localMouse->GetXPos()
		&& m_rightButtonDstY >= m_localMouse->GetYPos()
		)
	{
		if (m_curPage < m_maxPage)
		{
			m_curPage++;
		}
		UpdateShowList();
	}

	m_localMouse->OneClickEnd();
}

void Inventory::AddObject(IWool* obj)
{
	m_itemList.push_back(obj);
}

int Inventory::GetItemListSize()
{
	return this->m_itemList.size();
}

//�ش� �������� �ִ���
bool Inventory::CheckItem(eObjectDefine eOD)
{
	for (int i = 0; i < this->m_itemList.size(); i++)
	{
		if (m_itemList[i]->GetObjectDefine() == eOD)
		{
			return true;
		}
	}

	return false;
}

//���� �ʱ�ȭ
void Inventory::ResetInfos()
{
	this->m_itemList.clear();
	this->m_showItemList.clear();
	this->m_curPage = 0;
}

void Inventory::RenderObject()
{
	if (m_strCurScene == "AverageScene")
	{
		for (int i = 0; i < m_boxAmount; i++)
		{
			m_localD2D->DrawSprite(eObjectDefine::ITEM_BOX, m_boxSrcX + m_boxIntervalX * i, m_boxSrcY);
		}

		m_localD2D->DrawSprite(eObjectDefine::PAGING_BUTTON, m_leftButtonSrcX, m_leftButtonSrcY, 180.0f);
		m_localD2D->DrawSprite(eObjectDefine::PAGING_BUTTON, m_rightButtonSrcX, m_rightButtonSrcY);
		m_localD2D->DrawSprite(eObjectDefine::SKILL_NOTE, 1220, 809);

		if (m_showItemList.size() > 0)
		{
			eObjectDefine eoD;

			for (int i = 0; i < m_boxAmount; i++)
			{
				if (i < m_showItemList.size())
				{
					eoD = m_showItemList[i]->GetObjectDefine();
					m_localD2D->DrawSprite(eoD, m_boxSrcX + 15 + m_boxIntervalX * i, m_boxSrcY + 15);
				}
			}
		}

		UpdateStatBox();
		UpdateStatBox2();

		//m_localD2D->DrawText(100, 600, m_curPage);
		//m_localD2D->DrawText(100, 650, m_itemList.size());
		//m_localD2D->DrawText(100, 700, m_showItemList.size());

		//m_localD2D->DrawText(m_localMouse->GetXPos(), m_localMouse->GetYPos(), m_localMouse->GetXPos());
		//m_localD2D->DrawText(m_localMouse->GetXPos() + 100, m_localMouse->GetYPos(), m_localMouse->GetYPos());
	}
}

//���� scene�� �������� �˾ƿ��� �Լ�		
//�κ��丮�� ��հ� ���ϱ� ~ ���������� ������ ����� ���� ���� ������ �������� ������Ʈ�� ��� �޾ƿ;���
void Inventory::GetCurrentScene()
{
	m_curScene = m_localSceneManager->GetNowScene()->GetSceneIndex();
	m_strCurScene = m_localSceneManager->GetNowScene()->GetSceneName();

	m_pShop = (Shop*)m_localSceneManager->GetScene("AverageScene")->GetSceneObject("����");
	m_pGameMenu = (GameMenu*)m_localSceneManager->GetScene("AverageScene")->GetSceneObject("�޴�");
}