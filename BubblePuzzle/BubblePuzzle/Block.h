#pragma once
#include "GameObject.h"
class CBlock :public CGameObject
{

public:
	CBlock();
	CBlock(INFO _playerinfo,INFO _taiminfo);
	~CBlock();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;
public:

	void Move();


private:


};
