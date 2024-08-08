#pragma once

#include "Common.h"

class Object;
class SceneManager;

/// <summary>
/// ��� ���� �θ�
/// ���� ������ �߻�ȭ��
/// 
/// �������� �̿��ؼ�, ���� �ٸ� ������ �ϴ� �Ϻ� ����
/// �ϳ��� NowScene���� ���� �� �� �ֵ��� �Ѵ�.
/// 
/// 2023.02.06 YJHAll
/// </summary>
class IScene
{
public:
	// �����Ҷ� ���� �ε���, �̸�, �ڽ��� ȣ���ϴ� �� �Ŵ����� �����͸� ��� ����)
	IScene(const int sceneNum, std::string sceneName, SceneManager* pSceneManager);
	~IScene();

	virtual void UpdateScene() abstract;	/// �� �� ������Ʈ ����Ʈ�� ������Ʈ
	virtual void RenderScene() abstract;	/// �� �� ������Ʈ ����Ʈ�� �׸���
	virtual void Initialize() abstract;		/// �� �ʱ�ȭ	///ó�� �ѹ��� �����ؾ��ϴ°� ���� ���

protected:
	void OnUpdate();
	void OnRender();

public:
	const int GetSceneIndex();						// �� �ε��� ��������
	const std::string& GetSceneName();				// �� �̸� ��������

	void AddObject(Object* pObject);				// ������Ʈ ����Ʈ�� ������Ʈ�� �߰�
	Object* GetSceneObject(const int objectIndex);			// �� �� ������Ʈ ����Ʈ���� ������Ʈ �������� (��ȣ)
	Object* GetSceneObject(const std::string& objectName);	// �� �� ������Ʈ ����Ʈ���� ������Ʈ �������� (�̸�)
	void RemoveObject(const int objectIndex);		// �� ���� ������Ʈ�� ���� (���� ��ȣ)
	void RemoveObject(const std::string& objectName);// �� ���� ������Ʈ�� ���� (���� �̸�)
	void SortObjectList();
	bool GetOndraw();									// �׸��� ���� ���°� ��������
	void SetOndrawTrue();								// �� �� �׸��� 
	void SetOndrawFalse();								// �� �� �׸��� X

private:
	int m_Index;									// �� ������ �ε��� (���� ��ȣ)
	std::string m_Name;								// �� ������ �̸� (���� �̸�) 
	bool m_Ondraw;									// �� �׸��� ����

	// ���� �ڵ鸵�ϴ� �Ŵ����� Ŭ������ �����͸� ������ ������ ����
protected:
	std::vector<Object*> m_SceneObjectList;				// ������Ʈ�� ���� ����
	SceneManager* m_pSceneManager;
};

