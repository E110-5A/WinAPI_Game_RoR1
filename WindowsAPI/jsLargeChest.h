#pragma once
#include "jsChest.h"

namespace js
{
	class ItemObject;
	class LargeChest : public Chest
	{
	public:
		LargeChest();
		LargeChest(Pos pos);
		virtual ~LargeChest();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;
		
		virtual void Trigger();
	};
}