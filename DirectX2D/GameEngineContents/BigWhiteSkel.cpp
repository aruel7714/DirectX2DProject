#include "PreCompile.h"
#include "BigWhiteSkel.h"
#include "Player.h"

BigWhiteSkel::BigWhiteSkel()
{
}

BigWhiteSkel::~BigWhiteSkel()
{
}

void BigWhiteSkel::Start()
{
	if (nullptr == GameEngineSprite::Find("BigWhiteSkelIdle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Monster\\BigWhiteSkel\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	BigWhiteSkelRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);

	{
		BigWhiteSkelRenderer->CreateAnimation("BigWhiteSkel_Idle", "BigWhiteSkelIdle");
		BigWhiteSkelRenderer->CreateAnimation("BigWhiteSkel_Move", "BigWhiteSkelMove");
		BigWhiteSkelRenderer->CreateAnimation("BigWhiteSkel_Attack", "BigWhiteSkelAttack");
		BigWhiteSkelRenderer->CreateAnimation("BigWhiteSkel_AttackReady", "BigWhiteSkelAttack", 0.1f, 0, 0, false);
	}

	BigWhiteSkelRenderer->SetSprite("BigWhiteSkelIdle");

	BigWhiteSkelRenderer->SetPivotType(PivotType::Bottom);
	float4 Scale = BigWhiteSkelRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	BigWhiteSkelRenderer->SetImageScale(Scale);

	ChangeState(BigWhiteSkelState::Idle);

	BigWhiteSkelRenderer->LeftFlip();

	{
		SkelCollision = CreateComponent<GameEngineCollision>(CollisionType::Monster);
		SkelCollision->SetCollisionType(ColType::AABBBOX2D);
		SkelCollision->Transform.SetLocalPosition({ 0.0f, Scale.Y / 2.0f, 1.0f });
		SkelCollision->Transform.SetLocalScale({ Scale.X / 2.0f, Scale.Y, 1.0f });
	}

	{
		AttackCollision = CreateComponent<GameEngineCollision>(CollisionType::Monster);
		AttackCollision->SetCollisionType(ColType::AABBBOX2D);
	}

	AttackCollision->Off();
	
	GameEngineInput::AddInputObject(this);

}
void BigWhiteSkel::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (Dir == BigWhiteSkelDir::Left)
	{
		BigWhiteSkelRenderer->LeftFlip();
	}
	else if (Dir == BigWhiteSkelDir::Right)
	{
		BigWhiteSkelRenderer->RightFlip();
	}
}

void BigWhiteSkel::ChangeState(BigWhiteSkelState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BigWhiteSkelState::Idle:
			IdleStart();
			break;
		case BigWhiteSkelState::Move:
			MoveStart();
			break;
		case BigWhiteSkelState::Attack:
			AttackStart();
			break;
		case BigWhiteSkelState::AttackReady:
			AttackReadyStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void BigWhiteSkel::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BigWhiteSkelState::Idle:
		return IdleUpdate(_Delta);
	case BigWhiteSkelState::Move:
		return MoveUpdate(_Delta);
	case BigWhiteSkelState::Attack:
		return AttackUpdate(_Delta);
	case BigWhiteSkelState::AttackReady:
		return AttackReadyUpdate(_Delta);
	default:
		break;
	}
}
void BigWhiteSkel::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "BigWhiteSkel_";
	AnimationName += _State;
	BigWhiteSkelRenderer->ChangeAnimation(AnimationName);
}

void BigWhiteSkel::IdleStart()
{
	ChangeAnimationState("Idle");
	float4 Scale = BigWhiteSkelRenderer->GetCurSprite().Texture->GetScale() *= 4.0f;
	BigWhiteSkelRenderer->SetImageScale(Scale);
	BigWhiteSkelRenderer->SetPivotType(PivotType::Bottom);
}
void BigWhiteSkel::IdleUpdate(float _Delta)
{
	float4 MyPos = Transform.GetLocalPosition();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

	float Check = MyPos.X - PlayerPos.X;
	
	Check = abs(Check);

	if (Check < 600.0f)
	{
		ChangeState(BigWhiteSkelState::Move);
	}
}

