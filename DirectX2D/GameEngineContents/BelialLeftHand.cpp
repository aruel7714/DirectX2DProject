#include "PreCompile.h"
#include "BelialLeftHand.h"

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

	LeftHandRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossBody);

	{
		LeftHandRenderer->CreateAnimation("BelialLeftHand_Idle", "BelialLeftHandIdle");
		LeftHandRenderer->CreateAnimation("BelialLeftHand_Attack", "BelialLeftHandAttack");
	}

	LeftHandRenderer->SetSprite("BelialLeftHandIdle");
	float4 Scale = LeftHandRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	LeftHandRenderer->SetImageScale(Scale);

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
}
void BelialLeftHand::IdleUpdate(float _Delta)
{

}

void BelialLeftHand::AttackStart()
{
	ChangeAnimationState("Attack");
}
void BelialLeftHand::AttackUpdate(float _Delta)
{

}