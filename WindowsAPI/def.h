#pragma once

// Application enum
#define Window_Width    1280
#define Window_Height   720
enum class ePenColor
{
	Red,
	Green,
	Blue,
	End,
};
enum class eBrushColor
{
	Transparent,
	Black,
	Gray,	// 167 0 67
	White,
	End,
};
enum class eCameraEffect
{
	FadeIn,
	FadeOut,
	None,
	End,
};
#define KEY_PRESSE(KEY) js::Input::GetKeyState(KEY) == js::eKeyState::PRESSED
#define KEY_DOWN(KEY) js::Input::GetKeyState(KEY) == js::eKeyState::DOWN
#define KEY_UP(KEY) js::Input::GetKeyState(KEY) == js::eKeyState::UP

// Scene enum
enum class eSceneType
{
	MapTool,
	Test,
	Title,
	Select,
	Play,
	Option,
	End,
};

// UI enum
enum class eUIType
{
	TEST,
	SelectBtn,		// title
	OptionBtn,		// title
	QuitBtn,		// title

	PlayBtn,		// select

	PLAYER_INFO,	// 인게임 HUD
	ITEM_SELECT,	// 인게임 HUD
	OPTION,			// 

	END,
};
enum class eBtnType
{
	GoToSelectScene,
	GoToOption,
	GoToPlayScene,
	GoToTitleScene,
	End,
};


// Tool enum
union ColliderID
{
	struct
	{
		UINT32 left;
		UINT32 right;
	};
	UINT64 ID;
};
typedef ColliderID TileID;

#define TILE_SIZE	32			// 가로세로 크기
#define TILE_SCALE	2			// 이미지 크기
#define TILE_LINE_X 12			// 아틀라스 가로 개수
#define TILE_LINE_Y 6			// 아틀라스 세로 개수

#define GRID_SIZE 64			// 타일 크기


// Component enum
#define _COLLIDER_LAYER 16		// 충돌체 유형
enum class eComponentType
{
	Rigidbody,
	Collider,
	Animator,
	Sound,
	End,
};
enum class eColliderLayer
{
	Default,					//	0	//	// None
	BackGroundImage,			//	1		// 이미지만 존재하는 배경 이미지
	Tile,						//	2		// 타일로 존재하는 배경 오브젝트
	BGObj,						//	3		// 이미지 외에 컴포넌트가 필요한 배경 오브젝트

								//	4	//

	EventObject,				//	4		// 트리거를 가진 오브젝트
	Platform,					//	5		// 벽
	Ladder,						//	6		// 사다리
	Propellant,					//	7		// 오브젝트를 위로 날려버림
	Head,						//	8		// Creature 머리충돌
	Foot,						//	9		// Creature 바닥충돌

								//  10	//

	Player,						//	10		// 
	Player_Projectile,			//	11		// 플레이어가 매개가 되는 투사체 (스킬과 아이템효과)
	Monster,					//	12		// 플레이어 투사체에 의해서만 피해를 입음
	DamagingObj,				//	13		// 용암바닥, 몬스터 투사체 등

	UI = _COLLIDER_LAYER - 1,	//	14
	End = _COLLIDER_LAYER,		//	15
};
// 1 백그라운드 레이어 통일할 것

// Object enum
enum class ePlayerState
{
	Idle,		
	Move,		
	Jump,		
	Climb,		
	DoubleTab,
	FMJ,
	TacticalDive,		
	SupressiveFire,
	Death,		// 끝?
};
enum class eProjectileType
{
	DoubleTab,			// 1번 기술
	FMJ,				// 2번 기술
	TacticalDive,		// 3번 기술
	SuppresiveFire,		// 4번 기술

	End,
};

enum class eStagger
{
	Light,		// 소형 몬스터 넉백
	Nomal,		// 중형 몬스터 넉백
	Heave,		// 보스 제외 기절유발
};

#define PLAYER_PROJECTILE_POOL 40

// item enum
enum class eChestType
{
	Small,
	Large,
	Golden,
};

#define ITEM_SIZE 34
enum class eItemType
{
	Common,
	Uncommon,
	Rare,
	Active,
};
enum class eItemList
{
	// Common
	Glasses,		// 치명타 증가
	Syringe,		// 공격속도 증가
	Hoof,			// 이동속도 증가
	Tooth,			// 처치시 체력 회복
	Root,			// 최대 채력 증가
	// Uncommon
	TimeKeeper = 5,		// 치명상을 입을 때, 시간을 멈춤
	Wisp,			// 처치시 폭발
	MissileMk1,		// 일정확률로 투사체 사출
	Seed,			// 타격마다 회복
	Feather,		// 점프 1회 추가
	// Rare
	MissileMk2 = 10,// 더많이 더 강한 투사체 사출
	Behemoth,		// 모든 공격이 폭발함
	Ring,			// 치명타 증가, 치명타시 쿨다운 감소
	Scepter,		// 4번째 스킬 강화
	// Active
	Key	= 15,		// 화면에 보이는 상자를 열음
	Fruit,			// 즉시 회복
	Watch,			// 시간을 멈춤
	End,
};