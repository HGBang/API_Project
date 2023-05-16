
#include "Scene.h"
#include "../GameObject/GameObject.h"
#include "SceneResource.h"
#include "Camera.h"
#include "SceneCollision.h"
#include "../GameObject/TileMap.h"
#include "../GameObject/Player.h"
#include "../GameObject/BossMonster.h"
#include "../GameObject/SecondMonster.h"
#include "../GameObject/Npc.h"

CScene::CScene()
{
	m_Resource = new CSceneResource;
	m_Camera = new CCamera;
	m_Collision = new CSceneCollision;
}

CScene::~CScene()
{
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		m_ObjList[i].clear();
	}

	SAFE_DELETE(m_Collision);
	SAFE_DELETE(m_Camera);
	SAFE_DELETE(m_Resource);
}

void CScene::SetTileMap(CTileMap* TileMap)
{
	m_TileMap = TileMap;
}

void CScene::SetPlayer(CGameObject* Player)
{
	m_Player = Player;
}

void CScene::SetMonster(CGameObject* Monster)
{
	m_Monster = Monster;
}


bool CScene::Init()
{
	return true;
}

void CScene::Update(float DeltaTime)
{


	

	// 이렇게 꼭 연습하세요 제발....
	// std::list<CSharedPtr<class CGameObject>>::iterator

	// auto : 선언과 동시에 무조건 대입을 해주어야 한다.
	// 대입된 타입으로 타입이 선언된다.
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		auto	iter = m_ObjList[i].begin();
		auto	iterEnd = m_ObjList[i].end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->m_Start)
			{
				(*iter)->Start();
			}

			if (!(*iter)->GetActive())
			{
				// 리스트에서 제거하는 순간 SharedPtr의 소멸자가 호출되어
				// 카운트가 감소한다.
				iter = m_ObjList[i].erase(iter);
				iterEnd = m_ObjList[i].end();
				continue;
			}

			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Update(DeltaTime);

			++iter;
		}
	}

	auto	iter1 = m_vecWidgetWindow.begin();
	auto	iter1End = m_vecWidgetWindow.end();

	for (; iter1 != iter1End;)
	{
		if (!(*iter1)->GetActive())
		{
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}

		else if (!(*iter1)->GetEnable())
		{
			++iter1;
			continue;
		}

		(*iter1)->Update(DeltaTime);
		++iter1;
	}

	m_Camera->Update(DeltaTime);
}

void CScene::PostUpdate(float DeltaTime)
{
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		auto	iter = m_ObjList[i].begin();
		auto	iterEnd = m_ObjList[i].end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->m_Start)
			{
				(*iter)->Start();
			}

			if (!(*iter)->GetActive())
			{
				// 리스트에서 제거하는 순간 SharedPtr의 소멸자가 호출되어
				// 카운트가 감소한다.
				iter = m_ObjList[i].erase(iter);
				iterEnd = m_ObjList[i].end();
				continue;
			}

			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}

			(*iter)->PostUpdate(DeltaTime);

			++iter;
		}
	}

	auto	iter1 = m_vecWidgetWindow.begin();
	auto	iter1End = m_vecWidgetWindow.end();

	for (; iter1 != iter1End;)
	{
		if (!(*iter1)->GetActive())
		{
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}

		else if (!(*iter1)->GetEnable())
		{
			++iter1;
			continue;
		}

		(*iter1)->PostUpdate(DeltaTime);
		++iter1;
	}

	iter1 = m_vecWidgetWindow.begin();
	iter1End = m_vecWidgetWindow.end();

	for (; iter1 != iter1End;)
	{
		if (!(*iter1)->GetActive())
		{
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}

		else if (!(*iter1)->GetEnable())
		{
			++iter1;
			continue;
		}

		m_Collision->AddWidgetWindow(*iter1);
		++iter1;
	}

	m_Collision->CollisionMouse(DeltaTime);

	m_Collision->Collision(DeltaTime);
}

