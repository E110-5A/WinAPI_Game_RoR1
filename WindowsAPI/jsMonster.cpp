#include "jsMonster.h"

// 매니저
#include "jsApplication.h"
#include "jsCamera.h"
#include "jsGameManager.h"
#include "jsInput.h"
#include "jsTime.h"

// 리소스
#include "jsResources.h"
#include "jsImage.h"
#include "jsSound.h"

// 컴포넌트
#include "jsCollider.h"
#include "jsAnimator.h"
#include "jsRigidbody.h"

// 오브젝트
#include "jsPlayerProjectile.h"
#include "jsPlatform.h"
#include "jsPlayer.h"
#include "jsMonsterAttack.h"

namespace js
{
	Monster::Monster()
	{
		Initialize();
	}
	Monster::Monster(Pos pos)
	{
		Initialize();
		SetPos(pos);
	}
	Monster::~Monster()
	{
		delete mSkillInfo;
	}

	void Monster::Initialize()
	{
		// 기본 세팅
		Creature::Initialize();
		SetImage(Resources::Load<Image>(L"Monster", L"..\\Resources\\Image\\Enemy\\monster.bmp"));
		mImpAttackSound = Resources::Load<Sound>(L"ImpAttackSound", L"..\\Resources\\Sound\\Monster\\ImpShoot1.wav");
		mImpDeadSound = Resources::Load<Sound>(L"ImpDeadSound", L"..\\Resources\\Sound\\Monster\\ImpDeath.wav");
		SetScale(Vector2::One * 2);
		SetAnimator();

		// 공격기능 세팅
		mSkillInfo = new MonsterSkillInfo();
		mDamageObj = new MonsterAttack(this);
		mTarget = GameManager::GetPlayer();

		
		// 대기상태
		SetAble(false);
	}

	void Monster::SetAnimator()
	{
		// Imp Aniamtion
		mAnimator->CreateAnimation(L"ImpIdleR", mSpriteImage, Pos(0.f, 0.f), Size(17.f, 21.f)
			, Vector2(0.f, 0.f), 1, 0.1f);
		mAnimator->CreateAnimation(L"ImpIdleL", mSpriteImage, Pos(0.f, 21.f), Size(17.f, 21.f)
			, Vector2(0.f, 0.f), 1, 0.1f);

		mAnimator->CreateAnimation(L"ImpMoveR", mSpriteImage, Pos(0.f, 42.f), Size(18.0f, 25.f)
			, Vector2(0.f, 0.f), 6, 0.1f);
		mAnimator->CreateAnimation(L"ImpMoveL", mSpriteImage, Pos(0.f, 67.f), Size(18.0f, 25.f)
			, Vector2(0.f, 0.f), 6, 0.1f);

		mAnimator->CreateAnimation(L"ImpTeleportR", mSpriteImage, Pos(0.f, 92.f), Size(17.f, 21.f)
			, Vector2(0.f, 0.f), 3, 0.1f);
		mAnimator->CreateAnimation(L"ImpTeleportL", mSpriteImage, Pos(0.f, 113.f), Size(17.f, 21.f)
			, Vector2(0.f, 0.f), 3, 0.1f);

		mAnimator->CreateAnimation(L"ImpAttackR", mSpriteImage, Pos(0.f, 134.f), Size(33.f, 21.f)
			, Vector2(-7.f, 0.f), 11, 0.1f);
		mAnimator->CreateAnimation(L"ImpAttackL", mSpriteImage, Pos(0.f, 155.f), Size(33.f, 21.f)
			, Vector2(-10.f, 0.f), 11, 0.1f);

		mAnimator->CreateAnimation(L"ImpDeathR", mSpriteImage, Pos(0.f, 176.f), Size(26.0f, 21.f)
			, Vector2(-5.f, 0.f), 8, 0.1f);
		mAnimator->CreateAnimation(L"ImpDeathL", mSpriteImage, Pos(0.f, 197.f), Size(26.0f, 21.f)
			, Vector2(-5.f, 0.f), 8, 0.1f);


		// Parent Animation
		mAnimator->CreateAnimation(L"ParentSpawn", mSpriteImage, Pos(0.f, 92.f), Size(17.f, 21.f)
			, Vector2(0.f, 0.f), 3, 0.1f);

		mAnimator->CreateAnimation(L"ParentIdleR", mSpriteImage, Pos(0.f, 0.f), Size(17.f, 21.f)
			, Vector2(0.f, 0.f), 1, 0.1f);
		mAnimator->CreateAnimation(L"ParentIdleL", mSpriteImage, Pos(0.f, 21.f), Size(17.f, 21.f)
			, Vector2(0.f, 0.f), 1, 0.1f);

		mAnimator->CreateAnimation(L"ParentMoveR", mSpriteImage, Pos(0.f, 42.f), Size(18.0f, 25.f)
			, Vector2(0.f, 0.f), 6, 0.1f);
		mAnimator->CreateAnimation(L"ParentMoveL", mSpriteImage, Pos(0.f, 67.f), Size(18.0f, 25.f)
			, Vector2(0.f, 0.f), 6, 0.1f);
		mAnimator->CreateAnimation(L"ParentAttackR", mSpriteImage, Pos(0.f, 134.f), Size(33.f, 21.f)
			, Vector2(-7.f, 0.f), 11, 0.1f);
		mAnimator->CreateAnimation(L"ParentAttackL", mSpriteImage, Pos(0.f, 155.f), Size(33.f, 21.f)
			, Vector2(-10.f, 0.f), 11, 0.1f);

		mAnimator->CreateAnimation(L"ParentDeathR", mSpriteImage, Pos(0.f, 176.f), Size(26.0f, 21.f)
			, Vector2(-5.f, 0.f), 8, 0.1f);
		mAnimator->CreateAnimation(L"ParentDeathL", mSpriteImage, Pos(0.f, 197.f), Size(26.0f, 21.f)
			, Vector2(-5.f, 0.f), 8, 0.1f);


		/*mAnimator->GetEndEvents(L"ImpMoveR") = std::bind(&Monster::ReturnIdle, this);
		mAnimator->GetEndEvents(L"ImpMoveR") = std::bind(&Monster::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"ImpAttackR") = std::bind(&Monster::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"ImpAttackR") = std::bind(&Monster::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"ParentMoveR") = std::bind(&Monster::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"ParentMoveR") = std::bind(&Monster::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"ParentAttackR") = std::bind(&Monster::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"ParentAttackR") = std::bind(&Monster::ReturnIdle, this);*/
		mAnimator->GetEndEvents(L"ImpDeathR") = std::bind(&Monster::DeathAnimation, this);
		mAnimator->GetEndEvents(L"ImpDeathL") = std::bind(&Monster::DeathAnimation, this);
		mAnimator->GetEndEvents(L"ParentDeathR") = std::bind(&Monster::DeathAnimation, this);
		mAnimator->GetEndEvents(L"ParentDeathL") = std::bind(&Monster::DeathAnimation, this);
	}

