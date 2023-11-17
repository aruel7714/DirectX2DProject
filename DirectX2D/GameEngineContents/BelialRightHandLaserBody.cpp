#include "PreCompile.h"
#include "BelialRightHandLaserBody.h"

BelialRightHandLaserBody::BelialRightHandLaserBody()
{
}

BelialRightHandLaserBody::~BelialRightHandLaserBody()
{
}

void BelialRightHandLaserBody::Start()
{
	if (nullptr == GameEngineSprite::Find("BelialPatternLaserHead"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Boss\\Belial\\BelialPatternLaser\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	RightLaserBodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossProjectile);

	{
		RightLaserBodyRenderer->CreateAnimation("BelialRightLaserBody_Attack", "BelialPatternLaserBody", 0.1f, 0, 2, true);
		RightLaserBodyRenderer->CreateAnimation("BelialRightLaserBody_End", "BelialPatternLaserBody", 0.1f, 3, 6, false);
	}

	RightLaserBodyRenderer->SetSprite("BelialPatternLaserBody");
	float4 Scale = RightLaserBodyRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	RightLaserBodyRenderer->SetImageScale(Scale);

	RightLaserBodyRenderer->LeftFlip();

	ChangeState(LaserState::Attack);
}
void BelialRightHandLaserBody::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void BelialRightHandLaserBody::ChangeState(LaserState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case LaserState::Attack:
			AttackStart();
			break;
		case LaserState::End:
			EndStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void BelialRightHandLaserBody::StateUpdate(float _Delta)
{
	switch (State)
	{
	case LaserState::Attack:
		return AttackUpdate(_Delta);
	case LaserState::End:
		return EndUpdate(_Delta);
	default:
		break;
	}
}
void BelialRightHandLaserBody::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "BelialRightLaserBody_";
	AnimationName += _State;
	RightLaserBodyRenderer->ChangeAnimation(AnimationName);
}

void BelialRightHandLaserBody::AttackStart()
{
	ChangeAnimationState("Attack");
}
void BelialRightHandLaserBody::AttackUpdate(float _Delta)
{
	if (RightLaserBodyRenderer->IsCurAnimationEnd())
	{
		Count++;
	}
	if (Count >= 2)
	{
		ChangeState(LaserState::End);
	}
}

void BelialRightHandLaserBody::EndStart()
{
	ChangeAnimationState("End");
}
void BelialRightHandLaserBody::EndUpdate(float _Delta)
{
	if (RightLaserBodyRenderer->IsCurAnimationEnd())
	{
		RightLaserBodyRenderer->Death();
	}
}