void BigWhiteSkel::MoveStart()
{
	ChangeAnimationState("Move");
	float4 Scale = BigWhiteSkelRenderer->GetCurSprite().Texture->GetScale() *= 4.0f;
	BigWhiteSkelRenderer->SetImageScale(Scale);
	BigWhiteSkelRenderer->SetPivotType(PivotType::Bottom);
	AttackCollision->Off();
}
void BigWhiteSkel::MoveUpdate(float _Delta)
{
	DirCheck();
	if (Dir == BigWhiteSkelDir::Left)
	{
		Transform.AddLocalPosition(float4::LEFT * MoveSpeed * _Delta);
	}
	else if (Dir == BigWhiteSkelDir::Right)
	{
		Transform.AddLocalPosition(float4::RIGHT * MoveSpeed * _Delta);
	}

	EventParameter AttackParameter;
	AttackParameter.Stay = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		MoveToAttackTime += _Delta;
	};
	
	MoveToAttackTime += SkelCollision->CollisionEvent(CollisionType::Player, AttackParameter);

	if (MoveToAttackTime >= 1.0f)
	{
		ChangeState(BigWhiteSkelState::AttackReady);
	}
}

void BigWhiteSkel::AttackReadyStart()
{
	ChangeAnimationState("AttackReady");
	float4 Scale = BigWhiteSkelRenderer->GetCurSprite().Texture->GetScale() *= 4.0f;
	BigWhiteSkelRenderer->SetImageScale(Scale);
	MoveToAttackTime = 0.0f;
	if (Dir == BigWhiteSkelDir::Left)
	{
		BigWhiteSkelRenderer->SetPivotValue({ 0.25f, 1.0f });
	}
	if (Dir == BigWhiteSkelDir::Right)
	{
		BigWhiteSkelRenderer->SetPivotValue({ 0.75f, 1.0f });
	}
}
void BigWhiteSkel::AttackReadyUpdate(float _Delta)
{
	AttackReadyTime += _Delta;

	if (AttackReadyTime >= 1.0f)
	{
		ChangeState(BigWhiteSkelState::Attack);
	}
}

void BigWhiteSkel::AttackStart()
{
	ChangeAnimationState("Attack");
	AttackReadyTime = 0.0f;
	AttackCollision->On();
	float4 Scale = BigWhiteSkelRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	BigWhiteSkelRenderer->SetImageScale(Scale);
	AttackCollision->Transform.SetLocalScale({ (Scale.X / 3.0f * 2.0f), (Scale.Y / 5.0f * 4.0f)});
	if (Dir == BigWhiteSkelDir::Left)
	{
		//SkelCollision->Transform.SetLocalPosition({ 0.0f, Scale.Y / 2.0f, 1.0f });
		BigWhiteSkelRenderer->SetPivotValue({ 0.25f, 1.0f });
		AttackCollision->Transform.SetLocalPosition({ -(Scale.X / 3.0f), Scale.Y / 5.0f * 2.0f, 1.0f });
	}
	if (Dir == BigWhiteSkelDir::Right)
	{
		BigWhiteSkelRenderer->SetPivotValue({ 0.75f, 1.0f });
		AttackCollision->Transform.SetLocalPosition({ Scale.X / 3.0f, Scale.Y / 5.0f * 2.0f, 1.0f });
	}
}
void BigWhiteSkel::AttackUpdate(float _Delta)
{


	if (true == BigWhiteSkelRenderer->IsCurAnimationEnd())
	{
		ChangeState(BigWhiteSkelState::Move);
	}
}

void BigWhiteSkel::DirCheck()
{
	float4 MyPos = Transform.GetLocalPosition();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

	float Check = MyPos.X - PlayerPos.X;

	if (Check > 0)
	{
		Dir = BigWhiteSkelDir::Left;
	}
	else
	{
		Dir = BigWhiteSkelDir::Right;
	}
}