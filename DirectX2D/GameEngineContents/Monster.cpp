#include "PreCompile.h"
#include "Monster.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::DamageCheck()
{
	float PlayerDamage = Player::GetMainPlayer()->GetWeaponDamage();

	Hp -= PlayerDamage;
}

void Monster::AirWallCheck(float _Delta, float4 _CheckPos, float4 _CheckScale)
{
	GameEngineColor DownCheckColor = BackGround::DebugBackGround->GetColor({ _CheckPos.X, _CheckPos.Y - (_CheckScale.Y / 2.0f) }, GameEngineColor::RED);
	GameEngineColor UpCheckColor = BackGround::DebugBackGround->GetColor({ _CheckPos.X, _CheckPos.Y + (_CheckScale.Y / 2.0f) }, GameEngineColor::RED);
	GameEngineColor LeftCheckColor = BackGround::DebugBackGround->GetColor({ _CheckPos.X - (_CheckScale.X / 2.0f), _CheckPos.Y}, GameEngineColor::RED);
	GameEngineColor RightCheckColor = BackGround::DebugBackGround->GetColor({ _CheckPos.X + (_CheckScale.X / 2.0f), _CheckPos.Y}, GameEngineColor::RED);
	int a = 0;

	if (GameEngineColor::RED == UpCheckColor)
	{
		float4 CheckPos = { _CheckPos.X, _CheckPos.Y + (_CheckScale.Y / 2.0f) };
		CheckPos += float4::DOWN;
		GameEngineColor Color = BackGround::DebugBackGround->GetColor(CheckPos, GameEngineColor::RED);

		while (Color == GameEngineColor::RED)
		{
			CheckPos = CheckPos + float4::DOWN;
			Color = BackGround::DebugBackGround->GetColor(CheckPos, GameEngineColor::RED);
			Transform.AddLocalPosition(float4::DOWN);
		}
	}

	if (GameEngineColor::RED == LeftCheckColor)
	{
		float4 CheckPos = { _CheckPos.X - (_CheckScale.X / 2.0f), _CheckPos.Y };
		CheckPos += float4::RIGHT;
		GameEngineColor Color = BackGround::DebugBackGround->GetColor(CheckPos, GameEngineColor::RED);

		while (Color == GameEngineColor::RED)
		{
			CheckPos = CheckPos + float4::RIGHT;
			Color = BackGround::DebugBackGround->GetColor(CheckPos, GameEngineColor::RED);
			Transform.AddLocalPosition(float4::RIGHT);
		}
	}

	if (GameEngineColor::RED == RightCheckColor)
	{
		float4 CheckPos = { _CheckPos.X + (_CheckScale.X / 2.0f), _CheckPos.Y };
		CheckPos += float4::LEFT;
		GameEngineColor Color = BackGround::DebugBackGround->GetColor(CheckPos, GameEngineColor::RED);

		while (Color == GameEngineColor::RED)
		{
			CheckPos = CheckPos + float4::LEFT;
			Color = BackGround::DebugBackGround->GetColor(CheckPos, GameEngineColor::RED);
			Transform.AddLocalPosition(float4::LEFT);
		}
	}

	if (GameEngineColor::RED == DownCheckColor)
	{
		float4 CheckPos = { _CheckPos.X, _CheckPos.Y - (_CheckScale.Y / 2.0f) };
		GameEngineColor Color = BackGround::DebugBackGround->GetColor(CheckPos, GameEngineColor::RED);

		while (Color == GameEngineColor::RED)
		{
			CheckPos = CheckPos + float4::UP;
			Color = BackGround::DebugBackGround->GetColor(CheckPos, GameEngineColor::RED);
			Transform.AddLocalPosition(float4::UP);
		}
	}
}