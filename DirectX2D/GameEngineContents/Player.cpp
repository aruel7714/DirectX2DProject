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
#include "HandCrossbow.h"

#include "PlayerLife.h"
#include "PlayerEquippedWeapon.h"
#include "Level1F_Last.h"

Player* Player::MainPlayer = nullptr;

Player::Player()
{
	MainPlayer = this;
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

	//std::shared_ptr<ShortSword> WeaponShortSword = CreateActor<ShortSword>(RenderOrder::Weapon);
	WeaponHandCrossbow = GetLevel()->CreateActor<HandCrossbow>(RenderOrder::Weapon);
	WeaponDamage = WeaponHandCrossbow->GetDamage();
	

	{
		PlayerCollision = CreateComponent<GameEngineCollision>(CollisionType::Player);
		PlayerCollision->SetCollisionType(ColType::AABBBOX2D);
		PlayerCollision->Transform.SetLocalPosition({ 0.0f, Scale.Y / 4.0f, 1.0f });
		PlayerCollision->Transform.SetLocalScale({Scale.X / 2.0f, Scale.Y / 2.0f, 1.0f });
		//PlayerCollision->Transform.SetLocalScale({ 100.0f, 10.0f, 1.0f });
		
	}

	{
		UILife = GetLevel()->CreateActor<PlayerLife>(RenderOrder::MiddleUI);
		UIWeapon = GetLevel()->CreateActor<PlayerEquippedWeapon>(RenderOrder::MiddleUI);
	}

	GameEngineInput::AddInputObject(this);
}

void Player::Update(float _Delta)
{
	float4 PlayerPos = Transform.GetWorldPosition();
	Color = BackGround::DebugBackGround->GetColor(PlayerPos, GameEngineColor::RED);
	StatusUpdate();

	StateUpdate(_Delta);

	if (true == IsFocus)
	{
		CameraFocus();
	}

	PlayerCollisionEvent(_Delta);

	if (State != PlayerState::Stay ||
		State != PlayerState::Ending)
	{
		DirCheck();
	}

	if (State == PlayerState::Ending)
	{
		Dir = PlayerDir::Left;
	}
	
	CheckDelta += _Delta;
	int iCheckDelta = static_cast<int>(CheckDelta);

	if (Dir == PlayerDir::Left)
	{
		//Transform.SetLocalScale({ -abs(Transform.GetLocalScale().X), Transform.GetLocalScale().Y });
		MainRenderer->LeftFlip();
		PlayerPosition.X -= PlayerScale.X / 6.0f;
	}

	if (Dir == PlayerDir::Right)
	{
		//Transform.SetLocalScale({ abs(Transform.GetLocalScale().X), Transform.GetLocalScale().Y });
		MainRenderer->RightFlip();
		PlayerPosition.X += PlayerScale.X / 6.0f;
	}

	std::string Name = GetLevel()->GetName();
	int a = 0;
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
		case PlayerState::Ending:
			EndingStart();
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
	case PlayerState::Ending:
		return EndingUpdate(_Delta);
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
	//float4 PlayerLocalPos = Transform.GetLocalPosition();

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
void Player::ChangeStateEnding()
{
	ChangeState(PlayerState::Ending);
}
void Player::ChangeStateIdle()
{
	ChangeState(PlayerState::Idle);
}
bool Player::IsStateStay()
{
	if (State == PlayerState::Stay)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::DownFloorFunc()
{
	std::string Name = GetLevel()->GetName();
	if (true == GameEngineInput::IsPress('F', this))
	{
		if (Name == "Level1F_Last")
		{
			IsDown = true;
			//GameEngineCore::ChangeLevel("BeforeBossEncounterLevel");
		}
		else if (Name == "AfterBossEncounterLevel")
		{
			IsDown = true;
			//GameEngineCore::ChangeLevel("EndingLevel");
		}
	}
}

void Player::LevelStart(GameEngineLevel* _PrevLevel) 
{
	MainPlayer = this;
}

void Player::StatusUpdate()
{
	PlayerScale = GetRendererScale();
	PlayerPosition = Transform.GetWorldPosition();
	PlayerPosition.Y += (PlayerScale.Y / 5.0f);
}

void Player::SteleToPlayerMove(float _Delta, float ResultPos)
{
	if (ResultPos > 0)
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);

		if (State == PlayerState::Dash)
		{
			Transform.AddLocalPosition(float4::LEFT * _Delta * Speed * 2.0f);
		}
	}
	else
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);

		if (State == PlayerState::Dash)
		{
			Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed * 2.0f);
		}
	}
}

void Player::PlayerCollisionEvent(float _Delta)
{
	EventParameter Parameter;
	Parameter.Stay = [](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			_Other->Death();
		};
	PlayerCollision->CollisionEvent(CollisionType::Trigger, Parameter);

	EventParameter LevelChangeEvent;
	LevelChangeEvent.Stay = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			DownFloorFunc();
		};
	PlayerCollision->CollisionEvent(CollisionType::LevelChangeTrigger, LevelChangeEvent);

	EventParameter WallParameter;
	WallParameter.Stay = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			float4 PlayerPos = _This->Transform.GetWorldPosition();
			float4 StelePos = _Other->Transform.GetWorldPosition();

			SteleToPlayerMove(_Delta, (StelePos.X - PlayerPos.X));
		};
	PlayerCollision->CollisionEvent(CollisionType::Stele, WallParameter);
}

void Player::WeaponOn()
{
	if (true == WeaponHandCrossbow->IsUpdate())
	{
		return;
	}
	else
	{
		WeaponHandCrossbow->On();
	}
}

void Player::WeaponOff()
{
	WeaponHandCrossbow->Off();
}