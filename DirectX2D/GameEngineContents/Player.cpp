#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include "TownFloor.h"
#include "DebugFloor.h"
#include "TestMap.h"
#include "TownDungeonTrigger.h"
#include "BackGround.h"
#include "ShortSword.h"

Player* Player::MainPlayer = nullptr;

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	MainPlayer = this;

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
		MainRenderer->CreateAnimation("Player_Stay", "Idle");
	}

	MainRenderer->SetSprite("Idle");
	//MainRenderer->SetSamplerState(SamplerOption::POINT);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	float4 MapScale = GameEngineTexture::Find("Town.png")->GetScale() * 4.0f;
	//Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	//Transform.SetLocalPosition({ HalfWindowScale.X, -1200.0f, -500.0f });
	//Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f, 1.0f });
	//Transform.SetLocalPosition({MapScale.Half().X, -MapScale.Half().Y, -500.0f});
	
	MainRenderer->SetPivotType(PivotType::Bottom);

	//float4 Scale = MainRenderer->Transform.GetLocalScale();
	//Scale *= 4.0f;

	Scale = MainRenderer->GetCurSprite().Texture->GetScale();
	Scale *= 4.0f;

	//Transform.SetLocalScale(Scale);
	MainRenderer->SetImageScale(Scale);

	//float4 Scale2 = Transform.GetLocalScale();
	
	
	ChangeState(PlayerState::Idle);
	//ChangeState(PlayerState::Stay);

	{
		PlayerCollision = CreateComponent<GameEngineCollision>(CollisionType::Player);
		PlayerCollision->SetCollisionType(ColType::AABBBOX2D);
		PlayerCollision->Transform.SetLocalPosition({ 0.0f, Scale.Y / 4.0f, 1.0f });
		PlayerCollision->Transform.SetLocalScale({Scale.X / 2.0f, Scale.Y / 2.0f, 1.0f });
		//PlayerCollision->Transform.SetLocalScale({ 100.0f, 10.0f, 1.0f });
		
	}

	GameEngineInput::AddInputObject(this);
}

void Player::Update(float _Delta)
{
	float4 PlayerPos = Transform.GetWorldPosition();
	Color = BackGround::DebugBackGround->GetColor(PlayerPos, GameEngineColor::RED);
	int a = 0;

	StateUpdate(_Delta);
	CameraFocus();

	//GravityState(_Delta, Transform.GetLocalPosition());

	//float4 ColorPosition = Transform.GetWorldPosition();
	////ColorPosition.Y -= 64.0f;
	////GameEngineColor Color = TestMap::DebugFloor->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);
	//GameEngineColor Color = TownFloor::DebugFloor->GetColor(ColorPosition, GameEngineColor::RED);
	//GameEngineColor Color2 = TownFloor::DebugFloor->GetColor(ColorPosition, GameEngineColor { 0, 0, 255, 255 });

	///*while(GameEngineColor::RED != Color)
	//{
	//	GravityForce.Y -= _Delta * 100.0f;
	//	Transform.AddLocalPosition(GravityForce * _Delta);
	//}*/
	//if (GameEngineColor::RED != Color)
	//{
	//	GravityForce.Y -= _Delta * 1000.0f;
	//	Transform.AddLocalPosition(GravityForce * _Delta);
	//}
	//else
	//{
	//	GravityForce = 0.0f;
	//}
	if (State != PlayerState::Stay)
	{
		DirCheck();
	}
	
	CheckDelta += _Delta;
	int iCheckDelta = static_cast<int>(CheckDelta);

	/*if (iCheckDelta % 5 == 4)
	{
		MainRenderer->RightFlip();
		CheckDelta = 0.0f;
	}*/
	

	if (Dir == PlayerDir::Left)
	{
		//MainRenderer->LeftFlip();
		Transform.SetLocalScale({ -abs(Transform.GetLocalScale().X), Transform.GetLocalScale().Y });
	}

	if (Dir == PlayerDir::Right)
	{
		//MainRenderer->RightFlip();
		Transform.SetLocalScale({ abs(Transform.GetLocalScale().X), Transform.GetLocalScale().Y });
	}

	float4 Mat = PlayerCollision->Transform.GetLocalScale();
	int b = 0;

	EventParameter Parameter;
	Parameter.Stay = [](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		_Other->Death();
	};

	PlayerCollision->CollisionEvent(CollisionType::Trigger, Parameter);

	float4 WeaponPos = PlayerPos;

	//WeaponPos.X += MainRenderer->Transform.GetLocalScale().X;
	WeaponPos.X += Mat.X;
	WeaponPos.Y += Mat.Y / 2.0f;

	ShortSword::WeaponShortSword->ShortSwordRenderer->Transform.SetLocalPosition(WeaponPos);

}

