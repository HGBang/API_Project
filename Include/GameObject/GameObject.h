#pragma once

#include "../Ref.h"
#include "../Animation/Animation.h"
#include "../Widget/WidgetComponent.h"

class CGameObject :
	public CRef
{
	friend class CScene;
	friend class CInput;

protected:
	CGameObject();
	CGameObject(const CGameObject& Obj);
	virtual ~CGameObject();

protected:
	class CScene* m_Scene;

protected:
	ERender_Layer	m_RenderLayer;
	Vector2		m_PrevPos;
	Vector2		m_Move;
	Vector2		m_Pos;
	Vector2		m_Size;
	Vector2		m_Pivot;
	CSharedPtr<class CTexture>	m_Texture;
	CAnimation* m_Animation;
	float		m_TimeScale;
	float		m_MoveSpeed;
	std::list<CSharedPtr<class CCollider>>	m_ColliderList;
	std::list<CSharedPtr<CWidgetComponent>>	m_WidgetComponentList;
	bool		m_PhysicsSimulate;
	bool		m_Ground;	// 땅을 밟고 있는 상태인지 아닌지
	float		m_GravityAccel;
	float		m_FallTime;
	float		m_FallStartY;
	bool		m_Jump;
	float		m_JumpVelocity;
	bool		m_SideWallCheck;
	bool		m_Start;
	bool		m_Moving;
	bool		m_Alive;
	bool		m_Bomb;
	bool		m_UpDown;
	bool		m_Monster;
	bool		m_BossMonster;
	float		m_DirLR;
	float		m_DirUP;
	bool		m_StartMonster;
	bool		m_Stop;
	float		m_Time;
	bool		m_PlayerCheck;
	int			m_BombCount;
	bool		m_BombOK;
	bool		m_BombCheck;
	bool		m_GetSoul;
	bool		m_SoulSkill;
	bool		m_SecondMonster;
	bool		m_GetRocket;
	bool		m_Rocket;
	bool		m_Item;
	bool		m_MonsterCheck;
	bool		m_SecondMonsterCheck;
	bool		m_Effect;
	float		m_MoveDistance;
	float		m_BombTime;

	bool		m_Power1On;
	bool		m_Power2On;


	bool		m_ShoesOn;

	float		m_Angle;

	bool		m_DieOn;

	bool		m_Clear;

	bool		m_NoDie;


	int			m_Number;

	bool		m_Round;

	bool		m_BossRound;




public:
	class CCollider* FindCollider(const std::string& Name);

	ERender_Layer GetRenderLayer()	const
	{
		return m_RenderLayer;
	}

	float GetTimeScale()	const
	{
		return m_TimeScale;
	}

	const Vector2& GetPos()	const
	{
		return m_Pos;
	}

	const Vector2& GetSize()	const
	{
		return m_Size;
	}

	const Vector2& GetPivot()	const
	{
		return m_Pivot;
	}

	bool GetAlive ()
	{
		return m_Alive;
	}

	bool GetStop()
	{
		return m_Stop;
	}

	bool GetPlayerCheck()
	{
		return m_PlayerCheck;
	}

	bool GetBombCheck()
	{
		return m_BombCheck;
	}

	bool GetRocketCheck()
	{
		return m_Rocket;
	}

	bool GetItemCheck()
	{
		return m_Item;
	}

	bool GetMonsterCheck()
	{
		return m_MonsterCheck;
	}

	bool GetSecondMonsterCheck()
	{
		return m_SecondMonsterCheck;
	}



public:
	void SetSideWallCheck(bool Check)
	{
		m_SideWallCheck = Check;
	}

	void SetPhysicsSimulate(bool Physics)
	{
		m_PhysicsSimulate = Physics;
	}

	void SetBomb(bool Bomb)
	{
		m_Bomb = Bomb;
	}

	void SetGravityAccel(float Accel)
	{
		m_GravityAccel = Accel;
	}

	void SetJumpVelocity(float JumpVelocity)
	{
		m_JumpVelocity = JumpVelocity;
	}

	void SetUpDown(bool UpDown)
	{
		m_UpDown = UpDown;
	}

	void SetBombOK(bool OK)
	{
		m_BombOK = OK;
	}

	void SetPlayerCheck(bool Check)
	{
		m_PlayerCheck = Check;
	}

	void SetMoveSpeed(float Speed)
	{
		m_MoveSpeed = m_MoveSpeed + Speed;
	}

	void SetAddBombCount(int Count)
	{
		m_BombCount = m_BombCount + Count;
	}

	void SetEffect(bool Effect)
	{
		m_Effect = Effect;
	}

	void SetPower1(bool Power)
	{
		m_Power1On = Power;
	}

	bool GetPower1()
	{
		return m_Power1On;
	}

	void SetPower2(bool Power)
	{
		m_Power2On = Power;
	}

	bool GetPower2()
	{
		return m_Power2On;
	}

	void SetShoesOn(bool Shoes)
	{
		m_ShoesOn = true;
	}

	bool GetShoesOn()
	{
		return m_ShoesOn;
	}

	void SetBossRound(bool BossRound)
	{
		m_BossRound = BossRound;
	}




	int GetAddBombCount()
	{
		return m_BombCount;
	}

	bool GetSol()
	{
		return m_GetSoul;
	}

	void SetSol(bool Sol)
	{
		m_GetSoul = true;
	}

	void SetRocket(bool Rocket)
	{
		m_GetRocket = true;
	}

	bool GetRocket()
	{
		return m_GetRocket;
	}


	bool GetSolSKill()
	{
		return m_SoulSkill;
	}

	bool GetDieOn()
	{
		return m_DieOn;
	}

	bool GetClearOn()
	{
		return m_Clear;
	}



	void Jump()
	{
		if (!m_Jump)
		{
			m_Jump = true;
			m_Ground = false;

			m_FallTime = 0.f;
			m_FallStartY = m_Pos.y;
		}
	}

	void SetTimeScale(float Scale)
	{
		m_TimeScale = Scale;
	}

	virtual void SetPos(float x, float y)
	{
		m_Pos.x = x;
		m_Pos.y = y;
	}

	virtual void SetPos(const Vector2& Pos)
	{
		m_Pos = Pos;
	}

	void SetSize(float x, float y)
	{
		m_Size.x = x;
		m_Size.y = y;
	}

	void SetSize(const Vector2& Size)
	{
		m_Size = Size;
	}

	void SetPivot(float x, float y)
	{
		m_Pivot.x = x;
		m_Pivot.y = y;
	}

	void SetPivot(const Vector2& Pivot)
	{
		m_Pivot = Pivot;
	}

	void SetMoving(bool Moving)
	{
		m_Moving = Moving;
	}

	void SetDirLR(float Dir)
	{
		m_DirLR = Dir;
	}

	void SetDirUP(float UP)
	{
		m_DirUP = UP;
	}

	void SetDistance(float Distance)
	{
		m_MoveDistance = Distance;
	}

	void SetAngle(float Angle)
	{
		m_Angle = Angle;
	}

	void SetNoDie(bool Die)
	{
		m_NoDie = Die;
	}

	void SetNumber(int Number)
	{
		m_Number = Number;
	}

	void SetRound(bool Round)
	{
		m_Round = Round;
	}



public:
	void SetTexture(const std::string& Name);
	void SetTexture(class CTexture* Texture);
	void SetTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& Name, const TCHAR* FullPath);
	void AddBombCount();

