#include "PreCompile.h"
#include "BelialRightHand.h"

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
		RightHandRenderer->CreateAnimation("BelialRightHand_Attack", "BelialLeftHandAttack", 0.1f, -1, -1, false);
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
}
void BelialRightHand::IdleUpdate(float _Delta)
{

}

void BelialRightHand::AttackStart()
{
	ChangeAnimationState("Attack");
}
void BelialRightHand::AttackUpdate(float _Delta)
{

}