#pragma once
#include "Common.h"

class IScene;	// 씬 인터페이스 클래스 전방선언

/// <summary>
/// 씬을 관리한다.
/// 
/// 씬 생성, 불러오기, 삭제를 할 수 있다.
/// 내부적으로 현재 씬을 가진다.
/// 내부적으로 현재 씬을 돌아가게 해 준다. (update, render...)
/// 
/// 2023.02.06 YJHAll
/// </summary>
class SceneManager
{
	// 생성자 소멸자
public:
	SceneManager();
	~SceneManager();

	// 외부에서 호출 될 EventFunction
	void Update();
	void Render();

	///IScene* CreateScene(const std::string& sceneName);	// 새로운 씬 생성, 씬 이름 넣어줄 것

	// 다형성을 이용한 씬 제작
	IScene* CreateMainScene(const std::string& sceneName);
	IScene* CreateIntroScene(const std::string& sceneName);
	IScene* CreateTalking1Scene(const std::string& sceneName);
	IScene* CreateScene_Average(const std::string& sceneName);
	IScene* CreateScene_Spinning(const std::string& sceneName);
	IScene* CreateScene_Knitting(const std::string& sceneName);
	IScene* CreateTalking2Scene(const std::string& sceneName);
	IScene* CreateStageScene(const std::string& sceneName);
	IScene* CreateEndingScene(const std::string& sceneName);

	IScene* GetScene(const int sceneNum);				// 특정 씬 가져오기 (씬 이름를 통하여)
	IScene* GetScene(const std::string& sceneName);		// 특정 씬 가져오기 (씬 이름를 통하여)
	void DeleteScene(const int sceneNum);				// 특정 씬 삭제 (씬 번호를 통하여)
	void DeleteScene(const std::string& sceneName);		// 특정 씬 삭제 (씬 이름을 통하여)
	IScene* GetNowScene();								// 현재 씬 가져오기
	int GetSceneSize();
	void SetNowScene(const int sceneNum);				// 특정 씬을 현재 씬으로 지정 (번호를 통해)
	void SetNowScene(const std::string& sceneName);		// 특정 씬을 현재 씬으로 지정 (이름을 통해)

private:
	/// 싱글톤으로 객체가 하나로 사실상 static과 같은 기능으로 쓸 수 있기에 그냥 int로 선언
	int m_SceneIndex;									// 씬 생성할때 번호 부여 
	
	std::vector<IScene*> m_SceneList;					// 씬들을 담고 있음

	IScene* m_pNowScene;								// 지금 돌아가야 하는 씬
};




