#include "PreCompile.h"
#include "BeforeBossEncounterFloor.h"

BeforeBossEncounterFloor::BeforeBossEncounterFloor()
{
}

BeforeBossEncounterFloor::~BeforeBossEncounterFloor()
{
}

void BeforeBossEncounterFloor::Start()
{
	FloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrderDungeon::Floor);
	FloorRenderer->SetSprite("BossEncount.png");

	DebugFloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrderDungeon::Floor);
	DebugFloorRenderer->SetSprite("BossEncount_Debug.png");

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("BossEncount.png");
	float4 ImageScale = Texture->GetScale() * 4.0f;

	FloorRenderer->SetImageScale(ImageScale);
	DebugFloorRenderer->SetImageScale(ImageScale);

	float4 ImageHalfScale = ImageScale.Half();
	ImageHalfScale.Y *= -1.0f;
	Transform.SetLocalPosition(ImageHalfScale);
}
void BeforeBossEncounterFloor::Update(float _Delta)
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

void BeforeBossEncounterFloor::SetDebugBackGround()
{
	DebugBackGround = this;
}