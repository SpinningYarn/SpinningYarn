#include <math.h>
#include "../D2DEngine/D2DEngine.h"
#include "NextSceneButton.h"
#include "SceneManager.h"
#include "IScene.h"
#include "DatumPoint.h"
#include "Scene_Average.h"
#include "Scene_Knitting.h"
#include "Scene_Spinning.h"
#include "MouseManager.h"
#include "SpinningGaugBall.h"
#include "StageManager.h"
#include "SoundManager.h"

NextSceneButton::NextSceneButton(const int objectNum, const std::string& objectName, SceneManager* pSceneManager)
	: Object(objectNum, objectName, 1774, 919), m_ButtonSize(128), m_Activate(false), m_SceneIndex(0), m_CenterX(0), m_CenterY(0), m_Distance(0), m_pSceneManager(pSceneManager), m_pDatumPoint(nullptr), m_pSceneKnitting(nullptr), m_pScene_Spinning(nullptr), m_pSpinningGaugBall(nullptr), m_pStageManager(nullptr)
	, m_curStage(0)
{
	this->renderOrder = OBJECT_ORDER;
	m_CenterX = GetPositionX() + (m_ButtonSize / 2);
	m_CenterY = GetPositionY() + (m_ButtonSize / 2);

	m_pStageManager = StageManager::GetInstance();
}

NextSceneButton::~NextSceneButton()
{

}

