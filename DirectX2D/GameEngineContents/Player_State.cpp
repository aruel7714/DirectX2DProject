#include "PreCompile.h"
#include "Player.h"
#include "BackGround.h"
#include "HandCrossbow.h"
#include "PlayerLife.h"

void Player::IdleStart()
{
	ChangeAnimationState("Idle");
}
void Player::IdleUpdate(float _Delta)
{
	//Gravity(_Delta);
	GravityState(_Delta, Transform.GetLocalPosition(), (Scale / 2.0f));
	if (true == GameEngineInput::IsPress('A', this) || true == GameEngineInput::IsPress('D', this))
	{
		ChangeState(PlayerState::Run);
	}

	if (GameEngineColor::BLUE == BackGround::DebugBackGround->GetColor(Transform.GetLocalPosition(), GameEngineColor::BLUE))
	{
		if (true == GameEngineInput::IsPress('S', this) && true == GameEngineInput::IsPress(VK_SPACE, this))
		{
			//Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
			ChangeState(PlayerState::DownJump);
			return;
		}
	}

	//Debug
	if (true == GameEngineInput::IsPress('W', this) || true == GameEngineInput::IsPress(VK_SPACE, this))
	{
		PlayerSound = GameEngineSound::SoundPlay("Jumping.wav");
		ChangeState(PlayerState::Jump);
		//Transform.AddLocalPosition(float4::UP * _Delta * Speed);
		//ChangeState(PlayerState::Run);
	}

	

	if (true == GameEngineInput::IsPress(VK_RBUTTON, this))
	{
		PlayerSound = GameEngineSound::SoundPlay("ui-sound-13-dash.wav");
		ChangeState(PlayerState::Dash);
	}
	
}

void Player::RunStart()
{
	ChangeAnimationState("Run");
}
void Player::RunUpdate(float _Delta)
{
	//Gravity(_Delta);
	GravityState(_Delta, Transform.GetLocalPosition(), (Scale / 2.0f));


	if (true == GameEngineInput::IsPress('A', this))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}
	else if (true == GameEngineInput::IsPress('D', this))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}
	//else if (true == GameEngineInput::IsPress('W'))
	//{
	//	//Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	//	ChangeState(PlayerState::Jump);
	//}

	if (GameEngineColor::BLUE == BackGround::DebugBackGround->GetColor(Transform.GetLocalPosition(), GameEngineColor::BLUE))
	{
		if (true == GameEngineInput::IsPress('S', this) && true == GameEngineInput::IsPress(VK_SPACE, this))
		{
			//Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
			ChangeState(PlayerState::DownJump);
			return;
		}
	}

	if (true == GameEngineInput::IsPress('W', this) || true == GameEngineInput::IsPress(VK_SPACE, this))
	{
		PlayerSound = GameEngineSound::SoundPlay("Jumping.wav");
		ChangeState(PlayerState::Jump);
		//Transform.AddLocalPosition(float4::UP * _Delta * Speed);
		//ChangeState(PlayerState::Run);
	}

	


	if (true == GameEngineInput::IsFree('A', this) && true == GameEngineInput::IsFree('D', this) &&
		true == GameEngineInput::IsFree('W', this) && true == GameEngineInput::IsFree('S', this))
	{
		ChangeState(PlayerState::Idle);
	}

	if (true == GameEngineInput::IsPress(VK_RBUTTON, this))
	{
		PlayerSound = GameEngineSound::SoundPlay("ui-sound-13-dash.wav");
		ChangeState(PlayerState::Dash);
	}
}

void Player::JumpStart()
{
	SetGravityForce(float4::UP * JumpPower);
	ChangeAnimationState("Jump");
	
}
void Player::JumpUpdate(float _Delta)
{
	//Transform.AddLocalPosition(float4::UP * _Delta * JumpPower);
	
	//Transform.AddLocalPosition(float4::UP * _Delta * 100.0f);


	GravityState(_Delta, Transform.GetLocalPosition() + float4::UP, (Scale / 2.0f));

	
	if (GameEngineColor::RED == Color || (GameEngineColor::BLUE == Color && PassBlue == false))
	{
		ChangeState(PlayerState::Idle);
	}

	if (true == GameEngineInput::IsPress('A', this))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}
	else if (true == GameEngineInput::IsPress('D', this))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}

	if (true == GameEngineInput::IsPress(VK_RBUTTON, this))
	{
		GravityForceReset();
		PlayerSound = GameEngineSound::SoundPlay("ui-sound-13-dash.wav");
		ChangeState(PlayerState::Dash);
	}
}

