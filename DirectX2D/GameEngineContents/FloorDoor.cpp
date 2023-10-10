#include "PreCompile.h"
#include "FloorDoor.h"

FloorDoor::FloorDoor()
{
}

FloorDoor::~FloorDoor()
{
}

void FloorDoor::Start()
{
	DoorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Building);
	DoorRenderer->CreateAnimation("Door_Close", "Door");
	DoorRenderer->SetSprite("Door");

	float4 Scale = DoorRenderer->GetCurSprite().Texture->GetScale();
	Scale *= 4.0f;

	DoorRenderer->SetImageScale(Scale);

	DoorRenderer->SetPivotType(PivotType::Bottom);

	float4 MapScale = GameEngineTexture::Find("Start1F.png")->GetScale() * 4.0f;

	Transform.SetLocalPosition({ 515.0f, -(MapScale.Y - 128.0f) });

	DoorRenderer->ChangeAnimation("Door_Close");
}

void FloorDoor::Update(float _Delta)
{

}