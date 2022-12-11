#pragma once
#include "jsEventobject.h"

namespace js
{
	class ItemObject : public EventObject
	{
	public:
		ItemObject();
		virtual ~ItemObject();
		void Initialize();
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void SetIndex(UINT index);
		void Active(Pos pos, int index);
		void InActive();

		void PickUp();

	private:
		Event	mOnTrigger;

		// 아틀라스 이미지 설정 값
		UINT	mIndex;
		// 이미지 LT 좌표
		UINT	mX;
		UINT	mY;
	};
}