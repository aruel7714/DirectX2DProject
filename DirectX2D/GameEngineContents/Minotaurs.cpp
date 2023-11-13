#include "PreCompile.h"
#include "Minotaurs.h"

Minotaurs::Minotaurs()
{
}

Minotaurs::~Minotaurs()
{
}

void Minotaurs::Start()
{
	if (nullptr == GameEngineSprite::Find("MinotaursIdle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Monster\\Minotaurs\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	MinotaursRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);

	{
		MinotaursRenderer->CreateAnimation("Minotaurs_Idle", "MinotaursIdle");
		MinotaursRenderer->CreateAnimation("Minotaurs_Charge", "MinotaursCharge", 0.1f, 0, 3, false);
		MinotaursRenderer->CreateAnimation("Minotaurs_Rush", "MinotaursCharge", 0.1f, 4, 7, false);
		MinotaursRenderer->CreateAnimation("Minotaurs_AttackReady", "MinotaursAttack", 0.1f, 0, 2, false);
		MinotaursRenderer->CreateAnimation("Minotaurs_Attack", "MinotaursAttack", 0.1f, 3, 6, false);
	}

	MinotaursRenderer->SetSprite("MinotaursIdle");
	
	MinotaursRenderer->SetPivotType(PivotType::Bottom);
	float4 Scale = MinotaursRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	MinotaursRenderer->SetImageScale(Scale);

	ChangeState(MinotaursState::Idle);
}
void Minotaurs::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void Minotaurs::ChangeState(MinotaursState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case MinotaursState::Idle:
			IdleStart();
			break;
		case MinotaursState::Charge:
			ChargeStart();
			break;
		case MinotaursState::Rush:
			RushStart();
			break;
		case MinotaursState::AttackReady:
			AttackReadyStart();
			break;
		case MinotaursState::Attack:
			AttackStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void Minotaurs::StateUpdate(float _Delta)
{
	switch (State)
	{
	case MinotaursState::Idle:
		IdleUpdate(_Delta);
	case MinotaursState::Charge:
		ChargeUpdate(_Delta);
	case MinotaursState::Rush:
		RushUpdate(_Delta);
	case MinotaursState::AttackReady:
		AttackReadyUpdate(_Delta);
	case MinotaursState::Attack:
		AttackUpdate(_Delta);
	default:
		break;
	}
}
void Minotaurs::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "Minotaurs_";
	AnimationName += _State;
	MinotaursRenderer->ChangeAnimation(AnimationName);
}

void Minotaurs::IdleStart()
{
	ChangeAnimationState("Idle");
}
void Minotaurs::IdleUpdate(float _Delta)
{

}

void Minotaurs::ChargeStart()
{
	ChangeAnimationState("Charge");
}
void Minotaurs::ChargeUpdate(float _Delta)
{

}

void Minotaurs::RushStart()
{
	ChangeAnimationState("Rush");
}
void Minotaurs::RushUpdate(float _Delta)
{

}

void Minotaurs::AttackReadyStart()
{
	ChangeAnimationState("AttackReady");
}
void Minotaurs::AttackReadyUpdate(float _Delta)
{

}

void Minotaurs::AttackStart()
{
	ChangeAnimationState("Attack");
}
void Minotaurs::AttackUpdate(float _Delta)
{

}