void Player::CameraFocus()
{
	//float4 PlayerPos = Transform.GetWorldPosition();
	//GetLevel()->GetMainCamera()->Transform.SetLocalPosition(PlayerPos);

	//float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	float4 CameraPos = Transform.GetWorldPosition();

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();
	//float4 MapScale = GameEngineTexture::Find("Town.png")->GetScale() * 4;
	float4 MapScale = BackGround::DebugBackGround->DebugFloorRenderer->GetCurSprite().Texture->GetScale() * 4;

	if (WindowScale.Half().X >= CameraPos.X)
	{
		CameraPos.X = WindowScale.Half().X;
		//GetLevel()->GetMainCamera()->Transform.SetLocalPosition(CameraPos);
	}

	if (-MapScale.Y + WindowScale.Half().Y >= CameraPos.Y)
	{
		CameraPos.Y = -MapScale.Y + WindowScale.Half().Y;
		//GetLevel()->GetMainCamera()->Transform.SetLocalPosition(CameraPos);
	}

	if (MapScale.X - WindowScale.Half().X <= CameraPos.X)
	{
		CameraPos.X = MapScale.X - WindowScale.Half().X;
	}

	if (-WindowScale.Half().Y <= CameraPos.Y)
	{
		CameraPos.Y = -WindowScale.Half().Y;
	}

	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(CameraPos);
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
		case PlayerState::Dash:
			DashStart();
			break;
		case PlayerState::DownJump:
			DownJumpStart();
			break;
		case PlayerState::Stay:
			StayStart();
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
	case PlayerState::Dash:
		return DashUpdate(_Delta);
	case PlayerState::DownJump:
		return DownJumpUpdate(_Delta);
	case PlayerState::Stay:
		return StayUpdate(_Delta);
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

void Player::DirCheck()
{
	float4 WorldMousePos = GetLevel()->GetMainCamera()->GetWorldMousePos2D();
	float4 PlayerPos = Transform.GetWorldPosition();

	if (0.0f <= WorldMousePos.X - PlayerPos.X)
	{
		Dir = PlayerDir::Right;
		//OutputDebugStringA("Right\n");
	}
	else
	{
		Dir = PlayerDir::Left;
		//OutputDebugStringA("Left\n");
	}

	OutputDebugStringA(PlayerPos.ToString("\n").c_str());
}

//void Player::Gravity(float _Delta)
//{
//	float4 ColorPosition = Transform.GetWorldPosition();
//	//ColorPosition.Y -= 64.0f;
//	//GameEngineColor Color = TestMap::DebugFloor->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);
//	//GameEngineColor Color = TownFloor::DebugFloor->GetColor(ColorPosition, GameEngineColor::RED);
//	//GameEngineColor Color2 = TownFloor::DebugFloor->GetColor(ColorPosition, GameEngineColor{ 0, 0, 255, 255 });
//
//	//GameEngineColor Color = TownFloor::DebugFloor->GetColor(ColorPosition, GameEngineColor::RED);
//	Color = BackGround::DebugBackGround->GetColor(ColorPosition, GameEngineColor::RED);
//
//	/*while(GameEngineColor::RED != Color)
//	{
//		GravityForce.Y -= _Delta * 100.0f;
//		Transform.AddLocalPosition(GravityForce * _Delta);
//	}*/
//	if (GameEngineColor::RED != Color)
//	{
//		GravityForce.Y -= _Delta * 1000.0f;
//		Transform.AddLocalPosition(GravityForce * _Delta);
//	}
//	else
//	{
//		Transform.AddLocalPosition(float4::UP * 0.1f);
//		GravityForce = 0.0f;
//	}
//}

void Player::ChangeStateStay()
{
	ChangeState(PlayerState::Stay);
}
