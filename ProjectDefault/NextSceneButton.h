#pragma once
#include "Object.h"

class SceneManager;
class DatumPoint;
class Scene_Average;
class Scene_Knitting;
class Scene_Spinning;
class SpinningGaugBall;
class StageManager;

/// 씬 추가하면 여기서 숫자 변경
const int AverageScene = 5;
const int SpinningScene = AverageScene + 1;
const int KnittingScene = AverageScene + 2;

/// <summary>
/// 
/// 다음 단계로 넘어가는 버튼
/// 씬에 대한 정보를 갖기 위해 이 오브젝트만 특별히 씬 매니저를 들고 있음
/// 각 씬 별 충족되는 로직을 update에 switch문으로 작성하여
/// 하나의 버튼이 각 씬마다 다르게 동작하도록 구현
/// 
/// 2022.02.15 YJH
/// </summary>

class NextSceneButton : public Object
{
public:
	NextSceneButton(const int objectNum, const std::string& objectName, SceneManager* pSceneManager);

	~NextSceneButton();

	virtual void UpdateObject() override;		// 객체에서 업데이트 하는 것을 오버라이딩
	virtual void RenderObject() override;		// 객체에서 그리는 것을 오버라이딩	

private:
	int m_ButtonSize;							// 버튼 x 사이즈
	bool m_Activate;							// 활성화 여부 true일 경우 다음 단계 버튼 활성화
	int m_SceneIndex;							// 현재 씬 인덱스
	int m_CenterX;
	int m_CenterY;
	int m_Distance;
	int m_curStage;

	SceneManager* m_pSceneManager;				// 씬 매니저에 대한 포인터
	DatumPoint* m_pDatumPoint;					// 기준점에 대한 포인터
	Scene_Knitting* m_pSceneKnitting;			// 직조 씬에 대한 포인터
	Scene_Spinning* m_pScene_Spinning;
	Scene_Average* m_pScene_Average;
	SpinningGaugBall* m_pSpinningGaugBall;
	StageManager* m_pStageManager;
};


