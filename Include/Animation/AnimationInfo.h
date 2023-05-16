#pragma once

#include "../GameInfo.h"

struct AnimationNotify
{
	int		Frame;
	bool	Call;
	std::function<void()>	Function;

	AnimationNotify() :
		Frame(0),
		Call(false)
	{
	}
};

/*
애니메이션 시퀀스를 하나 가지고 있으면서 해당 애니메이션을 총 몇초에 걸쳐서 한번
재생을 할것인지, 이 애니메이션이 계속 반복해서 재생하는지 등을 정의해두는 객체이다.
*/
class CAnimationInfo
{
	friend class CAnimation;
	friend class CGameObject;

private:
	CAnimationInfo();
	~CAnimationInfo();

private:
	CSharedPtr<class CAnimationSequence>	m_Sequence;
	int				m_Frame;	// 현재 애니메이션이 동작되는 프레임.
	float			m_Time;		// 애니메이션 프레임을 증가시켜주기 위한 시간값.
	float			m_FrameTime;	// 한 프레임이 증가하기 위한 시간.
	float			m_PlayTime;		// 모션 한번이 동작되기 위한 시간.
	float			m_PlayScale;	// 재생속도 배율.
	bool			m_Loop;			// 반복해서 재생해야 하는지 여부.
	bool			m_Reverse;		// 역재생 여부.
	std::function<void()>		m_EndFunction;	// 애니메이션이 끝날때마다 호출될 함수 등록.
	std::vector<AnimationNotify*>	m_vecNotify;

public:
	template <typename T>
	void SetEndFunction(T* Obj, void(T::* Func)())
	{
		m_EndFunction = std::bind(Func, Obj);
	}

	template <typename T>
	void AddNotify(int Frame, T* Obj, void(T::* Func)())
	{
		AnimationNotify* Notify = new AnimationNotify;

		Notify->Frame = Frame;
		Notify->Function = std::bind(Func, Obj);

		m_vecNotify.push_back(Notify);
	}
};

