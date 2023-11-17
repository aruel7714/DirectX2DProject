#include "PreCompile.h"
#include "BelialLeftHandLaserHead.h"

BelialLeftHandLaserHead::BelialLeftHandLaserHead()
{
}

BelialLeftHandLaserHead::~BelialLeftHandLaserHead()
{
}

void BelialLeftHandLaserHead::Start()
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

	LeftLaserHeadRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossProjectile);

	{
		LeftLaserHeadRenderer->CreateAnimation("BelialLeftLaserHead_Attack", "BelialPatternLaserHead", 0.1f, 0, 2, true);
		LeftLaserHeadRenderer->CreateAnimation("BelialLeftLaserHead_End", "BelialPatternLaserHead", 0.1f, 3, 6, false);
	}

	LeftLaserHeadRenderer->SetSprite("BelialPatternLaserHead");
	float4 Scale = LeftLaserHeadRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	LeftLaserHeadRenderer->SetImageScale(Scale);

	ChangeState(LaserState::Attack);
}
void BelialLeftHandLaserHead::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void BelialLeftHandLaserHead::ChangeState(LaserState _State)
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
void BelialLeftHandLaserHead::StateUpdate(float _Delta)
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
void BelialLeftHandLaserHead::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "BelialLeftLaserHead_";
	AnimationName += _State;
	LeftLaserHeadRenderer->ChangeAnimation(AnimationName);
}

void BelialLeftHandLaserHead::AttackStart()
{
	ChangeAnimationState("Attack");
}
void BelialLeftHandLaserHead::AttackUpdate(float _Delta)
{
	if (LeftLaserHeadRenderer->IsCurAnimationEnd())
	{
		Count++;
	}
	if (Count >= 2)
	{
		ChangeState(LaserState::End);
	}
}


void BelialLeftHandLaserHead::EndStart()
{
	ChangeAnimationState("End");
}
void BelialLeftHandLaserHead::EndUpdate(float _Delta)
{
	if (LeftLaserHeadRenderer->IsCurAnimationEnd())
	{
		LeftLaserHeadRenderer->Death();
	}
}