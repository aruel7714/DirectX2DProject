#include "PreCompile.h"
#include "ArcherSkel.h"
#include "BowArrow.h"
#include "MonsterLife.h"

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
		ArcherSkelRenderer->CreateAnimation("ArcherSkel_Death", "Die", 0.025f, -1, -1, false);
	}

	{
		BowRenderer->CreateAnimation("Bow_Idle", "DaimyoOakBow", 0.1f, 0, 0, false);
		BowRenderer->CreateAnimation("Bow_AttackReady", "DaimyoOakBow", 0.05f, 1, 3, false);
		BowRenderer->CreateAnimation("Bow_Attack", "DaimyoOakBow", 0.05f, 4, 5, false);
	}

	ArcherSkelRenderer->SetSprite("SkelIdle");

	ArcherSkelRenderer->SetPivotType(PivotType::Bottom);
	float4 SkelScale = ArcherSkelRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	ArcherSkelRenderer->SetImageScale(SkelScale);

	ChangeSkelState(ArcherSkelState::Idle);

	{
		// statue
		MaxHp = 30.0f;
		Hp = 30.0f;
		//Damage = 6.0f;
	}

	BowRenderer->SetSprite("DaimyoOakBow");
	float4 BowScale = BowRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	BowRenderer->SetImageScale(BowScale);

	ChangeBowState(SkelBowState::Idle);

	{
		SkelCollision = CreateComponent<GameEngineCollision>(CollisionType::Monster);
		SkelCollision->SetCollisionType(ColType::AABBBOX2D);
		SkelCollision->Transform.SetLocalPosition({ 0.0f, SkelScale.Y / 4.0f, 1.0f });
		SkelCollision->Transform.SetLocalScale({ SkelScale.X / 3.0f, SkelScale.Y / 2.0f, 1.0f });
	}

	ArcherLife = GetLevel()->CreateActor<MonsterLife>(RenderOrder::MonsterLifeBase);
	ArcherLife->Off();
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
		BowRenderer->SetPivotValue({ 0.6f, 0.5f });
		//Pos.X -= Scale.X / 8.0f;
		ArcherSkelRenderer->RightFlip();
		BowRenderer->RightFlip();
	}
	if (SkelDir == ArcherSkelDir::Left)
	{
		BowRenderer->SetPivotValue({ 0.4f, 0.5f });
		//Pos.X += Scale.X / 8.0f;
		ArcherSkelRenderer->LeftFlip();
		BowRenderer->LeftFlip();
	}

	BowRenderer->Transform.SetLocalPosition(Pos);

	EventParameter DamageEvent;
	DamageEvent.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			DamageCheck();
		};
	SkelCollision->CollisionEvent(CollisionType::Weapon, DamageEvent);

	if (Hp < MaxHp)
	{
		ArcherLife->On();
		ArcherLife->Transform.SetLocalPosition({ Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 15.0f});
	}
	else
	{
		ArcherLife->Off();
	}

	float Per = Hp / MaxHp * 100.0f;

	if (true == ArcherLife->IsUpdate())
	{
		ArcherLife->SetLifeBarScale(Per);
	}

	if (Hp <= 0)
	{
		ChangeSkelState(ArcherSkelState::Death);
	}
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
		case ArcherSkelState::Death:
			SkelDeathStart();
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
		return SkelIdleUpdate(_Delta);
	case ArcherSkelState::AttackReady:
		return SkelAttackReadyUpdate(_Delta);
	case ArcherSkelState::Attack:
		return SkelAttackUpdate(_Delta);
	case ArcherSkelState::Death:
		return SkelDeathUpdate(_Delta);
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
		case SkelBowState::AttackReady:
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
		return BowIdleUpdate(_Delta);
	case SkelBowState::AttackReady:
		return BowAttackReadyUpdate(_Delta);
	case SkelBowState::Attack:
		return BowAttackUpdate(_Delta);
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
	DirCheck();
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

