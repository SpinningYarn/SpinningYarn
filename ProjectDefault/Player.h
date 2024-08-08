#pragma once
#include "Inventory.h"

class Player
{
private:
	Inventory* m_inventory; // ¿Œ∫•≈‰∏Æ
	int m_money; // µ∑

public:
	Player();
	~Player();

	Inventory* GetInventory() { return m_inventory; }

	int GetMoney() { return m_money; }
	void SetMoney(int money) { m_money = money; }

};

