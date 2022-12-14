#include "jsCreature.h"

// component
#include "jsCollider.h"
#include "jsAnimator.h"
#include "jsRigidbody.h"


// resource
#include "jsResources.h"

// object
#include "jsObject.h"
#include "jsFoot.h"
#include "jsHead.h"

namespace js
{
	Creature::Creature()
		: mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mHeadCollider(nullptr)
		, mBodyCollider(nullptr)
		, mFootCollider(nullptr)
		, mHealthStat{}
		, mOffenceStat{}
		, mUtilityStat{}
		, mResistance{}
		, mFootObject(nullptr)
		, mHeadObject(nullptr)
		, mSpriteImage(nullptr)
	{
	}
	Creature::Creature(Pos pos)
		: mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mHeadCollider(nullptr)
		, mBodyCollider(nullptr)
		, mFootCollider(nullptr)
		, mHealthStat{}
		, mOffenceStat{}
		, mUtilityStat{}
		, mResistance{}
		, mFootObject(nullptr)
		, mHeadObject(nullptr)
		, mSpriteImage(nullptr)
	{
	}
	Creature::~Creature()
	{
		if (nullptr != mHealthStat)
			delete mHealthStat;

		if (nullptr != mOffenceStat)
			delete mOffenceStat;

		if (nullptr != mUtilityStat)
			delete mUtilityStat;		
	}

	void Creature::Initialize()
	{
		InitComponent();
	}

	void Creature::Tick()
	{
		GameObject::Tick();
		mFootObject->Tick();
		mHeadObject->Tick();
	}
	void Creature::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		mFootObject->Render(hdc);
		mHeadObject->Render(hdc);
	}

	void Creature::OnCollisionEnter(Collider* other)
	{
	}
	void Creature::OnCollisionStay(Collider* other)
	{
	}
	void Creature::OnCollisionExit(Collider* other)
	{
	}

	void Creature::InitComponent()
	{
		mAnimator = AddComponent<Animator>();
		mRigidbody = AddComponent<Rigidbody>();

		// body
		mBodyCollider = AddComponent<Collider>();
		// foot
		mFootObject = new Foot();
		mFootObject->SetType(eColliderLayer::Foot);
		mFootObject->SetOwner(this);
		mFootCollider = mFootObject->GetComponent<Collider>();
		// head
		mHeadObject = new Head();
		mHeadObject->SetType(eColliderLayer::Head);
		mHeadObject->SetOwner(this);
		mHeadCollider = mHeadObject->GetComponent<Collider>();
	}

	void Creature::AddComponentScene()
	{
		Scene* scene = SceneManager::GetPlayScene();
		scene->AddGameObject(mFootObject, eColliderLayer::Foot);
		scene->AddGameObject(mHeadObject, eColliderLayer::Head);
	}

	void Creature::BodyCollision(GameObject* other)
	{
		// ???? ???? ???? ??????
		Vector2 targetPos = other->GetPos();
		Vector2 myPos = GetPos();

		// ???????? ?? ???? ????
		Vector2 wallLocationDir = myPos - targetPos;
		if (0 < wallLocationDir.x)					// x?? ?????? ???? ???????? ?? ????
			wallLocationDir = Vector2::Left;
		else
			wallLocationDir = Vector2::Right;

		// ???? ???? ???? x ?????? 0???? ??????
		if (wallLocationDir == mDir)
		{
			mRigidbody->EraseVelocity(wallLocationDir, mRigidbody->GetVelocity());
		}
	}

	void Creature::SelfHit(GameObject* attaker, float damage, eStagger stagger, float power)
	{
		SelfDamaged(damage);
		SelfKnockBack(attaker->GetDir().x, stagger, power);
	}
	void Creature::SelfDamaged(float damage)
	{
		// ?????? ???????? ?? ????
		float finalDamage = damage - mHealthStat->defance;

		// ???? ??????
		if (1 > damage - mHealthStat->defance)
			finalDamage = 1;

		mHealthStat->curHP -= finalDamage;
	}
	void Creature::SelfKnockBack(float dir, eStagger stagger, float power)
	{
		// ???????? ?????????? ???? ????
		if (stagger >= mResistance)		// ?????? 0???? ???????? 0???? ????
		{
			// ????
			Vector2 knockBack = mRigidbody->GetVelocity();
			knockBack.x = dir * power * 2.5f;
			mRigidbody->AddForce(knockBack);

			// ???????? ???? ????
			if (eStagger::Heave == stagger)
				SelfStun(power);
		}
	}
	// ????
	void Creature::SelfStun(float power)
	{
	}
}