void ArcherSkel::SkelDeathStart()
{
	ArcherSound = GameEngineSound::SoundPlay("Explosion.wav");
	ChangeSkelAnimationState("Death");
	float4 Scale = ArcherSkelRenderer->GetCurSprite().Texture->GetScale() *= 4.0f;
	ArcherSkelRenderer->SetImageScale(Scale);
	ArcherSkelRenderer->SetPivotType(PivotType::Center);
	BowRenderer->Off();
	ArcherLife->Death();

}
void ArcherSkel::SkelDeathUpdate(float _Delta)
{
	if (true == ArcherSkelRenderer->IsCurAnimationEnd())
	{
		Death();
	}
}

void ArcherSkel::BowIdleStart()
{
	ChangeBowAnimationState("Idle");
	AttackTime = 0.0f;
}
void ArcherSkel::BowIdleUpdate(float _Delta)
{
	IdleToAttackTime += _Delta;

	float4 PlayerScale = Player::GetMainPlayer()->GetRendererScale();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();
	
	PlayerPos.Y += (PlayerScale.Y / 4.0f);

	float4 Scale = ArcherSkelRenderer->GetImageTransform().GetLocalScale();
	float4 MyPos = Transform.GetLocalPosition();
	MyPos.Y += (Scale.Y / 4.0f) - 6.0f;

	float4 TargetPos = MyPos - PlayerPos;

	SaveDir = TargetPos.NormalizeReturn();
	SaveDeg = SaveDir.Angle2DDeg();

	if (SkelDir == ArcherSkelDir::Left)
	{
		
		if (TargetPos.Y < 0)
		{
			SaveDeg *= -1.0f;
		}
	}

	if (SkelDir == ArcherSkelDir::Right)
	{
		SaveDeg += 180.0f;
		if (TargetPos.Y < 0)
		{
			SaveDeg *= -1.0f;
		}
	}

	BowRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f, SaveDeg });

	if (IdleToAttackTime > 2.5f)
	{
		ChangeSkelState(ArcherSkelState::AttackReady);
		ChangeBowState(SkelBowState::AttackReady);
	}
}

void ArcherSkel::BowAttackReadyStart()
{
	ArcherSound = GameEngineSound::SoundPlay("bow_crossbow_arrow_draw_stretch1_03.wav");
	ChangeBowAnimationState("AttackReady");
	IdleToAttackTime = 0.0f;
}
void ArcherSkel::BowAttackReadyUpdate(float _Delta)
{
	AttackTime += _Delta;

	if (AttackTime > 1.0f)
	{
		ChangeSkelState(ArcherSkelState::Attack);
		ChangeBowState(SkelBowState::Attack);
	}
}

void ArcherSkel::BowAttackStart()
{
	ArcherSound = GameEngineSound::SoundPlay("bow_crossbow_arrow_shoot_type1_03.wav");
	ChangeBowAnimationState("Attack");
	std::shared_ptr<BowArrow> SkelArrow = GetLevel()->CreateActor<BowArrow>(RenderOrder::MonsterProjectile);

	float4 ArcherPos = Transform.GetLocalPosition();
	float4 ArcherScale = ArcherSkelRenderer->GetImageTransform().GetLocalScale();

	ArcherPos.Y += (ArcherScale.Y / 4.0f) - 6.0f;

	SkelArrow->Transform.SetLocalPosition(ArcherPos);

	SkelArrow->Dir = SaveDir * -1.0f;
	SkelArrow->Deg = SaveDeg;
}
void ArcherSkel::BowAttackUpdate(float _Delta)
{
	if (true == BowRenderer->IsCurAnimationEnd())
	{
		ChangeSkelState(ArcherSkelState::Idle);
		ChangeBowState(SkelBowState::Idle);
	}
}

void ArcherSkel::DirCheck()
{
	float4 MyPos = Transform.GetLocalPosition();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

	float Check = MyPos.X - PlayerPos.X;

	if (Check > 0)
	{
		SkelDir = ArcherSkelDir::Left;
	}
	else
	{
		SkelDir = ArcherSkelDir::Right;
	}
}
