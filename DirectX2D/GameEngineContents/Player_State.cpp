#include "PreCompile.h"
#include "Player.h"

void Player::IdleStart()
{
	ChangeAnimationState("Idle");
}
void Player::IdleUpdate(float _Delta)
{
	Gravity(_Delta);
	if (true == GameEngineInput::IsPress('A') || true == GameEngineInput::IsPress('D'))
	{
		ChangeState(PlayerState::Run);
	}


	//Debug
	if (true == GameEngineInput::IsPress('W') || true == GameEngineInput::IsPress('S'))
	{
		//ChangeState(PlayerState::Jump);
		//Transform.AddLocalPosition(float4::UP * _Delta * Speed);
		ChangeState(PlayerState::Run);
	}
}

void Player::RunStart()
{
	ChangeAnimationState("Run");
}
void Player::RunUpdate(float _Delta)
{
	Gravity(_Delta);

	if (true == GameEngineInput::IsPress('A'))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}
	else if (true == GameEngineInput::IsPress('D'))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}
	else if (true == GameEngineInput::IsPress('W'))
	{
		//Transform.AddLocalPosition(float4::UP * _Delta * Speed);
		ChangeState(PlayerState::Jump);
	}
	else if (true == GameEngineInput::IsPress('S'))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	}

	//if (true == GameEngineInput::IsPress('W'))
	//{
	//	ChangeState(PlayerState::Jump);
	//}


	if (true == GameEngineInput::IsFree('A') && true == GameEngineInput::IsFree('D') &&
		true == GameEngineInput::IsFree('W') && true == GameEngineInput::IsFree('S'))
	{
		ChangeState(PlayerState::Idle);
	}
}

void Player::JumpStart()
{
	ChangeAnimationState("Jump");
}
void Player::JumpUpdate(float _Delta)
{
	Transform.AddLocalPosition(float4::UP * _Delta * JumpPower);
	Gravity(_Delta);

	if (GameEngineColor::RED == Color)
	{
		ChangeState(PlayerState::Idle);
	}

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