	void Monster::ReturnIdle()
	{
		Vector2 dir = GetDir();
		if (dir == Vector2::Right)
			mAnimator->Play(L"ImpIdleR");
		else
			mAnimator->Play(L"ImpIdleL");
	}

	void Monster::DeathAnimation()
	{
		// 비활성화
		SetAble(false);
	}

	void Monster::InitImp()
	{
		// stat
		SetMonsterStat(70.0f, 0, 0, 13, 1, 100, 16.0f);

		// collider
		mBodyCollider->SetSize(Size(20.f, 25.f) * GetScale());
		mBodyCollider->SetOffset(Vector2(9.f, 14.f));

		mFootCollider->SetSize(Size(15, 5) * GetScale());
		mFootCollider->SetOffset(Vector2(8, 42.f));

		mHeadCollider->SetSize(Size(15, 5) * GetScale());
		mHeadCollider->SetOffset(Vector2(8, -10.f));
		mAnimator->Play(L"ImpTeleportR", false);

		// skill
		InitSkill(mOffenceStat->damage, 0.6f, 2.0f);
		mDropExp = 2;
	}

	void Monster::InitParent()
	{
		// 충돌체
		SetMonsterStat(315.0f, 0, 0, 15, 1, 100, 15.0f);
		
		// collider
		mBodyCollider->SetSize(Size(20.f, 25.f) * GetScale());
		mBodyCollider->SetOffset(Vector2(8.f, 13.f));

		mFootCollider->SetSize(Size(15, 5) * GetScale());
		mFootCollider->SetOffset(Vector2(8, 38.f));

		mHeadCollider->SetSize(Size(15, 5) * GetScale());
		mHeadCollider->SetOffset(Vector2(8, 18.f));

		mAnimator->Play(L"ImpTeleportR", false);

		// skill
		InitSkill(mOffenceStat->damage, 0.6f, 2.0f);
		mDropExp = 3;
	}

	void Monster::InitSkill(float damage, float castDelay, float coolDown)
	{
		mSkillInfo->damage = damage;
		mSkillInfo->castDelay = castDelay;
		mSkillInfo->castDelayTime = 0.0f;
		mSkillInfo->coolDown = coolDown;
		mSkillInfo->coolDownTime = 0.0f;
		mSkillInfo->maxCount = 1;
		mSkillInfo->curCount = 0;
		mSkillInfo->active = false;
		mSkillInfo->run = false;
		mSkillInfo->finish = false;
	}

