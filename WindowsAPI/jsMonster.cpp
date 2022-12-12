#include "jsMonster.h"

// 매니저
#include "jsCamera.h"
// 리소스
#include "jsResources.h"
#include "jsImage.h"

// 컴포넌트
#include "jsCollider.h"
#include "jsAnimator.h"
#include "jsRigidbody.h"

// 오브젝트
#include "jsPlayerProjectile.h"

namespace js
{
	Monster::Monster()
		: mImage(nullptr)
	{
	}
	Monster::Monster(Pos pos)
		: mImage(nullptr)
	{
	}
	Monster::~Monster()
	{
	}

	void Monster::Initialize()
	{
		SetType(eColliderLayer::Monster);
	}
	void Monster::Tick()
	{
	}
	void Monster::Render(HDC hdc)
	{
	}

	

	void Monster::OnCollisionEnter(Collider* other)
	{
	}
	void Monster::OnCollisionStay(Collider* other)
	{
	}
	void Monster::OnCollisionExit(Collider* other)
	{
	}

	// damage, stagger, power
	void Monster::SelfHit(GameObject* attaker, float damage, eStagger stagger, float power)
	{
		SelfDamaged(damage);
		SelfKnockBack(attaker->GetDir().x, stagger, power);
	}

	// damage
	void Monster::SelfDamaged(float damage)
	{
		// 방어력 계산해서 피 까기
		float finalDamage = damage - mMonsterHealth.defance;

		// 최소 피해량
		if (1 > damage - mMonsterHealth.defance)
			finalDamage = 1;
		
		mMonsterHealth.curHP -= finalDamage;
	}

	//stagger, power
	void Monster::SelfKnockBack(float dir, eStagger stagger, float power)
	{
		Vector2 knockBack = mRigidbody->GetVelocity();
		knockBack.x = dir * power;
		mRigidbody->SetVelocity(knockBack);

		// 경우에 따라서 SelfStun 호출
		if (stagger >= mMonsterResistance)
			SelfStun(power);
	}

	// power
	void Monster::SelfStun(float power)
	{
		// power에 따라서 기절시간이 달라짐
	}
}