void Player::DashStart()
{
	ChangeAnimationState("Jump");
	ResetLiveTime();
	
}
void Player::DashUpdate(float _Delta)
{
	float4 WorldMousePos = GetLevel()->GetMainCamera()->GetWorldMousePos2D();
	float4 PlayerPos = Transform.GetWorldPosition();

	float4 Dir = WorldMousePos - PlayerPos;

	Dir.Normalize();
	Dir *= 1500.0f;

	if (GetLiveTime() < 0.15f)
	{
		Transform.AddLocalPosition(Dir * _Delta);
		SetGravityForce(float4::UP);
		GravityState(_Delta, Transform.GetLocalPosition(), (Scale / 2.0f));
	}
	else
	{
		GravityState(_Delta, Transform.GetLocalPosition(), (Scale / 2.0f));
	}

	if (GameEngineColor::RED == Color || (GameEngineColor::BLUE == Color && PassBlue == false))
	{
		ChangeState(PlayerState::Idle);
	}

	if (true == GameEngineInput::IsPress('A', this))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}
	else if (true == GameEngineInput::IsPress('D', this))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}
}

void Player::DownJumpStart()
{
	ChangeAnimationState("Jump");
}
void Player::DownJumpUpdate(float _Delta)
{
	GameEngineColor CheckColor = BackGround::DebugBackGround->GetColor(Transform.GetLocalPosition(), GameEngineColor::RED);
	if (GameEngineColor::BLUE == CheckColor || GameEngineColor::WHITE == CheckColor)
	{
		Gravity(_Delta);
		if (GameEngineColor::WHITE == CheckColor)
		{
			IsBlue = false;
		}
	}

	if (IsBlue == false)
	{
		//GravityState(_Delta, Transform.GetLocalPosition(), (Scale / 2.0f));
		if (GameEngineColor::BLUE == CheckColor || GameEngineColor::RED == CheckColor)
		{
			IsBlue = true;
			ChangeState(PlayerState::Idle);
		}
	}
	//else
	//{
	//	float4 CheckPos = Transform.GetLocalPosition() + float4::UP;
	//	GameEngineColor Color = BackGround::DebugBackGround->GetColor(CheckPos, GameEngineColor::RED);

	//	while (Color == GameEngineColor::RED)
	//	{
	//		CheckPos = CheckPos + float4::UP;
	//		Color = BackGround::DebugBackGround->GetColor(CheckPos, GameEngineColor::RED);
	//		Transform.AddLocalPosition(float4::UP);
	//	}

	//	GravityForceReset();
	//}

	if (true == GameEngineInput::IsPress('A', this))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}
	else if (true == GameEngineInput::IsPress('D', this))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}
	if (true == GameEngineInput::IsPress(VK_RBUTTON, this))
	{
		PlayerSound = GameEngineSound::SoundPlay("ui-sound-13-dash.wav");
		ChangeState(PlayerState::Dash);
	}
}

void Player::StayStart()
{
	ChangeAnimationState("Stay");
}
void Player::StayUpdate(float _Delta)
{
	//Gravity(_Delta);
	GravityState(_Delta, Transform.GetLocalPosition(), (Scale / 2.0f));
}

void Player::EndingStart()
{
	ChangeAnimationState("Idle");
	IsFocus = false;
	WeaponHandCrossbow->Off();
	UILife->Off();
}
void Player::EndingUpdate(float _Delta)
{

}

//if (GameEngineColor::RED != Color)
//{
//	GravityForce.Y -= _Delta * 1000.0f;
//	Transform.AddLocalPosition(GravityForce * _Delta);
//}
//else
//{
//	GravityForce = 0.0f;
//}
