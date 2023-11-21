#include "PreCompile.h"
#include "BelialRightHand.h"
#include "BelialRightHandLaserHead.h"
#include "BelialRightHandLaserBody.h"

BelialRightHand::BelialRightHand()
{
}

BelialRightHand::~BelialRightHand()
{
}

void BelialRightHand::Start()
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

	RightHandRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossBody);

	{
		RightHandRenderer->CreateAnimation("BelialRightHand_Idle", "BelialLeftHandIdle");
		RightHandRenderer->CreateAnimation("BelialRightHand_AttackReady", "BelialLeftHandAttack", 0.1f, 0, 7, false);
		RightHandRenderer->CreateAnimation("BelialRightHand_Attack", "BelialLeftHandAttack", 0.1f, 8, 17, false);
	}

	RightHandRenderer->SetSprite("BelialLeftHandIdle");
	float4 Scale = RightHandRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	RightHandRenderer->SetImageScale(Scale);

	ChangeState(RightHandState::Idle);
	RightHandRenderer->LeftFlip();
}
void BelialRightHand::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void BelialRightHand::ChangeState(RightHandState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case RightHandState::Idle:
			IdleStart();
			break;
		case RightHandState::AttackReady:
			AttackReadyStart();
			break;
		case RightHandState::Attack:
			AttackStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void BelialRightHand::StateUpdate(float _Delta)
{
	switch (State)
	{
	case RightHandState::Idle:
		return IdleUpdate(_Delta);
	case RightHandState::AttackReady:
		return AttackReadyUpdate(_Delta);
	case RightHandState::Attack:
		return AttackUpdate(_Delta);
	default:
		break;
	}
}
void BelialRightHand::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "BelialRightHand_";
	AnimationName += _State;
	RightHandRenderer->ChangeAnimation(AnimationName);
}

void BelialRightHand::IdleStart()
{
	ChangeAnimationState("Idle");
	float4 Scale = RightHandRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	RightHandRenderer->SetImageScale(Scale);
}
void BelialRightHand::IdleUpdate(float _Delta)
{
	//ChangeState(RightHandState::AttackReady);
}

void BelialRightHand::AttackReadyStart()
{
	ChangeAnimationState("AttackReady");
	float4 Scale = RightHandRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	RightHandRenderer->SetImageScale(Scale);
	PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();
}
void BelialRightHand::AttackReadyUpdate(float _Delta)
{
	if (0 < PlayerPos.Y - Transform.GetLocalPosition().Y)
	{
		Transform.AddLocalPosition(float4::UP * _Delta * abs(PlayerPos.Y - Transform.GetLocalPosition().Y) * 20.0f);
	}
	else
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * abs(PlayerPos.Y - Transform.GetLocalPosition().Y) * 20.0f);
	}
	

	if (RightHandRenderer->IsCurAnimationEnd())
	{
		ChangeState(RightHandState::Attack);
	}
}

void BelialRightHand::AttackStart()
{
	ChangeAnimationState("Attack");
	float4 Scale = RightHandRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	RightHandRenderer->SetImageScale(Scale);

	std::shared_ptr<BelialRightHandLaserHead> LaserHead = GetLevel()->CreateActor<BelialRightHandLaserHead>(RenderOrder::BossProjectile);
	float4 LaserHeadPos = Transform.GetLocalPosition();
	LaserHead->Transform.SetLocalPosition(LaserHeadPos);

	for (int i = 1; i < 10; i++)
	{
		std::shared_ptr<BelialRightHandLaserBody> LaserBody = GetLevel()->CreateActor<BelialRightHandLaserBody>(RenderOrder::BossProjectile);

		LaserBody->Transform.SetLocalPosition({ LaserHeadPos.X - (32.0f * 4 * i) , LaserHeadPos.Y });
	}
}
void BelialRightHand::AttackUpdate(float _Delta)
{
	if (RightHandRenderer->IsCurAnimationEnd())
	{
		ChangeState(RightHandState::Idle);
	}
}