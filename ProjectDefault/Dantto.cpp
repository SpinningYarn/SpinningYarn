#include "../D2DEngine/D2DEngine.h"
#include "../D2DEngine/Animator.h"
#include "Dantto.h"
#include "TimerManager.h"
#include "Needle.h"
#include "AnswerBoard.h"
#include "DatumPoint.h"
#include "ResultProduct.h"
#include "MouseManager.h"
#include "DrawBoard.h"
#include "StageManager.h"
#include "SoundManager.h"
#include "KeyManager.h"

Animator* DanttoEnter = new Animator();
Animator* DanttoAttack = new Animator();
Animator* DanttoSightAttack1 = new Animator();
Animator* DanttoSightAttack2 = new Animator();
Animator* DanttoSightAttack3 = new Animator();
Animator* DanttoSightAttack4 = new Animator();


Dantto::Dantto(const int objectNum, std::string objectName)
	:Object(objectNum, objectName, 1250, 280), m_1stScene(false), m_WarningFlag(false), m_AttackFlag(false), m_Timer(0), m_AttackTimer(0), m_AttackMove(0), m_MoveLeft(true), m_MoveStop(false), m_pNeedle(nullptr), m_pDatum(nullptr), m_pResult(nullptr), m_pDrawBaord(nullptr),
	m_pBoard1(nullptr), m_pBoard2(nullptr), m_pBoard3(nullptr), m_pBoard4(nullptr), m_pBoard5(nullptr), m_pBoard6(nullptr), m_pBoard7(nullptr), m_pBoard8(nullptr), m_MoveCount(0), m_MoveDistance(0), m_ClickMiss(false), m_MoveSize(0), m_PrevMove(0), m_Size(700), m_PlayAnimation(false), m_MoveSpeed(0), m_Enter(false), m_EnterTimer(0),
	m_AttackX(GetPositionX()), m_Attack1Enterflag(false), m_Attack2Enterflag(false), m_Attack3Enterflag(false), m_Attack4Enterflag(false), m_OutTimer(0), m_FinalTimer(0), m_Attack2Flag(false), m_StandOndraw(true), m_Rcount(0)
{
	this->renderOrder = CAT_ORDER+100;
	for (int i = 0; i < 7; i++)
	{
		DanttoEnter->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 700 * i, 0, 700, 700, 1));
	}
	for (int i = 0; i < 100; i++)
	{
		DanttoEnter->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 700 * 6, 0, 700, 700, 1));
	}
	


	DanttoAttack->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 4900, 0, 700, 700, 1));
	DanttoAttack->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 5600, 0, 700, 700, 1));
	DanttoAttack->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 4900, 0, 700, 700, 1));

	DanttoSightAttack1->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 3500, 0, 700, 700, 1));
	DanttoSightAttack1->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 2800, 0, 700, 700, 1));
	DanttoSightAttack1->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 3500, 0, 700, 700, 1));

	for (int i = 0; i < 3; i++)
	{
		DanttoSightAttack2->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_OUT, 700 * i, 0, 700, 700, 1));
	}

	DanttoSightAttack3->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_OUT, 700 * 3, 0, 700, 700, 1));
	DanttoSightAttack3->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_OUT, 700 * 2, 0, 700, 700, 1));
	DanttoSightAttack3->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_OUT, 700 * 3, 0, 700, 700, 1));

	DanttoSightAttack4->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_OUT, 700 * 4, 0, 700, 700, 1));
	DanttoSightAttack4->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_OUT, 700 * 5, 0, 700, 700, 1));
	DanttoSightAttack4->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_OUT, 700 * 6, 0, 700, 700, 1));
	DanttoSightAttack4->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_OUT, 700 * 7, 0, 700, 700, 1));
	DanttoSightAttack4->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_OUT, 700 * 8, 0, 700, 700, 1));

	DanttoSightAttack4->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 700 * 0, 0, 700, 700, 1));
	DanttoSightAttack4->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 700 * 1, 0, 700, 700, 1));
	DanttoSightAttack4->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 700 * 2, 0, 700, 700, 1));
	DanttoSightAttack4->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 700 * 3, 0, 700, 700, 1));
	DanttoSightAttack4->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 700 * 4, 0, 700, 700, 1));
	DanttoSightAttack4->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 700 * 5, 0, 700, 700, 1));
	DanttoSightAttack4->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 700 * 6, 0, 700, 700, 1));
	DanttoSightAttack4->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 700 * 6, 0, 700, 700, 1));
	DanttoSightAttack4->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 700 * 6, 0, 700, 700, 1));
	DanttoSightAttack4->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 700 * 6, 0, 700, 700, 1));
}

