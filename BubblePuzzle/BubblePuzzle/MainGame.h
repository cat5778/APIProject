#pragma once
class CMainGame
{

public:
	CMainGame();
	~CMainGame();
	void Initialize();
	int Update();
	void Render();
	void Release();

private:
	CPlayer *pPlayer;

};