static bool success = false;
static bool fail = false;
static bool success2 = false;
void NextSceneButton::UpdateObject()
{

	// ���� ���� �ε����� ������
	m_SceneIndex = m_pSceneManager->GetNowScene()->GetSceneIndex();
	// ���� ���������� ���° �������������� �޾ƿ�
	m_curStage = m_pStageManager->GetStageNum();

	/// ���� ������ �Ѿ�� ������ �� �κ�
	/// ����ٰ� ���� ���� ���� Ŭ���� ���� �����Ͻø� �˴ϴ�
	switch (m_SceneIndex)
	{

		case AverageScene:
			m_pScene_Average = (Scene_Average*)m_pSceneManager->GetScene("AverageScene");

			if (m_curStage == 1)
			{
				if (m_pStageManager->isLownessRange(m_pScene_Average->GetAverageWarmth())
					&& m_pStageManager->isMiddleRange(m_pScene_Average->GetAverageDurability())
					&& m_pScene_Average->GetAveragePrice() <= 30
					&& m_pScene_Average->GetSum() == 1
					)
				{
					m_Activate = true;
				}
				else
				{
					m_Activate = false;
				}
			}
			else if (m_curStage == 2)
			{
				if (m_pStageManager->isMiddleRange(m_pScene_Average->GetAverageWarmth())
					&& m_pStageManager->isMiddleRange(m_pScene_Average->GetAverageDurability())
					&& m_pScene_Average->GetAveragePrice() <= 80
					&& m_pScene_Average->GetSum() == 2
					)
				{
					m_Activate = true;
				}
				else
				{
					m_Activate = false;
				}
			}
			else if (m_curStage == 3)
			{
				if (m_pStageManager->isHighRange(m_pScene_Average->GetAverageDurability())
					&& m_pStageManager->isMiddleRange(m_pScene_Average->GetAveragePermeability())
					&& m_pScene_Average->GetAveragePrice() <= 150
					&& m_pScene_Average->GetSum() == 4
					&& m_pScene_Average->isStiff()
					)
				{
					m_Activate = true;
				}
				else
				{
					m_Activate = false;
				}
			}
			else if (m_curStage == 4)
			{
				if (m_pStageManager->isMiddleRange(m_pScene_Average->GetAverageWarmth())
					&& m_pStageManager->isMiddleRange(m_pScene_Average->GetAverageDurability())
					&& m_pStageManager->isMiddleRange(m_pScene_Average->GetAveragePermeability())
					&& m_pScene_Average->GetAveragePrice() <= 250
					&& m_pScene_Average->GetSum() == 4
					&& !m_pScene_Average->isRough()
					)
				{
					m_Activate = true;
				}
				else
				{
					m_Activate = false;
				}
			}
			else if (m_curStage == 5)
			{
				if (m_pStageManager->isHighRange(m_pScene_Average->GetAverageWarmth())
					&& m_pStageManager->isMiddleRange(m_pScene_Average->GetAverageDurability())
					&& m_pScene_Average->GetAveragePrice() <= 350
					&& m_pScene_Average->GetSum() == 5
					&& m_pScene_Average->isSoftness()
					)
				{
					m_Activate = true;
				}
				else
				{
					m_Activate = false;
				}
			}

			//����׿� ���߿� �������
			if (m_pScene_Average->GetAveragePrice() > 1)
			{
				int a = 10;
			}

			break;

			// ������� ��
		case SpinningScene:
			// ���� ������ ����
			m_pScene_Spinning = (Scene_Spinning*)m_pSceneManager->GetScene("SpinningScene");
			m_pSpinningGaugBall = (SpinningGaugBall*)m_pScene_Spinning->GetSceneObject("������ ��");
			m_pStageManager = StageManager::GetInstance();

			if (m_pStageManager->GetSpinningGameState() == false)
			{
				m_Activate = true;

				/// �ϼ���
				if (success == false)
				{
					SoundManager::GetInstance().PlaySounds(Success);
					success = true;
					success2 = false;
					fail = false;
				}

			}
			else
			{
				m_Activate = false;
			}

			break;
			// �߰��� ��

			//success = false;
			//success2 = false;
			//fail = false;
		case KnittingScene:
			m_pDatumPoint = (DatumPoint*)m_pSceneManager->GetScene("KnittingScene")->GetSceneObject("������");
			m_pSceneKnitting = (Scene_Knitting*)m_pSceneManager->GetScene("KnittingScene");

			if ((m_pDatumPoint->GetCount() == m_pSceneKnitting->GetGoal()) &&
				(m_pDatumPoint->GetGoalCount() * 8 - m_pSceneKnitting->GetTotalAnswer()) <= 10)
			{
				m_Activate = true;

				/// �ϼ���
				if (success2 == false)
				{
					SoundManager::GetInstance().PlaySounds(Success);
					success2 = true;
					success = false;
				}
			}
			else if ((m_pDatumPoint->GetCount() == m_pSceneKnitting->GetGoal()) &&
				(m_pDatumPoint->GetGoalCount() * 8 - m_pSceneKnitting->GetTotalAnswer()) > 10)
			{
				m_Activate = false;

				if (fail == false)
				{
					SoundManager::GetInstance().PlaySounds(Fail);
					fail = true;
				}
			}
			else if (m_pDatumPoint->GetCount() < m_pSceneKnitting->GetGoal())
			{
				m_Activate = false;
			}
			break;


		default:
			m_Activate = false;
			break;
	}

	/// ���� ������ �Ѿ����

	static bool Next1 = false;
	static bool Next2 = false;

	if (m_SceneIndex != AverageScene)
	{
		Next1 = false;
		Next2 = false;

		if (m_Activate == true)
		{
			m_Distance = pow(MouseManager::GetInstance()->GetXPos() - m_CenterX, 2) + pow(MouseManager::GetInstance()->GetYPos() - m_CenterY, 2);
		}

		if (m_Activate == true &&
			MouseManager::GetInstance()->GetLeftOneDownClickState() == true &&
			m_Distance <= pow((m_ButtonSize / 2), 2))
		{

			switch (m_SceneIndex)
			{
				case SpinningScene:
					/// <summary>
					/// 
					/// </summary>
					if (Next1 == false)
					{
						SoundManager::GetInstance().PlaySounds(NextScene);
						Next1 = true;
					}

					m_pSceneManager->SetNowScene("KnittingScene");
					break;
				case KnittingScene:
					/// <summary>
					/// 
					/// </summary>

					if (Next2 == false)
					{
						SoundManager::GetInstance().PlaySounds(NextScene);
						Next2 = true;
					}

					m_pSceneManager->SetNowScene("TalkingScene2");
					break;
				default:
					break;
			}
		}
	}
	else if (m_SceneIndex == AverageScene)
	{
		if (m_Activate == true
			&& MouseManager::GetInstance()->GetLeftOneDownClickState() == true
			&& 1521 <= MouseManager::GetInstance()->GetXPos()
			&& 647 <= MouseManager::GetInstance()->GetYPos()
			&& 1649 >= MouseManager::GetInstance()->GetXPos()
			&& 711 >= MouseManager::GetInstance()->GetYPos()
			)
		{
			m_pSceneManager->SetNowScene("SpinningScene");
		}
	}
}

void NextSceneButton::RenderObject()
{
	if (m_Activate == true && m_SceneIndex != AverageScene)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::NextSceneButton, GetPositionX(), GetPositionY());
	}
	else if (m_Activate == false && m_SceneIndex == AverageScene)
	{
		D2DEngine::GetInstance()->DrawSpriteAlpha(eObjectDefine::TOSPINNING, 1521, 647, 0.5f);
	}
	else if (m_Activate == true && m_SceneIndex == AverageScene)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::TOSPINNING, 1521, 647);
	}
}
