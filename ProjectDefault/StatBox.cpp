#include "StatBox.h"
#include "IWool.h"
#include "MouseManager.h"
#include "../D2DEngine/D2DEngine.h"
#include "Scene_Average.h"

/// <summary>
/// 인벤토리의 wool을 클릭시 조합창으로 가져오는 역할을 한다
/// 아이콘, 스탯을 가져오며
/// 그 수량을 조절 할 수 있게 한다
/// 
/// 원레는 기능별로 다 따로 작성되었지만
/// 이 cpp에 기능을 통합 했다.
/// 
/// 김현재 2023.02.10
/// </summary>
/// <param name="objectNum"></param>
/// <param name="objectName"></param>

StatBox::StatBox(const int objectNum, std::string objectName)
	:Object(objectNum, objectName), returnWoolStat(false), targetWarmth(0), targetAbsoptivity(0), targetAeration(0), targetPrice(0), targetQuantity(0)
	, MouseCount(1), returnTestWool(false), m_MouseClickOnce(true)
	, changeBox(false), InactivateButton(false), m_dataIwool(nullptr)
{
	this->renderOrder = OBJECT_ORDER + 1;
	this->renderOrder = 50;
	m_pMouseManager = MouseManager::GetInstance();
	//AverageCount = 1;
}

StatBox::StatBox(const int objectNum, const std::string& objectName, const double posX, const double posY)
	:Object(objectNum, objectName, posX, posY), returnWoolStat(false), targetWarmth(0), targetAbsoptivity(0), targetAeration(0), targetPrice(0), targetQuantity(0)
	, MouseCount(1), returnTestWool(false), m_MouseClickOnce(true), m_dataIwool(nullptr)
	, changeBox(false), InactivateButton(false)
{
	this->renderOrder = OBJECT_ORDER + 1;
	m_pMouseManager = MouseManager::GetInstance();

}

StatBox::~StatBox()
{

}

void StatBox::UpdateObject()
{
	PlusMinus();

	Remover();

	SetEmpty();
}

void StatBox::RenderObject()
{
	//D2DEngine::GetInstance()->DrawRect(529, 403, 559, 433);			// 증가버튼
	//D2DEngine::GetInstance()->DrawRect(470, 403, 500, 433);			// 감소버튼

	D2DEngine::GetInstance()->DrawSprite(eObjectDefine::STATBOX, 283, 163);
	if (returnTestWool == true)
	{
	//	D2DEngine::GetInstance()->DrawRect(283, 163, 411, 291);		// 이미지파일

		D2DEngine::GetInstance()->DrawSprite(eOD, 298,178);
	}

	if (returnTestWool == true && this->targetPrice != 0)
	{
		eObjectDefine newEOD = eObjectDefine::EMPTYEMPTY;

		switch (eOD)
		{
			case eObjectDefine::SPIDERWEB:
			{
				newEOD = eObjectDefine::SPIDERWEB_EMPTY;
				break;
			}
			case eObjectDefine::LAMBSWOOL:
			{
				newEOD = eObjectDefine::LAMBSWOOL_EMPTY;
				break;
			}
			case eObjectDefine::COTTON:
			{
				newEOD = eObjectDefine::COTTON_EMPTY;
				break;
			}
			case eObjectDefine::HEMP:
			{
				newEOD = eObjectDefine::HEMP_EMPTY;
				break;
			}
			case eObjectDefine::ANGORA:
			{
				newEOD = eObjectDefine::ANGORA_EMPTY;
				break;
			}
			case eObjectDefine::CASHMERE:
			{
				newEOD = eObjectDefine::CASHMERE_EMPTY;
				break;
			}

			default:
				break;
		}

		D2DEngine::GetInstance()->DrawSprite(newEOD, 395, 230);
		D2DEngine::GetInstance()->DrawTextInt(370, 314, this->targetWarmth * (MouseCount));
		D2DEngine::GetInstance()->DrawTextInt(370, 348, this->targetAbsoptivity * (MouseCount));
		D2DEngine::GetInstance()->DrawTextInt(370, 381, this->targetAeration * (MouseCount));
		D2DEngine::GetInstance()->DrawTextInt(370, 415, this->targetPrice * (MouseCount));
		D2DEngine::GetInstance()->DrawTextInt(466, 415, this->targetQuantity * (MouseCount));
		// 오브젝트의 수치값
	}
}


