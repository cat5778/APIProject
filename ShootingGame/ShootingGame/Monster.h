#pragma once
#include "GameObject.h"
class CMonster :public CGameObject
{
public:
	CMonster();
	~CMonster();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
private:
	virtual void Release() override;
	void Move();


};

