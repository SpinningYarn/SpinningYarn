#include "ObjectManager.h"
#include "SceneManager.h"
#include "Object.h"
#include "AverageBackground.h"
#include "KnttingBackGround.h"
#include "AnswerBoard.h"
#include "DatumPoint.h"
#include "AverageObject.h"
#include "StartButton.h"
#include "SpinningBackGround.h"
#include "SpinningCenterPoint.h"
#include "SpinningWheel.h"
#include "SpinningGuideLine.h"
#include "SpinningGaugeBar.h"
#include "SpinningGaugBall.h"
#include "SpinningOrderMemo.h"

#include "StatBox.h"
#include "StatBox2.h"
#include "TestObject2.h"
#include "Inventory.h"
#include "Shop.h"
#include "GameMenu.h"
#include "Credit.h"
#include "ResultProduct.h"
#include "NextSceneButton.h"
#include "Dantto.h"
#include "Needle.h"
#include "MainBackground.h"
#include "HowtoPlay.h"
#include "DrawBoard.h"

//울 종류
#include "SpiderWeb.h"
#include "LambsWool.h"
#include "Cotton.h"
#include "Burlap.h"
#include "Angora.h"
#include "Cashmere.h"


ObjectManager::ObjectManager()
	: m_ObjectIndex(0)
{

}

ObjectManager::~ObjectManager()
{

}

