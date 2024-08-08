#pragma once
#include "Common.h"

class IScene;	// �� �������̽� Ŭ���� ���漱��

/// <summary>
/// ���� �����Ѵ�.
/// 
/// �� ����, �ҷ�����, ������ �� �� �ִ�.
/// ���������� ���� ���� ������.
/// ���������� ���� ���� ���ư��� �� �ش�. (update, render...)
/// 
/// 2023.02.06 YJHAll
/// </summary>
class SceneManager
{
	// ������ �Ҹ���
public:
	SceneManager();
	~SceneManager();

	// �ܺο��� ȣ�� �� EventFunction
	void Update();
	void Render();

	///IScene* CreateScene(const std::string& sceneName);	// ���ο� �� ����, �� �̸� �־��� ��

	// �������� �̿��� �� ����
	IScene* CreateMainScene(const std::string& sceneName);
	IScene* CreateIntroScene(const std::string& sceneName);
	IScene* CreateTalking1Scene(const std::string& sceneName);
	IScene* CreateScene_Average(const std::string& sceneName);
	IScene* CreateScene_Spinning(const std::string& sceneName);
	IScene* CreateScene_Knitting(const std::string& sceneName);
	IScene* CreateTalking2Scene(const std::string& sceneName);
	IScene* CreateStageScene(const std::string& sceneName);
	IScene* CreateEndingScene(const std::string& sceneName);

	IScene* GetScene(const int sceneNum);				// Ư�� �� �������� (�� �̸��� ���Ͽ�)
	IScene* GetScene(const std::string& sceneName);		// Ư�� �� �������� (�� �̸��� ���Ͽ�)
	void DeleteScene(const int sceneNum);				// Ư�� �� ���� (�� ��ȣ�� ���Ͽ�)
	void DeleteScene(const std::string& sceneName);		// Ư�� �� ���� (�� �̸��� ���Ͽ�)
	IScene* GetNowScene();								// ���� �� ��������
	int GetSceneSize();
	void SetNowScene(const int sceneNum);				// Ư�� ���� ���� ������ ���� (��ȣ�� ����)
	void SetNowScene(const std::string& sceneName);		// Ư�� ���� ���� ������ ���� (�̸��� ����)

private:
	/// �̱������� ��ü�� �ϳ��� ��ǻ� static�� ���� ������� �� �� �ֱ⿡ �׳� int�� ����
	int m_SceneIndex;									// �� �����Ҷ� ��ȣ �ο� 
	
	std::vector<IScene*> m_SceneList;					// ������ ��� ����

	IScene* m_pNowScene;								// ���� ���ư��� �ϴ� ��
};




