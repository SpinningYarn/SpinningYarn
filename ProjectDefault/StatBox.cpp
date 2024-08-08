#include "StatBox.h"
#include "IWool.h"
#include "MouseManager.h"
#include "../D2DEngine/D2DEngine.h"
#include "Scene_Average.h"

/// <summary>
/// �κ��丮�� wool�� Ŭ���� ����â���� �������� ������ �Ѵ�
/// ������, ������ ��������
/// �� ������ ���� �� �� �ְ� �Ѵ�
/// 
/// ������ ��ɺ��� �� ���� �ۼ��Ǿ�����
/// �� cpp�� ����� ���� �ߴ�.
/// 
/// ������ 2023.02.10
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
	//D2DEngine::GetInstance()->DrawRect(529, 403, 559, 433);			// ������ư
	//D2DEngine::GetInstance()->DrawRect(470, 403, 500, 433);			// ���ҹ�ư

	D2DEngine::GetInstance()->DrawSprite(eObjectDefine::STATBOX, 283, 163);
	if (returnTestWool == true)
	{
	//	D2DEngine::GetInstance()->DrawRect(283, 163, 411, 291);		// �̹�������

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
		// ������Ʈ�� ��ġ��
	}
}


/// <summary>
/// ������ư�̴�
/// Ư������(������ ���� 10�̵Ǹ�)
/// ������ư�� ��Ȱ��ȭ ��Ű�� ���ҹ�ư�� ������ �ְ� �ȴ�
/// </summary>
void StatBox::PlusMinus()
{
	if (InactivateButton == false)
	{
		// Ư�� ��ư�� ������ ���� ��ġ�� �����Ѵ�
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
	// Ư�� ��ư�� ������ ���� ��ġ�� �����Ѵ�
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

//�̾� true�϶� ���� ����ִ°Ŵ� ������ �����ͼ� �ٲٱ⿣ �� �ʾ���
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
/// ���� StatBox�� ������Ʈ�� ��� ������ 
/// ��Ŭ��(���� update�� ���ǹ� �� ����)���� �������� Ŭ���ϸ� 
/// �׸��� ������ �����.
/// </summary>
void StatBox::UnDo()
{
	// false�̸� ����ϴ°��� �����
	returnTestWool = false;
	changeBox = false;

	MouseCount = 1;
}









