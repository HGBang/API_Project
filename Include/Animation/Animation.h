#pragma once
#include"AnimationInfo.h"
#include "../GameInfo.h"

class CAnimation
{
	friend class CGameObject;

private:
	CAnimation();
	~CAnimation();

private:
	class CGameObject* m_Owner;
	class CScene* m_Scene;
	std::unordered_map<std::string, CAnimationInfo*>	m_mapAnimation;
	CAnimationInfo* m_CurrentAnimation;
	std::function<void()>	m_currentAnimationEndFunc;

public:
	void AddAnimation(const std::string& SequenceName, bool Loop = true,
		float PlayTime = 1.f, float PlayScale = 1.f, bool Reverse = false);
	void SetPlayTime(const std::string& Name, float PlayTime);
	void SetPlayScale(const std::string& Name, float PlayScale);
	void SetPlayLoop(const std::string& Name, bool Loop);
	void SetPlayReverse(const std::string& Name, float Reverse);
	void SetCurrentAnimation(std::string& Name);
	void ChangeAnimation(const std::string& Name);
	bool CheckCurrentAnimation(const std::string& Name);
	void Update(float DeltaTime);

private:
	 CAnimationInfo* FindInfo(const std::string& Name);

public:
	template <typename T>
	void SetEndFunction(const std::string& Name, T* Obj, void(T::* Func)())
	{
		CAnimationInfo* Info = FindInfo(Name);
		if (!Info)
			return;

		Info->SetEndFunction<T>(Obj, Func);

	
	}

	template <typename T>
	void AddNotify(const std::string& Name, int Frame, T* Obj, void(T::* Func)())
	{
		CAnimationInfo* Info = FindInfo(Name);
		if (!Info)
			return;

		Info->AddNotify<T>(Frame, Obj, Func);
	}

	template <typename T>
	void SetCurrentAnimationEndFunction(T* Obj, void(T::* Func)())
	{
		m_currentAnimationEndFunc = std::bind(Func, Obj);
	}
};

