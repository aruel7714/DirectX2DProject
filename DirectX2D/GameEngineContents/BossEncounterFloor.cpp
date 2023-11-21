#include "PreCompile.h"
#include "BossEncounterFloor.h"

BossEncounterFloor::BossEncounterFloor()
{
}

BossEncounterFloor::~BossEncounterFloor()
{
}

void BossEncounterFloor::Start()
{
	FloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Floor);
	FloorRenderer->SetSprite("BossRoom.png");

	DebugFloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Floor);
	DebugFloorRenderer->SetSprite("BossRoom_Debug.png");

	WallFloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DungeonWall);
	WallFloorRenderer->SetSprite("BossRoomWall.png");

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("BossRoom.png");
	float4 ImageScale = Texture->GetScale() * 4.0f;

	FloorRenderer->SetImageScale(ImageScale);
	DebugFloorRenderer->SetImageScale(ImageScale);
	WallFloorRenderer->SetImageScale(ImageScale);

	float4 ImageHalfScale = ImageScale.Half();
	ImageHalfScale.Y *= -1.0f;
	Transform.SetLocalPosition(ImageHalfScale);
}
void BossEncounterFloor::Update(float _Delta)
{
	if (false == IsDebug)
	{
		FloorRenderer->On();
		DebugFloorRenderer->Off();
	}
	else
	{
		FloorRenderer->Off();
		DebugFloorRenderer->On();
	}

	if (true == GameEngineInput::IsDown(VK_F5, this))
	{
		IsDebug = !IsDebug;
	}
}

void BossEncounterFloor::SetDebugBackGround()
{
	DebugBackGround = this;
}