Dantto::Dantto(const int objectNum, const string& objectName, const double posX, const double posY)
	:Object(objectNum, objectName, posX, posY), m_1stScene(false), m_WarningFlag(false), m_AttackFlag(false), m_Timer(0), m_AttackTimer(0), m_AttackMove(0), m_MoveLeft(false), m_MoveStop(true), m_pNeedle(nullptr), m_pDatum(nullptr), m_pResult(nullptr), m_pDrawBaord(nullptr),
	m_pBoard1(nullptr), m_pBoard2(nullptr), m_pBoard3(nullptr), m_pBoard4(nullptr), m_pBoard5(nullptr), m_pBoard6(nullptr), m_pBoard7(nullptr), m_pBoard8(nullptr), m_MoveCount(0), m_MoveDistance(0), m_ClickMiss(false), m_MoveSize(0), m_PrevMove(0), m_Size(700), m_PlayAnimation(true), m_MoveSpeed(0), m_EnterTimer(0), m_Rcount(0)
{
	this->renderOrder = CAT_ORDER;
	for (int i = 0; i < 7; i++)
	{
		DanttoEnter->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 700 * i, 0, 700, 700, 1));
	}
	for (int i = 0; i < 100; i++)
	{
		DanttoEnter->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 700 * 6, 0, 700, 700, 1));
	}

	DanttoAttack->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 4900, 0, 700, 700, 1));
	DanttoAttack->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 5600, 0, 700, 700, 1));
	DanttoAttack->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 4900, 0, 700, 700, 1));

	DanttoSightAttack1->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 3500, 0, 700, 700, 1));
	DanttoSightAttack1->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 2800, 0, 700, 700, 1));
	DanttoSightAttack1->animationList.push_back(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::CAT_HIT, 3500, 0, 700, 700, 1));
}

Dantto::~Dantto()
{
	DanttoAttack->ClearAnimation();
	delete DanttoAttack;
}
static bool catReady = false;
void Dantto::UpdateObject()
{
	if (m_pDatum->GetCount() == m_pDatum->GetGoalCount())
	{
		m_WarningFlag = false;
		m_AttackFlag = false;
		m_Timer = 0;
	}

	if (m_pDatum->GetCount() < m_pDatum->GetGoalCount())
	{
		if (m_AttackFlag == false && m_pDatum->GetCount() < m_pDatum->GetGoalCount() && m_pDatum->GetStartFlag() == true)									// ���� ���Ҷ� ����~
		{
			m_Timer += TimerManager::GetInstance().GetDeltaTime();	// ���� ����
		}

		Warning();

		if (m_AttackFlag == true || m_ClickMiss == true)
		{
			m_PlayAnimation = true;
			Attack();
		}
	}

	if (m_Enter == false)
	{
		m_EnterTimer += TimerManager::GetInstance().GetDeltaTime();

		if (m_EnterTimer >= ENTERTIME)
		{
			m_Enter = true;
		}
	}

	if (KeyManager::GetInstance().GetKnittingKey() == 6 && m_Attack2Flag == false && m_pDatum->GetStartFlag() == true)
	{
		m_Rcount++;
		if (m_Rcount == 3)
		{
			m_Attack2Flag = true;
			m_StandOndraw = false;
		}
	}

	Attack2();
}

