#include "jsGameObject.h"
#include "jsComponent.h"
#include "jsTime.h"

namespace js
{
	GameObject::GameObject()
		: mType(eColliderLayer::Default)
		, mPos(Vector2::Zero)
		, mScale(Vector2::One)
		, mDir(Vector2::Right)
		, mDead(false)
		, mBeDeath(false)
		, mDeathTime(-10.f)
		, mAble(true)
	{
	}

	GameObject::GameObject(Pos pos)
		: mType(eColliderLayer::Default)
		, mPos(pos)
		, mScale(Vector2::One)
		, mDir(Vector2::Right)
		, mDead(false)
		, mBeDeath(false)
		, mDeathTime(-10.f)
		, mAble(true)
	{
	}

	GameObject::~GameObject()
	{
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;
			delete component;
			component = nullptr;
		}
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Tick()
	{
		DeathLoop();

		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;
			
			component->Tick();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;
			
			component->Render(hdc);
		}
	}
	void GameObject::OnCollisionEnter(Collider* other)
	{
	}
	void GameObject::OnCollisionStay(Collider* other)
	{
	}
	void GameObject::OnCollisionExit(Collider* other)
	{
	}
	void GameObject::SetDeath(float time)
	{
		if (0.f >= mDeathTime)
		{
		mDeathTime = time; 
		mBeDeath = true;
		}
	}
	void GameObject::DeathLoop()
	{
		if (true == mBeDeath)
		{
			mDeathTime -= Time::GetDeltaTime();
			if (0 > mDeathTime)
			{
				Death();
			}
		}
	}
	void GameObject::AddComponent(Component* component)
	{
		if (nullptr == component)
			return;

		mComponents.push_back(component);
		component->mOwner = this;
	}
}