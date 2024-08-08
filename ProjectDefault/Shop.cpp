#include "Shop.h"
#include "Inventory.h"
#include "Credit.h"
#include "IWool.h"
#include "MouseManager.h"
#include "StageManager.h"
#include "../D2DEngine/D2DEngine.h"
#include "SoundManager.h"

Shop::Shop(const int objectNum, string objectName)
	:Object(objectNum, objectName),
	m_iconSrcX(23), m_iconSrcY(929), m_iconDstX(151), m_iconDstY(1057),
	m_containerSrcX(418), m_containerSrcY(42), m_containerDstX(1418), m_containerDstY(1034),
	m_imageBoxSrcX(576), m_imageBoxSrcY(213), m_imageBoxDstX(704), m_imageBoxDstY(341),
	m_imageSrcX(590), m_imageSrcY(227), m_imageDstX(690), m_imageDstY(327),
	m_statBoxSrcX(604), m_statBoxSrcY(243), m_statBoxDstX(860), m_statBoxDstY(499), m_rot(0.0f), m_rotStatus(false),
	m_statTextSrcX(688), m_statTextSrcY(280), m_statTextDstX(888), m_statTextDstY(480),
	m_unlockButtonSrcX(682), m_unlockButtonSrcY(510), m_unlockButtonDstX(782), m_unlockButtonDstY(574),
	m_closeButtonSrcX(1290), m_closeButtonSrcY(47), m_closeButtonDstX(1390), m_closeButtonDstY(147),
	m_productAmount(4), m_boxIntervalX(414), m_boxIntervalY(397), m_isActivated(false), m_mouseClickOnce(true),
	m_curCredit(0), m_1stPrice(40), m_2ndPrice(55), m_3rdPrice(90), m_4thPrice(120),
	m_firstItemUnlocked(false), m_secondItemUnlocked(false), m_thirdItemUnlocked(false), m_fourthItemUnlocked(false)
{
	this->renderOrder = SHOP_ORDER;
	m_localD2D = D2DEngine::GetInstance();
	m_localMouse = MouseManager::GetInstance();
	m_pStageManager = StageManager::GetInstance();
}

Shop::Shop(const int objectNum, const string& objectName, const double posX, const double posY)
	:Object(objectNum, objectName, posX, posY),
	m_iconSrcX(posX), m_iconSrcY(posY), m_iconDstX(151), m_iconDstY(1057),
	m_containerSrcX(418), m_containerSrcY(42), m_containerDstX(1418), m_containerDstY(1034),
	m_imageSrcX(590), m_imageSrcY(227), m_imageDstX(690), m_imageDstY(327),
	m_imageBoxSrcX(576), m_imageBoxSrcY(213), m_imageBoxDstX(704), m_imageBoxDstY(341),
	m_statBoxSrcX(604), m_statBoxSrcY(243), m_statBoxDstX(860), m_statBoxDstY(499), m_rot(0.0f), m_rotStatus(false),
	m_statTextSrcX(688), m_statTextSrcY(280), m_statTextDstX(888), m_statTextDstY(480),
	m_unlockButtonSrcX(682), m_unlockButtonSrcY(510), m_unlockButtonDstX(782), m_unlockButtonDstY(574),
	m_closeButtonSrcX(1290), m_closeButtonSrcY(47), m_closeButtonDstX(1390), m_closeButtonDstY(147),
	m_productAmount(4), m_boxIntervalX(414), m_boxIntervalY(397), m_isActivated(false), m_mouseClickOnce(true),
	m_curCredit(0), m_1stPrice(50), m_2ndPrice(80), m_3rdPrice(100), m_4thPrice(130),
	m_firstItemUnlocked(false), m_secondItemUnlocked(false), m_thirdItemUnlocked(false), m_fourthItemUnlocked(false)
{
	this->renderOrder = SHOP_ORDER;
	m_localD2D = D2DEngine::GetInstance();
	m_localMouse = MouseManager::GetInstance();
	m_pStageManager = StageManager::GetInstance();
}

Shop::~Shop()
{

}

void Shop::UpdateObject()
{
	OpenStore();
	RotateIcon();
}

