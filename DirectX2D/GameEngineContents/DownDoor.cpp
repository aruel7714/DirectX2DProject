#include "PreCompile.h"
#include "DownDoor.h"

DownDoor::DownDoor()
{
}

DownDoor::~DownDoor()
{
}

void DownDoor::Start()
{
	GameEngineSprite::CreateSingle("Door.png");
	GameEngineSprite::CreateSingle("Keyboard_F.png");
	DoorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::NPC);
	DoorRenderer->SetSprite("Door.png");

	float4 ImageScale = GameEngineTexture::Find("Door.png")->GetScale() * 4.0f;

	DoorRenderer->SetImageScale(ImageScale);
	DoorRenderer->SetPivotType(PivotType::Bottom);

	{
		DoorCollision = CreateComponent<GameEngineCollision>(CollisionType::LevelChangeTrigger);
		DoorCollision->SetCollisionType(ColType::AABBBOX2D);
		DoorCollision->Transform.SetLocalPosition({ 0.0f, (ImageScale.Y / 2.0f), 1.0f });
		DoorCollision->Transform.SetLocalScale({ ImageScale.X, ImageScale.Y, 1.0f });
	}
	
	KeyRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::NPCEventKey);
	KeyRenderer->SetSprite("Keyboard_F.png");
	float4 KeyScale = KeyRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	KeyRenderer->SetImageScale(KeyScale);
	KeyRenderer->Off();
}
void DownDoor::Update(float _Delta)
{
	EventParameter FloorDownEvent;
	FloorDownEvent.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
			KeyRenderer->On();
	};
	FloorDownEvent.Exit = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
			KeyRenderer->Off();
	};
	DoorCollision->CollisionEvent(CollisionType::Player, FloorDownEvent);
	KeyRenderer->Transform.SetLocalPosition({ 0.0f, 196.0f });

}

void DownDoor::SetDoorPosition(float4 _Pos)
{
	Transform.SetLocalPosition(_Pos);
}