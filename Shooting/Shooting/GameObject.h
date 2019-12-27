#pragma once
class CGameObject
{
public:

	CGameObject();
	virtual ~CGameObject();
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Release() = 0;

protected:
	Info m_Info;
	

};

