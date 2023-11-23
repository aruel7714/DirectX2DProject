#include "PreCompile.h"
#include "RustyGreatSwordSkel.h"
#include "Player.h"

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
		RustyGreatSwordRenderer->CreateAnimation("RustyGreatSword_Attack", "RustyGreatSword", 0.1f, 6, 14, false);
		RustyGreatSwordRenderer->CreateAnimation("RustyGreatSword_AttackReady", "RustyGreatSword", 0.1f, 1, 5, false);
	}

	RustyGreatSwordSkelRenderer->SetSprite("SkelIdle");

	RustyGreatSwordSkelRenderer->SetPivotType(PivotType::Bottom);
	float4 SkelScale = RustyGreatSwordSkelRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	RustyGreatSwordSkelRenderer->SetImageScale(SkelScale);

	ChangeSkelState(RustyGreatSwordSkelState::Idle);

	RustyGreatSwordRenderer->SetSprite("RustyGreatSword");
	float4 SwordScale = RustyGreatSwordRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	RustyGreatSwordRenderer->SetImageScale(SwordScale);
	
	ChangeSwordState(RustyGreatSwordState::Idle);

	{
		// Status
		Hp = 37.0f;
		MoveSpeed = 300.0f;
	}

	{
		SkelCollision = CreateComponent<GameEngineCollision>(CollisionType::Monster);
		SkelCollision->SetCollisionType(ColType::AABBBOX2D);
		SkelCollision->Transform.SetLocalPosition({ 0.0f, SkelScale.Y / 4.0f, 1.0f });
		SkelCollision->Transform.SetLocalScale({ SkelScale.X / 3.0f, SkelScale.Y / 2.0f, 1.0f });
	}

	{
		AttackCollision = CreateComponent<GameEngineCollision>(CollisionType::MonsterAttack);
		AttackCollision->SetCollisionType(ColType::AABBBOX2D);
	}

	AttackCollision->Off();
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

	EventParameter DamageEvent;
	DamageEvent.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			DamageCheck();
		};
	SkelCollision->CollisionEvent(CollisionType::Weapon, DamageEvent);


	if (Hp <= 0)
	{
		ChangeSkelState(RustyGreatSwordSkelState::Death);
	}
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
		case RustyGreatSwordSkelState::Death:
			SkelDeathStart();
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
	case RustyGreatSwordSkelState::Death:
		return SkelDeathUpdate(_Delta);
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
		return SwordIdleUpdate(_Delta);
	case RustyGreatSwordState::Attack:
		return SwordAttackUpdate(_Delta);
	case RustyGreatSwordState::AttackReady:
		return SwordAttackReadyUpdate(_Delta);
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
	float4 MyPos = Transform.GetLocalPosition();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

	float Check = MyPos.X - PlayerPos.X;

	Check = abs(Check);

	if (Check < 600.0f)
	{
		ChangeSkelState(RustyGreatSwordSkelState::Move);
	}
}

void RustyGreatSwordSkel::SkelMoveStart()
{
	ChangeSkelAnimationState("Move");
	AttackCollision->Off();
}
void RustyGreatSwordSkel::SkelMoveUpdate(float _Delta)
{
	DirCheck();

	if (SkelDir == RustyGreatSwordSkelDir::Left)
	{
		Transform.AddLocalPosition(float4::LEFT * MoveSpeed * _Delta);
	}
	else if (SkelDir == RustyGreatSwordSkelDir::Right)
	{
		Transform.AddLocalPosition(float4::RIGHT * MoveSpeed * _Delta);
	}

	{
		float4 MyPos = Transform.GetLocalPosition();
		float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

		float Check = MyPos.X - PlayerPos.X;

		Check = abs(Check);

		if (Check < 50.0f)
		{
			ChangeSkelState(RustyGreatSwordSkelState::AttackReady);
			ChangeSwordState(RustyGreatSwordState::AttackReady);
		}
	}
}

void RustyGreatSwordSkel::SkelAttackReadyStart()
{
	ChangeSkelAnimationState("AttackReady");
}
void RustyGreatSwordSkel::SkelAttackReadyUpdate(float _Delta)
{
	AttackReadyTime += _Delta;

	if (AttackReadyTime >= 1.0f)
	{
		ChangeSkelState(RustyGreatSwordSkelState::Attack);
		ChangeSwordState(RustyGreatSwordState::Attack);
	}
}

void RustyGreatSwordSkel::SkelAttackStart()
{
	ChangeSkelAnimationState("Attack");
	AttackReadyTime = 0.0f;
}
void RustyGreatSwordSkel::SkelAttackUpdate(float _Delta)
{

}

void RustyGreatSwordSkel::SkelDeathStart()
{
	Death();
}
void RustyGreatSwordSkel::SkelDeathUpdate(float _Delta)
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
	AttackCollision->On();
	float4 Scale = RustyGreatSwordRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	AttackCollision->Transform.SetLocalScale(Scale / 2.0f);

	if (SkelDir == RustyGreatSwordSkelDir::Left)
	{
		AttackCollision->Transform.SetLocalPosition({ -(Scale.X / 4.0f) , Scale.Y / 4.0f });
	}
	else if (SkelDir == RustyGreatSwordSkelDir::Right)
	{
		AttackCollision->Transform.SetLocalPosition({ Scale.X / 4.0f , Scale.Y / 4.0f });
	}
}
void RustyGreatSwordSkel::SwordAttackUpdate(float _Delta)
{
	if (RustyGreatSwordRenderer->IsCurAnimationEnd())
	{
		ChangeSkelState(RustyGreatSwordSkelState::Move);
		ChangeSwordState(RustyGreatSwordState::Idle);
	}
}

void RustyGreatSwordSkel::DirCheck()
{
	float4 MyPos = Transform.GetLocalPosition();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

	float Check = MyPos.X - PlayerPos.X;

	if (Check > 0)
	{
		SkelDir = RustyGreatSwordSkelDir::Left;
	}
	else
	{
		SkelDir = RustyGreatSwordSkelDir::Right;
	}
}