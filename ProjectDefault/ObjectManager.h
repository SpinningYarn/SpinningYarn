#pragma once
#include "Common.h"
#include "eObjectDefine.h"

class Object;
class SceneManager;

/// <summary>
/// 오브젝트 매니저...
/// </summary>
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	Object* CreateObject(eObjectDefine objectType, const std::string& objectName);									// 새로운 오브젝트 생성, 오브젝트 타입, 이름 넣어줄 것
	Object* CreateObject(eObjectDefine objectType, const std::string& objectName, int posX, int posY);			    // 새로운 오브젝트 생성, 오브젝트 타입, 이름, X좌표, Y좌표 넣어줄 것
	Object* CreateObject(eObjectDefine objectType, const std::string& objectName, SceneManager* p_SceneManager);	//  씬 매니저를 들고 있을 특수한 오브젝트 (다음 단계)

	Object* GetObject(const int objectNum);					// 특정 오브젝트 가져오기 (오브젝트 번호를 통하여)
	Object* GetObject(const std::string& objectName);		// 특정 오브젝트 가져오기 (오브젝트 이름를 통하여)

	void DeleteObject(const int objectNum);					// 특정 오브젝트 삭제 (오브젝트 번호를 통하여)
	void DeleteObject(const std::string& ojbectName);		// 특정 오브젝트 삭제 (오브젝트 이름을 통하여)

private:
	int m_ObjectIndex;										// 오브젝트 생성할때 번호 부여 

	std::vector<Object*> m_ObjectList;						// 오브젝트들을 담고 있음
};

