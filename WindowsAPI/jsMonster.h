#pragma once
#include "jsGameObject.h"

namespace js
{
	class Image;
	class Monster : public GameObject
	{
	public:
		Monster();
		~Monster();
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

	private:
		Image* mImage;
	};
}
