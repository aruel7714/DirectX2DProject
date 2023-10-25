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
	DoorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrderDungeon::NPC);
	DoorRenderer->SetSprite("Door.png");

	ImageScale = GameEngineTexture::Find("Door.png")->GetScale() * 4.0f;

	DoorRenderer->SetImageScale(ImageScale);
	DoorRenderer->SetPivotType(PivotType::Bottom);

	{
		DoorCollision = CreateComponent<GameEngineCollision>(CollisionType::NPC);
		DoorCollision->SetCollisionType(ColType::AABBBOX2D);
		DoorCollision->Transform.SetLocalPosition({ 0.0f, (ImageScale.Y / 2.0f), 1.0f });
		DoorCollision->Transform.SetLocalScale({ ImageScale.X, ImageScale.Y, 1.0f });
	}
}
void DownDoor::Update(float _Delta)
{
	float4 Pos = Transform.GetLocalPosition();
	int a = 0;
}

void DownDoor::SetDoorPosition(float4 _Pos)
{
	Transform.SetLocalPosition(_Pos);
}