	void Monster::Spawn(Platform* spawnPlatform)
	{
		// 활성화
		SetAble(true);
		
		// 몬스터 타입 설정
		/*int spawnType = (rand() % (int)eMonsterType::End);
		mMonsterType = (eMonsterType)spawnType;*/

		// 디버깅용
		mMonsterType = eMonsterType::Imp;
		// 몬스터 초기화
		switch (mMonsterType)
		{
		case eMonsterType::Imp:
		{
			InitImp();
			mEyesight = mBodyCollider->GetSize().x * 6;
			mAnimator->Play(L"ImpIdleR");
		}
		break;
		case eMonsterType::Parent:
		{
			InitParent();
			mEyesight = mBodyCollider->GetSize().x * 6;
			mAnimator->Play(L"ParentIdleR");
		}
		break;
		}
		mState = eMonsterState::Stay;
	}


	void Monster::Tick()
	{
		if (false == IsAble())
			return;

		Creature::Tick();
		Cooldown();
		SkillProcess();
		DeadCheck();
		switch (mState)
		{
		case eMonsterState::Stay:
		{
			Stay();
		}
		break;
		case eMonsterState::Chase:
		{
			Chase();
		}
		break;
		case eMonsterState::Skill:
		{
			Attack();
		}
		break;
		case eMonsterState::Stun:
		{
			Stun();
		}
		break;
		case eMonsterState::Death:
		{
			Death();
		}
		break;
		}
	}

	void Monster::Render(HDC hdc)
	{
		if (false == IsAble())
			return;
		
		Creature::Render(hdc);

		//HBRUSH tr = Application::GetInstance().GetBrush(eBrushColor::Transparent);
		//Brush brush(hdc, tr);
		//Vector2 pos = GetPos();
		//Vector2 size = mBodyCollider->GetSize();

		//Rectangle(hdc, pos.x - mEyesight / 2, pos.y, pos.x + mEyesight / 2, pos.y + size.y);

	}

	void Monster::Stay()
	{
		// 대상과 나 사이의 거리
		float targetDistance = fabs((GetPos().x - mTarget->GetPos().x));

		// Chase | mEyesight / 2
		if (targetDistance <= mEyesight / 2)
		{
			mState = eMonsterState::Chase;
			switch (mMonsterType)
			{
			case eMonsterType::Imp:
			{
				if (Vector2::Right == GetDir())
				{
					mAnimator->Play(L"ImpMoveR");
				}
				else
				{
					mAnimator->Play(L"ImpMoveL");
				}
			}
			break;
			case eMonsterType::Parent:
			{
				if (Vector2::Right == GetDir())
				{
					mAnimator->Play(L"ParentMoveR");
				}
				else
				{
					mAnimator->Play(L"ParentMoveL");
				}
			}
			break;
			}
		}

		// Attack | mOffenceStat->range
		if (targetDistance <= mOffenceStat->range - 50)
		{
			mState = eMonsterState::Skill;
			switch (mMonsterType)
			{
			case eMonsterType::Imp:
			{
				if (Vector2::Right == GetDir())
				{
					mAnimator->Play(L"ImpAttackR");
				}
				else
				{
					mAnimator->Play(L"ImpAttackL");
				}
			}
			break;
			case eMonsterType::Parent:
			{
				if (Vector2::Right == GetDir())
				{
					mAnimator->Play(L"ParentAttackR");
				}
				else
				{
					mAnimator->Play(L"ParentAttackL");
				}
			}
			break;
			}
		}
	}

	void Monster::Chase()
	{
		// 대상과 나 사이의 거리
		float targetDistance = (GetPos().x - mTarget->GetPos().x);
		// 이동방향 찾기
		if (0 < targetDistance)					// x가 양수일 경우 벽위치는 내 왼쪽
			SetDir(Vector2::Left);
		else
			SetDir(Vector2::Right);

		targetDistance = fabs(targetDistance);
		// 플레이어 방향으로 이동
		mRigidbody->AddForce(GetDir() * 10 * mUtilityStat->moveSpeed * Time::GetDeltaTime());
		


		// 상태변경 조건
		// Attack | mOffenceStat->range
		if (targetDistance <= mOffenceStat->range - 50)
		{
			mState = eMonsterState::Skill;
			switch (mMonsterType)
			{
			case eMonsterType::Imp:
			{
				if (Vector2::Right == GetDir())
				{
					mAnimator->Play(L"ImpAttackR");
				}
				else
				{
					mAnimator->Play(L"ImpAttackL");
				}
			}
			break;
			case eMonsterType::Parent:
			{
				if (Vector2::Right == GetDir())
				{
					mAnimator->Play(L"ParentAttackR");
				}
				else
				{
					mAnimator->Play(L"ParentAttackL");
				}
			}
			break;
			}
		}
	}


