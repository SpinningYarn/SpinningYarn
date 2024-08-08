#pragma once
#include "D2DDefine.h"

class D2DSprite : public DRSprite
{
public:
	D2DSprite();
	D2DSprite(int spriteSheetIndex, int oriX, int oriY, int index, int width, int height, int keyColor,
		int centerPosX, int centerPosY, int delayFrame, const RECT& collision1, const RECT& collision2, int damage);
	virtual ~D2DSprite();


public:
	// ��������Ʈ ��Ʈ�� �ε���
	int m_SheetIndex;

	// ���������� ��ġ
	int m_OriX;
	int m_OriY;
};