#ifdef UNICODE

	void SetTexture(const std::string& Name, const std::vector<std::wstring>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& Name, const std::vector<std::wstring>& vecFullPath);

#else

	void SetTexture(const std::string& Name, const std::vector<std::string>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& Name, const std::vector<std::string>& vecFullPath);

#endif // UNICODE

	bool SetColorKey(unsigned char r, unsigned char g, unsigned char b,
		int Index = 0);
	bool SetColorKeyAll(unsigned char r, unsigned char g, unsigned char b);

public:
	void CreateAnimation();
	void AddAnimation(const std::string& SequenceName, bool Loop = true,
		float PlayTime = 1.f, float PlayScale = 1.f,
		bool Reverse = false);
	void SetPlayTime(const std::string& Name, float PlayTime);
	void SetPlayScale(const std::string& Name, float PlayScale);
	void SetPlayLoop(const std::string& Name, bool Loop);
	void SetPlayReverse(const std::string& Name, bool Reverse);
	void SetCurrentAnimation(std::string& Name);
	void ChangeAnimation(const std::string& Name);
	bool CheckCurrentAnimation(const std::string& Name);


public:
	void MoveDir(const Vector2& Dir);
	void Move(const Vector2& MoveValue);
	void Move(float Angle);



public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	void SaveFullPath(const char* FullPath);
	void LoadFullPath(const char* FullPath);
	void SaveFileName(const char* FileName, const std::string& PathName);
	void LoadFileName(const char* FileName, const std::string& PathName);



private:
	void CheckMoveRight();
	void CheckMoveLeft();


public:
	template <typename T>
	void SetEndFunction(const std::string& Name, T* Obj, void(T::* Func)())
	{
		if (m_Animation)
			m_Animation->SetEndFunction<T>(Name, Obj, Func);
	}

	template <typename T>
	void SetCurrentAnimationEndFunction(T* Obj, void(T::* Func)())
	{
		if (m_Animation)
			m_Animation->SetCurrentAnimationEndFunction<T>(Obj, Func);
	}

	template <typename T>
	void AddNotify(const std::string& Name, int Frame, T* Obj, void(T::* Func)())
	{
		if (m_Animation)
			m_Animation->AddNotify<T>(Name, Frame, Obj, Func);
	}

	template <typename T>
	T* AddCollider(const std::string& Name)
	{
		T* Collider = new T;

		Collider->SetName(Name);
		Collider->m_Owner = this;
		Collider->m_Scene = m_Scene;

		if (!Collider->Init())
		{
			SAFE_DELETE(Collider);
			return nullptr;
		}

		m_ColliderList.push_back(Collider);

		return Collider;
	}

	CWidgetComponent* FindWidgetComponent(const std::string& Name)
	{
		auto	iter = m_WidgetComponentList.begin();
		auto	iterEnd = m_WidgetComponentList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->GetName() == Name)
				return *iter;
		}

		return nullptr;
	}

	template <typename T>
	CWidgetComponent* CreateWidgetComponent(const std::string& Name)
	{
		CWidgetComponent* Widget = FindWidgetComponent(Name);

		if (Widget)
			return Widget;

		Widget = new CWidgetComponent;

		Widget->m_Owner = this;
		Widget->m_Scene = m_Scene;
		Widget->SetName(Name);

		if (!Widget->Init())
		{
			SAFE_DELETE(Widget);
			return nullptr;
		}

		Widget->CreateWidget<T>(Name);

		m_WidgetComponentList.push_back(Widget);

		return Widget;
	}
};

