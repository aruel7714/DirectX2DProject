#include "PreCompile.h"
#include "DebugFloor.h"

DebugFloor* DebugFloor::MainDebugFloor;

DebugFloor::DebugFloor()
{
	MainDebugFloor = this;
}

DebugFloor::~DebugFloor()
{
}

void DebugFloor::Start()
{
	DebugFloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Floor);
	DebugFloorRenderer->SetSprite("Town_Debug.png");

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Town_Debug.png");

	//DebugFloorRenderer->SetSamplerState(SamplerOption::POINT);

	float4 HScale = Texture->GetScale().Half();

	HScale.Y *= -1.0f;

	float4 Scale = DebugFloorRenderer->Transform.GetLocalScale();
	Scale *= 4.0f;
	Transform.SetLocalScale(Scale);

	Transform.SetLocalPosition({ Scale.X, -Scale.Y, -500.0f, 1.0f });

	DebugFloorRenderer->On();
}
void DebugFloor::Update(float _Delta)
{
	float4 DebugPos = Transform.GetWorldPosition();
	float4 Scale = Transform.GetLocalScale();
	int a = 0;
}

GameEngineColor DebugFloor::GetColor(float4 _Pos, GameEngineColor _DefaultColor)
{
	// �÷��̾��� ��ġ�� �̹����� ��ǥ��� �����Ѵ�.
	// �̹����� ���������� �Ʒ��� ���������� +�� �Ǳ� �����̴�.
	_Pos.Y *= -1.0f;

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Town_Debug.png");


	return Tex->GetColor(_Pos, _DefaultColor);
}