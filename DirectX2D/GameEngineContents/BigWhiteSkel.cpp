#include "PreCompile.h"
#include "BigWhiteSkel.h"

BigWhiteSkel::BigWhiteSkel()
{
}

BigWhiteSkel::~BigWhiteSkel()
{
}

void BigWhiteSkel::Start()
{
	if (nullptr == GameEngineSprite::Find("BigWhiteSkelIdle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Monster\\BigWhiteSkel\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	BigWhiteSkelRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);

	{
		BigWhiteSkelRenderer->CreateAnimation("BigWhiteSkel_Idle", "BigWhiteSkelIdle");
		BigWhiteSkelRenderer->CreateAnimation("BigWhiteSkel_Move", "BigWhiteSkelMove");
		BigWhiteSkelRenderer->CreateAnimation("BigWhiteSkel_Attack", "BigWhiteSkelAttack");
		BigWhiteSkelRenderer->CreateAnimation("BigWhiteSkel_AttackReady", "BigWhiteSkelAttack", 0.1f, 0, 0, false);
	}

	BigWhiteSkelRenderer->SetSprite("BigWhiteSkelIdle");

	BigWhiteSkelRenderer->SetPivotType(PivotType::Bottom);
	float4 Scale = BigWhiteSkelRenderer->GetCurSprite().Texture->GetScale() *= 4.0f;
	BigWhiteSkelRenderer->SetImageScale(Scale);

	ChangeState(BigWhiteSkelState::Idle);

	BigWhiteSkelRenderer->LeftFlip();

	
	GameEngineInput::AddInputObject(this);

}
void BigWhiteSkel::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (GameEngineInput::IsPress('1', this))
	{
		ChangeState(BigWhiteSkelState::Idle);
	}

	if (GameEngineInput::IsPress('2', this))
	{
		ChangeState(BigWhiteSkelState::Move);
	}

	if (GameEngineInput::IsPress('3', this))
	{
		ChangeState(BigWhiteSkelState::Attack);
	}

	if (GameEngineInput::IsPress('4', this))
	{
		BigWhiteSkelRenderer->LeftFlip();
		Dir = BigWhiteSkelDir::Left;
	}

	if (GameEngineInput::IsPress('5', this))
	{
		BigWhiteSkelRenderer->RightFlip();
		Dir = BigWhiteSkelDir::Right;
	}
}

void BigWhiteSkel::ChangeState(BigWhiteSkelState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BigWhiteSkelState::Idle:
			IdleStart();
			break;
		case BigWhiteSkelState::Move:
			MoveStart();
			break;
		case BigWhiteSkelState::Attack:
			AttackStart();
			break;
		case BigWhiteSkelState::AttackReady:
			AttackReadyStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void BigWhiteSkel::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BigWhiteSkelState::Idle:
		return IdleUpdate(_Delta);
	case BigWhiteSkelState::Move:
		return MoveUpdate(_Delta);
	case BigWhiteSkelState::Attack:
		return AttackUpdate(_Delta);
	case BigWhiteSkelState::AttackReady:
		return AttackReadyUpdate(_Delta);
	default:
		break;
	}
}
void BigWhiteSkel::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "BigWhiteSkel_";
	AnimationName += _State;
	BigWhiteSkelRenderer->ChangeAnimation(AnimationName);
}

void BigWhiteSkel::IdleStart()
{
	ChangeAnimationState("Idle");
	float4 Scale = BigWhiteSkelRenderer->GetCurSprite().Texture->GetScale() *= 4.0f;
	BigWhiteSkelRenderer->SetImageScale(Scale);
	BigWhiteSkelRenderer->SetPivotType(PivotType::Bottom);
}
void BigWhiteSkel::IdleUpdate(float _Delta)
{

}

void BigWhiteSkel::MoveStart()
{
	ChangeAnimationState("Move");
	float4 Scale = BigWhiteSkelRenderer->GetCurSprite().Texture->GetScale() *= 4.0f;
	BigWhiteSkelRenderer->SetImageScale(Scale);
	BigWhiteSkelRenderer->SetPivotType(PivotType::Bottom);
}
void BigWhiteSkel::MoveUpdate(float _Delta)
{

}

void BigWhiteSkel::AttackReadyStart()
{
	ChangeAnimationState("AttackReady");
	float4 Scale = BigWhiteSkelRenderer->GetCurSprite().Texture->GetScale() *= 4.0f;
	BigWhiteSkelRenderer->SetImageScale(Scale);
}
void BigWhiteSkel::AttackReadyUpdate(float _Delta)
{

}

void BigWhiteSkel::AttackStart()
{
	ChangeAnimationState("Attack");
	float4 Scale = BigWhiteSkelRenderer->GetCurSprite().Texture->GetScale() *= 4.0f;
	BigWhiteSkelRenderer->SetImageScale(Scale);
	if (Dir == BigWhiteSkelDir::Left)
	{
		//BigWhiteSkelRenderer->SetPivotType(PivotType::RightBottom);
		BigWhiteSkelRenderer->SetPivotValue({ 0.25f, 1.0f });
	}
	if (Dir == BigWhiteSkelDir::Right)
	{
		//BigWhiteSkelRenderer->SetPivotType(PivotType::LeftBottom);
		BigWhiteSkelRenderer->SetPivotValue({ 0.75f, 1.0f });
	}
}
void BigWhiteSkel::AttackUpdate(float _Delta)
{

}

void BigWhiteSkel::DirCheck()
{

}