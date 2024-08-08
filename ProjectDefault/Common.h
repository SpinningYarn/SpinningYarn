#pragma once
/// �������� ���̴� ����� ��Ƴ���

#include <vector>
#include <string>

#define BACKGROUND_ORDER 0
#define UI_ORDER 10
#define OBJECT_ORDER 20
#define KNITTING_ORDER 21
#define CAT_ORDER 30
#define SHOP_ORDER 50

// nullptr�� �ƴ� �� Release���ִ� �Լ� 
// �̰� ������ �������� nullptr�̾����ϴ� ������ ���� ü���� ������
// �ٵ� ��¥ �װ� nullptr�̾ ������ ����� ����� �� ���� ����´�
// �� ��쿣 Release�� �ٲ㼭�غ����� ���ߵ�
template<class Interface>
inline void SafeRelease(Interface** ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}