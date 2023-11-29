#include "PreCompile.h"
#include "BlueBat.h"
#include "MonsterLife.h"

BlueBat::BlueBat()
{
}

BlueBat::~BlueBat()
{
}

void BlueBat::Start()
{
	if (nullptr == GameEngineSprite::Find("BlueBatIdle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Monster\\BlueBat\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	BlueBatRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);
	
	{
		BlueBatRenderer->CreateAnimation("BlueBat_Move", "BlueBatIdle");
		BlueBatRenderer->CreateAnimation("BlueBat_Death", "Die", 0.025f, -1, -1, false);
	}

	BlueBatRenderer->SetSprite("BlueBatIdle");
	float4 Scale = BlueBatRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	BlueBatRenderer->SetImageScale(Scale);

	ChangeState(BlueBatState::Move);

	{
		// Status
		MaxHp = 6.0f;
		Hp = 6.0f;
		MoveSpeed = 100.0f;
		// Not ATtack
	}

	{
		BlueBatCollision = CreateComponent<GameEngineCollision>(CollisionType::Monster);
		BlueBatCollision->SetCollisionType(ColType::SPHERE2D);
		BlueBatCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });
		BlueBatCollision->Transform.SetLocalScale(Scale / 2.0f);
	}

	BlueBatLife = GetLevel()->CreateActor<MonsterLife>(RenderOrder::MonsterLifeBase);
	BlueBatLife->Off();
}

void BlueBat::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (Dir == BlueBatDir::Left)
	{
		BlueBatRenderer->LeftFlip();
	}
	if (Dir == BlueBatDir::Right)
	{
		BlueBatRenderer->RightFlip();
	}

	EventParameter DamageEvent;
	DamageEvent.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			DamageCheck();
		};
	BlueBatCollision->CollisionEvent(CollisionType::Weapon, DamageEvent);

	if (Hp < MaxHp)
	{
		BlueBatLife->On();
		BlueBatLife->Transform.SetLocalPosition({ Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 30.0f });
	}
	else
	{
		BlueBatLife->Off();
	}

	float Per = Hp / MaxHp * 100.0f;

	if (true == BlueBatLife->IsUpdate())
	{
		BlueBatLife->SetLifeBarScale(Per);
	}

	if (Hp <= 0)
	{
		ChangeState(BlueBatState::Death);
	}
}

void BlueBat::ChangeState(BlueBatState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BlueBatState::Move:
			MoveStart();
			break;
		case BlueBatState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void BlueBat::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BlueBatState::Move:
		return MoveUpdate(_Delta);
	case BlueBatState::Death:
		return DeathUpdate(_Delta);
	default:
		break;
	}
}
void BlueBat::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "BlueBat_";
	AnimationName += _State;
	BlueBatRenderer->ChangeAnimation(AnimationName);
}

void BlueBat::MoveStart()
{
	ChangeAnimationState("Move");
}
void BlueBat::MoveUpdate(float _Delta)
{
	DirCheck();
	AirWallCheck(_Delta, Transform.GetLocalPosition(), BlueBatRenderer->GetImageTransform().GetLocalScale() / 2.0f);

	MoveTime += _Delta;

	if (MoveTime >= 1.0f)
	{
		RandomDir = static_cast<float>(Random.RandomInt(1, 360));

		MoveTime = 0.0f;
	}

	float4 MoveDir = float4::GetUnitVectorFromRad(RandomDir);

	Transform.AddLocalPosition(MoveDir * _Delta * MoveSpeed);
}

void BlueBat::DeathStart()
{
	ChangeAnimationState("Death");
	float4 Scale = BlueBatRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	BlueBatRenderer->SetImageScale(Scale);
	BlueBatLife->Death();
}
void BlueBat::DeathUpdate(float _Delta)
{
	if (true == BlueBatRenderer->IsCurAnimationEnd())
	{
		Death();
	}
}

void BlueBat::DirCheck()
{
	float4 MyPos = Transform.GetLocalPosition();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

	float Check = MyPos.X - PlayerPos.X;

	if (Check > 0)
	{
		Dir = BlueBatDir::Left;
	}
	else
	{
		Dir = BlueBatDir::Right;
	}
}