void Dantto::RenderObject()
{

}

void Dantto::RenderDantto()
{
	/// ����� �Դٰ��� �ϴ� ����
	if (m_Attack2Flag == true && m_pDatum->GetCount() < m_pDatum->GetGoalCount())
	{
		if (m_Attack1Enterflag == false)
		{
			DanttoSightAttack1->PlayAnimation(m_AttackX, this->GetPositionY(), 0.4, 15);
		}

		if (m_Attack1Enterflag == true && m_Attack2Enterflag == false)
		{
			DanttoSightAttack2->PlayAnimation(m_AttackX, this->GetPositionY(), 5, 25);
		}

		if (m_Attack1Enterflag == true && m_Attack2Enterflag == true && m_Attack3Enterflag == false)
		{
			DanttoSightAttack3->PlayAnimation(m_AttackX, this->GetPositionY(), 0.4, 15);
		}

		if (m_Attack1Enterflag == true && m_Attack2Enterflag == true && m_Attack3Enterflag == true && m_Attack4Enterflag == false)
		{
			DanttoSightAttack4->PlayAnimation(this->GetPositionX(), this->GetPositionY(), 5, 25);
		}
	}

	/// �⺻
	if (m_StandOndraw == true)
	{
		if (m_Enter == false)
		{
			DanttoEnter->PlayAnimation(this->GetPositionX(), this->GetPositionY(), 3, 25);
		}

		if (m_WarningFlag == false && m_AttackFlag == false && m_Enter == true)		// �⺻
		{
			D2DEngine::GetInstance()->DrawSprite(eObjectDefine::Cat_Stand, GetPositionX(), GetPositionY());
		}
		if (m_WarningFlag == true && m_AttackFlag == false && m_Enter == true)		// ���� ����
		{
			D2DEngine::GetInstance()->DrawSprite(eObjectDefine::Cat_Wait, GetPositionX(), GetPositionY());
		}

		if (m_PlayAnimation == true && m_Enter == true)								// ���� �� �ִϸ��̼�
		{
			DanttoAttack->PlayAnimation(this->GetPositionX(), this->GetPositionY(), 0.4, 15);
		}
	}
}

/// ���� �������� �Ѿ�� ���� �ʱ�ȭ �ؾ��� �͵� �־������
void Dantto::Initialize(Needle* p_Needle, AnswerBoard* p_Board, DatumPoint* p_Datum, ResultProduct* P_Result, DrawBoard* p_DrawBoard)
{
	m_1stScene = false;
	m_WarningFlag = false, m_AttackFlag = false, m_Timer = 0, m_AttackTimer = 0,
	m_AttackMove = 0, m_MoveLeft = true, m_MoveStop = false, m_MoveSize = 0,
	m_MoveCount = 0, m_MoveDistance = 0, m_ClickMiss = false;
	m_MoveSpeed = MOVESPEED + MOVESPEED * ((INCREASE_PERCENT * (StageManager::GetInstance()->GetStageNum() - 1) * 0.01));
	m_pNeedle = p_Needle;
	m_pDatum = p_Datum;
	m_pResult = P_Result;
	m_pBoard1 = p_Board;
	m_pBoard2 = m_pBoard1->GetNextBoard();
	m_pBoard3 = m_pBoard2->GetNextBoard();
	m_pBoard4 = m_pBoard3->GetNextBoard();
	m_pBoard5 = m_pBoard4->GetNextBoard();
	m_pBoard6 = m_pBoard5->GetNextBoard();
	m_pBoard7 = m_pBoard6->GetNextBoard();
	m_pBoard8 = m_pBoard7->GetNextBoard();
	m_pDrawBaord = p_DrawBoard;
	m_PlayAnimation = false;
	m_Enter = false;
	m_EnterTimer = 0;
	m_AttackX = GetPositionX();
	m_Attack1Enterflag = false;
	m_Attack2Enterflag = false;
	m_Attack3Enterflag = false;
	m_Attack4Enterflag = false;
	m_OutTimer = 0;
	m_FinalTimer = 0;
	m_Attack2Flag = false;
	m_Rcount = 0;
	m_PrevMove = 0;
	m_Size = 0;
	m_StandOndraw = true;
}

