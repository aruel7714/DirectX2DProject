#include "PreCompile.h"
#include "LittleGhost.h"

LittleGhost::LittleGhost()
{
}

LittleGhost::~LittleGhost()
{
}

void LittleGhost::Start()
{
	if (nullptr == GameEngineSprite::Find("LittleGhostMove"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Monster\\LittleGhost\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	LittleGhostRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);

	{
		LittleGhostRenderer->CreateAnimation("LittleGhost_Idle", "LittleGhostMove");
		LittleGhostRenderer->CreateAnimation("LittleGhost_Move", "LittleGhostMove");
		LittleGhostRenderer->CreateAnimation("LittleGhost_Attack", "LittleGhostAttack");
	}

	LittleGhostRenderer->SetSprite("LittleGhostMove");
	
	float4 Scale = LittleGhostRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	LittleGhostRenderer->SetImageScale(Scale);

	ChangeState(LittleGhostState::Idle);

	LittleGhostRenderer->LeftFlip();

	{
		LittleGhostCollision = CreateComponent<GameEngineCollision>(CollisionType::Monster);
		LittleGhostCollision->SetCollisionType(ColType::AABBBOX2D);
		LittleGhostCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });
		LittleGhostCollision->Transform.SetLocalScale(Scale);
	}
}
void LittleGhost::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (Dir == LittleGhostDir::Left)
	{
		LittleGhostRenderer->LeftFlip();
	}
	if (Dir == LittleGhostDir::Right)
	{
		LittleGhostRenderer->RightFlip();
	}
}

void LittleGhost::ChangeState(LittleGhostState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case LittleGhostState::Idle:
			IdleStart();
			break;
		case LittleGhostState::Move:
			MoveStart();
			break;
		case LittleGhostState::Attack:
			AttackStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void LittleGhost::StateUpdate(float _Delta)
{
	switch (State)
	{
	case LittleGhostState::Idle:
		return IdleUpdate(_Delta);
	case LittleGhostState::Move:
		return MoveUpdate(_Delta);
	case LittleGhostState::Attack:
		return AttackUpdate(_Delta);
	default:
		break;
	}
}
void LittleGhost::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "LittleGhost_";
	AnimationName += _State;
	LittleGhostRenderer->ChangeAnimation(AnimationName);
}

void LittleGhost::IdleStart()
{
	ChangeAnimationState("Idle");
}
void LittleGhost::IdleUpdate(float _Delta)
{
	ChangeState(LittleGhostState::Move);
}

void LittleGhost::MoveStart()
{
	ChangeAnimationState("Move");
	AttackTime = 0.0f;
}
void LittleGhost::MoveUpdate(float _Delta)
{
	DirCheck();

	float4 MyPos = Transform.GetLocalPosition();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

	SaveDir = PlayerPos - MyPos;
	Distance = SaveDir.Size();

	if (Distance < 200.0f)
	{
		MoveToAttackTime += _Delta;
	}

	SaveDir.Normalize();

	Transform.AddLocalPosition(SaveDir * _Delta * MoveSpeed);

	if (MoveToAttackTime > 0.5f)
	{
		ChangeState(LittleGhostState::Attack);
	}
}

void LittleGhost::AttackStart()
{
	ChangeAnimationState("Attack");
	MoveToAttackTime = 0.0f;
}
void LittleGhost::AttackUpdate(float _Delta)
{
	AttackTime += _Delta;

	Transform.AddLocalPosition(SaveDir * _Delta * AttackSpeed);

	if (AttackTime > 1.0f)
	{
		ChangeState(LittleGhostState::Move);
	}
}

void LittleGhost::DirCheck()
{
	float4 MyPos = Transform.GetLocalPosition();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

	float Check = MyPos.X - PlayerPos.X;

	if (Check > 0)
	{
		Dir = LittleGhostDir::Left;
	}
	else
	{
		Dir = LittleGhostDir::Right;
	}
}