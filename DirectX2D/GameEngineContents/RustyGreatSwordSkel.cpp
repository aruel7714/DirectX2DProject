#include "PreCompile.h"
#include "RustyGreatSwordSkel.h"

RustyGreatSwordSkel::RustyGreatSwordSkel()
{
}

RustyGreatSwordSkel::~RustyGreatSwordSkel()
{
}

void RustyGreatSwordSkel::Start()
{
	if (nullptr == GameEngineSprite::Find("RustyGreatSword"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Monster\\Skel\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	RustyGreatSwordSkelRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);
	RustyGreatSwordRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MonsterWeapon);

	{
		RustyGreatSwordSkelRenderer->CreateAnimation("RustyGreatSwordSkel_Idle", "SkelIdle");
		RustyGreatSwordSkelRenderer->CreateAnimation("RustyGreatSwordSkel_Move", "SkelWalk");
		RustyGreatSwordSkelRenderer->CreateAnimation("RustyGreatSwordSkel_Attack", "SkelAttack");
		RustyGreatSwordSkelRenderer->CreateAnimation("RustyGreatSwordSkel_AttackReady", "SkelAttack");
	}
	{
		RustyGreatSwordRenderer->CreateAnimation("RustyGreatSword_Idle", "RustyGreatSword", 0.1f, 0, 0, false);
		RustyGreatSwordRenderer->CreateAnimation("RustyGreatSword_Attack", "RustyGreatSword", 0.1f, 1, 14, false);
		RustyGreatSwordRenderer->CreateAnimation("RustyGreatSword_AttackReady", "RustyGreatSword", 0.1f, 1, 1, false);
	}

	RustyGreatSwordSkelRenderer->SetSprite("SkelIdle");

	RustyGreatSwordSkelRenderer->SetPivotType(PivotType::Bottom);
	float4 SkelScale = RustyGreatSwordSkelRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	RustyGreatSwordSkelRenderer->SetImageScale(SkelScale);

	ChangeSkelState(RustyGreatSwordSkelState::Idle);

	RustyGreatSwordRenderer->SetSprite("RustyGreatSword");
	float4 SwordScale = RustyGreatSwordRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	RustyGreatSwordRenderer->SetImageScale(SwordScale);
	
	ChangeSwordState(RustyGreatSwordState::Attack);
}
void RustyGreatSwordSkel::Update(float _Delta)
{
	SkelStateUpdate(_Delta);
	SwordStateUpdate(_Delta);

	float4 Pos = float4::ZERO;
	float4 Scale = RustyGreatSwordSkelRenderer->GetImageTransform().GetLocalScale();

	Pos.Y += (Scale.Y / 4.0f) + 6.0f;

	if (SkelDir == RustyGreatSwordSkelDir::Right)
	{
		Pos.X += Scale.X / 8.0f * 3.0f;
		RustyGreatSwordSkelRenderer->RightFlip();
		RustyGreatSwordRenderer->RightFlip();
	}
	if (SkelDir == RustyGreatSwordSkelDir::Left)
	{
		Pos.X -= Scale.X / 8.0f * 3.0f;
		RustyGreatSwordSkelRenderer->LeftFlip();
		RustyGreatSwordRenderer->LeftFlip();
	}
	
	RustyGreatSwordRenderer->Transform.SetLocalPosition(Pos);
}

void RustyGreatSwordSkel::ChangeSkelState(RustyGreatSwordSkelState _State)
{
	if (_State != SkelState)
	{
		switch (_State)
		{
		case RustyGreatSwordSkelState::Idle:
			SkelIdleStart();
			break;
		case RustyGreatSwordSkelState::Move:
			SkelMoveStart();
			break;
		case RustyGreatSwordSkelState::Attack:
			SkelAttackStart();
			break;
		case RustyGreatSwordSkelState::AttackReady:
			SkelAttackReadyStart();
			break;
		default:
			break;
		}
	}
	SkelState = _State;
}
void RustyGreatSwordSkel::SkelStateUpdate(float _Delta)
{
	switch (SkelState)
	{
	case RustyGreatSwordSkelState::Idle:
		return SkelIdleUpdate(_Delta);
	case RustyGreatSwordSkelState::Move:
		return SkelMoveUpdate(_Delta);
	case RustyGreatSwordSkelState::Attack:
		return SkelAttackUpdate(_Delta);
	case RustyGreatSwordSkelState::AttackReady:
		return SkelAttackReadyUpdate(_Delta);
	default:
		break;
	}
}
void RustyGreatSwordSkel::ChangeSkelAnimationState(const std::string& _State)
{
	std::string AnimationName = "RustyGreatSwordSkel_";
	AnimationName += _State;
	RustyGreatSwordSkelRenderer->ChangeAnimation(AnimationName);
}

void RustyGreatSwordSkel::ChangeSwordState(RustyGreatSwordState _State)
{
	if (_State != SwordState)
	{
		switch (_State)
		{
		case RustyGreatSwordState::Idle:
			SwordIdleStart();
			break;
		case RustyGreatSwordState::Attack:
			SwordAttackStart();
			break;
		case RustyGreatSwordState::AttackReady:
			SwordAttackReadyStart();
			break;
		default:
			break;
		}
	}
	SwordState = _State;
}
void RustyGreatSwordSkel::SwordStateUpdate(float _Delta)
{
	switch (SwordState)
	{
	case RustyGreatSwordState::Idle:
		SwordIdleUpdate(_Delta);
	case RustyGreatSwordState::Attack:
		SwordAttackUpdate(_Delta);
	case RustyGreatSwordState::AttackReady:
		SwordAttackReadyUpdate(_Delta);
	default:
		break;
	}
}
void RustyGreatSwordSkel::ChangeSwordAnimationState(const std::string& _State)
{
	std::string AnimationName = "RustyGreatSword_";
	AnimationName += _State;
	RustyGreatSwordRenderer->ChangeAnimation(AnimationName);
}

void RustyGreatSwordSkel::SkelIdleStart()
{
	ChangeSkelAnimationState("Idle");
}
void RustyGreatSwordSkel::SkelIdleUpdate(float _Delta)
{

}

void RustyGreatSwordSkel::SkelMoveStart()
{
	ChangeSkelAnimationState("Move");
}
void RustyGreatSwordSkel::SkelMoveUpdate(float _Delta)
{

}

void RustyGreatSwordSkel::SkelAttackReadyStart()
{
	ChangeSkelAnimationState("AttackReady");
}
void RustyGreatSwordSkel::SkelAttackReadyUpdate(float _Delta)
{

}

void RustyGreatSwordSkel::SkelAttackStart()
{
	ChangeSkelAnimationState("Attack");
}
void RustyGreatSwordSkel::SkelAttackUpdate(float _Delta)
{

}

void RustyGreatSwordSkel::SwordIdleStart()
{
	ChangeSwordAnimationState("Idle");
}
void RustyGreatSwordSkel::SwordIdleUpdate(float _Delta)
{

}

void RustyGreatSwordSkel::SwordAttackReadyStart()
{
	ChangeSwordAnimationState("AttackReady");
}
void RustyGreatSwordSkel::SwordAttackReadyUpdate(float _Delta)
{

}

void RustyGreatSwordSkel::SwordAttackStart()
{
	ChangeSwordAnimationState("Attack");
}
void RustyGreatSwordSkel::SwordAttackUpdate(float _Delta)
{
	if (RustyGreatSwordRenderer->IsCurAnimationEnd())
	{
		ChangeSwordState(RustyGreatSwordState::Idle);
	}
}