bool Dantto::GetWarningFlag()
{
	return m_WarningFlag;
}

void Dantto::SetWarningFlag(bool OX)
{
	
	m_WarningFlag = OX;
}

bool Dantto::GetAttackFlag()
{

	return m_AttackFlag;
}

void Dantto::SetAttackFlag(bool OX)
{
	m_AttackFlag = OX;
	
}


void Dantto::Warning()
{
	static bool catClick = false;


	if (m_Timer >= WARNING && m_AttackFlag == false)	// 2���� �������� + ���콺Ŭ�� ���� �������� ������, ���콺�������� true ����
	{
		m_WarningFlag = true;
	}

	if (m_WarningFlag == true)
	{
		/// ����� ���� ���� �Ҹ�
		if (catReady == false)
		{
			SoundManager::GetInstance().PlaySounds(Nyangko1);
			catReady = true;
		}
	}

	if (m_Timer >= ATTACK && m_WarningFlag == true && m_pDatum->GetWaitState() == false)	// 15�� ������ ���������� ������ true�� ���� �ߵ�
	{
		
		m_MoveStop = false;
		m_AttackFlag = true;
		m_WarningFlag = false;
	}
	/// ����� �׸��� ��ǥ �־���� �� �ӽ÷� �簢�� ��ǥ �־���
	if (m_WarningFlag == true &&
		MouseManager::GetInstance()->GetLeftOneDownClickState() == true &&
		MouseManager::GetInstance()->GetXPos() >= 1350 &&
		MouseManager::GetInstance()->GetXPos() <= 1745 &&
		MouseManager::GetInstance()->GetYPos() >= 390 &&
		MouseManager::GetInstance()->GetYPos() <= 915
		)
	{
		/// <summary>
		/// ����� ���� �������� �� �Ҹ�
		/// </summary>

		if (catClick == false)
		{
			SoundManager::GetInstance().PlaySounds(NyangkoClick);
			catClick = true;
			catReady = false;
		}


		m_WarningFlag = false;		// ��� false
		m_Timer = 0;				// Ÿ�̸� 0���� ����
	}
	/// ��Ÿ�� ��� �����ؼ� �߸� ������ ������ ���� ����
	else if (m_ClickMiss == false &&
		m_WarningFlag == false &&
		MouseManager::GetInstance()->GetLeftOneDownClickState() == true &&
		MouseManager::GetInstance()->GetXPos() >= 1350 &&
		MouseManager::GetInstance()->GetXPos() <= 1745 &&
		MouseManager::GetInstance()->GetYPos() >= 390 &&
		MouseManager::GetInstance()->GetYPos() <= 915 &&
		m_pDatum->GetStartFlag() == true
		)
	{
		m_ClickMiss = true;
		m_MoveStop = false;
		m_AttackFlag = true;
	}


	catClick = false;
}

