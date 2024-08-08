#include "D2DEngine.h"

class Animator
{
private:
	int timeCheck;
public:
	Animator();
	~Animator();
	
	void AddAnimation(D2DSprite* sprite);
	void PlayAnimation(int posX, int posY, float duration, int divide);
	void ClearAnimation();

	vector<D2DSprite*> animationList;

	float m_deltaTime;		//�ǽð����� ��ŸŸ���� �޾ƿ�
	int m_CurFrame;			//�����Ҷ����� ī��Ʈ?

};
