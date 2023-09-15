#include "PreCompile.h"
#include "TestMap.h"

TestMap* TestMap::DebugFloor;

TestMap::TestMap()
{
	DebugFloor = this;
}

TestMap::~TestMap()
{
}

void TestMap::Start()
{
	TestRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Floor);
	TestRenderer->SetSprite("Test.png");

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Test.png");

	float4 ImageScale = Texture->GetScale() * 4;

	TestRenderer->SetSamplerState(SamplerOption::POINT);
	TestRenderer->SetImageScale(ImageScale);

	float4 HScale = TestRenderer->GetCurSprite().Texture->GetScale();
	
	int a = 0;
	//HScale.Z = -500.0f;
	//HScale *= 4.0f;
	//Transform.SetLocalScale(HScale);

	HScale.Y *= -1.0f;
	Transform.SetLocalPosition(HScale);

	//Transform.SetLocalPosition(float4::ZERO);

}
void TestMap::Update(float _Delta)
{
	float4 TestPos = Transform.GetWorldPosition();
	int a = 0;
}

GameEngineColor TestMap::GetColor(float4 _Pos, GameEngineColor _DefaultColor)
{
	// 플레이어의 위치를 이미지의 좌표계로 변경한다.
	// 이미지는 위에서부터 아래로 내려갈수록 +가 되기 때문이다.
	_Pos.Y *= -1.0f;

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Test.png");


	return Tex->GetColor(_Pos, _DefaultColor);
}