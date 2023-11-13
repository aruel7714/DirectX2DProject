#include "PreCompile.h"
#include "ArcherSkel.h"

ArcherSkel::ArcherSkel()
{
}

ArcherSkel::~ArcherSkel()
{
}

void ArcherSkel::Start()
{
	if (nullptr == GameEngineSprite::Find("DaimyoOakBow"))
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
	ArcherSkelRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);
	BowRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MonsterFrontWeapon);

	{
		ArcherSkelRenderer->CreateAnimation("ArcherSkel_Idle", "SkelIdle");
		ArcherSkelRenderer->CreateAnimation("ArcherSkel_AttackReady", "SkelAttack");
		ArcherSkelRenderer->CreateAnimation("ArcherSkel_Attack", "SkelAttack");
	}

	{
		BowRenderer->CreateAnimation("Bow_Idle", "DaimyoOakBow", 0.1f, 0, 0, false);
		BowRenderer->CreateAnimation("Bow_AttackReady", "DaimyoOakBow", 0.1f, 1, 3, false);
		BowRenderer->CreateAnimation("Bow_Attack", "DaimyoOakBow", 0.1f, 4, 5, false);
	}

	ArcherSkelRenderer->SetSprite("SkelIdle");

	ArcherSkelRenderer->SetPivotType(PivotType::Bottom);
	float4 SkelScale = ArcherSkelRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	ArcherSkelRenderer->SetImageScale(SkelScale);

	ChangeSkelState(ArcherSkelState::Idle);

	BowRenderer->SetSprite("DaimyoOakBow");
	float4 BowScale = BowRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	BowRenderer->SetImageScale(BowScale);

	ChangeBowState(SkelBowState::Idle);
}

void ArcherSkel::Update(float _Delta)
{
	SkelStateUpdate(_Delta);
	BowStateUpdate(_Delta);

	float4 Pos = float4::ZERO;
	float4 Scale = ArcherSkelRenderer->GetImageTransform().GetLocalScale();

	Pos.Y += (Scale.Y / 4.0f) - 6.0f;
	
	if (SkelDir == ArcherSkelDir::Right)
	{
		BowRenderer->SetPivotValue({ 0.4f, 0.5f });
		Pos.X += Scale.X / 8.0f;
		ArcherSkelRenderer->RightFlip();
		BowRenderer->RightFlip();
	}
	if (SkelDir == ArcherSkelDir::Left)
	{
		BowRenderer->SetPivotValue({ 0.6f, 0.5f });
		Pos.X -= Scale.X / 8.0f;
		ArcherSkelRenderer->LeftFlip();
		BowRenderer->LeftFlip();
	}

	BowRenderer->Transform.SetLocalPosition(Pos);
}

void ArcherSkel::ChangeSkelState(ArcherSkelState _State)
{
	if (_State != SkelState)
	{
		switch (_State)
		{
		case ArcherSkelState::Idle:
			SkelIdleStart();
			break;
		case ArcherSkelState::AttackReady:
			SkelAttackReadyStart();
			break;
		case ArcherSkelState::Attack:
			SkelAttackStart();
			break;
		default:
			break;
		}
	}
	SkelState = _State;
}
void ArcherSkel::SkelStateUpdate(float _Delta)
{
	switch (SkelState)
	{
	case ArcherSkelState::Idle:
		SkelIdleUpdate(_Delta);
	case ArcherSkelState::AttackReady:
		SkelAttackReadyUpdate(_Delta);
	case ArcherSkelState::Attack:
		SkelAttackUpdate(_Delta);
	default:
		break;
	}
}
void ArcherSkel::ChangeSkelAnimationState(const std::string& _State)
{
	std::string AnimationName = "ArcherSkel_";
	AnimationName += _State;
	ArcherSkelRenderer->ChangeAnimation(AnimationName);
}

void ArcherSkel::ChangeBowState(SkelBowState _State)
{
	if (_State != BowState)
	{
		switch (_State)
		{
		case SkelBowState::Idle:
			BowIdleStart();
			break;
		case SkelBowState::AttckReady:
			BowAttackReadyStart();
			break;
		case SkelBowState::Attack:
			BowAttackStart();
			break;
		default:
			break;
		}
	}
	BowState = _State;
}
void ArcherSkel::BowStateUpdate(float _Delta)
{
	switch (BowState)
	{
	case SkelBowState::Idle:
		BowIdleUpdate(_Delta);
	case SkelBowState::AttckReady:
		BowAttackReadyUpdate(_Delta);
	case SkelBowState::Attack:
		BowAttackUpdate(_Delta);
	default:
		break;
	}
}
void ArcherSkel::ChangeBowAnimationState(const std::string& _State)
{
	std::string AnimationName = "Bow_";
	AnimationName += _State;
	BowRenderer->ChangeAnimation(AnimationName);
}

void ArcherSkel::SkelIdleStart()
{
	ChangeSkelAnimationState("Idle");
}
void ArcherSkel::SkelIdleUpdate(float _Delta)
{

}

void ArcherSkel::SkelAttackReadyStart()
{
	ChangeSkelAnimationState("AttackReady");
}
void ArcherSkel::SkelAttackReadyUpdate(float _Delta)
{

}

void ArcherSkel::SkelAttackStart()
{
	ChangeSkelAnimationState("Attack");
}
void ArcherSkel::SkelAttackUpdate(float _Delta)
{

}

void ArcherSkel::BowIdleStart()
{
	ChangeBowAnimationState("Idle");
}
void ArcherSkel::BowIdleUpdate(float _Delta)
{

}

void ArcherSkel::BowAttackReadyStart()
{
	ChangeBowAnimationState("AttackReady");
}
void ArcherSkel::BowAttackReadyUpdate(float _Delta)
{

}

void ArcherSkel::BowAttackStart()
{
	ChangeBowAnimationState("Attack");
}
void ArcherSkel::BowAttackUpdate(float _Delta)
{

}