void Dantto::Attack()
{
	
	static bool catPunch = false;
	{
		if (m_AttackFlag == true)
		{
			/// ����� ���� ������
			if (catPunch == false)
			{
				SoundManager::GetInstance().PlaySounds(NyangkoPunch1);
				catPunch = true;
				catReady = false;
			}
		}
		m_MoveSize = MOVESIZE * (1 - (m_MoveCount / (MOVEGOAL + 1)));

		/// ù �������� ������
		if (m_AttackFlag == true && m_MoveLeft == true && m_MoveStop == false && (int)m_MoveCount == 0)
		{
			m_AttackMove = -m_MoveSpeed * TimerManager::GetInstance().GetDeltaTime();
			m_MoveDistance += m_AttackMove;

			m_pNeedle->MoveNeedleX(m_AttackMove);	// �ٴ� �����̱�
			m_pDatum->SetDatumX(m_AttackMove);		// ������ �����̱�
			m_pResult->SetPositionX(m_AttackMove);	// �ϼ�ǰ �����̱�
			m_pBoard1->SetPositionX(m_AttackMove);	// ������ �����̱�
			m_pBoard2->SetPositionX(m_AttackMove);
			m_pBoard3->SetPositionX(m_AttackMove);
			m_pBoard4->SetPositionX(m_AttackMove);
			m_pBoard5->SetPositionX(m_AttackMove);
			m_pBoard6->SetPositionX(m_AttackMove);
			m_pBoard7->SetPositionX(m_AttackMove);
			m_pBoard8->SetPositionX(m_AttackMove);
			m_pDrawBaord->MoveXflagPos(m_AttackMove);

			// �������� �� �̵��� ���
			if (m_MoveDistance <= -m_MoveSize)
			{
				m_PrevMove = m_MoveDistance;
				if (m_PrevMove < 0)
				{
					m_PrevMove *= -1;
				}
				m_MoveDistance = 0;
				m_MoveLeft = false;
				m_MoveCount++;
			}
		}

		/// ���� �� -> ������ ��
		else if (m_AttackFlag == true && m_MoveLeft == false && m_MoveStop == false && (int)m_MoveCount % 2 == 1 && m_MoveCount < MOVEGOAL)
		{
			m_AttackMove = m_MoveSpeed * TimerManager::GetInstance().GetDeltaTime();
			m_MoveDistance += m_AttackMove;

			m_pNeedle->MoveNeedleX(m_AttackMove);	// �ٴ� �����̱�
			m_pDatum->SetDatumX(m_AttackMove);		// ������ �����̱�
			m_pResult->SetPositionX(m_AttackMove);	// �ϼ�ǰ �����̱�
			m_pBoard1->SetPositionX(m_AttackMove);	// ������ �����̱�
			m_pBoard2->SetPositionX(m_AttackMove);
			m_pBoard3->SetPositionX(m_AttackMove);
			m_pBoard4->SetPositionX(m_AttackMove);
			m_pBoard5->SetPositionX(m_AttackMove);
			m_pBoard6->SetPositionX(m_AttackMove);
			m_pBoard7->SetPositionX(m_AttackMove);
			m_pBoard8->SetPositionX(m_AttackMove);
			m_pDrawBaord->MoveXflagPos(m_AttackMove);

			// ���������� �� �̵��� ���
			if (m_MoveDistance >= m_PrevMove + m_MoveSize)
			{
				m_PrevMove = m_MoveDistance - m_PrevMove;
				m_MoveDistance = 0;
				m_MoveLeft = true;
				m_MoveCount++;
			}
		}

		/// ������ �� -> ���� ��
		else if (m_AttackFlag == true && m_MoveLeft == true && m_MoveStop == false && (int)m_MoveCount % 2 == 0 && m_MoveCount < MOVEGOAL)
		{
			m_AttackMove = -m_MoveSpeed * TimerManager::GetInstance().GetDeltaTime();
			m_MoveDistance += m_AttackMove;

			m_pNeedle->MoveNeedleX(m_AttackMove);	// �ٴ� �����̱�
			m_pDatum->SetDatumX(m_AttackMove);		// ������ �����̱�
			m_pResult->SetPositionX(m_AttackMove);	// �ϼ�ǰ �����̱�
			m_pBoard1->SetPositionX(m_AttackMove);	// ������ �����̱�
			m_pBoard2->SetPositionX(m_AttackMove);
			m_pBoard3->SetPositionX(m_AttackMove);
			m_pBoard4->SetPositionX(m_AttackMove);
			m_pBoard5->SetPositionX(m_AttackMove);
			m_pBoard6->SetPositionX(m_AttackMove);
			m_pBoard7->SetPositionX(m_AttackMove);
			m_pBoard8->SetPositionX(m_AttackMove);
			m_pDrawBaord->MoveXflagPos(m_AttackMove);


			// �������� �� �̵��� ���
			if (m_MoveDistance <= -(m_PrevMove + m_MoveSize))
			{
				m_PrevMove = m_MoveDistance + m_PrevMove;
				if (m_PrevMove < 0)
				{
					m_PrevMove *= -1;
				}
				m_MoveDistance = 0;
				m_MoveLeft = false;
				m_MoveCount++;
			}
		}

		/// ������ �� -> ����
		else if (m_AttackFlag == true && m_MoveLeft == true && m_MoveStop == false && m_MoveCount == MOVEGOAL)
		{
			m_AttackMove = -m_MoveSpeed * TimerManager::GetInstance().GetDeltaTime();
			m_MoveDistance += m_AttackMove;

			m_pNeedle->MoveNeedleX(m_AttackMove);	// �ٴ� �����̱�
			m_pDatum->SetDatumX(m_AttackMove);		// ������ �����̱�
			m_pResult->SetPositionX(m_AttackMove);	// �ϼ�ǰ �����̱�
			m_pBoard1->SetPositionX(m_AttackMove);	// ������ �����̱�
			m_pBoard2->SetPositionX(m_AttackMove);
			m_pBoard3->SetPositionX(m_AttackMove);
			m_pBoard4->SetPositionX(m_AttackMove);
			m_pBoard5->SetPositionX(m_AttackMove);
			m_pBoard6->SetPositionX(m_AttackMove);
			m_pBoard7->SetPositionX(m_AttackMove);
			m_pBoard8->SetPositionX(m_AttackMove);
			m_pDrawBaord->MoveXflagPos(m_AttackMove);



			// ���� ������ �����̰� ���� ������ ���
			if (m_MoveDistance <= -m_PrevMove)
			{
				m_MoveDistance = 0;
				m_MoveCount = 0;
				m_MoveStop = true;
				m_MoveLeft = true;
				m_AttackFlag = false;
				m_ClickMiss = false;
				m_Timer = 0;
				m_AttackMove = 0;
				m_MoveDistance = 0;

				m_pNeedle->SetOriginX();
				m_pResult->SetOriginX(632);
				m_pBoard1->SetOriginX(632);
				m_pBoard2->SetOriginX(712);
				m_pBoard3->SetOriginX(792);
				m_pBoard4->SetOriginX(872);
				m_pBoard5->SetOriginX(952);
				m_pBoard6->SetOriginX(1032);
				m_pBoard7->SetOriginX(1112);
				m_pBoard8->SetOriginX(1192);
				m_pDrawBaord->OriginXflagPos();
				m_PlayAnimation = false;


				catPunch = false;
			}
		}
	}

}

