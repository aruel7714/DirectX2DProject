#include "PreCompile.h"
#include "Player.h"

void Player::IdleStart()
{
	ChangeAnimationState("Idle");
}
void Player::IdleUpdate(float _Delta)
{
	//Gravity(_Delta);
	GravityState(_Delta, Transform.GetLocalPosition());
	if (true == GameEngineInput::IsPress('A', this) || true == GameEngineInput::IsPress('D', this))
	{
		ChangeState(PlayerState::Run);
	}


	//Debug
	if (true == GameEngineInput::IsPress('W', this) || true == GameEngineInput::IsPress('S', this))
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
	//Gravity(_Delta);
	GravityState(_Delta, Transform.GetLocalPosition());


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
	else if (true == GameEngineInput::IsPress('S', this))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	}

	if (true == GameEngineInput::IsPress('W', this))
	{
		ChangeState(PlayerState::Jump);
	}


	if (true == GameEngineInput::IsFree('A', this) && true == GameEngineInput::IsFree('D', this) &&
		true == GameEngineInput::IsFree('W', this) && true == GameEngineInput::IsFree('S', this))
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
	//Transform.AddLocalPosition(float4::UP * _Delta * 100.0f);
	GravityState(_Delta, Transform.GetLocalPosition());

	if (GameEngineColor::RED == Color)
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

void Player::StayStart()
{
	ChangeAnimationState("Stay");
}
void Player::StayUpdate(float _Delta)
{
	//Gravity(_Delta);
	GravityState(_Delta, Transform.GetLocalPosition());
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