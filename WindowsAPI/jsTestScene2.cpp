#include "jsTestScene2.h"
#include "jsApplication.h"

// manager
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsCollisionManager.h"
#include "jsCamera.h"
#include "jsGameManager.h"

// tool
#include "jsMapToolScene.h"

// ui
#include "jsUIManager.h"
#include "jsHUD.h"
#include "jsButton.h"
#include "jsBarUI.h"
#include "jsIcon.h"
#include "jsDifficultyHUD.h"

// obj
#include "jsPlayer.h"
#include "jsObject.h"
#include "jsPlayerProjectile.h"
#include "jsImp.h"
#include "jsSmallChest.h"
#include "jsLargeChest.h"
#include "jsGoldenChest.h"
#include "jsItemObject.h"
#include "jsDamageObject.h"

// env
#include "jsBGObj.h"
#include "jsPlatform.h"
#include "jsLadder.h"
#include "jsPropellant.h"

// component
#include "jsCollider.h"

namespace js
{
	TestScene2::TestScene2()
	{
	}

	TestScene2::~TestScene2()
	{
	}

	void TestScene2::Initialize()
	{
		// 윈도우 크기
		// 1280
		// 720

		// 맵 로딩
		TileLoadTest();
		// 배경 오브젝트
		InitBG();
		// 오브젝트 추가
		InitObject();
	}

	void TestScene2::Tick()
	{
		// 오브젝트 tick 을 호출한다.
		Scene::Tick();

		GameManager::Playing();
		// ESC 누를경우
		/*
		*  - 시간 진행 멈추기
		*  - 메뉴 UI 불러오기
		*
		*/
		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::Title);
		}
	}

	void TestScene2::Render(HDC hdc)
	{
		Scene::Render(hdc);
		//
		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"Test2 Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 5, 10, szFloat, strLen);
	}

	void TestScene2::TileLoadTest()
	{
		// SceneManager::LoadMap<MapToolScene>(L"..\\Resources\\Tile\\STGA\\stage1", eSceneType::MapTool);
	}

	void TestScene2::InitBG()
	{
		Platform* leftGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(0.0f, 384.0f));
		leftGround->SetColliderSize(Size(GRID_SIZE, GRID_SIZE * 5));
		leftGround->SetColliderOffset(Vector2(GRID_SIZE / 2, GRID_SIZE * 5 / 2));

		/*Platform* mainGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(64.0f, 640.0f));
		mainGround->SetColliderSize(Size(GRID_SIZE * 16, GRID_SIZE));
		mainGround->SetColliderOffset(Vector2(GRID_SIZE * 8, GRID_SIZE / 2));*/

		Platform* secondGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(128.0f, 512.0f));
		secondGround->SetColliderSize(Size(GRID_SIZE * 5, GRID_SIZE));
		secondGround->SetColliderOffset(Vector2(GRID_SIZE * 5 / 2, GRID_SIZE / 2));

		//Platform* thirdGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(702.0f, 448.0f));
		//thirdGround->SetColliderSize(Size(GRID_SIZE * 5, GRID_SIZE * 2));
		//thirdGround->SetColliderOffset(Vector2(GRID_SIZE * 5 / 2, GRID_SIZE * 2 / 2));

		Ladder* ladder = object::Instantiate<Ladder>(eColliderLayer::Ladder, Pos(256.0f, 512.0f));
		ladder->SetColliderSize(Size(GRID_SIZE, GRID_SIZE * 2));
		ladder->SetColliderOffset(Vector2(GRID_SIZE / 2, GRID_SIZE * 2 / 2));

		Propellant* propellant = object::Instantiate<Propellant>(eColliderLayer::Propellant, Pos(610, 550));
	}

	void TestScene2::InitObject()
	{
		// 플레이어 상호작용 테스트
		DamageObject* damageTest = object::Instantiate<DamageObject>(eColliderLayer::DamageObject, Pos(GRID_SIZE * 5, GRID_SIZE * 9));
	}

	void TestScene2::SetLayer()
	{
		CollisionManager::SetLayer(eColliderLayer::Platform, eColliderLayer::Head, true);
		CollisionManager::SetLayer(eColliderLayer::Platform, eColliderLayer::Foot, true);
		CollisionManager::SetLayer(eColliderLayer::Platform, eColliderLayer::Player, true);
		CollisionManager::SetLayer(eColliderLayer::Platform, eColliderLayer::Monster, true);

		CollisionManager::SetLayer(eColliderLayer::Ladder, eColliderLayer::Head, true);
		CollisionManager::SetLayer(eColliderLayer::Ladder, eColliderLayer::Foot, true);
		CollisionManager::SetLayer(eColliderLayer::Ladder, eColliderLayer::Player, true);

		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Propellant, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Chest, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Item, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::DamageObject, true);

		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Propellant, true);
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Projectile, true);
	}

	void TestScene2::SetUI()
	{
		// ui 추가
		UIManager::Push(eUIType::PlayerInfo);

		BarUI* hpBar = UIManager::GetUIInstant<BarUI>(eUIType::HpBar);
		hpBar->SetType(eBarType::HP);
		hpBar->SetHealth(GameManager::GetPlayerInfo()->stat->playerHealth);


		BarUI* expBar = UIManager::GetUIInstant<BarUI>(eUIType::ExpBar);
		expBar->SetType(eBarType::EXP);
		expBar->SetExp(GameManager::GetPlayerInfo());


		Player* player = GameManager::GetPlayer();
		Icon* z = UIManager::GetUIInstant<Icon>(eUIType::Z);
		z->SetSkillInfo(player->GetDubleTabInfo());
		Icon* x = UIManager::GetUIInstant<Icon>(eUIType::X);
		x->SetSkillInfo(player->GetFMJInfo());
		Icon* c = UIManager::GetUIInstant<Icon>(eUIType::C);
		c->SetSkillInfo(player->GetTacticalDiveInfo());
		Icon* v = UIManager::GetUIInstant<Icon>(eUIType::V);
		v->SetSkillInfo(player->GetSupressiveFireInfo());

		UIManager::Push(eUIType::Difficulty);

		DifficultyHUD* difficultyHud = UIManager::GetUIInstant<DifficultyHUD>(eUIType::DifficultyBar);
		difficultyHud->SetDifficulty(GameManager::GetDifficulty());
	}

	// 충돌 및 UI 설정
	void TestScene2::Enter()
	{
		Platform* mainGround = object::Instantiate<Platform>(eColliderLayer::Platform, Pos(64.0f, 640.0f));
		mainGround->SetColliderSize(Size(GRID_SIZE * 16, GRID_SIZE));
		mainGround->SetColliderOffset(Vector2(GRID_SIZE * 8, GRID_SIZE / 2));

		GameManager::SetSpawnPlatform(mainGround);

		GameManager::AddObject();
		Player* player = GameManager::GetPlayer();
		player->SetPos(Pos(440.f, 576.f));

		// 씬에서 상자 받아오고, 그것을 연결
		for (int idx = 0; idx < CHEST_POOL; ++idx)
		{
			mChest[idx] = GameManager::GetChest(idx);
		}

		mChest[0]->SetPos(Pos(70.0f, 610.0f));
		mChest[1]->SetPos(Pos(140.0f, 610.0f));
		mChest[2]->SetPos(Pos(220.0f, 610.0f));

		SetLayer();
		SetUI();
		GameManager::SetPlayable(true);
	}

	// 
	void TestScene2::Exit()
	{

	}
}