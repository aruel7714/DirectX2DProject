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
	// �÷��̾��� ��ġ�� �̹����� ��ǥ��� �����Ѵ�.
	// �̹����� ���������� �Ʒ��� ���������� +�� �Ǳ� �����̴�.
	_Pos.Y *= -1.0f;

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Test.png");


	return Tex->GetColor(_Pos, _DefaultColor);
}