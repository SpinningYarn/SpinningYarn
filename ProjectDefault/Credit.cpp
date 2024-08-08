#include "Credit.h"
#include "../D2DEngine/D2DEngine.h"

#include "KeyManager.h"
#include "StageManager.h"

//static ���� �ʱ�ȭ - ������
int Credit::m_credits = 0;

Credit::Credit(const int objectNum, string objectName)
	:Object(objectNum, objectName),
	m_SrcX(1664), m_SrcY(281), m_DstX(1920), m_DstY(324),
	m_sizeX(256), m_sizeY(64), m_padding(0)
{
	m_pStageManager = StageManager::GetInstance();
	m_credits = m_pStageManager->GetStartPossessedMoney();
}

Credit::Credit(const int objectNum, const string& objectName, const double posX, const double posY)
	:Object(objectNum, objectName, posX, posY),
	m_SrcX(posX), m_SrcY(posY), m_DstX(1920), m_DstY(324),
	m_sizeX(256), m_sizeY(64), m_padding(0)
{
	m_pStageManager = StageManager::GetInstance();
	m_credits = m_pStageManager->GetStartPossessedMoney();
}

Credit::~Credit()
{

}

void Credit::UpdateObject()
{
	// ���� ������ ��� ������Ʈ
	m_credits = m_pStageManager->GetCurPossessedMoney();

	//�ӽ÷� �־�ô� ���ִ� ���� ������ �ٲ���
	if (KeyManager::GetInstance().GetKeyAndState(Key::M) == KeyState::TAP)
	{
		m_pStageManager->IncreaseMoney(2, 500);
		//this->m_credits += 500;
	}

	UpdatePadding();
}

void Credit::RenderObject()
{
	D2DEngine::GetInstance()->DrawSprite(eObjectDefine::CREDIT, m_SrcX, m_SrcY);
	D2DEngine::GetInstance()->DrawTextInt(m_SrcX + (m_sizeX / 2) - 30 + m_padding * 5, m_SrcY + (m_sizeY / 2) - 4, m_credits);
}

//������ �� ��ȯ		//����� Get�Լ�
int Credit::GetCredits()
{
	return this->m_credits;
}

void Credit::AddCredits(int addt)
{
	this->m_credits = m_credits + addt;
}

//�������� �������ִ� �Լ�	//������ ���ų� ���� ������ �߰����ִ� ������ ����
void Credit::SetCredits(int credits)
{
	this->m_credits = credits;
}

//������ �ڸ����� �þ�� �������� ���� ���淡 �����ʿ� �����ַ��� �������
void Credit::UpdatePadding()
{
	m_padding = to_string(m_credits).size() - 1;
}
