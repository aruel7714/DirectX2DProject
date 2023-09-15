#include "PreCompile.h"
#include "Player.h"

void Player::IdleStart()
{
	ChangeAnimationState("Idle");
}
void Player::IdleUpdate(float _Delta)
{
	if (true == GameEngineInput::IsPress('A') || true == GameEngineInput::IsPress('D'))
	{
		ChangeState(PlayerState::Run);
	}


	//Debug
	if (true == GameEngineInput::IsPress('W') || true == GameEngineInput::IsPress('S'))
	{
		ChangeState(PlayerState::Run);
	}
}

void Player::RunStart()
{
	ChangeAnimationState("Run");
}
void Player::RunUpdate(float _Delta)
{
	float Speed = 1000.0f;

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
		Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	}
	else if (true == GameEngineInput::IsPress('S'))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	}

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

}