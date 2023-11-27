#include "PreCompile.h"
#include "RedBat.h"
#include "BatBullet.h"

RedBat::RedBat()
{
}

RedBat::~RedBat()
{
}

void RedBat::Start()
{
	if (nullptr == GameEngineSprite::Find("RedBatIdle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Monster\\RedBat\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	RedBatRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);

	{
		RedBatRenderer->CreateAnimation("RedBat_Move", "RedBatIdle");
		RedBatRenderer->CreateAnimation("RedBat_AttackReady", "RedBatAttack", 0.1f, 0, 4, false);
		RedBatRenderer->CreateAnimation("RedBat_Attack", "RedBatAttack", 0.1f, 5, 9, false);
		RedBatRenderer->CreateAnimation("RedBat_Death", "Die", 0.025f, -1, -1, false);
	}

	RedBatRenderer->SetSprite("RedBatIdle");
	float4 Scale = RedBatRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	RedBatRenderer->SetImageScale(Scale);

	ChangeState(RedBatState::Move);

	{
		// Status
		MoveSpeed = 100.0f;
	}

	{
		RedBatCollision = CreateComponent<GameEngineCollision>(CollisionType::Monster);
		RedBatCollision->SetCollisionType(ColType::SPHERE2D);
		RedBatCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });
		RedBatCollision->Transform.SetLocalScale(Scale / 2.0f);
	}

	{
		//Status
		// Hp = 16.0f;
		// Damage = 5.0f;
	}
	//IdleToAttackTime > 2.5f ?
}

void RedBat::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (Dir == RedBatDir::Left)
	{
		RedBatRenderer->LeftFlip();
	}
	if (Dir == RedBatDir::Right)
	{
		RedBatRenderer->RightFlip();
	}

	EventParameter DamageEvent;
	DamageEvent.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			DamageCheck();
		};
	RedBatCollision->CollisionEvent(CollisionType::Weapon, DamageEvent);


	/*if (Hp <= 0)
	{
		ChangeState(RedBatState::Death);
	}*/
}

void RedBat::ChangeState(RedBatState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case RedBatState::Move:
			MoveStart();
			break;
		case RedBatState::AttackReady:
			AttackReadyStart();
			break;
		case RedBatState::Attack:
			AttackStart();
			break;
		case RedBatState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void RedBat::StateUpdate(float _Delta)
{
	switch (State)
	{
	case RedBatState::Move:
		return MoveUpdate(_Delta);
	case RedBatState::AttackReady:
		return AttackReadyUpdate(_Delta);
	case RedBatState::Attack:
		return AttackUpdate(_Delta);
	case RedBatState::Death:
		return DeathUpdate(_Delta);
	default:
		break;
	}
}
void RedBat::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "RedBat_";
	AnimationName += _State;
	RedBatRenderer->ChangeAnimation(AnimationName);
}

void RedBat::MoveStart()
{
	ChangeAnimationState("Move");
}
void RedBat::MoveUpdate(float _Delta)
{
	DirCheck();
	AirWallCheck(_Delta, Transform.GetLocalPosition(), RedBatRenderer->GetImageTransform().GetLocalScale() / 2.0f);

	MoveTime += _Delta;
	AttackTime += _Delta;

	if (MoveTime >= 1.0f)
	{
		RandomDir = static_cast<float>(Random.RandomInt(1, 360));

		MoveTime = 0.0f;
	}

	float4 MoveDir = float4::GetUnitVectorFromRad(RandomDir);

	Transform.AddLocalPosition(MoveDir * _Delta * MoveSpeed);

	if (AttackTime >= 2.5f)
	{
		ChangeState(RedBatState::AttackReady);
	}
}

void RedBat::AttackReadyStart()
{
	ChangeAnimationState("AttackReady");
	MoveTime = 0.0f;
	AttackTime = 0.0f;
}
void RedBat::AttackReadyUpdate(float _Delta)
{
	float4 PlayerScale = Player::GetMainPlayer()->GetRendererScale();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

	PlayerPos.Y += (PlayerScale.Y / 4.0f);

	float4 Scale = RedBatRenderer->GetImageTransform().GetLocalScale();
	float4 MyPos = Transform.GetLocalPosition();

	float4 TargetPos = MyPos - PlayerPos;

	SaveDir = TargetPos.NormalizeReturn();

	if (RedBatRenderer->IsCurAnimationEnd())
	{
		ChangeState(RedBatState::Attack);
	}
}

void RedBat::AttackStart()
{
	ChangeAnimationState("Attack");
	std::shared_ptr<BatBullet> Bullet = GetLevel()->CreateActor<BatBullet>(RenderOrder::MonsterProjectile);

	float4 BatPos = Transform.GetLocalPosition();
	
	Bullet->Transform.SetLocalPosition(BatPos);
	Bullet->Dir = SaveDir * -1.0f;
}
void RedBat::AttackUpdate(float _Delta)
{
	if (RedBatRenderer->IsCurAnimationEnd())
	{
		ChangeState(RedBatState::Move);
	}
}

void RedBat::DeathStart()
{
	ChangeAnimationState("Death");
	float4 Scale = RedBatRenderer->GetCurSprite().Texture->GetScale() *= 4.0f;
	RedBatRenderer->SetImageScale(Scale);
}
void RedBat::DeathUpdate(float _Delta)
{
	if (true == RedBatRenderer->IsCurAnimationEnd())
	{
		Death(); 
	}
}

void RedBat::DirCheck()
{
	float4 MyPos = Transform.GetLocalPosition();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

	float Check = MyPos.X - PlayerPos.X;

	if (Check > 0)
	{
		Dir = RedBatDir::Left;
	}
	else
	{
		Dir = RedBatDir::Right;
	}
}