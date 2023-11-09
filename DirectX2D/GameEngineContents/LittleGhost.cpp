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

	LittleGhostRenderer->SetSprite("LittleGhost_Idle");
	
	float4 Scale = LittleGhostRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	LittleGhostRenderer->SetImageScale(Scale);

	ChangeState(LittleGhostState::Idle);

	LittleGhostRenderer->LeftFlip();
}
void LittleGhost::Update(float _Delta)
{
	StateUpdate(_Delta);
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

}

void LittleGhost::MoveStart()
{
	ChangeAnimationState("Move");
}
void LittleGhost::MoveUpdate(float _Delta)
{

}

void LittleGhost::AttackStart()
{
	ChangeAnimationState("Attack");
}
void LittleGhost::AttackUpdate(float _Delta)
{

}

void LittleGhost::DirCheck()
{

}