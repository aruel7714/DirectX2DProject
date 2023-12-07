#include "PreCompile.h"
#include "Minotaurs.h"
#include "MonsterLife.h"

Minotaurs::Minotaurs()
{
}

Minotaurs::~Minotaurs()
{
}

void Minotaurs::Start()
{
	if (nullptr == GameEngineSprite::Find("MinotaursIdle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Monster\\Minotaurs\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	MinotaursRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);

	{
		MinotaursRenderer->CreateAnimation("Minotaurs_Idle", "MinotaursIdle");
		MinotaursRenderer->CreateAnimation("Minotaurs_Charge", "MinotaursCharge", 0.1f, 0, 3, false);
		MinotaursRenderer->CreateAnimation("Minotaurs_Rush", "MinotaursCharge", 0.1f, 4, 7, false);
		MinotaursRenderer->CreateAnimation("Minotaurs_AttackReady", "MinotaursAttack", 0.1f, 0, 2, false);
		MinotaursRenderer->CreateAnimation("Minotaurs_Attack", "MinotaursAttack", 0.1f, 3, 6, false);
		MinotaursRenderer->CreateAnimation("Minotaurs_Death", "Die", 0.025f, -1, -1, false);
	}

	MinotaursRenderer->SetSprite("MinotaursIdle");
	
	MinotaursRenderer->SetPivotType(PivotType::Bottom);
	float4 Scale = MinotaursRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	MinotaursRenderer->SetImageScale(Scale);

	ChangeState(MinotaursState::Stay);

	{
		// Status
		MaxHp = 85.0f;
		Hp = 85.0f;
		Damage = 18.0f;
	}

	{
		MinotaursCollision = CreateComponent<GameEngineCollision>(CollisionType::Monster);
		MinotaursCollision->SetCollisionType(ColType::AABBBOX2D);
		MinotaursCollision->Transform.SetLocalPosition({ 0.0f, Scale.Y / 3.0f, 1.0f });
		MinotaursCollision->Transform.SetLocalScale({ Scale.X / 3.0f * 2.0f, Scale.Y / 3.0f * 2.0f, 1.0f });
	}

	{
		RushCollision = CreateComponent<GameEngineCollision>(CollisionType::MonsterAttack);
		RushCollision->SetCollisionType(ColType::AABBBOX2D);
		RushCollision->Transform.SetLocalPosition({ 0.0f, Scale.Y / 3.0f, 1.0f });
		RushCollision->Transform.SetLocalScale({ Scale.X / 3.0f * 2.0f, Scale.Y / 3.0f * 2.0f, 1.0f });
	}

	{
		AttackCollision = CreateComponent<GameEngineCollision>(CollisionType::MonsterAttack);
		AttackCollision->SetCollisionType(ColType::AABBBOX2D);
		AttackCollision->Transform.SetLocalScale({ Scale.X / 3.0f * 2.0f, Scale.Y / 3.0f * 2.0f, 1.0f });
	}

	RushCollision->Off();
	AttackCollision->Off();

	MinotaursLife = GetLevel()->CreateActor<MonsterLife>(RenderOrder::MonsterLifeBase);
	MinotaursLife->Off();
}
void Minotaurs::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (Dir == MinotaursDir::Left)
	{
		MinotaursRenderer->SetPivotValue({ 0.35f, 1.0f });
		MinotaursRenderer->LeftFlip();
	}
	else if (Dir == MinotaursDir::Right)
	{
		MinotaursRenderer->SetPivotValue({ 0.65f, 1.0f });
		MinotaursRenderer->RightFlip();
	}

	EventParameter DamageEvent;
	DamageEvent.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			DamageCheck();
		};
	MinotaursCollision->CollisionEvent(CollisionType::Weapon, DamageEvent);

	if (Hp < MaxHp)
	{
		MinotaursLife->On();
		MinotaursLife->Transform.SetLocalPosition({ Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 30.0f });
	}
	else
	{
		MinotaursLife->Off();
	}

	float Per = Hp / MaxHp * 100.0f;

	if (true == MinotaursLife->IsUpdate())
	{
		MinotaursLife->SetLifeBarScale(Per);
	}

	if (Hp <= 0)
	{
		ChangeState(MinotaursState::Death);
	}
}

void Minotaurs::ChangeState(MinotaursState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case MinotaursState::Idle:
			IdleStart();
			break;
		case MinotaursState::Charge:
			ChargeStart();
			break;
		case MinotaursState::Rush:
			RushStart();
			break;
		case MinotaursState::AttackReady:
			AttackReadyStart();
			break;
		case MinotaursState::Attack:
			AttackStart();
			break;
		case MinotaursState::Death:
			DeathStart();
			break;
		case MinotaursState::Stay:
			StayStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void Minotaurs::StateUpdate(float _Delta)
{
	switch (State)
	{
	case MinotaursState::Idle:
		return IdleUpdate(_Delta);
	case MinotaursState::Charge:
		return ChargeUpdate(_Delta);
	case MinotaursState::Rush:
		return RushUpdate(_Delta);
	case MinotaursState::AttackReady:
		return AttackReadyUpdate(_Delta);
	case MinotaursState::Attack:
		return AttackUpdate(_Delta);
	case MinotaursState::Death:
		return DeathUpdate(_Delta);
	case MinotaursState::Stay:
		return StayUpdate(_Delta);
	default:
		break;
	}
}
void Minotaurs::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "Minotaurs_";
	AnimationName += _State;
	MinotaursRenderer->ChangeAnimation(AnimationName);
}