void Dantto::Attack2()
{
	if (m_Attack2Flag == true && m_StandOndraw == false && m_pDatum->GetStartFlag() == true)
	{
		if (m_AttackX >= 400 && m_Attack1Enterflag == false)
		{
			m_AttackX -= 10;
		}
		if (m_AttackX < 400)
		{
			m_Attack1Enterflag = true;
		}
		if (m_Attack1Enterflag == true && m_Attack2Enterflag == false)
		{
			m_OutTimer += TimerManager::GetInstance().GetDeltaTime();
		}
		if (m_OutTimer >= 1)
		{
			m_Attack2Enterflag = true;
		}
		if (m_Attack2Enterflag == true && m_AttackX < GetPositionX())
		{
			m_AttackX += 10;
		}
		if (m_AttackX == GetPositionX())
		{
			m_Attack3Enterflag = true;
		}
		if (m_Attack1Enterflag == true && m_Attack2Enterflag == true &&
			m_Attack3Enterflag == true && m_Attack4Enterflag == false)
		{
			m_FinalTimer += TimerManager::GetInstance().GetDeltaTime();
		}
		if (m_FinalTimer >= 5)
		{
			m_Attack4Enterflag = true;
			m_StandOndraw = true;
		}
	}
}

bool Dantto::GetEnterFlag()
{
	return m_Enter;
}