void CScene::Render(HDC hDC, float DeltaTime)
{

	

	// 출력 목록을 정렬한다. (Y소팅)
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		m_ObjList[i].sort(SortY);

		auto	iter = m_ObjList[i].begin();
		auto	iterEnd = m_ObjList[i].end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->m_Start)
			{
				(*iter)->Start();
			}

			if (!(*iter)->GetActive())
			{
				// 리스트에서 제거하는 순간 SharedPtr의 소멸자가 호출되어
				// 카운트가 감소한다.
				iter = m_ObjList[i].erase(iter);
				iterEnd = m_ObjList[i].end();
				continue;
			}

			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Render(hDC, DeltaTime);

			++iter;
		}
	}

	// WidgetComponent 출력
	// 제거될 위젯 컴포넌트는 제거한다.
	{
		auto	iter = m_WidgetComponentList.begin();
		auto	iterEnd = m_WidgetComponentList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				iter = m_WidgetComponentList.erase(iter);
				iterEnd = m_WidgetComponentList.end();
				continue;
			}

			++iter;
		}

		// 정렬한다.
		m_WidgetComponentList.sort(SortYWidgetComponent);

		iter = m_WidgetComponentList.begin();
		iterEnd = m_WidgetComponentList.end();

		for (; iter != iterEnd; ++iter)
		{
			if (!(*iter)->GetEnable())
			{
				continue;
			}

			(*iter)->Render(hDC, DeltaTime);
		}
	}

	// 월드공간의 물체가 출력된 이후에 UI를 출력한다.
	if (m_vecWidgetWindow.size() > 1)
		std::sort(m_vecWidgetWindow.begin(), m_vecWidgetWindow.end(), CScene::SortWidget);

	auto	iter1 = m_vecWidgetWindow.begin();
	auto	iter1End = m_vecWidgetWindow.end();

	for (; iter1 != iter1End;)
	{
		if (!(*iter1)->GetActive())
		{
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}

		else if (!(*iter1)->GetEnable())
		{
			++iter1;
			continue;
		}

		(*iter1)->Render(hDC, DeltaTime);
		++iter1;
	}



	// UI를 출력한 이후에 마우스를 출력한다.
}

void CScene::DeletePlayer()
{
	m_Player = nullptr;
}

void CScene::DeleteMonster()
{
	m_Monster = nullptr;
}

void CScene::DeleteSecondMonster()
{
	m_SecondMonster = nullptr;
}

void CScene::DeleteNpc()
{
	m_Npc = nullptr;
}

void CScene::DeleteBossMonster()
{
	m_BossMonster = nullptr;
}

void CScene::DeleteBossNpc()
{
	m_BossNpc = nullptr;
}

void CScene::DeleteAngelNpc()
{
	m_AngelNpc = nullptr;
}

void CScene::DeleteFinalBoss()
{
	m_FinalBossMonster = nullptr;
}

bool CScene::SortY(const CSharedPtr<CGameObject>& Src, const CSharedPtr<CGameObject>& Dest)
{
	// 발밑 기준으로 정렬을 진행해야 하기 때문에 발밑의 Y를 구해준다.
	float	SrcY = Src->GetPos().y + (1.f - Src->GetPivot().y) * Src->GetSize().y;
	float	DestY = Dest->GetPos().y + (1.f - Dest->GetPivot().y) * Dest->GetSize().y;

	return SrcY < DestY;
}

bool CScene::SortYWidgetComponent(
	const CSharedPtr<class CWidgetComponent>& Src,
	const CSharedPtr<class CWidgetComponent>& Dest)
{
	return Src->GetBottom() < Dest->GetBottom();
}

bool CScene::SortWidget(const CSharedPtr<CWidgetWindow>& Src, const CSharedPtr<CWidgetWindow>& Dest)
{
	return Src->GetZOrder() < Dest->GetZOrder();
}
