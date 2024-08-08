#pragma once

#include "Common.h"

class Object;
class SceneManager;

/// <summary>
/// 모든 씬의 부모
/// 씬의 동작을 추상화함
/// 
/// 다형성을 이용해서, 서로 다른 동작을 하는 하부 씬을
/// 하나의 NowScene으로 동작 할 수 있도록 한다.
/// 
/// 2023.02.06 YJHAll
/// </summary>
class IScene
{
public:
	// 생성할때 씬에 인덱스, 이름, 자신을 호출하는 씬 매니저의 포인터를 담고 있음)
	IScene(const int sceneNum, std::string sceneName, SceneManager* pSceneManager);
	~IScene();

	virtual void UpdateScene() abstract;	/// 씬 내 오브젝트 리스트를 업데이트
	virtual void RenderScene() abstract;	/// 씬 내 오브젝트 리스트를 그리기
	virtual void Initialize() abstract;		/// 씬 초기화	///처음 한번만 실행해야하는게 있을 경우

protected:
	void OnUpdate();
	void OnRender();

public:
	const int GetSceneIndex();						// 씬 인덱스 가져오기
	const std::string& GetSceneName();				// 씬 이름 가져오기

	void AddObject(Object* pObject);				// 오브젝트 리스트에 오브젝트를 추가
	Object* GetSceneObject(const int objectIndex);			// 씬 내 오브젝트 리스트에서 오브젝트 가져오기 (번호)
	Object* GetSceneObject(const std::string& objectName);	// 씬 내 오브젝트 리스트에서 오브젝트 가져오기 (이름)
	void RemoveObject(const int objectIndex);		// 씬 내에 오브젝트를 삭제 (고유 번호)
	void RemoveObject(const std::string& objectName);// 씬 내에 오브젝트를 삭제 (고유 이름)
	void SortObjectList();
	bool GetOndraw();									// 그리기 여부 상태값 가져오기
	void SetOndrawTrue();								// 씬 내 그리기 
	void SetOndrawFalse();								// 씬 내 그리기 X

private:
	int m_Index;									// 씬 본인의 인덱스 (고유 번호)
	std::string m_Name;								// 씬 본인의 이름 (고유 이름) 
	bool m_Ondraw;									// 씬 그리는 여부

	// 나를 핸들링하는 매니저급 클래스의 포인터를 가지는 디자인 패턴
protected:
	std::vector<Object*> m_SceneObjectList;				// 오브젝트를 담을 벡터
	SceneManager* m_pSceneManager;
};

