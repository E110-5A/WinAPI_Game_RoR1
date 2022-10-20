#pragma once
#include "Common.h"

namespace js
{
	class jsApplication
	{
	public:
		static jsApplication& GetInstance()
		{
			static jsApplication m_Instance;
			return m_Instance;
		}

		void Initialize(WindowData _data);
		void Tick();

	private:
		jsApplication();
		~jsApplication();
	private:
		
		WindowData				m_WindowData;
	};
}


