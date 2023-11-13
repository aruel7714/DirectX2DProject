#include "PreCompile.h"
#include "RustyShortSwordSkel.h"

RustyShortSwordSkel::RustyShortSwordSkel()
{
}

RustyShortSwordSkel::~RustyShortSwordSkel()
{
}

void RustyShortSwordSkel::Start()
{
	if (nullptr == GameEngineSprite::Find("RustyShortSword"))
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

	RustyShortSwordSkelRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);
	RustyShortSwordRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MonsterWeapon);

	{
		RustyShortSwordSkelRenderer->CreateAnimation("RustyShortSwordSkel_Idle", "SkelIdle");
		RustyShortSwordSkelRenderer->CreateAnimation("RustyShortSwordSkel_Move", "SkelWalk");
		RustyShortSwordSkelRenderer->CreateAnimation("RustyShortSwordSkel_AttackReady", "SkelAttack");
		RustyShortSwordSkelRenderer->CreateAnimation("RustyShortSwordSkel_Attack", "SkelAttack");
	}
	{
		RustyShortSwordRenderer->CreateAnimation("RustyShortSword_Idle", "RustyShortSword", 0.1f, 0, 0, false);
		RustyShortSwordRenderer->CreateAnimation("RustyShortSword_AttackReady", "RustyShortSword", 0.1f, 1, 4, false);
		RustyShortSwordRenderer->CreateAnimation("RustyShortSword_Attack", "RustyShortSword", 0.1f, 5, 11, false);
	}

	RustyShortSwordSkelRenderer->SetSprite("SkelIdle");

	RustyShortSwordSkelRenderer->SetPivotType(PivotType::Bottom);
	float4 SkelScale = RustyShortSwordSkelRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	RustyShortSwordSkelRenderer->SetImageScale(SkelScale);

	ChangeSkelState(RustyShortSwordSkelState::Idle);

	RustyShortSwordRenderer->SetSprite("RustyShortSword");
	float4 SwordScale = RustyShortSwordRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	RustyShortSwordRenderer->SetImageScale(SwordScale);

	ChangeSwordState(RustyShortSwordState::Idle);
}
void RustyShortSwordSkel::Update(float _Delta)
{
	SkelStateUpdate(_Delta);
	SwordStateUpdate(_Delta);
	
	float4 Pos = float4::ZERO;
	float4 Scale = RustyShortSwordSkelRenderer->GetImageTransform().GetLocalScale();

	Pos.Y += (Scale.Y / 4.0f);

	if (SkelDir == RustyShortSwordSkelDir::Right)
	{
		Pos.X += Scale.X / 3.0f - 1.0f;
		RustyShortSwordSkelRenderer->RightFlip();
		RustyShortSwordRenderer->RightFlip();
	}
	if (SkelDir == RustyShortSwordSkelDir::Left)
	{
		Pos.X -= Scale.X / 3.0f + 1.0f;
		RustyShortSwordSkelRenderer->LeftFlip();
		RustyShortSwordRenderer->LeftFlip();
	}
	RustyShortSwordRenderer->Transform.SetLocalPosition(Pos);
}

void RustyShortSwordSkel::ChangeSkelState(RustyShortSwordSkelState _State)
{
	if (_State != SkelState)
	{
		switch (_State)
		{
		case RustyShortSwordSkelState::Idle:
			SkelIdleStart();
			break;
		case RustyShortSwordSkelState::Move:
			SkelMoveStart();
			break;
		case RustyShortSwordSkelState::AttackReady:
			SkelAttackReadyStart();
			break;
		case RustyShortSwordSkelState::Attack:
			SkelAttackStart();
			break;
		default:
			break;
		}
	}
	SkelState = _State;
}
void RustyShortSwordSkel::SkelStateUpdate(float _Delta)
{
	switch (SkelState)
	{
	case RustyShortSwordSkelState::Idle:
		return SkelIdleUpdate(_Delta);
	case RustyShortSwordSkelState::Move:
		return SkelMoveUpdate(_Delta);
	case RustyShortSwordSkelState::AttackReady:
		return SkelAttackReadyUpdate(_Delta);
	case RustyShortSwordSkelState::Attack:
		return SkelAttackUpdate(_Delta);
	default:
		break;
	}
}
void RustyShortSwordSkel::ChangeSkelAnimationState(const std::string& _State)
{
	std::string AnimationName = "RustyShortSwordSkel_";
	AnimationName += _State;
	RustyShortSwordSkelRenderer->ChangeAnimation(AnimationName);
}

void RustyShortSwordSkel::ChangeSwordState(RustyShortSwordState _State)
{
	if (_State != SwordState)
	{
		switch (_State)
		{
		case RustyShortSwordState::Idle:
			SwordIdleStart();
			break;
		case RustyShortSwordState::Attack:
			SwordAttackStart();
			break;
		case RustyShortSwordState::AttackReady:
			SwordAttackReadyStart();
			break;
		default:
			break;
		}
	}
	SwordState = _State;
}
void RustyShortSwordSkel::SwordStateUpdate(float _Delta)
{
	switch (SwordState)
	{
	case RustyShortSwordState::Idle:
		SwordIdleUpdate(_Delta);
	case RustyShortSwordState::Attack:
		SwordAttackUpdate(_Delta);
	case RustyShortSwordState::AttackReady:
		SwordAttackReadyUpdate(_Delta);
	default:
		break;
	}
}
void RustyShortSwordSkel::ChangeSwordAnimationState(const std::string& _State)
{
	std::string AnimationName = "RustyShortSword_";
	AnimationName += _State;
	RustyShortSwordRenderer->ChangeAnimation(AnimationName);
}

void RustyShortSwordSkel::SkelIdleStart()
{
	ChangeSkelAnimationState("Idle");
}
void RustyShortSwordSkel::SkelIdleUpdate(float _Delta)
{

}

void RustyShortSwordSkel::SkelMoveStart()
{
	ChangeSkelAnimationState("Move");
}
void RustyShortSwordSkel::SkelMoveUpdate(float _Delta)
{

}

void RustyShortSwordSkel::SkelAttackReadyStart()
{
	ChangeSkelAnimationState("AttackReady");
}
void RustyShortSwordSkel::SkelAttackReadyUpdate(float _Delta)
{

}

void RustyShortSwordSkel::SkelAttackStart()
{
	ChangeSkelAnimationState("Attack");
}
void RustyShortSwordSkel::SkelAttackUpdate(float _Delta)
{

}

void RustyShortSwordSkel::SwordIdleStart()
{
	ChangeSwordAnimationState("Idle");
}
void RustyShortSwordSkel::SwordIdleUpdate(float _Delta)
{

}

void RustyShortSwordSkel::SwordAttackReadyStart()
{
	ChangeSwordAnimationState("AttackReady");
}
void RustyShortSwordSkel::SwordAttackReadyUpdate(float _Delta)
{

}

void RustyShortSwordSkel::SwordAttackStart()
{
	ChangeSwordAnimationState("Attack");
}
void RustyShortSwordSkel::SwordAttackUpdate(float _Delta)
{

}