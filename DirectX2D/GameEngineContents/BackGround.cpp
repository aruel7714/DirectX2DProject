#include "PreCompile.h"
#include "BackGround.h"

BackGround* BackGround::DebugBackGround;

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::Start()
{
	WindowScale = GameEngineCore::MainWindow.GetScale();
}
void BackGround::Update(float _Delta)
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
}

GameEngineColor BackGround::GetColor(float4 _Pos, GameEngineColor _DefaultColor)
{
	// �÷��̾��� ��ġ�� �̹����� ��ǥ��� �����Ѵ�.
	// �̹����� ���������� �Ʒ��� ���������� +�� �Ǳ� �����̴�.
	std::string_view TextureName = DebugFloorRenderer->GetCurSprite().Texture->GetName();

	_Pos.Y *= -1.0f;

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find(TextureName);

	return Tex->GetColor(_Pos / 4.0f, _DefaultColor);
}