void Minotaurs::IdleStart()
{
	ChangeAnimationState("Idle");
}
void Minotaurs::IdleUpdate(float _Delta)
{
	DirCheck();
	IdleToAttackTime += _Delta;

	float4 MyPos = Transform.GetLocalPosition();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

	float Check = MyPos.X - PlayerPos.X;
	
	// IdleToAttackTime > 2.0f;

	if (IdleToAttackTime >= 2.0f)
	{
		if (abs(Check) <= 200.0f)
		{
			ChangeState(MinotaursState::AttackReady);
		}
		else if (abs(Check) > 200.0f)
		{
			ChangeState(MinotaursState::Charge);
		}
	}
	
}

void Minotaurs::ChargeStart()
{
	MinotaursSound = GameEngineSound::SoundPlay("minotaur_dashready.wav");
	ChangeAnimationState("Charge");
	IdleToAttackTime = 0.0f;
}
void Minotaurs::ChargeUpdate(float _Delta)
{
	ChargeTime += _Delta;
	
	if (ChargeTime >= 0.5f)
	{
		ChangeState(MinotaursState::Rush);
	}
}

void Minotaurs::RushStart()
{
	MinotaursSound = GameEngineSound::SoundPlay("minotaur_dash.wav");
	ChangeAnimationState("Rush");
	ChargeTime = 0.0f;
	RushCollision->On();

	if (Dir == MinotaursDir::Left)
	{
		RushDir = float4::LEFT;
	}
	else if (Dir == MinotaursDir::Right)
	{
		RushDir = float4::RIGHT;
	}

}
void Minotaurs::RushUpdate(float _Delta)
{
	RushTime += _Delta;

	Transform.AddLocalPosition(RushDir * _Delta * RushSpeed);

	if (RushTime > 0.4f && true == MinotaursRenderer->IsCurAnimationEnd())
	{
		ChangeState(MinotaursState::AttackReady);
		RushCollision->Off();
	}
}

void Minotaurs::AttackReadyStart()
{
	ChangeAnimationState("AttackReady");
	DirCheck();
	RushTime = 0.0f;
	IdleToAttackTime = 0.0f;
}
void Minotaurs::AttackReadyUpdate(float _Delta)
{
	AttackReadyTime += _Delta;

	if (AttackReadyTime > 1.0f)
	{
		ChangeState(MinotaursState::Attack);
	}
}

void Minotaurs::AttackStart()
{
	MinotaursSound = GameEngineSound::SoundPlay("minotaur_attack.wav");
	ChangeAnimationState("Attack");
	AttackReadyTime = 0.0f;
	AttackCollision->On();
	float4 Scale = MinotaursRenderer->GetCurSprite().Texture->GetScale() * 4.0f;

	if (Dir == MinotaursDir::Left)
	{
		AttackCollision->Transform.SetLocalPosition({ -(Scale.X / 4.0f), Scale.Y / 3.0f, 1.0f });
	}
	if (Dir == MinotaursDir::Right)
	{
		AttackCollision->Transform.SetLocalPosition({ Scale.X / 4.0f, Scale.Y / 3.0f, 1.0f });
	}
}
void Minotaurs::AttackUpdate(float _Delta)
{
	if (MinotaursRenderer->IsCurAnimationEnd())
	{
		ChangeState(MinotaursState::Idle);
		AttackCollision->Off();
	}
}

void Minotaurs::DeathStart()
{
	MinotaursSound = GameEngineSound::SoundPlay("Explosion_02.wav");
	ChangeAnimationState("Death");
	float4 Scale = MinotaursRenderer->GetCurSprite().Texture->GetScale() *= 4.0f;
	MinotaursRenderer->SetImageScale(Scale);
	MinotaursRenderer->SetPivotType(PivotType::Center);
	MinotaursLife->Death();
}
void Minotaurs::DeathUpdate(float _Delta)
{
	if (true == MinotaursRenderer->IsCurAnimationEnd())
	{
		Death();
	}
}

void Minotaurs::StayStart()
{
	ChangeAnimationState("Idle");
}
void Minotaurs::StayUpdate(float _Delta)
{
	float4 MyPos = Transform.GetLocalPosition();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

	float Check = MyPos.Y - PlayerPos.Y;

	if (abs(Check) < 10.0f)
	{
		ChangeState(MinotaursState::Idle);
	}
}

void Minotaurs::DirCheck()
{
	float4 MyPos = Transform.GetLocalPosition();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

	float Check = MyPos.X - PlayerPos.X;

	if (Check > 0)
	{
		Dir = MinotaursDir::Left;
	}
	else
	{
		Dir = MinotaursDir::Right;
	}
}