/// <summary>
/// 증감버튼이다
/// 특정조건(수량의 합이 10이되면)
/// 증가버튼을 비활성화 시키고 감소버튼만 누를수 있게 된다
/// </summary>
void StatBox::PlusMinus()
{
	if (InactivateButton == false)
	{
		// 특정 버튼을 누르면 울의 수치가 증가한다
		if (m_pMouseManager->GetLeftButtonDownState() == true
			&& m_MouseClickOnce == true
			&& 529 <= m_pMouseManager->GetXPos()
			&& 403 <= m_pMouseManager->GetYPos()
			&& 559 >= m_pMouseManager->GetXPos()
			&& 433 >= m_pMouseManager->GetYPos())
		{

			m_MouseClickOnce = false;
		}
		if (m_pMouseManager->GetLeftButtonUpState() == true
			&& m_MouseClickOnce == false
			&& 529 <= m_pMouseManager->GetXPos()
			&& 403 <= m_pMouseManager->GetYPos()
			&& 559 >= m_pMouseManager->GetXPos()
			&& 433 >= m_pMouseManager->GetYPos())
		{
			MouseCount++;
			m_MouseClickOnce = true;
		}

	}
	// 특정 버튼을 누르면 울의 수치가 감소한다
	if (m_pMouseManager->GetLeftButtonDownState() == true
		&& m_MouseClickOnce == true
		&& 470 <= m_pMouseManager->GetXPos()
		&& 403 <= m_pMouseManager->GetYPos()
		&& 500 >= m_pMouseManager->GetXPos()
		&& 433 >= m_pMouseManager->GetYPos())
	{
		m_MouseClickOnce = false;
	}

	if (m_pMouseManager->GetLeftButtonUpState() == true
		&& m_MouseClickOnce == false
		&& 470 <= m_pMouseManager->GetXPos()
		&& 403 <= m_pMouseManager->GetYPos()
		&& 500 >= m_pMouseManager->GetXPos()
		&& 433 >= m_pMouseManager->GetYPos())
	{
		MouseCount--;
		m_MouseClickOnce = true;
	}

}

void StatBox::UpdateStat(IWool* targetWool)
{
	if (targetWool == nullptr)
	{
		EmptyStatBox();
		return;
	}

	this->targetWarmth = targetWool->m_Warmth;
	this->targetAbsoptivity = targetWool->m_Durability;
	this->targetAeration = targetWool->m_Aeration;
	this->targetPrice = targetWool->m_Price;
	this->targetQuantity = targetWool->m_Quantity;

	eOD = targetWool->GetObjectDefine();
	
	m_spcAbil1 = targetWool->m_abil1;
	m_spcAbil2 = targetWool->m_abil2;
}

void StatBox::EmptyStatBox()
{
// 	if (returnTestWool == true
// 		&& m_pMouseManager->GetRightButtonDownState() == true
// 		&& 283 <= m_pMouseManager->GetXPos()
// 		&& 163 <= m_pMouseManager->GetYPos()
// 		&& 411 >= m_pMouseManager->GetXPos()
// 		&& 291 >= m_pMouseManager->GetYPos())
	{
		UnDo();

		this->targetWarmth = 0;
		this->targetAbsoptivity = 0;
		this->targetAeration = 0;
		this->targetPrice = 0;
		this->targetQuantity = 0;
	}
}

void StatBox::SetEmpty()
{
	if (this->targetWarmth + this->targetAbsoptivity + this->targetAeration + this->targetPrice + this->targetQuantity > 0)
	{
		this->returnTestWool = true;
	}
	else
	{
		this->returnTestWool = false;
	}
}

//미안 true일때 뭔가 들어있는거다 하지만 이제와서 바꾸기엔 좀 늦었다
bool StatBox::IsEmpty()
{
	if (this->targetWarmth + this->targetAbsoptivity + this->targetAeration + this->targetPrice + this->targetQuantity > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void StatBox::Remover()
{
	if (m_pMouseManager->GetRightButtonDownState() == true
		&& m_MouseClickOnce == true
		&& 283 <= m_pMouseManager->GetXPos()
		&& 163 <= m_pMouseManager->GetYPos()
		&& 411 >= m_pMouseManager->GetXPos()
		&& 291 >= m_pMouseManager->GetYPos())
	{
		m_MouseClickOnce = false;
	}

	if (m_pMouseManager->GetRightButtonDownState() == true
		&& m_MouseClickOnce == false
		&& returnTestWool == true
		&& 283 <= m_pMouseManager->GetXPos()
		&& 163 <= m_pMouseManager->GetYPos()
		&& 411 >= m_pMouseManager->GetXPos()
		&& 291 >= m_pMouseManager->GetYPos())
	{
		EmptyStatBox();
		m_MouseClickOnce = true;
	}
}

/// <summary>
/// 지금 StatBox에 오브젝트가 들어 있을때 
/// 우클릭(위에 update에 조건문 들어가 있음)으로 아이콘을 클릭하면 
/// 그림과 스탯을 지운다.
/// </summary>
void StatBox::UnDo()
{
	// false이면 출력하는것을 지운다
	returnTestWool = false;
	changeBox = false;

	MouseCount = 1;
}









