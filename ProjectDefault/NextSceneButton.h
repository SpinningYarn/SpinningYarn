#pragma once
#include "Object.h"

class SceneManager;
class DatumPoint;
class Scene_Average;
class Scene_Knitting;
class Scene_Spinning;
class SpinningGaugBall;
class StageManager;

/// �� �߰��ϸ� ���⼭ ���� ����
const int AverageScene = 5;
const int SpinningScene = AverageScene + 1;
const int KnittingScene = AverageScene + 2;

/// <summary>
/// 
/// ���� �ܰ�� �Ѿ�� ��ư
/// ���� ���� ������ ���� ���� �� ������Ʈ�� Ư���� �� �Ŵ����� ��� ����
/// �� �� �� �����Ǵ� ������ update�� switch������ �ۼ��Ͽ�
/// �ϳ��� ��ư�� �� ������ �ٸ��� �����ϵ��� ����
/// 
/// 2022.02.15 YJH
/// </summary>

class NextSceneButton : public Object
{
public:
	NextSceneButton(const int objectNum, const std::string& objectName, SceneManager* pSceneManager);

	~NextSceneButton();

	virtual void UpdateObject() override;		// ��ü���� ������Ʈ �ϴ� ���� �������̵�
	virtual void RenderObject() override;		// ��ü���� �׸��� ���� �������̵�	

private:
	int m_ButtonSize;							// ��ư x ������
	bool m_Activate;							// Ȱ��ȭ ���� true�� ��� ���� �ܰ� ��ư Ȱ��ȭ
	int m_SceneIndex;							// ���� �� �ε���
	int m_CenterX;
	int m_CenterY;
	int m_Distance;
	int m_curStage;

	SceneManager* m_pSceneManager;				// �� �Ŵ����� ���� ������
	DatumPoint* m_pDatumPoint;					// �������� ���� ������
	Scene_Knitting* m_pSceneKnitting;			// ���� ���� ���� ������
	Scene_Spinning* m_pScene_Spinning;
	Scene_Average* m_pScene_Average;
	SpinningGaugBall* m_pSpinningGaugBall;
	StageManager* m_pStageManager;
};


