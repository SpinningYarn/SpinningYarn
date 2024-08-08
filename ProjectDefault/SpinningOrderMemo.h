#pragma once
#include "Object.h"

class StageManager;

/// <summary>
/// 방적 작업 시작부터 끝날때까지 보여주는 메모장 (배경보다 레이어 높음)
/// 
/// 2022.02.20
/// </summary>
class SpinningOrderMemo : public Object
{
public:
	SpinningOrderMemo(const int objectNum, std::string objectName);
	SpinningOrderMemo(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~SpinningOrderMemo();

	virtual void UpdateObject() override;
	virtual void RenderObject() override;

private:
	StageManager* m_pStageManager;

	float m_PosX;
	float m_PosY;
};