//걱정마셈 나도 어지러움
void Shop::RenderObject()
{
	m_localD2D->DrawSprite(eObjectDefine::SHOP_ICON, m_iconSrcX, m_iconSrcY, m_rot);

	if (this->m_isActivated == true)
	{
		m_localD2D->DrawSprite(eObjectDefine::SHOP_BACKGROUND_INTERFACE, m_containerSrcX, m_containerSrcY);
		m_localD2D->DrawSprite(eObjectDefine::SHOP_CLOSE, m_closeButtonSrcX, m_closeButtonSrcY);

		//첫번째 박스	//램스울
		if (m_firstItemUnlocked == false)
		{
			m_localD2D->DrawSprite(eObjectDefine::SHOP_BACK_BOX, m_statBoxSrcX, m_statBoxSrcY);
			m_localD2D->DrawSprite(eObjectDefine::SHOP_LAMBSWOOL_INFO, m_statTextSrcX, m_statTextSrcY);
			m_localD2D->DrawSprite(eObjectDefine::SHOP_ITEM_ICON, m_imageBoxSrcX, m_imageBoxSrcY);
			m_localD2D->DrawSprite(eObjectDefine::LAMBSWOOL, m_imageSrcX, m_imageSrcY);
			m_localD2D->DrawSprite(eObjectDefine::SHOP_UNLOCK, m_unlockButtonSrcX, m_unlockButtonSrcY);

			if (m_pStageManager->GetStageNum() < 2)
			{
				m_localD2D->DrawSprite(eObjectDefine::SHOP_CHAIN, m_imageBoxSrcX, m_imageBoxSrcY);
			}
		}
		else if (m_firstItemUnlocked == true)
		{
			m_localD2D->DrawSpriteAlpha(eObjectDefine::SHOP_BACK_BOX, m_statBoxSrcX, m_statBoxSrcY, 0.5f);
			m_localD2D->DrawSpriteAlpha(eObjectDefine::SHOP_LAMBSWOOL_INFO, m_statTextSrcX, m_statTextSrcY, 0.5f);
			m_localD2D->DrawSpriteAlpha(eObjectDefine::SHOP_ITEM_ICON, m_imageBoxSrcX, m_imageBoxSrcY, 0.5f);
			m_localD2D->DrawSpriteAlpha(eObjectDefine::LAMBSWOOL, m_imageSrcX, m_imageSrcY, 0.5f);
			m_localD2D->DrawSpriteAlpha(eObjectDefine::SHOP_UNLOCK, m_unlockButtonSrcX, m_unlockButtonSrcY, 0.5f);
		}

		//두번째 박스	//삼베실
		if (m_secondItemUnlocked == false)
		{
			m_localD2D->DrawSprite(eObjectDefine::SHOP_BACK_BOX, m_statBoxSrcX + m_boxIntervalX, m_statBoxSrcY);
			m_localD2D->DrawSprite(eObjectDefine::SHOP_HEMP_INFO, m_statTextSrcX + m_boxIntervalX, m_statTextSrcY);
			m_localD2D->DrawSprite(eObjectDefine::SHOP_ITEM_ICON, m_imageBoxSrcX + m_boxIntervalX, m_imageBoxSrcY);
			m_localD2D->DrawSprite(eObjectDefine::HEMP, m_imageSrcX + m_boxIntervalX, m_imageSrcY);
			m_localD2D->DrawSprite(eObjectDefine::SHOP_UNLOCK, m_unlockButtonSrcX + m_boxIntervalX, m_unlockButtonSrcY);
		
			if (m_pStageManager->GetStageNum() < 3)
			{
				m_localD2D->DrawSprite(eObjectDefine::SHOP_CHAIN, m_imageBoxSrcX + m_boxIntervalX, m_imageBoxSrcY);
			}
		}	
		else if (m_secondItemUnlocked == true)
		{
			m_localD2D->DrawSpriteAlpha(eObjectDefine::SHOP_BACK_BOX, m_statBoxSrcX + m_boxIntervalX, m_statBoxSrcY, 0.5f);
			m_localD2D->DrawSpriteAlpha(eObjectDefine::SHOP_HEMP_INFO, m_statTextSrcX + m_boxIntervalX, m_statTextSrcY, 0.5f);
			m_localD2D->DrawSpriteAlpha(eObjectDefine::SHOP_ITEM_ICON, m_imageBoxSrcX + m_boxIntervalX, m_imageBoxSrcY, 0.5f);
			m_localD2D->DrawSpriteAlpha(eObjectDefine::HEMP, m_imageSrcX + m_boxIntervalX, m_imageSrcY, 0.5f);
			m_localD2D->DrawSpriteAlpha(eObjectDefine::SHOP_UNLOCK, m_unlockButtonSrcX + m_boxIntervalX, m_unlockButtonSrcY, 0.5f);
		}

		//세번째 박스	//앙고라털
		if (m_thirdItemUnlocked == false)
		{
			m_localD2D->DrawSprite(eObjectDefine::SHOP_BACK_BOX, m_statBoxSrcX, m_statBoxSrcY + m_boxIntervalY);
			m_localD2D->DrawSprite(eObjectDefine::SHOP_ANGORA_INFO, m_statTextSrcX, m_statTextSrcY + m_boxIntervalY);
			m_localD2D->DrawSprite(eObjectDefine::SHOP_ITEM_ICON, m_imageBoxSrcX, m_imageBoxSrcY + m_boxIntervalY);
			m_localD2D->DrawSprite(eObjectDefine::ANGORA, m_imageSrcX, m_imageSrcY + m_boxIntervalY);
			m_localD2D->DrawSprite(eObjectDefine::SHOP_UNLOCK, m_unlockButtonSrcX, m_unlockButtonSrcY + m_boxIntervalY);
		
			if (m_pStageManager->GetStageNum() < 3)
			{
				m_localD2D->DrawSprite(eObjectDefine::SHOP_CHAIN, m_imageBoxSrcX, m_imageBoxSrcY + m_boxIntervalY);
			}
		}
		else if (m_thirdItemUnlocked == true)
		{
			m_localD2D->DrawSpriteAlpha(eObjectDefine::SHOP_BACK_BOX, m_statBoxSrcX, m_statBoxSrcY + m_boxIntervalY, 0.5f);
			m_localD2D->DrawSpriteAlpha(eObjectDefine::SHOP_ANGORA_INFO, m_statTextSrcX, m_statTextSrcY + m_boxIntervalY, 0.5f);
			m_localD2D->DrawSpriteAlpha(eObjectDefine::SHOP_ITEM_ICON, m_imageBoxSrcX, m_imageBoxSrcY + m_boxIntervalY, 0.5f);
			m_localD2D->DrawSpriteAlpha(eObjectDefine::ANGORA, m_imageSrcX, m_imageSrcY + m_boxIntervalY, 0.5f);
			m_localD2D->DrawSpriteAlpha(eObjectDefine::SHOP_UNLOCK, m_unlockButtonSrcX, m_unlockButtonSrcY + m_boxIntervalY, 0.5f);
		}

		//네번째 박스	//캐시미어
		if (m_fourthItemUnlocked == false)
		{
			m_localD2D->DrawSprite(eObjectDefine::SHOP_BACK_BOX, m_statBoxSrcX + m_boxIntervalX, m_statBoxSrcY + m_boxIntervalY);
			m_localD2D->DrawSprite(eObjectDefine::SHOP_CASHMERE_INFO, m_statTextSrcX + m_boxIntervalX, m_statTextSrcY + m_boxIntervalY);
			m_localD2D->DrawSprite(eObjectDefine::SHOP_ITEM_ICON, m_imageBoxSrcX + m_boxIntervalX, m_imageBoxSrcY + m_boxIntervalY);
			m_localD2D->DrawSprite(eObjectDefine::CASHMERE, m_imageSrcX + m_boxIntervalX, m_imageSrcY + m_boxIntervalY);
			m_localD2D->DrawSprite(eObjectDefine::SHOP_UNLOCK, m_unlockButtonSrcX + m_boxIntervalX, m_unlockButtonSrcY + m_boxIntervalY);
		
			if (m_pStageManager->GetStageNum() < 3)
			{
				m_localD2D->DrawSprite(eObjectDefine::SHOP_CHAIN, m_imageBoxSrcX + m_boxIntervalX, m_imageBoxSrcY + m_boxIntervalY);
			}
		}
		else if (m_fourthItemUnlocked == true)
		{
			m_localD2D->DrawSpriteAlpha(eObjectDefine::SHOP_BACK_BOX, m_statBoxSrcX + m_boxIntervalX, m_statBoxSrcY + m_boxIntervalY, 0.5f);
			m_localD2D->DrawSpriteAlpha(eObjectDefine::SHOP_CASHMERE_INFO, m_statTextSrcX + m_boxIntervalX, m_statTextSrcY + m_boxIntervalY, 0.5f);
			m_localD2D->DrawSpriteAlpha(eObjectDefine::SHOP_ITEM_ICON, m_imageBoxSrcX + m_boxIntervalX, m_imageBoxSrcY + m_boxIntervalY, 0.5f);
			m_localD2D->DrawSpriteAlpha(eObjectDefine::CASHMERE, m_imageSrcX + m_boxIntervalX, m_imageSrcY + m_boxIntervalY, 0.5f);
			m_localD2D->DrawSpriteAlpha(eObjectDefine::SHOP_UNLOCK, m_unlockButtonSrcX + m_boxIntervalX, m_unlockButtonSrcY + m_boxIntervalY, 0.5f);
		}
	}
}