	void Monster::Attack()
	{
		if (false == mSkillInfo->active)
			mSkillInfo->run = true;

		if (true == mSkillInfo->finish)
		{
			mState = eMonsterState::Stay;
			mSkillInfo->finish = false;
			switch (mMonsterType)
			{
			case eMonsterType::Imp:
			{
				if (Vector2::Right == GetDir())
				{
					mAnimator->Play(L"ImpIdleR");
				}
				else
				{
					mAnimator->Play(L"ImpIdleL");
				}
			}
			break;
			case eMonsterType::Parent:
			{
				if (Vector2::Right == GetDir())
				{
					mAnimator->Play(L"ParentIdleR");
				}
				else
				{
					mAnimator->Play(L"ParentIdleL");
				}
			}
			break;
			}
		}
	}

	void Monster::Stun()
	{
		// 시간이 지나면 Stay로 상태 변경
	}

	void Monster::Death()
	{
		
		// 경험치 드랍
		int bonusExp = (*GameManager::GetDifficulty()) / 2;
		GameManager::AddExp(mDropExp + bonusExp);

		
	}

	void Monster::Cooldown()
	{
		if (true == mSkillInfo->active)
		{
			mSkillInfo->coolDownTime += Time::GetDeltaTime();
			if (mSkillInfo->coolDownTime > mSkillInfo->coolDown)
			{
				mSkillInfo->active = false;
				mSkillInfo->coolDownTime = 0.0f;
			}
		}
	}

	void Monster::SkillProcess()
	{
		if (true == mSkillInfo->run)
		{
			mSkillInfo->castDelayTime += Time::GetDeltaTime();

			// 스킬 카운트가 유효하다면 반복
			if (mSkillInfo->curCount < mSkillInfo->maxCount)
			{
				// 시전 준비가 되면 발사
				if (mSkillInfo->castDelayTime >= mSkillInfo->castDelay)
				{
					Skill();
					mSkillInfo->castDelayTime = 0.0f;
					++mSkillInfo->curCount;
				}
			}
			else
			{
				mSkillInfo->curCount = 0;
				mSkillInfo->run = false;
				mSkillInfo->finish = true;
			}
		}
	}

	void Monster::Skill()
	{
		mImpAttackSound->Stop(true);
		mImpAttackSound->Play(false);
		mDamageObj->Active();
		mSkillInfo->active = true;
		mSkillInfo->run = true;
	}

	void Monster::DeadCheck()
	{
		if (0 >= mHealthStat->curHP)
		{
			mState = eMonsterState::Death;
			mImpDeadSound->Stop(true);
			mImpDeadSound->Play(false);
			// 애니메이션 재생
			switch (mMonsterType)
			{
			case eMonsterType::Imp:
			{
				if (Vector2::Right == GetDir())
					mAnimator->Play(L"ImpDeathR", false);
				else
					mAnimator->Play(L"ImpDeathL", false);
			}
			break;
			case eMonsterType::Parent:
			{
				if (Vector2::Right == GetDir())
					mAnimator->Play(L"ParentDeathR", false);
				else
					mAnimator->Play(L"ParentDeathL", false);
			}
			break;
			}
		}
	}

	void Monster::AddMonster()
	{
		SetAble(false);
		Scene* scene = SceneManager::GetPlayScene();
		// 씬에 추가
		scene->AddGameObject(this, eColliderLayer::Monster);
		scene->AddGameObject(mDamageObj, eColliderLayer::Projectile);
	}
	
	void Monster::OnCollisionEnter(Collider* other)
	{
		GameObject* collisionObj = other->GetOwner();
		eColliderLayer type = collisionObj->GetType();

		// 벽에 닿음
		if (type == eColliderLayer::Platform)
		{
			// 나아가지 못하게 막기
			BodyCollision(this);
		}
		// 피해받으면 추격상태로 변경
		if (type == eColliderLayer::Projectile)
		{
			PlayerProjectile* projectile = dynamic_cast<PlayerProjectile*>(collisionObj);
			if (nullptr != projectile)
			{
				mState = eMonsterState::Chase;

			}
		}
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
		float finalDamage = damage - mHealthStat->defance;

		// 최소 피해량
		if (1 > damage - mHealthStat->defance)
			finalDamage = 1;
		
		mHealthStat->curHP -= finalDamage;
	}

	//stagger, power
	void Monster::SelfKnockBack(float dir, eStagger stagger, float power)
	{
		// 저항력이 관통력보다 낮은 경우
		if (stagger >= mResistance)		// 관통이 0이고 저항력이 0이면 넉백
		{
			// 넉백
			Vector2 knockBack = mRigidbody->GetVelocity();
			knockBack.x = dir * power * 2.5f;
			mRigidbody->SetVelocity(knockBack);

			// 관통력이 쌔면 기절
			if (eStagger::Heave == stagger)
				SelfStun(power);
		}
	}

	// power
	void Monster::SelfStun(float power)
	{
		// power에 따라서 기절시간이 달라짐
	}
}