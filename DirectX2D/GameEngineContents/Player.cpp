#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	if(nullptr == GameEngineSprite::Find("Idle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Player\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	//if (nullptr == GameEngineSprite::Find("Run"))
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExistsChild("ContentsResources");
	//	Dir.MoveChild("ContentsResources\\Texture\\Player\\");

	//	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	//	for (size_t i = 0; i < Directorys.size(); i++)
	//	{
	//		GameEngineDirectory& Dir = Directorys[i];

	//		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	//	}
	//}

	MainRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Player);

	//std::shared_ptr<GameEngineRenderer> Renderer = CreateComponent<GameEngineRenderer>(0);
	// Renderer->SetCameraOreder(0);
	//CreateChild<GameEngineRenderer>();

	{
		MainRenderer->CreateAnimation("Player_Idle", "Idle");
		MainRenderer->CreateAnimation("Player_Run", "Run");
		MainRenderer->CreateAnimation("Player_Jump", "Jump");
	}

	MainRenderer->SetSprite("Idle");
	MainRenderer->SetSamplerState(SamplerOption::POINT);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	
	float4 Scale = MainRenderer->Transform.GetLocalScale();
	Scale *= 4.0f;

	Transform.SetLocalScale(Scale);
	
	ChangeState(PlayerState::Idle);


	//MainSpriteRenderer->SetSprite("TestPlayer.png", 5);
		/*Renderer0->Transform.SetLocalPosition({ 0, 150, 0 });
		Renderer0->Transform.SetLocalScale({ 50, 50, 100 });*/

	//{
	//	std::shared_ptr<GameEngineRenderer> Renderer = CreateComponent<GameEngineRenderer>(0);
	//	Renderer->Transform.SetLocalPosition({ 0, -150, 0 });
	//	Renderer->Transform.SetLocalScale({ 50, 50, 100 });
	//}

	//{
	//	std::shared_ptr<GameEngineRenderer> Renderer = CreateComponent<GameEngineRenderer>(0);
	//	Renderer->Transform.SetLocalPosition({ -150, 0, 0 });
	//	Renderer->Transform.SetLocalScale({ 50, 50, 100 });
	//}

	//{
	//	std::shared_ptr<GameEngineRenderer> Renderer = CreateComponent<GameEngineRenderer>(0);
	//	Renderer->Transform.SetLocalPosition({ 150, 0, 0 });
	//	Renderer->Transform.SetLocalScale({ 50, 50, 100 });
	//}
}

void Player::Update(float _Delta)
{
	StateUpdate(_Delta);
	CameraFocus();

	//float Speed = 100.0f;

	//if (GameEngineInput::IsPress('A'))
	//{
	//	Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	//}

	//if (GameEngineInput::IsPress('D'))
	//{
	//	Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	//}

	//if (GameEngineInput::IsPress('W'))
	//{
	//	Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	//}

	//if (GameEngineInput::IsPress('S'))
	//{
	//	Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	//}

	//if (GameEngineInput::IsPress('Q'))
	//{
	//	Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	//}

	//if (GameEngineInput::IsPress('E'))
	//{
	//	Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	//}
}

void Player::CameraFocus()
{
	float4 PlayerPos = Transform.GetWorldPosition();
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(PlayerPos);
}

void Player::ChangeState(PlayerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Run:
			RunStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);
	case PlayerState::Run:
		return RunUpdate(_Delta);
	case PlayerState::Jump:
		return JumpUpdate(_Delta);
	default:
		break;
	}
}

void Player::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "Player_";

	AnimationName += _State;

	MainRenderer->ChangeAnimation(AnimationName);
}

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
	float Speed = 100.0f;

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