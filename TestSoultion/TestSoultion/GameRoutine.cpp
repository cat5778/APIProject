#include "stdafx.h"
#include "GameRoutine.h"
#include "Player.h"
#include "Monster.h"
#include "CollisionManager.h"


CGameRoutine::CGameRoutine()
{
}


CGameRoutine::~CGameRoutine()
{
}

void CGameRoutine::Initialize()
{
	srand(unsigned(time(nullptr)));
	m_hWnd=GetDC(g_hWnd);

	//m_pPlayer = new CPlayer;
	//m_pPlayer->Initialize();
	//for (int i = 0; i < 4; i++)
	//{
	//	CMonster *temp = new CMonster;
	//	temp->Initialize();
	//	m_pMonsterList.push_back(temp);
	//}
	m_objectList[PLAYER].push_back(AbstractFactory<CPlayer>::CreateObject());
	for (int i = 0; i < 5; i++)
	{
		m_objectList[MONSTER].push_back(AbstractFactory<CMonster>::CreateObject());
	}

}

int CGameRoutine::Update()
{
	//m_pPlayer->Update();

	//for (auto &monster : m_pMonsterList)
	//{
	//	monster->Update();
	//}

	for (int i = 0; i < OBJECT_END; i++)
	{
		auto itr_begin = m_objectList[i].begin();
		auto itr_end = m_objectList[i].end();

		for (; itr_begin != itr_end;)
		{
			bool bISDead = (*itr_begin)->Update();
			if (bISDead == DEAD_OBJ)
			{
				SafeDelete((*itr_begin));
				itr_begin=m_objectList[i].erase(itr_begin);
			}
			else
				itr_begin++;

		}

	}
	if(!(m_objectList[PLAYER].empty()) || !(m_objectList[MONSTER].empty()))
		CCollisionManager::CollisionSphere(m_objectList[PLAYER], m_objectList[MONSTER]);
		//CCollisionManager::CollisionRect(m_objectList[PLAYER], m_objectList[MONSTER]);

	return 0;
}

void CGameRoutine::Render()
{
	Rectangle(m_hWnd, 0, 0, WinCX, WinCY);
	//m_pPlayer->Render(m_hWnd);
	//for (auto &monster : m_pMonsterList)
	//{
	//	monster->Render(m_hWnd);
	//}
	for (int i = 0; i < OBJECT_END; ++i)
	{
		for (auto &Object : m_objectList[i])
			Object->Render(m_hWnd);
	}



}

void CGameRoutine::Release()
{
}
