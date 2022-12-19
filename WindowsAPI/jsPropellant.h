#pragma once
#include "jsEventObject.h"

namespace js
{
	class Propellant : public EventObject
	{
	public:
		Propellant();
		Propellant(Pos pos);
		virtual ~Propellant();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void Push();

	private:

	};
}