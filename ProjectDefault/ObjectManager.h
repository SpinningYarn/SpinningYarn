#pragma once
#include "Common.h"
#include "eObjectDefine.h"

class Object;
class SceneManager;

/// <summary>
/// ������Ʈ �Ŵ���...
/// </summary>
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	Object* CreateObject(eObjectDefine objectType, const std::string& objectName);									// ���ο� ������Ʈ ����, ������Ʈ Ÿ��, �̸� �־��� ��
	Object* CreateObject(eObjectDefine objectType, const std::string& objectName, int posX, int posY);			    // ���ο� ������Ʈ ����, ������Ʈ Ÿ��, �̸�, X��ǥ, Y��ǥ �־��� ��
	Object* CreateObject(eObjectDefine objectType, const std::string& objectName, SceneManager* p_SceneManager);	//  �� �Ŵ����� ��� ���� Ư���� ������Ʈ (���� �ܰ�)

	Object* GetObject(const int objectNum);					// Ư�� ������Ʈ �������� (������Ʈ ��ȣ�� ���Ͽ�)
	Object* GetObject(const std::string& objectName);		// Ư�� ������Ʈ �������� (������Ʈ �̸��� ���Ͽ�)

	void DeleteObject(const int objectNum);					// Ư�� ������Ʈ ���� (������Ʈ ��ȣ�� ���Ͽ�)
	void DeleteObject(const std::string& ojbectName);		// Ư�� ������Ʈ ���� (������Ʈ �̸��� ���Ͽ�)

private:
	int m_ObjectIndex;										// ������Ʈ �����Ҷ� ��ȣ �ο� 

	std::vector<Object*> m_ObjectList;						// ������Ʈ���� ��� ����
};

