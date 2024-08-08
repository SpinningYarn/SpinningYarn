#include "../D2DEngine/D2DEngine.h"
#include "DrawBoard.h"
#include "AnswerBoard.h"
#include "DatumPoint.h"

DrawBoard::DrawBoard(const int objectNum, std::string objectName)
	: Object(objectNum, objectName)
{
	this->renderOrder = KNITTING_ORDER;
}

DrawBoard::DrawBoard(const int objectNum, const std::string& objectName, const double posX, const double posY)
	: Object(objectNum, objectName, posX, posY)
{
	this->renderOrder = KNITTING_ORDER;
}

DrawBoard::~DrawBoard()
{

}

void DrawBoard::UpdateObject()
{

}

void DrawBoard::RenderObject()
{

	for (int i = 0; i < 8; i++)
	{
		if (m_FlagArray[0][i].xFlag == true)
		{

			D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::AnswerX, m_FlagArray[0][i].Xpos, m_FlagArray[0][i].Ypos + (80 * (m_pDatum->GetCount())));
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (m_FlagArray[1][i].xFlag == true)
		{
			D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::AnswerX, m_FlagArray[1][i].Xpos, m_FlagArray[1][i].Ypos + (80 * (m_pDatum->GetCount() - 1)));
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (m_FlagArray[2][i].xFlag == true)
		{
			D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::AnswerX, m_FlagArray[2][i].Xpos, m_FlagArray[2][i].Ypos + (80 * (m_pDatum->GetCount() - 2)));
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (m_FlagArray[3][i].xFlag == true)
		{
			D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::AnswerX, m_FlagArray[3][i].Xpos, m_FlagArray[3][i].Ypos + (80 * (m_pDatum->GetCount() - 3)));
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (m_FlagArray[4][i].xFlag == true)
		{
			D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::AnswerX, m_FlagArray[4][i].Xpos, m_FlagArray[4][i].Ypos + (80 * (m_pDatum->GetCount() - 4)));
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (m_FlagArray[5][i].xFlag == true)
		{
			D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::AnswerX, m_FlagArray[5][i].Xpos, m_FlagArray[5][i].Ypos + (80 * (m_pDatum->GetCount() - 5)));
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (m_FlagArray[6][i].xFlag == true)
		{
			D2DEngine::D2DEngine::GetInstance()->DrawSprite(eObjectDefine::AnswerX, m_FlagArray[6][i].Xpos, m_FlagArray[6][i].Ypos + (80 * (m_pDatum->GetCount() - 6)));
		}
	}
}

void DrawBoard::Initialize(AnswerBoard* m_pFirstBoard, DatumPoint* p_Datum)
{
	m_PBoard1st = m_pFirstBoard;
	m_pBoard2nd = m_PBoard1st->GetNextBoard();
	m_pBoard3rd = m_pBoard2nd->GetNextBoard();
	m_pBoard4th = m_pBoard3rd->GetNextBoard();
	m_pBoard5th = m_pBoard4th->GetNextBoard();
	m_pBoard6th = m_pBoard5th->GetNextBoard();
	m_pBoard7th = m_pBoard6th->GetNextBoard();
	m_pBoard8th = m_pBoard7th->GetNextBoard();
	m_pDatum = p_Datum;

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_FlagArray[i][j].xFlag = false;
			m_FlagArray[i][j].Xpos = 0;
			m_FlagArray[i][j].Ypos = 0;
		}
	}

}

void DrawBoard::SetXflagArray(int count)
{
	for (int i = 0; i < 8; i++)
	{
		m_FlagArray[count][i].xFlag = false;
	}
}

void DrawBoard::InitializeFlagArray(int count, int index, bool OX, int Xposition, int Yposition)
{
	m_FlagArray[count][index].xFlag = OX;
	m_FlagArray[count][index].Xpos = Xposition;
	m_FlagArray[count][index].Ypos = Yposition;
}

void DrawBoard::MoveXflagPos(double move)
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_FlagArray[i][j].Xpos += move;
		}
	}
}

void DrawBoard::OriginXflagPos()
{
	for (int i = 0; i < 7; i++)
	{
		m_FlagArray[i][0].Xpos = 632;
	}
	for (int i = 0; i < 7; i++)
	{
		m_FlagArray[i][1].Xpos = 712;
	}
	for (int i = 0; i < 7; i++)
	{
		m_FlagArray[i][2].Xpos = 792;
	}
	for (int i = 0; i < 7; i++)
	{
		m_FlagArray[i][3].Xpos = 872;
	}
	for (int i = 0; i < 7; i++)
	{
		m_FlagArray[i][4].Xpos = 952;
	}
	for (int i = 0; i < 7; i++)
	{
		m_FlagArray[i][5].Xpos = 1032;
	}
	for (int i = 0; i < 7; i++)
	{
		m_FlagArray[i][6].Xpos = 1112;
	}
	for (int i = 0; i < 7; i++)
	{
		m_FlagArray[i][7].Xpos = 1192;
	}
}
