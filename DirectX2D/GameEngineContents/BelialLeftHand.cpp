#include "PreCompile.h"
#include "BelialLeftHand.h"
#include "BelialLeftHandLaserHead.h"
#include "BelialLeftHandLaserBody.h"

BelialLeftHand::BelialLeftHand()
{
}

BelialLeftHand::~BelialLeftHand()
{
}

void BelialLeftHand::Start()
{
	if (nullptr == GameEngineSprite::Find("BelialLeftHandIdle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Boss\\Belial\\BelialLeftHand\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	LeftHandRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossBody2);

	{
		LeftHandRenderer->CreateAnimation("BelialLeftHand_Idle", "BelialLeftHandIdle");
		LeftHandRenderer->CreateAnimation("BelialLeftHand_AttackReady", "BelialLeftHandAttack", 0.1f, 0, 7, false);
		LeftHandRenderer->CreateAnimation("BelialLeftHand_Attack", "BelialLeftHandAttack", 0.1f, 8, 17, false);
	}

	LeftHandRenderer->SetSprite("BelialLeftHandIdle");
	float4 Scale = LeftHandRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	LeftHandRenderer->SetImageScale(Scale);

	LeftHandRenderer->GetColorData().MulColor.A = 0.0f;

	ChangeState(LeftHandState::Idle);
}
void BelialLeftHand::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void BelialLeftHand::ChangeState(LeftHandState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case LeftHandState::Idle:
			IdleStart();
			break;
		case LeftHandState::AttackReady:
			AttackReadyStart();
			break;
		case LeftHandState::Attack:
			AttackStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void BelialLeftHand::StateUpdate(float _Delta)
{
	switch (State)
	{
	case LeftHandState::Idle:
		return IdleUpdate(_Delta);
	case LeftHandState::AttackReady:
		return AttackReadyUpdate(_Delta);
	case LeftHandState::Attack:
		return AttackUpdate(_Delta);
	default:
		break;
	}
}
void BelialLeftHand::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "BelialLeftHand_";
	AnimationName += _State;
	LeftHandRenderer->ChangeAnimation(AnimationName);
}

void BelialLeftHand::IdleStart()
{
	ChangeAnimationState("Idle");
	float4 Scale = LeftHandRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	LeftHandRenderer->SetImageScale(Scale);
}
void BelialLeftHand::IdleUpdate(float _Delta)
{
	//ChangeState(LeftHandState::AttackReady);
}

void BelialLeftHand::AttackReadyStart()
{
	ChangeAnimationState("AttackReady");
	float4 Scale = LeftHandRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	LeftHandRenderer->SetImageScale(Scale);
	PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();
	float4 PlayerScale = Player::GetMainPlayer()->GetRendererScale();
	PlayerPos.Y += (PlayerScale.Y / 4.0f);
}
void BelialLeftHand::AttackReadyUpdate(float _Delta)
{
	if (0 < PlayerPos.Y - Transform.GetLocalPosition().Y)
	{
		Transform.AddLocalPosition(float4::UP * _Delta * abs(PlayerPos.Y - Transform.GetLocalPosition().Y) * 20.0f);
	}
	else
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * abs(PlayerPos.Y - Transform.GetLocalPosition().Y) * 20.0f);
	}

	if (LeftHandRenderer->IsCurAnimationEnd())
	{
		ChangeState(LeftHandState::Attack);
	}
}

void BelialLeftHand::AttackStart()
{
	LaserSound = GameEngineSound::SoundPlay("iceball.wav");
	ChangeAnimationState("Attack");
	float4 Scale = LeftHandRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	LeftHandRenderer->SetImageScale(Scale);

	std::shared_ptr<BelialLeftHandLaserHead> LaserHead = GetLevel()->CreateActor<BelialLeftHandLaserHead>(RenderOrder::BossProjectile);
	float4 LaserHeadPos = Transform.GetLocalPosition();
	LaserHead->Transform.SetLocalPosition(LaserHeadPos);

	for (int i = 1; i < 10; i++)
	{
		std::shared_ptr<BelialLeftHandLaserBody> LaserBody = GetLevel()->CreateActor<BelialLeftHandLaserBody>(RenderOrder::BossProjectile);

		LaserBody->Transform.SetLocalPosition({ LaserHeadPos.X + (32.0f * 4 * i), LaserHeadPos.Y });
	}
}
void BelialLeftHand::AttackUpdate(float _Delta)
{
	if (LeftHandRenderer->IsCurAnimationEnd())
	{
		ChangeState(LeftHandState::Idle);
	}
}