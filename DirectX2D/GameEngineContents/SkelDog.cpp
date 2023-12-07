#include "PreCompile.h"
#include "SkelDog.h"
#include "MonsterLife.h"

SkelDog::SkelDog()
{
}

SkelDog::~SkelDog()
{
}

void SkelDog::Start()
{
	if (nullptr == GameEngineSprite::Find("SkelDogIdle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Monster\\SkelDog\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	SkelDogRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);

	{
		SkelDogRenderer->CreateAnimation("SkelDog_Idle", "SkelDogIdle");
		SkelDogRenderer->CreateAnimation("SkelDog_Move", "SkelDogRun");
		SkelDogRenderer->CreateAnimation("SkelDog_AttackReady", "SkelDogIdle", 0.1f, -1, -1, false);
		SkelDogRenderer->CreateAnimation("SkelDog_Attack", "SkelDogRun", 0.1f, 0, 3, false);
		SkelDogRenderer->CreateAnimation("SkelDog_Death", "Die", 0.025f, -1, -1, false);
	}

	SkelDogRenderer->SetSprite("SkelDogIdle");
	SkelDogRenderer->SetPivotType(PivotType::Bottom);
	float4 Scale = SkelDogRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	SkelDogRenderer->SetImageScale(Scale);

	ChangeState(SkelDogState::Idle);

	{
		// Status
		MaxHp = 20.0f;
		Hp = 20.0f;
		MoveSpeed 420.0f;
		Damage = 10.0f;
	}

	{
		SkelDogCollision = CreateComponent<GameEngineCollision>(CollisionType::Monster);
		SkelDogCollision->SetCollisionType(ColType::AABBBOX2D);
		SkelDogCollision->Transform.SetLocalPosition({ 0.0f, Scale.Y / 2.0f, 1.0f });
		SkelDogCollision->Transform.SetLocalScale({ Scale.X, Scale.Y, 1.0f });
	}
	{
		SkelDogAttackCollision = CreateComponent<GameEngineCollision>(CollisionType::MonsterAttack);
		SkelDogAttackCollision->SetCollisionType(ColType::AABBBOX2D);
		SkelDogAttackCollision->Transform.SetLocalPosition({ 0.0f, Scale.Y / 2.0f, 1.0f });
		SkelDogAttackCollision->Transform.SetLocalScale({ Scale.X, Scale.Y, 1.0f });
	}

	SkelDogAttackCollision->Off();

	SkelDogLife = GetLevel()->CreateActor<MonsterLife>(RenderOrder::MonsterLifeBase);
	SkelDogLife->Off();
}

void SkelDog::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (Dir == SkelDogDir::Left)
	{
		SkelDogRenderer->LeftFlip();
	}
	else if (Dir == SkelDogDir::Right)
	{
		SkelDogRenderer->RightFlip();
	}

	EventParameter DamageEvent;
	DamageEvent.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			DamageCheck();
		};
	SkelDogCollision->CollisionEvent(CollisionType::Weapon, DamageEvent);

	if (Hp < MaxHp)
	{
		SkelDogLife->On();
		SkelDogLife->Transform.SetLocalPosition({ Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 15.0f });
	}
	else
	{
		SkelDogLife->Off();
	}

	float Per = Hp / MaxHp * 100.0f;

	if (true == SkelDogLife->IsUpdate())
	{
		SkelDogLife->SetLifeBarScale(Per);
	}

	if (Hp <= 0)
	{
		ChangeState(SkelDogState::Death);
	}
}

void SkelDog::ChangeState(SkelDogState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case SkelDogState::Idle:
			IdleStart();
			break;
		case SkelDogState::Move:
			MoveStart();
			break;
		case SkelDogState::AttackReady:
			AttackReadyStart();
			break;
		case SkelDogState::Attack:
			AttackStart();
			break;
		case SkelDogState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void SkelDog::StateUpdate(float _Delta)
{
	switch (State)
	{
	case SkelDogState::Idle:
		return IdleUpdate(_Delta);
	case SkelDogState::Move:
		return MoveUpdate(_Delta);
	case SkelDogState::AttackReady:
		return AttackReadyUpdate(_Delta);
	case SkelDogState::Attack:
		return AttackUpdate(_Delta);
	case SkelDogState::Death:
		return DeathUpdate(_Delta);
	default:
		break;
	}
}
void SkelDog::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "SkelDog_";
	AnimationName += _State;
	SkelDogRenderer->ChangeAnimation(AnimationName);
}

