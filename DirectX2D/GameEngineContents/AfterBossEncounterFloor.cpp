#include "PreCompile.h"
#include "AfterBossEncounterFloor.h"

AfterBossEncounterFloor::AfterBossEncounterFloor()
{
}

AfterBossEncounterFloor::~AfterBossEncounterFloor()
{
}

void AfterBossEncounterFloor::Start()
{
	FloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Floor);
	FloorRenderer->SetSprite("AfterBossEncounter.png");

	DebugFloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Floor);
	DebugFloorRenderer->SetSprite("AfterBossEncounter_Debug.png");

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("AfterBossEncounter.png");
	float4 ImageScale = Texture->GetScale() * 4.0f;

	FloorRenderer->SetImageScale(ImageScale);
	DebugFloorRenderer->SetImageScale(ImageScale);

	float4 ImageHalfScale = ImageScale.Half();
	ImageHalfScale.Y *= -1.0f;
	Transform.SetLocalPosition(ImageHalfScale);
}
void AfterBossEncounterFloor::Update(float _Delta)
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

void AfterBossEncounterFloor::SetDebugBackGround()
{
	DebugBackGround = this;
}