//소지금의 정보를 받아오는 함수
void Shop::UpdateCredits(Credit* crd)
{
	this->m_curCredit = crd->GetCredits();
}

//상점의 품목을 해금하는 함수
void Shop::UnlockItems(Credit* crd, vector<IWool*> iwools, Inventory* inven)
{
	static bool Buy1 = false;
	static bool Buy2 = false;
	static bool Buy3 = false;
	static bool Buy4 = false;

	int curStageNum = StageManager::GetInstance()->GetStageNum();

	if (m_isActivated == true)
	{
		IWool* theItem = nullptr;
		//첫번째 아이템		//램스울
		if (m_localMouse->GetLeftButtonDownState() == true
			&& m_mouseClickOnce == true
			&& m_unlockButtonSrcX <= m_localMouse->GetXPos()
			&& m_unlockButtonSrcY <= m_localMouse->GetYPos()
			&& m_unlockButtonDstX >= m_localMouse->GetXPos()
			&& m_unlockButtonDstY >= m_localMouse->GetYPos()
			)
		{
			m_mouseClickOnce = false;
		}

		if (m_localMouse->GetLeftButtonUpState() == true
			&& m_mouseClickOnce == false
			&& m_firstItemUnlocked == false
			&& m_curCredit >= m_1stPrice
			&& curStageNum > 1
			&& m_unlockButtonSrcX <= m_localMouse->GetXPos()
			&& m_unlockButtonSrcY <= m_localMouse->GetYPos()
			&& m_unlockButtonDstX >= m_localMouse->GetXPos()
			&& m_unlockButtonDstY >= m_localMouse->GetYPos()
			)
		{
			m_firstItemUnlocked = true;
			
			// Stage 매니저애서 처리하도록 수정
			//crd->SetCredits(crd->GetCredits() - m_1stPrice);
			m_pStageManager->DecreaseMoney(m_1stPrice);

			for (int i = 0; i < iwools.size(); i++)
			{
				if (iwools[i]->GetObjectDefine() == eObjectDefine::LAMBSWOOL)
				{
					theItem = iwools[i];
				}
			}

			if (inven != nullptr && theItem != nullptr)
			{
				///
				if (Buy1 == false)
				{
					SoundManager::GetInstance().PlaySounds(UnlockItem);
					Buy1 = true;
				}
				inven->AddObject(theItem);
				inven->UpdateShowList();
			}

			m_mouseClickOnce = true;
		}

		//두번째 아이템		//삼베실
		if (m_localMouse->GetLeftButtonDownState() == true
			&& m_mouseClickOnce == true
			&& m_unlockButtonSrcX + m_boxIntervalX <= m_localMouse->GetXPos()
			&& m_unlockButtonSrcY <= m_localMouse->GetYPos()
			&& m_unlockButtonDstX + m_boxIntervalX >= m_localMouse->GetXPos()
			&& m_unlockButtonDstY >= m_localMouse->GetYPos()
			)
		{
			m_mouseClickOnce = false;
		}

		if (m_localMouse->GetLeftButtonUpState() == true
			&& m_mouseClickOnce == false
			&& m_secondItemUnlocked == false
			&& m_curCredit >= m_2ndPrice
			&& curStageNum > 2
			&& m_unlockButtonSrcX + m_boxIntervalX <= m_localMouse->GetXPos()
			&& m_unlockButtonSrcY <= m_localMouse->GetYPos()
			&& m_unlockButtonDstX + m_boxIntervalX >= m_localMouse->GetXPos()
			&& m_unlockButtonDstY >= m_localMouse->GetYPos()
			)
		{
			m_secondItemUnlocked = true;

			// Stage 매니저애서 처리하도록 수정
			//crd->SetCredits(crd->GetCredits() - m_2ndPrice);
			m_pStageManager->DecreaseMoney(m_2ndPrice);

			for (int i = 0; i < iwools.size(); i++)
			{
				if (iwools[i]->GetObjectDefine() == eObjectDefine::HEMP)
				{
					theItem = iwools[i];
				}
			}

			if (inven != nullptr && theItem != nullptr)
			{
				///
				if (Buy2 == false)
				{
					SoundManager::GetInstance().PlaySounds(UnlockItem);
					Buy2 = true;
				}
				inven->AddObject(theItem);
				inven->UpdateShowList();
			}

			m_mouseClickOnce = true;
		}

		//세번째 아이템		//앙고라털
		if (m_localMouse->GetLeftButtonDownState() == true
			&& m_mouseClickOnce == true
			&& m_unlockButtonSrcX <= m_localMouse->GetXPos()
			&& m_unlockButtonSrcY + m_boxIntervalY <= m_localMouse->GetYPos()
			&& m_unlockButtonDstX >= m_localMouse->GetXPos()
			&& m_unlockButtonDstY + m_boxIntervalY >= m_localMouse->GetYPos()
			)
		{
			m_mouseClickOnce = false;
		}

		if (m_localMouse->GetLeftButtonUpState() == true
			&& m_mouseClickOnce == false
			&& m_thirdItemUnlocked == false
			&& m_curCredit >= m_3rdPrice
			&& curStageNum > 2
			&& m_unlockButtonSrcX <= m_localMouse->GetXPos()
			&& m_unlockButtonSrcY + m_boxIntervalY <= m_localMouse->GetYPos()
			&& m_unlockButtonDstX >= m_localMouse->GetXPos()
			&& m_unlockButtonDstY + m_boxIntervalY >= m_localMouse->GetYPos()
			)
		{
			m_thirdItemUnlocked = true;

			// Stage 매니저애서 처리하도록 수정
			//crd->SetCredits(crd->GetCredits() - m_3rdPrice);
			m_pStageManager->DecreaseMoney(m_3rdPrice);

			for (int i = 0; i < iwools.size(); i++)
			{
				if (iwools[i]->GetObjectDefine() == eObjectDefine::ANGORA)
				{
					theItem = iwools[i];
				}
			}

			if (inven != nullptr && theItem != nullptr)
			{
				///
				if (Buy3 == false)
				{
					SoundManager::GetInstance().PlaySounds(UnlockItem);
					Buy3 = true;
				}
				inven->AddObject(theItem);
				inven->UpdateShowList();
			}

			m_mouseClickOnce = true;
		}

		//네번째 아이템		//캐시미어
		if (m_localMouse->GetLeftButtonDownState() == true
			&& m_mouseClickOnce == true
			&& m_unlockButtonSrcX + m_boxIntervalX <= m_localMouse->GetXPos()
			&& m_unlockButtonSrcY + m_boxIntervalY <= m_localMouse->GetYPos()
			&& m_unlockButtonDstX + m_boxIntervalX >= m_localMouse->GetXPos()
			&& m_unlockButtonDstY + m_boxIntervalY >= m_localMouse->GetYPos()
			)
		{
			m_mouseClickOnce = false;
		}

		if (m_localMouse->GetLeftButtonUpState() == true
			&& m_mouseClickOnce == false
			&& m_fourthItemUnlocked == false
			&& m_curCredit >= m_4thPrice
			&& curStageNum > 2
			&& m_unlockButtonSrcX + m_boxIntervalX <= m_localMouse->GetXPos()
			&& m_unlockButtonSrcY + m_boxIntervalY <= m_localMouse->GetYPos()
			&& m_unlockButtonDstX + m_boxIntervalX >= m_localMouse->GetXPos()
			&& m_unlockButtonDstY + m_boxIntervalY >= m_localMouse->GetYPos()
			)
		{
			m_fourthItemUnlocked = true;
			
			// Stage 매니저애서 처리하도록 수정
			//crd->SetCredits(crd->GetCredits() - m_4thPrice);
			m_pStageManager->DecreaseMoney(m_4thPrice);

			for (int i = 0; i < iwools.size(); i++)
			{
				if (iwools[i]->GetObjectDefine() == eObjectDefine::CASHMERE)
				{
					theItem = iwools[i];
				}
			}

			if (inven != nullptr && theItem != nullptr)
			{
				///
				if (Buy4 == false)
				{
					SoundManager::GetInstance().PlaySounds(UnlockItem);
					Buy4 = true;
				}
				inven->AddObject(theItem);
				inven->UpdateShowList();
			}

			m_mouseClickOnce = true;
		}
	}
}

