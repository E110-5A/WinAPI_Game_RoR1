#pragma once
#include "jsScene.h"
#include "jsTilePalette.h"

namespace js
{
	class MapToolScene : public Scene
	{
	public:
		MapToolScene();
		~MapToolScene();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		virtual void Enter() override;		// �ش� ������ ����� �� ȣ��
		virtual void Exit() override;

		void SaveTilePalette();
		void LoadTilePalette();
		void LoadTilePalette(const std::wstring& path);

		// ���� �������� ������Ʈ ���� ������ �ϼ��Ұ�
		void SaveObjectPalette();
		void LoadObjectPalette();
		void LoadObjectPalette(const std::wstring& path);

		Image* GetAtlasImage() { return mTilePalette->GetImage(); }
		void SetTileIndex(UINT index) { mTileIndex = index; }
		UINT GetTileIndex() { return mTileIndex; }

		// ������Ʈ �������� ��� �߰�


	private:
		TilePalette* mTilePalette;

		UINT mTileIndex;
	};
}