#include "PreCompile.h"
#include "DungeonStele.h"

DungeonStele::DungeonStele()
{
}

DungeonStele::~DungeonStele()
{
}

void DungeonStele::Start()
{
	if (nullptr == GameEngineSprite::Find("SteleIdle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Dungeon\\Stele\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	SteleRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DungeonBuilding);

	{
		SteleRenderer->CreateAnimation("Stele_Closed", "SteleClosed", 0.1f, -1, -1, false);
		SteleRenderer->CreateAnimation("Stele_Idle", "SteleIdle");
		SteleRenderer->CreateAnimation("Stele_Opened", "SteleOpened", 0.1f, -1, -1, false);
	}

	SteleRenderer->SetSprite("SteleIdle");
	float4 Scale = SteleRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	SteleRenderer->SetImageScale(Scale);

	{
		SteleCollision = CreateComponent<GameEngineCollision>(CollisionType::Stele);
		SteleCollision->SetCollisionType(ColType::AABBBOX2D);
		SteleCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });
	}
	//SteleCollision->Off();

	ChangeState(SteleState::Closed);
}
void DungeonStele::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void DungeonStele::ChangeState(SteleState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case SteleState::Closed:
			ClosedStart();
			break;
		case SteleState::Idle:
			IdleStart();
			break;
		case SteleState::Opened:
			OpenedStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void DungeonStele::StateUpdate(float _Delta)
{
	switch (State)
	{
	case SteleState::Closed:
		return ClosedUpdate(_Delta);
	case SteleState::Idle:
		return IdleUpdate(_Delta);
	case SteleState::Opened:
		return OpenedUpdate(_Delta);
	default:
		break;
	}
}
void DungeonStele::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName = "Stele_";
	AnimationName += _State;
	SteleRenderer->ChangeAnimation(AnimationName);
}

void DungeonStele::ClosedStart()
{
	//MoveSound = GameEngineSound::SoundPlay("stoneDoor.wav");
	ChangeAnimationState("Closed");
	//SteleCollision->On();
}
void DungeonStele::ClosedUpdate(float _Delta)
{
	if (SteleRenderer->IsCurAnimationEnd())
	{
		ChangeState(SteleState::Idle);
	}
}

void DungeonStele::IdleStart()
{
	ChangeAnimationState("Idle");
	
}
void DungeonStele::IdleUpdate(float _Delta)
{

}

void DungeonStele::OpenedStart()
{
	MoveSound = GameEngineSound::SoundPlay("stoneDoor.wav");
	ChangeAnimationState("Opened");
	//SteleCollision->Off();
}
void DungeonStele::OpenedUpdate(float _Delta)
{
	if (SteleRenderer->IsCurAnimationEnd())
	{
		SteleCollision->Death();
		SteleRenderer->Death();
	}
}

void DungeonStele::SteleOpened()
{
	ChangeState(SteleState::Opened);
}