#include "jsPanel.h"
#include "jsImage.h"

namespace js
{
	Panel::Panel(eUIType type)
		: UIBase(type)
	{
	}
	Panel::~Panel()
	{
	}

	void Panel::OnInit()
	{
	}

	void Panel::OnActive()
	{
	}

	void Panel::OnInActive()
	{
	}

	void Panel::OnTick()
	{
	}

	void Panel::OnRender(HDC hdc)
	{
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
			, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
	}

	void Panel::OnClear()
	{
	}

}