#pragma once
#include "GameObject.h"
class CPlayer : public CGameObject
{
public:
	CPlayer();
	~CPlayer();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Relese() override;
	void SetBulletList(GameList& _bulletlist) { m_pBulletList = &_bulletlist; };
	void InputKey();
private:
	GameList* m_pBulletList;

};

