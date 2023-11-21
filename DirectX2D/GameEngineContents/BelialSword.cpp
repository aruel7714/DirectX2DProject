#include "PreCompile.h"
#include "BelialSword.h"

BelialSword::BelialSword()
{
}

BelialSword::~BelialSword()
{
}

void BelialSword::Start()
{
	if (nullptr == GameEngineSprite::Find("BelialPatternSwordSwordBody"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Boss\\Belial\\BelialPatternSword\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	GameEngineSprite::CreateSingle("BossSword.png");
	GameEngineSprite::CreateSingle("BossSwordFX.png");

	{
		SwordChargeRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossProjectileEffect);
		SwordChargeRenderer->CreateAnimation("SwordChargeFX", "BelialPatternSwordCharge");
		SwordChargeRenderer->ChangeAnimation("SwordChargeFX");
		float4 Scale = SwordChargeRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
		SwordChargeRenderer->SetImageScale(Scale);
	}

	SwordRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BossProjectile);
	SwordRenderer->SetSprite("BossSword.png");
	float4 Scale = SwordChargeRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	SwordRenderer->SetImageScale(Scale);

	ChangeState(SwordState::Idle);
}
void BelialSword::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void BelialSword::ChangeState(SwordState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case SwordState::Idle:
			IdleStart();
			break;
		case SwordState::Fire:
			FireStart();
			break;
		case SwordState::HIt:
			HitStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void BelialSword::StateUpdate(float _Delta)
{
	switch (State)
	{
	case SwordState::Idle:
		return IdleUpdate(_Delta);
	case SwordState::Fire:
		return FireUpdate(_Delta);
	case SwordState::HIt:
		return HitUpdate(_Delta);
	default:
		break;
	}
}

void BelialSword::IdleStart()
{
	SwordRenderer->SetSprite("BossSword.png");
	float4 Scale = SwordChargeRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	SwordRenderer->SetImageScale(Scale);
}
void BelialSword::IdleUpdate(float _Delta)
{
	IdleTime += _Delta;

	float4 PlayerScale = Player::GetMainPlayer()->GetRendererScale();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();

	PlayerPos.Y += (PlayerScale.Y / 4.0f);
	
	float4 SwordPos = Transform.GetLocalPosition();

	float4 TargetPos = PlayerPos - SwordPos;
	SaveDir = TargetPos.NormalizeReturn();
	SaveDeg = SaveDir.Angle2DDeg();

	if (TargetPos.X < 0)
	{
		if (TargetPos.Y < 0)
		{
			SaveDeg *= -1.0f;
		}
		SaveDeg -= 90.0f;
	}

	if (TargetPos.X >= 0)
	{
		SaveDeg += 180.0f;
		if (TargetPos.Y < 0)
		{
			SaveDeg *= -1.0f;
		}
		SaveDeg += 90.0f;
	}

	Transform.SetLocalRotation({ 0.0f, 0.0f, SaveDeg });
	//if (SaveDir.Y < 0)
	//{
	//	Transform.SetLocalRotation({ 0.0f, 0.0f, SaveDeg + 90.0f });
	//}
	//else
	//{
	//	Transform.SetLocalRotation({ 0.0f, 0.0f, SaveDeg - 90.0f});
	//}

	//SwordRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f, SaveDeg });

	if (IdleTime >= 2.0f)
	{
		ChangeState(SwordState::Fire);
	}
}

void BelialSword::FireStart()
{
	SwordRenderer->SetSprite("BossSwordFX.png");
	float4 Scale = SwordChargeRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	SwordRenderer->SetImageScale(Scale);
}
void BelialSword::FireUpdate(float _Delta)
{
	Transform.AddLocalPosition(SaveDir * _Delta * 2000.0f);
}

void BelialSword::HitStart()
{
	SwordRenderer->SetSprite("BossSword.png");
	float4 Scale = SwordChargeRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	SwordRenderer->SetImageScale(Scale);
}
void BelialSword::HitUpdate(float _Delta)
{

}