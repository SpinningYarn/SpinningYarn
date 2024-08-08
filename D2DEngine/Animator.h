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

	float m_deltaTime;		//실시간으로 델타타임을 받아옴
	int m_CurFrame;			//실행할때마다 카운트?

};
