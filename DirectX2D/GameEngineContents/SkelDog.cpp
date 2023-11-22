#include "PreCompile.h"
#include "SkelDog.h"

SkelDog::SkelDog()
{
}

SkelDog::~SkelDog()
{
}

void SkelDog::Start()
{
	if (nullptr == GameEngineSprite::Find("BigWhiteSkelIdle"))
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
		SkelDogRenderer->CreateAnimation("SkelDog_Attack", "SkelDogMove", 0.1f, -1, -1, false);
	}

	SkelDogRenderer->SetSprite("SkelDogIdle");
	float4 Scale = SkelDogRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	SkelDogRenderer->SetImageScale(Scale);

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

	ChangeState(SkelDogState::Idle);
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
}

void SkelDog::ChangeState(SkelDogState _State)
{
	if (_State == State)
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
	DirCheck();
}

void SkelDog::AttackReadyStart()
{
	ChangeAnimationState("AttackReady");
}
void SkelDog::AttackReadyUpdate(float _Delta)
{
	if (SkelDogRenderer->IsCurAnimationEnd())
	{
		ChangeState(SkelDogState::Attack);
	}
}

void SkelDog::AttackStart()
{
	ChangeAnimationState("Attack");
	SkelDogAttackCollision->On();
}
void SkelDog::AttackUpdate(float _Delta)
{
	GravityState(_Delta, Transform.GetLocalPosition(), SkelDogRenderer->GetImageTransform().GetLocalScale());

	float4 Pos = Transform.GetWorldPosition();
	GameEngineColor Color = BackGround::DebugBackGround->GetColor(Pos, GameEngineColor::RED);

	if (GameEngineColor::RED == Color || (GameEngineColor::BLUE == Color && PassBlue == false))
	{
		ChangeState(SkelDogState::Move);
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