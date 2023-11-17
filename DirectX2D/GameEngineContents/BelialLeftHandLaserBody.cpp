#include "PreCompile.h"
#include "BelialLeftHandLaserBody.h"

BelialLeftHandLaserBody::BelialLeftHandLaserBody()
{
}

BelialLeftHandLaserBody::~BelialLeftHandLaserBody()
{
}

void BelialLeftHandLaserBody::Start()
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

	LeftLaserBodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossProjectile);

	{
		LeftLaserBodyRenderer->CreateAnimation("BelialLeftLaserBody_Attack", "BelialPatternLaserBody", 0.1f, 0, 2, true);
		LeftLaserBodyRenderer->CreateAnimation("BelialLeftLaserBody_End", "BelialPatternLaserBody", 0.1f, 3, 6, false);
	}

	LeftLaserBodyRenderer->SetSprite("BelialPatternLaserBody");
	float4 Scale = LeftLaserBodyRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	LeftLaserBodyRenderer->SetImageScale(Scale);

	ChangeState(LaserState::Attack);
}
void BelialLeftHandLaserBody::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void BelialLeftHandLaserBody::ChangeState(LaserState _State)
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
void BelialLeftHandLaserBody::StateUpdate(float _Delta)
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
void BelialLeftHandLaserBody::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "BelialLeftLaserBody_";
	AnimationName += _State;
	LeftLaserBodyRenderer->ChangeAnimation(AnimationName);
}

void BelialLeftHandLaserBody::AttackStart()
{
	ChangeAnimationState("Attack");
}
void BelialLeftHandLaserBody::AttackUpdate(float _Delta)
{
	if (LeftLaserBodyRenderer->IsCurAnimationEnd())
	{
		Count++;
	}
	if (Count >= 2)
	{
		ChangeState(LaserState::End);
	}
}

void BelialLeftHandLaserBody::EndStart()
{
	ChangeAnimationState("End");
}
void BelialLeftHandLaserBody::EndUpdate(float _Delta)
{
	if (LeftLaserBodyRenderer->IsCurAnimationEnd())
	{
		LeftLaserBodyRenderer->Death();
	}
}