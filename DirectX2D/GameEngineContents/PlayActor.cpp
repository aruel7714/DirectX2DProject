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
	GravityForce.Y -= GravityPower * _Delta;
	Transform.AddLocalPosition(GravityForce * _Delta);
}

void PlayActor::GravityState(float _Delta, float4 _CheckPos)
{
	GameEngineColor CheckColor = BackGround::DebugBackGround->GetColor(_CheckPos, GameEngineColor::RED);

	if (GameEngineColor::RED != CheckColor && GameEngineColor::BLUE != CheckColor)
	{
		Gravity(_Delta);
	}
	else
	{
		float4 CheckPos = _CheckPos + float4::UP;
		GameEngineColor Color = BackGround::DebugBackGround->GetColor(CheckPos, GameEngineColor::RED);

		while (Color == GameEngineColor::RED)
		{
			CheckPos = CheckPos + float4::UP;
			Color = BackGround::DebugBackGround->GetColor(CheckPos, GameEngineColor::RED);
			Transform.AddLocalPosition(float4::UP);
		}

		GravityForceReset();
	}
}