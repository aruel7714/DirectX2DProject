#include "PreCompile.h"
#include "BelialRightHandLaserHead.h"

BelialRightHandLaserHead::BelialRightHandLaserHead()
{
}

BelialRightHandLaserHead::~BelialRightHandLaserHead()
{
}

void BelialRightHandLaserHead::Start()
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

	RightLaserHeadRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossProjectile);

	{
		RightLaserHeadRenderer->CreateAnimation("BelialRightLaserHead_Attack", "BelialPatternLaserHead", 0.1f, 0, 2, true);
		RightLaserHeadRenderer->CreateAnimation("BelialRightLaserHead_End", "BelialPatternLaserHead", 0.1f, 3, 6, false);
	}

	RightLaserHeadRenderer->SetSprite("BelialPatternLaserHead");
	float4 Scale = RightLaserHeadRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	RightLaserHeadRenderer->SetImageScale(Scale);

	RightLaserHeadRenderer->LeftFlip();

	ChangeState(LaserState::Attack);
}
void BelialRightHandLaserHead::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void BelialRightHandLaserHead::ChangeState(LaserState _State)
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
void BelialRightHandLaserHead::StateUpdate(float _Delta)
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
void BelialRightHandLaserHead::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "BelialRightLaserHead_";
	AnimationName += _State;
	RightLaserHeadRenderer->ChangeAnimation(AnimationName);
}

void BelialRightHandLaserHead::AttackStart()
{
	ChangeAnimationState("Attack");
}
void BelialRightHandLaserHead::AttackUpdate(float _Delta)
{
	if (RightLaserHeadRenderer->IsCurAnimationEnd())
	{
		Count++;
	}
	if (Count >= 2)
	{
		ChangeState(LaserState::End);
	}
}


void BelialRightHandLaserHead::EndStart()
{
	ChangeAnimationState("End");
}
void BelialRightHandLaserHead::EndUpdate(float _Delta)
{
	if (RightLaserHeadRenderer->IsCurAnimationEnd())
	{
		RightLaserHeadRenderer->Death();
	}
}