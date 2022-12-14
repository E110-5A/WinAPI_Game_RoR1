#pragma once
#include "jsGameObject.h"
namespace js
{
	class Image;
	class tempGround : public GameObject
	{
	public:
		tempGround();
		~tempGround();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetImage(const std::wstring& key, const std::wstring& fileName);

	private:
		Image* mImage;
		std::wstring mImageName;
	};
}
