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
		RustyShortSwordSkelRenderer->CreateAnimation("RustyShortSwordSkel_Death", "Die", 0.025f, -1, -1, false);
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

	EventParameter DamageEvent;
	DamageEvent.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			DamageCheck();
		};
	SkelCollision->CollisionEvent(CollisionType::Weapon, DamageEvent);


	if (Hp <= 0)
	{
		ChangeSkelState(RustyShortSwordSkelState::Death);
	}
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
		case RustyShortSwordSkelState::Death:
			SkelDeathStart();
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
	case RustyShortSwordSkelState::Death:
		return SkelDeathUpdate(_Delta);
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
		return SwordIdleUpdate(_Delta);
	case RustyShortSwordState::Attack:
		return SwordAttackUpdate(_Delta);
	case RustyShortSwordState::AttackReady:
		return SwordAttackReadyUpdate(_Delta);
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
	float4 MyPos = Transform.GetLocalPosition();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

	float CheckX = MyPos.X - PlayerPos.X;
	float CheckY = MyPos.Y - PlayerPos.Y;

	CheckX = abs(CheckX);
	CheckY = abs(CheckY);

	if (CheckX < 600.0f && CheckY < 200.0f)
	{
		ChangeSkelState(RustyShortSwordSkelState::Move);
	}
}

void RustyShortSwordSkel::SkelMoveStart()
{
	ChangeSkelAnimationState("Move");
	AttackCollision->Off();
}
void RustyShortSwordSkel::SkelMoveUpdate(float _Delta)
{
	DirCheck();

	if (SkelDir == RustyShortSwordSkelDir::Left)
	{
		Transform.AddLocalPosition(float4::LEFT * MoveSpeed * _Delta);
	}
	else if (SkelDir == RustyShortSwordSkelDir::Right)
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
			ChangeSkelState(RustyShortSwordSkelState::AttackReady);
			ChangeSwordState(RustyShortSwordState::AttackReady);
		}
	}
}

void RustyShortSwordSkel::SkelAttackReadyStart()
{
	ChangeSkelAnimationState("AttackReady");
}
void RustyShortSwordSkel::SkelAttackReadyUpdate(float _Delta)
{
	AttackReadyTime += _Delta;

	if (AttackReadyTime >= 1.0f)
	{
		ChangeSkelState(RustyShortSwordSkelState::Attack);
		ChangeSwordState(RustyShortSwordState::Attack);
	}
}

void RustyShortSwordSkel::SkelAttackStart()
{
	ChangeSkelAnimationState("Attack");
	AttackReadyTime = 0.0f;
}
void RustyShortSwordSkel::SkelAttackUpdate(float _Delta)
{

}

void RustyShortSwordSkel::SkelDeathStart()
{
	ChangeSkelAnimationState("Death");
	float4 Scale = RustyShortSwordSkelRenderer->GetCurSprite().Texture->GetScale() *= 4.0f;
	RustyShortSwordSkelRenderer->SetImageScale(Scale);
	RustyShortSwordSkelRenderer->SetPivotType(PivotType::Center);
	RustyShortSwordRenderer->Off();
}
void RustyShortSwordSkel::SkelDeathUpdate(float _Delta)
{
	if (true == RustyShortSwordSkelRenderer->IsCurAnimationEnd())
	{
		Death();
	}
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
	AttackCollision->On();
	float4 Scale = RustyShortSwordRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	//AttackCollision->Transform.SetLocalScale(Scale / 2.0f);
	AttackCollision->Transform.SetLocalScale({ Scale.X / 4.0f * 3.0f, Scale.Y / 2.0f });

	if (SkelDir == RustyShortSwordSkelDir::Left)
	{
		AttackCollision->Transform.SetLocalPosition({ -(Scale.X / 3.0f) , Scale.Y / 4.0f });
	}
	else if (SkelDir == RustyShortSwordSkelDir::Right)
	{
		AttackCollision->Transform.SetLocalPosition({ Scale.X / 3.0f , Scale.Y / 4.0f });
	}
}
void RustyShortSwordSkel::SwordAttackUpdate(float _Delta)
{
	if (RustyShortSwordRenderer->IsCurAnimationEnd())
	{
		ChangeSkelState(RustyShortSwordSkelState::Move);
		ChangeSwordState(RustyShortSwordState::Idle);
	}
}

void RustyShortSwordSkel::DirCheck()
{
	float4 MyPos = Transform.GetLocalPosition();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

	float Check = MyPos.X - PlayerPos.X;

	if (Check > 0)
	{
		SkelDir = RustyShortSwordSkelDir::Left;
	}
	else
	{
		SkelDir = RustyShortSwordSkelDir::Right;
	}
}