//상점 아이콘을 클릭하면 상점이 열리는 함수
//상점 밑에 깔린 것들은 활성화되면 안되겠지
void Shop::OpenStore()
{
	if (m_localMouse->GetLeftButtonDownState() == true
		&& m_mouseClickOnce == true
		&& m_iconSrcX <= m_localMouse->GetXPos()
		&& m_iconSrcY <= m_localMouse->GetYPos()
		&& m_iconDstX >= m_localMouse->GetXPos()
		&& m_iconDstY >= m_localMouse->GetYPos()
		)
	{
		m_mouseClickOnce = false;
	}

	if (m_localMouse->GetLeftButtonUpState() == true
		&& m_mouseClickOnce == false
		&& m_iconSrcX <= m_localMouse->GetXPos()
		&& m_iconSrcY <= m_localMouse->GetYPos()
		&& m_iconDstX >= m_localMouse->GetXPos()
		&& m_iconDstY >= m_localMouse->GetYPos()
		)
	{
		this->m_isActivated = true;

		m_mouseClickOnce = true;
	}
}

//상점을 닫는 함수
//상점을 닫으면 비활성화한 다른 오브젝트들이 활성화되어야 할텐데
void Shop::CloseStore()
{
	if (m_localMouse->GetLeftOneDownClickState() == true
		&& m_closeButtonSrcX <= m_localMouse->GetXPos()
		&& m_closeButtonSrcY <= m_localMouse->GetYPos()
		&& m_closeButtonDstX >= m_localMouse->GetXPos()
		&& m_closeButtonDstY >= m_localMouse->GetYPos()
		)
	{
		this->m_isActivated = false;
	}

	m_localMouse->OneClickEnd();
}

//좌하단 상점 아이콘을 회전시키는 함수
void Shop::RotateIcon()
{
	if (m_rotStatus == false)
	{
		m_rot = m_rot + 0.5;
	}
	else if (m_rotStatus == true)
	{
		m_rot = m_rot - 0.5;
	}

	if (m_rot > 23)
	{
		m_rotStatus = true;
	}
	else if (m_rot < -23)
	{
		m_rotStatus = false;
	}
}

//상점이 활성화되어 있는지를 반환해주는 함수
bool Shop::GetActivated()
{
	return m_isActivated;
}

//초기화..?
void Shop::ResetInfos()
{
	this->m_firstItemUnlocked = false;
	this->m_secondItemUnlocked = false;
	this->m_thirdItemUnlocked = false;
	this->m_fourthItemUnlocked = false;
	this->m_isActivated = false;
}