Object* ObjectManager::CreateObject(eObjectDefine objectType, const std::string& objectName)
{
	switch (objectType)
	{
		case eObjectDefine::KnttingMainScreen:
		{
			Object* newObject = new KnttingBackGround(m_ObjectIndex, objectName);		// 새로운 씬 생성, 첫 씬의 인덱스는 0
			m_ObjectList.push_back(newObject);											// 씬 리스트에 새로만든 씬 넣음
			m_ObjectIndex++;															// 씬 번호 ++
			return newObject;
		}

		case eObjectDefine::AnswerBoard:		
		{
			Object* newObject = new AnswerBoard(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newObject);									
			m_ObjectIndex++;													
			return newObject;
		}

		case eObjectDefine::DatumPoint:
		{
			Object* newobject = new DatumPoint(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::StartButton:
		{
			Object* newobject = new StartButton(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningMainScreen:
		{
			Object* newobject = new SpinningBackGround(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningCenterObject:
		{
			Object* newobject = new SpinningCenterPoint(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningWheel:
		{
			Object* newobject = new SpinningWheel(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningGuideLine:
		{
			Object* newobject = new SpinningGuideLine(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningGaugeBar:
		{
			Object* newobject = new SpinningGaugeBar(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningGaugeBarRange:
		{
			Object* newobject = new SpinningGaugeBar(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningGaugeBall:
		{
			Object* newobject = new SpinningGaugBall(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningOrderMemo:
		{
			Object* newobject = new SpinningOrderMemo(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningOrderMemoCustomer1:
		{
			Object* newobject = new SpinningOrderMemo(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningOrderMemoCustomer2:
		{
			Object* newobject = new SpinningOrderMemo(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningOrderMemoCustomer3:
		{
			Object* newobject = new SpinningOrderMemo(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningOrderMemoCustomer4:
		{
			Object* newobject = new SpinningOrderMemo(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningOrderMemoCustomer5:
		{
			Object* newobject = new SpinningOrderMemo(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::EMPTYBOX1:
		{
			Object* newobject = new AverageObject(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::EMPTYBOX2:
		{
			Object* newobject = new AverageObject(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::AVERAGEBOX:
		{
			Object* newobject = new AverageObject(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}




		case eObjectDefine::STATBOX:
		{
			Object* newobject = new StatBox(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::AverageMainScreen:
		{
			Object* newobject = new AverageBackground(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::STATBOX2:
		{
			Object* newobject = new StatBox2(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}


		case eObjectDefine::CAT_HIT:
		{
			Object* newobject = new TestObject2(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SPIDERWEB:
		{
			Object* newobject = new SpiderWeb(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::LAMBSWOOL:
		{
			Object* newobject = new LambsWool(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::COTTON:
		{
			Object* newobject = new Cotton(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::HEMP:
		{
			Object* newobject = new Burlap(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::ANGORA:
		{
			Object* newobject = new Angora(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::CASHMERE:
		{
			Object* newobject = new Cashmere(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SHOP:
		{
			Object* newobject = new Shop(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::CREDIT:
		{
			Object* newobject = new Credit(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::RESULT_PRODUCT:
		{
			Object* newobject = new ResultProduct(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::Dantto:
		{
			Object* newobject = new Dantto(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::Needle:
		{
			Object* newobject = new Needle(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::MainScreen:
		{
			Object* newobject = new MainBackground(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

 		case eObjectDefine::HOWTOPLAY:
 		{
 			Object* newobject = new HowtoPlay(m_ObjectIndex, objectName);
 			m_ObjectList.push_back(newobject);
 			m_ObjectIndex++;
 			return newobject;
 		}

		case eObjectDefine::DrawBoard:
		{
			Object* newobject = new DrawBoard(m_ObjectIndex, objectName);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		default: 
			break;
	}
}

Object* ObjectManager::CreateObject(eObjectDefine objectType, const std::string& objectName, int posX, int posY)
{
	switch (objectType)
	{
		case eObjectDefine::KnttingMainScreen:							// enum 클래스에서 int 형 변환을 위해 static_cast<int>를 해줘야함
		{
			Object* newObject = new KnttingBackGround(m_ObjectIndex, objectName, posX, posY);		// 새로운 씬 생성, 첫 씬의 인덱스는 0
			m_ObjectList.push_back(newObject);									// 씬 리스트에 새로만든 씬 넣음
			m_ObjectIndex++;													// 씬 번호 ++
			return newObject;
		}

		case eObjectDefine::AnswerBoard:							// enum 클래스에서 int 형 변환을 위해 static_cast<int>를 해줘야함
		{
			Object* newObject2 = new AnswerBoard(m_ObjectIndex, objectName, posX, posY);	// 새로운 씬 생성, 첫 씬의 인덱스는 0
			m_ObjectList.push_back(newObject2);									// 씬 리스트에 새로만든 씬 넣음
			m_ObjectIndex++;													// 씬 번호 ++
			return newObject2;
		}

		case eObjectDefine::DatumPoint:
		{
			Object* newobject = new DatumPoint(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::StartButton:
		{
			Object* newobject = new StartButton(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningMainScreen:
		{
			Object* newobject = new SpinningBackGround(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningCenterObject:
		{
			Object* newobject = new SpinningCenterPoint(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningWheel:
		{
			Object* newobject = new SpinningWheel(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningGuideLine:
		{
			Object* newobject = new SpinningGuideLine(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningGaugeBar:
		{
			Object* newobject = new SpinningGaugeBar(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningGaugeBarRange:
		{
			Object* newobject = new SpinningGaugeBar(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningGaugeBall:
		{
			Object* newobject = new SpinningGaugBall(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningOrderMemo:
		{
			Object* newobject = new SpinningOrderMemo(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningOrderMemoCustomer1:
		{
			Object* newobject = new SpinningOrderMemo(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningOrderMemoCustomer2:
		{
			Object* newobject = new SpinningOrderMemo(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningOrderMemoCustomer3:
		{
			Object* newobject = new SpinningOrderMemo(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningOrderMemoCustomer4:
		{
			Object* newobject = new SpinningOrderMemo(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SpinningOrderMemoCustomer5:
		{
			Object* newobject = new SpinningOrderMemo(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::EMPTYBOX1:
		{
			Object* newobject = new AverageObject(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::EMPTYBOX2:
		{
			Object* newobject = new AverageObject(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::AVERAGEBOX:
		{
			Object* newobject = new AverageObject(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}
		



		case eObjectDefine::STATBOX:
		{
			Object* newobject = new StatBox(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::STATBOX2:
		{
			Object* newobject = new StatBox2(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::AverageMainScreen:
		{
			Object* newobject = new AverageBackground(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}


		case eObjectDefine::CAT_HIT:
		{
			Object* newobject = new TestObject2(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SPIDERWEB:
		{
			Object* newobject = new SpiderWeb(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::LAMBSWOOL:
		{
			Object* newobject = new LambsWool(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::COTTON:
		{
			Object* newobject = new Cotton(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::HEMP:
		{
			Object* newobject = new Burlap(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::ANGORA:
		{
			Object* newobject = new Angora(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::CASHMERE:
		{
			Object* newobject = new Cashmere(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::SHOP:
		{
			Object* newobject = new Shop(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::CREDIT:
		{
			Object* newobject = new Credit(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::RESULT_PRODUCT:
		{
			Object* newobject = new ResultProduct(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::Dantto:
		{
			Object* newobject = new Dantto(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::Needle:
		{
			Object* newobject = new Needle(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::MainScreen:
		{
			Object* newobject = new MainBackground(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::HOWTOPLAY:
		{
			Object* newobject = new HowtoPlay(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::DrawBoard:
		{
			Object* newobject = new DrawBoard(m_ObjectIndex, objectName, posX, posY);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		default:
			break;
	}
}

Object* ObjectManager::CreateObject(eObjectDefine objectType, const std::string& objectName, SceneManager* p_SceneManager)
{
	switch (objectType)
	{
		case eObjectDefine::NextSceneButton:
		{
			Object* newobject = new NextSceneButton(m_ObjectIndex, objectName, p_SceneManager);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::INVENTORY:
		{
			Object* newobject = new Inventory(m_ObjectIndex, objectName, p_SceneManager);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		case eObjectDefine::MENU:
		{
			Object* newobject = new GameMenu(m_ObjectIndex, objectName, p_SceneManager);
			m_ObjectList.push_back(newobject);
			m_ObjectIndex++;
			return newobject;
		}

		default:
			break;
	}
}

Object* ObjectManager::GetObject(const int objectNum)
{
	for (int i = 0; i < m_ObjectList.size(); i++)
	{
		if (m_ObjectList[i]->GetObjectIndex() == objectNum)
		{
			return m_ObjectList[i];
		}
	}
	return nullptr;
}

Object* ObjectManager::GetObject(const std::string& objectName)
{
	for (int i = 0; i < m_ObjectList.size(); i++)
	{
		if (m_ObjectList[i]->GetObjectName() == objectName)
		{
			return m_ObjectList[i];
		}
	}
	return nullptr;
}

void ObjectManager::DeleteObject(const int objectNum)
{
	for (int i = 0; i < m_ObjectList.size(); i++)
	{
		if (m_ObjectList[i]->GetObjectIndex() == objectNum)
		{
			m_ObjectList.erase(m_ObjectList.begin() + i);
		}
	}
}

void ObjectManager::DeleteObject(const std::string& objectName)
{
	for (int i = 0; i < m_ObjectList.size(); i++)
	{
		if (m_ObjectList[i]->GetObjectName() == objectName)
		{
			m_ObjectList.erase(m_ObjectList.begin() + i);
		}
	}
}

