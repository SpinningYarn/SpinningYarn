#include "../D2DEngine/D2DEngine.h"
#include "AnswerBoard.h"
#include "SoundManager.h"

AnswerBoard::AnswerBoard(const int objectNum, std::string objectName)
	: Object(objectNum, objectName, 632, 439), m_BoardSize(80), m_Answer{ 0 }, m_AnswerCount(0), m_AnswerGoal(0),
	m_QuesitonActivate(true), m_CountFlag(true), m_WrongFlag(true), m_SkipFlag(true), m_OX(21), m_XdrawFlag{ false, }, m_pNextBoard(nullptr), m_NowCount(0), m_Index(0)
{
	this->renderOrder = OBJECT_ORDER;
}

AnswerBoard::AnswerBoard(const int objectNum, const std::string& objectName, const double posX, const double posY)
	: Object(objectNum, objectName, 632 + posX, 439 + posY), m_BoardSize(80), m_Answer{ 0 }, m_AnswerCount(0), m_AnswerGoal(0),
	m_QuesitonActivate(true), m_CountFlag(true), m_WrongFlag(true), m_SkipFlag(true), m_OX(21), m_XdrawFlag{ false, }, m_pNextBoard(nullptr), m_NowCount(0), m_Index(0)
{
	this->renderOrder = OBJECT_ORDER;
}

AnswerBoard::~AnswerBoard()
{
}

void AnswerBoard::UpdateObject()
{

}

// 7대신 count만큼 반복문 돌면 반복 횟수 줄일 수 있을듯
void AnswerBoard::RenderObject()
{
	// 정답판 그리기
	D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::AnswerBoard, GetPositionX(), GetPositionY());
	// 	for (int i = 0; i < 7; i++)
	// 	{
	// 		if (m_XdrawFlag[i] == true)
	// 		{
	// 			D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::AnswerX, GetPositionX(), GetPositionY() + 80 * ((m_NowCount+1) - i));
	// 		}
	// 	}
}

//static bool knittingX = false;
void AnswerBoard::DrawAnswer(int answer)
{
	if (answer == 1)
	{
		D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::AnswerBoardUP, GetPositionX(), GetPositionY());
	}
	else if (answer == 2)
	{
		D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::AnswerBoardDOWN, GetPositionX(), GetPositionY());
	}
	else if (answer == 3)
	{
		D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::AnswerBoardLEFT, GetPositionX(), GetPositionY());
	}
	else if (answer == 4)
	{
		D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::AnswerBoardRIGHT, GetPositionX(), GetPositionY());
	}

	if (m_OX == 22)
	{
		D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::AnswerO, GetPositionX(), GetPositionY());
	}
	else if (m_OX == 23)
	{
		D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::AnswerX, GetPositionX(), GetPositionY());
// 		if (knittingX == false)
// 		{
// 			SoundManager::GetInstance().PlaySounds(KnittingFail);
// 			knittingX = true;
// 		}
	}
	
}

double AnswerBoard::GetXpos()
{
	//knittingX = false;
	return GetPositionX();
}

void AnswerBoard::SetXpos(double Xposition)
{
	Object::SetPositionX(Xposition);
}

double AnswerBoard::GetXposPlusSize()
{
	double PosPlusSize = GetPositionX() + m_BoardSize;
	return PosPlusSize;
}

void AnswerBoard::SetAnswer(int AnswerBoxNum, int book[7][8])
{
	for (int i = 0; i < 7; i++)
	{
		m_Answer[i] = book[i][AnswerBoxNum];
	}
}

int AnswerBoard::GetAnswerCount()
{
	return m_AnswerCount;
}

void AnswerBoard::PlusAnswerCount()
{
	m_AnswerCount++;
}

void AnswerBoard::SetAnswerGoal(int goal)
{
	m_AnswerGoal = goal;
}

int AnswerBoard::GetAnswerGoal()
{
	return m_AnswerGoal;
}

bool AnswerBoard::GetQuestionActivate()
{
	return m_QuesitonActivate;
}

void AnswerBoard::SetQuestionActivate(bool OX)
{
	m_QuesitonActivate = OX;
}

bool AnswerBoard::GetCountFlag()
{
	return m_CountFlag;
}

void AnswerBoard::SetCountFlag(bool OX)
{
	m_CountFlag = OX;
}

bool AnswerBoard::GetWrongCountFlag()
{
	return m_WrongFlag;
}

void AnswerBoard::SetWrongCountFlag(bool OX)
{
	m_WrongFlag = OX;
}

bool AnswerBoard::GetSkipFlag()
{
	return m_SkipFlag;
}

void AnswerBoard::SetSkipFlag(bool OX)
{
	m_SkipFlag = OX;
}

int AnswerBoard::GetOX()
{
	return m_OX;
}

void AnswerBoard::SetOX(int num)
{
	m_OX = num;
}

bool AnswerBoard::GetXdrawFlag()
{
	return m_XdrawFlag;
}

void AnswerBoard::SetXdrawFlag(int index, bool OX)
{
	m_XdrawFlag[index] = OX;
}

void AnswerBoard::SetNextBoard(AnswerBoard* p_NextBoard)
{
	m_pNextBoard = p_NextBoard;
}

void AnswerBoard::FinishGame()
{
	for (int i = 0; i < 7; i++)
	{
		m_Answer[i] = 0;
		m_XdrawFlag[i] = false;
	}
	m_AnswerCount = 0, m_AnswerGoal = 0, m_QuesitonActivate = true, m_CountFlag = true, m_WrongFlag = true, m_SkipFlag = true, m_OX = 21;
}

AnswerBoard* AnswerBoard::GetNextBoard()
{
	return m_pNextBoard;
}

void AnswerBoard::GetDatumPoint(int NowCount)
{
	m_NowCount = NowCount;
}

int AnswerBoard::GetIndex()
{
	return m_Index;
}

void AnswerBoard::SetIndex(int num)
{
	m_Index = num;
}

