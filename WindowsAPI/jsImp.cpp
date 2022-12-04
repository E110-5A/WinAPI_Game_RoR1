#include "jsImp.h"

// �Ŵ���
#include "jsInput.h"

// ���ҽ�
#include "jsResources.h"
#include "jsImage.h"

// ������Ʈ
#include "jsAnimator.h"
#include "jsCollider.h"
#include "jsRigidbody.h"

namespace js
{
    Imp::Imp()
    {
        SetPos(Vector2(600.0f, 400.0f));
        SetScale(Vector2::One);
        SetDir(Vector2::Right);
        Initialize();
    }
    Imp::Imp(Pos pos)
    {
        SetPos(pos);
        SetScale(Vector2::One * 2);
        SetDir(Vector2::Right);
        Initialize();
    }
    Imp::~Imp()
    {
    }

    void Imp::Initialize()
    {
        InitAnimator();
        InitCollider();
        InitRigidbody();
        InitStat();
		mAnimator->Play(L"ImpIdleL");
    }
    void Imp::InitCollider()
    {
        mCollider = AddComponent<Collider>();
        mCollider->SetPos(GetPos());
        mCollider->SetSize(Size(20.f,25.f)* GetScale());
        mCollider->SetOffset(Vector2(8.f, 13.f));
    }
    void Imp::InitAnimator()
    {
        if (nullptr == mImage)
        {
            mImage = Resources::Load<Image>
                (L"Imp", L"..\\Resources\\Image\\Enemy\\imp.bmp");
        }
        mAnimator = AddComponent<Animator>();

        mAnimator->CreateAnimation(L"ImpIdleR", mImage, Pos(0.f, 0.f), Size(17.f, 21.f)
            , Vector2(0.f, 0.f), 1, 0.1f);
        mAnimator->CreateAnimation(L"ImpIdleL", mImage, Pos(0.f, 21.f), Size(17.f, 21.f)
            , Vector2(0.f, 0.f), 1, 0.1f);

        mAnimator->CreateAnimation(L"ImpMoveR", mImage, Pos(0.f, 42.f), Size(18.0f, 25.f)
            , Vector2(0.f, 0.f), 6, 0.1f);
        mAnimator->CreateAnimation(L"ImpMoveL", mImage, Pos(0.f, 67.f), Size(18.0f, 25.f)
            , Vector2(0.f, 0.f), 6, 0.1f);

        mAnimator->CreateAnimation(L"ImpTeleportR", mImage, Pos(0.f, 92.f), Size(17.f, 21.f)
            , Vector2(0.f, 0.f), 3, 0.1f);
        mAnimator->CreateAnimation(L"ImpTeleportL", mImage, Pos(0.f, 113.f), Size(17.f, 21.f)
            , Vector2(0.f, 0.f), 3, 0.1f);

        mAnimator->CreateAnimation(L"ImpAttackR", mImage, Pos(0.f, 134.f), Size(33.f, 21.f)
            , Vector2(-7.f, 0.f), 11, 0.1f);
        mAnimator->CreateAnimation(L"ImpAttackL", mImage, Pos(0.f, 155.f), Size(33.f, 21.f)
            , Vector2(-10.f, 0.f), 11, 0.1f);

        mAnimator->CreateAnimation(L"ImpDeathR", mImage, Pos(0.f, 176.f), Size(26.0f, 21.f)
            , Vector2(-5.f, 0.f), 8, 0.1f);
        mAnimator->CreateAnimation(L"ImpDeathL", mImage, Pos(0.f, 197.f), Size(26.0f, 21.f)
            , Vector2(-5.f, 0.f), 8, 0.1f);

    }
    void Imp::InitRigidbody()
    {
        mRigidbody = AddComponent<Rigidbody>();
    }
    void Imp::InitStat()
    {
        mStat.maxHp = 310;
        mStat.curHp = 310;
        mStat.def = 0;
        mStat.moveSpeed = 16;
        mStat.att = 13;
    }

    void Imp::Tick()
    {
        GameObject::Tick();

        // ���ϸ��̼� �׽�Ʈ��
		if (KEY_DOWN(eKeyCode::L))
		{
			mAnimator->Play(L"ImpMoveR");
            SetDir(Vector2::Right);
		}
		if (KEY_DOWN(eKeyCode::J))
		{
			mAnimator->Play(L"ImpMoveL");
            SetDir(Vector2::Left);
		}
		if (KEY_DOWN(eKeyCode::U))
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"ImpTeleportR", false);
			else
				mAnimator->Play(L"ImpTeleportL", false);
		}
		if (KEY_DOWN(eKeyCode::O))
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"ImpAttackR", false);
			else
				mAnimator->Play(L"ImpAttackL", false);
		}
		if (KEY_DOWN(eKeyCode::P))
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"ImpDeathR", false);
			else
				mAnimator->Play(L"ImpDeathL", false);
		}
		if (KEY_UP(eKeyCode::L))
		{
			mAnimator->Play(L"ImpIdleR");
		}
		if (KEY_UP(eKeyCode::J))
		{
			mAnimator->Play(L"ImpIdleL");
		}
    }
    void Imp::Render(HDC hdc)
    {
        GameObject::Render(hdc);
    }
    void Imp::OnCollisionEnter(Collider* other)
    {
    }
    void Imp::OnCollisionStay(Collider* other)
    {
    }
    void Imp::OnCollisionExit(Collider* other)
    {
    }
}