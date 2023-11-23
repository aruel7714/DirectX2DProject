#include "PreCompile.h"
#include "Banshee.h"
#include "BansheeBullet.h"

Banshee::Banshee()
{
}

Banshee::~Banshee()
{
}

void Banshee::Start()
{
	if (nullptr == GameEngineSprite::Find("BansheeIdle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Monster\\Banshee\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	BansheeRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);
	
	{
		BansheeRenderer->CreateAnimation("Banshee_Idle", "BansheeIdle", 0.1f, -1, -1, true);
		BansheeRenderer->CreateAnimation("Banshee_Attack", "BansheeAttack", 0.1f, -1, -1, false);
	}

	BansheeRenderer->SetSprite("BansheeIdle");

	float4 Scale = BansheeRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	BansheeRenderer->SetImageScale(Scale);

	ChangeState(BansheeState::Idle);

	{
		// Status
		Hp = 40.0f;
	}

	{
		BansheeCollision = CreateComponent<GameEngineCollision>(CollisionType::Monster);
		BansheeCollision->SetCollisionType(ColType::AABBBOX2D);
		BansheeCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });
		BansheeCollision->Transform.SetLocalScale(Scale);
	}
}
void Banshee::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (Dir == BansheeDir::Left)
	{
		BansheeRenderer->LeftFlip();
	}
	if (Dir == BansheeDir::Right)
	{
		BansheeRenderer->RightFlip();
	}

	EventParameter DamageEvent;
	DamageEvent.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			DamageCheck();
		};
	BansheeCollision->CollisionEvent(CollisionType::Weapon, DamageEvent);


	if (Hp <= 0)
	{
		ChangeState(BansheeState::Death);
	}
}

void Banshee::ChangeState(BansheeState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BansheeState::Idle:
			IdleStart();
			break;
		case BansheeState::Attack:
			AttackStart();
			break;
		case BansheeState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void Banshee::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BansheeState::Idle:
		return IdleUpdate(_Delta);
	case BansheeState::Attack:
		return AttackUpdate(_Delta);
	case BansheeState::Death:
		return DeathUpdate(_Delta);
	default:
		break;
	}
}
void Banshee::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "Banshee_";
	AnimationName += _State;
	BansheeRenderer->ChangeAnimation(AnimationName);
}

void Banshee::IdleStart()
{
	ChangeAnimationState("Idle");
}
void Banshee::IdleUpdate(float _Delta)
{
	DirCheck();

	IdleToAttackTime += _Delta;

	if (IdleToAttackTime > 3.0f)
	{
		ChangeState(BansheeState::Attack);
	}
}

void Banshee::AttackStart()
{
	ChangeAnimationState("Attack");
	IdleToAttackTime = 0.0f;
	float4 MyPos = Transform.GetLocalPosition();
	for (int i = 0; i < 8; i++)
	{
		std::shared_ptr<BansheeBullet> Bullet = GetLevel()->CreateActor<BansheeBullet>(RenderOrder::MonsterProjectile);
		Bullet->Transform.SetLocalPosition(MyPos);
		Bullet->SetDir(i);
	}
}
void Banshee::AttackUpdate(float _Delta)
{
	if (true == BansheeRenderer->IsCurAnimationEnd())
	{
		ChangeState(BansheeState::Idle);
	}
}

void Banshee::DeathStart()
{
	Death();
}
void Banshee::DeathUpdate(float _Delta)
{

}

void Banshee::DirCheck()
{
	float4 MyPos = Transform.GetLocalPosition();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

	float Check = MyPos.X - PlayerPos.X;

	if (Check > 0)
	{
		Dir = BansheeDir::Left;
	}
	else
	{
		Dir = BansheeDir::Right;
	}
}