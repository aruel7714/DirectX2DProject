#include "PreCompile.h"
#include "PlayActor.h"
#include "BackGround.h"


PlayActor::PlayActor()
{
}

PlayActor::~PlayActor()
{
}

void PlayActor::Gravity(float _Delta)
{
	Transform.AddLocalPosition(GravityForce * _Delta);
	GravityForce.Y -= GravityPower * _Delta;
}

void PlayActor::GravityState(float _Delta, float4 _CheckPos, float4 _CheckScale)
{
	GameEngineColor CheckColor = BackGround::DebugBackGround->GetColor(_CheckPos, GameEngineColor::RED);
	GameEngineColor UpCheckColor = BackGround::DebugBackGround->GetColor({_CheckPos.X, _CheckPos.Y + _CheckScale.Y}, GameEngineColor::RED);
	GameEngineColor LeftCheckColor = BackGround::DebugBackGround->GetColor({ _CheckPos.X - (_CheckScale.X / 2), _CheckPos.Y + (_CheckScale.Y / 2)}, GameEngineColor::RED);
	GameEngineColor RightCheckColor = BackGround::DebugBackGround->GetColor({ _CheckPos.X + (_CheckScale.X / 2), _CheckPos.Y + (_CheckScale.Y / 2) }, GameEngineColor::RED);
	int a = 0;

	if (GameEngineColor::RED == UpCheckColor)
	{
		float4 CheckPos = { _CheckPos.X, _CheckPos.Y + _CheckScale.Y };
		CheckPos += float4::DOWN;
		GameEngineColor Color = BackGround::DebugBackGround->GetColor(CheckPos, GameEngineColor::RED);
		GravityForce.Y = -JumpPower;

		while (Color == GameEngineColor::RED)
		{
			CheckPos = CheckPos + float4::DOWN;
			Color = BackGround::DebugBackGround->GetColor(CheckPos, GameEngineColor::RED);
			Transform.AddLocalPosition(float4::DOWN);
		}
	}

	if (GameEngineColor::RED == LeftCheckColor)
	{
		float4 CheckPos = { _CheckPos.X - (_CheckScale.X / 2), _CheckPos.Y + (_CheckScale.Y) };
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
		float4 CheckPos = { _CheckPos.X + (_CheckScale.X / 2), _CheckPos.Y + (_CheckScale.Y) };
		CheckPos += float4::LEFT;
		GameEngineColor Color = BackGround::DebugBackGround->GetColor(CheckPos, GameEngineColor::RED);


		while (Color == GameEngineColor::RED)
		{
			CheckPos = CheckPos + float4::LEFT;
			Color = BackGround::DebugBackGround->GetColor(CheckPos, GameEngineColor::RED);
			Transform.AddLocalPosition(float4::LEFT);
		}
	}

	if (GravityForce.Y > 0)
	{
		PassBlue = true;
		if (GameEngineColor::BLUE == CheckColor)
		{
			Gravity(_Delta);
			return;
		}
	}
	else
	{
		PassBlue = false;
	}
	
	
	

	if (GameEngineColor::RED != CheckColor && GameEngineColor::BLUE != CheckColor)
	{
		Gravity(_Delta);
	}
	else
	{
		float4 CheckPos = _CheckPos + float4::UP;
		GameEngineColor Color = BackGround::DebugBackGround->GetColor(CheckPos, GameEngineColor::RED);

		while (Color == GameEngineColor::RED || Color == GameEngineColor::BLUE)
		{
			CheckPos = CheckPos + float4::UP;
			Color = BackGround::DebugBackGround->GetColor(CheckPos, GameEngineColor::RED);
			Transform.AddLocalPosition(float4::UP);
		}
		
		GravityForceReset();
	}
}