void SkelDog::IdleStart()
{
	ChangeAnimationState("Idle");
}
void SkelDog::IdleUpdate(float _Delta)
{
	float4 MyPos = Transform.GetLocalPosition();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

	float Check = MyPos.X - PlayerPos.X;

	Check = abs(Check);

	if (Check < 600.0f)
	{
		ChangeState(SkelDogState::Move);
	}
}

void SkelDog::MoveStart()
{
	ChangeAnimationState("Move");
}
void SkelDog::MoveUpdate(float _Delta)
{
	GravityState(_Delta, Transform.GetLocalPosition(), SkelDogRenderer->GetImageTransform().GetLocalScale());
	DirCheck();

	if (Dir == SkelDogDir::Left)
	{
		Transform.AddLocalPosition(float4::LEFT * MoveSpeed * _Delta);
	}
	else if (Dir == SkelDogDir::Right)
	{
		Transform.AddLocalPosition(float4::RIGHT * MoveSpeed * _Delta);
	}

	EventParameter AttackParameter;
	AttackParameter.Stay = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		MoveToAttackTime += _Delta;
	};
	SkelDogCollision->CollisionEvent(CollisionType::Player, AttackParameter);

	if (MoveToAttackTime >= 0.5f)
	{
		ChangeState(SkelDogState::AttackReady);
	}
}

void SkelDog::AttackReadyStart()
{
	ChangeAnimationState("AttackReady");
}
void SkelDog::AttackReadyUpdate(float _Delta)
{
	GravityState(_Delta, Transform.GetLocalPosition(), SkelDogRenderer->GetImageTransform().GetLocalScale());
	if (SkelDogRenderer->IsCurAnimationEnd())
	{
		ChangeState(SkelDogState::Attack);
	}
}

void SkelDog::AttackStart()
{
	Transform.SetLocalPosition(Transform.GetLocalPosition() + float4::UP);
	if (Dir == SkelDogDir::Left)
	{
		SetGravityForce((float4::UP + float4::LEFT) * 400.0f);
	}
	else if (Dir == SkelDogDir::Right)
	{
		SetGravityForce((float4::UP + float4::RIGHT) * 400.0f);
	}
	MoveToAttackTime = 0.0f;
	ChangeAnimationState("Attack");
	SkelDogAttackCollision->On();
}
void SkelDog::AttackUpdate(float _Delta)
{
	GravityState(_Delta, Transform.GetLocalPosition(), SkelDogRenderer->GetImageTransform().GetLocalScale());

	if (GravityForce.Y <= 0)
	{
		float4 Pos = Transform.GetWorldPosition();
		GameEngineColor Color = BackGround::DebugBackGround->GetColor(Pos, GameEngineColor::RED);

		if (GameEngineColor::RED == Color || (GameEngineColor::BLUE == Color && PassBlue == false))
		{
			SkelDogAttackCollision->Off();
			ChangeState(SkelDogState::Move);
		}
	}
}

void SkelDog::DeathStart()
{
	DogSound = GameEngineSound::SoundPlay("Explosion.wav");
	ChangeAnimationState("Death");
	float4 Scale = SkelDogRenderer->GetCurSprite().Texture->GetScale() *= 4.0f;
	SkelDogRenderer->SetImageScale(Scale);
	SkelDogRenderer->SetPivotType(PivotType::Center);
	SkelDogLife->Death();
}
void SkelDog::DeathUpdate(float _Delta)
{
	if (true == SkelDogRenderer->IsCurAnimationEnd())
	{
		Death();
	}
}

void SkelDog::DirCheck()
{
	float4 MyPos = Transform.GetLocalPosition();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

	float Check = MyPos.X - PlayerPos.X;

	if (Check > 0)
	{
		Dir = SkelDogDir::Left;
	}
	else
	{
		Dir = SkelDogDir::Right;
	}
}