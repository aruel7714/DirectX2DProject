#include "PreCompile.h"
#include "HandCrossbow.h"
#include "Player.h"
#include "Arrow.h"

HandCrossbow::HandCrossbow()
{
}

HandCrossbow::~HandCrossbow()
{
}

void HandCrossbow::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Weapon\\HandCrossbow");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
		GameEngineSprite::CreateSingle("Crossbow0.png");
		GameEngineSprite::CreateSingle("Crossbow2.png");
	}

	HandCrossbowRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Weapon);
	HandCrossbowRenderer->SetSprite("Crossbow2.png");

	float4 ImageScale = GameEngineTexture::Find("Crossbow2.png")->GetScale() * 4.0f;

	HandCrossbowRenderer->SetImageScale(ImageScale);

	//HandCrossbowRenderer->SetPivotValue({ 0.2f, 0.5f });

	GameEngineInput::AddInputObject(this);
	
}
void HandCrossbow::Update(float _Delta)
{
	AttackTime += _Delta;

	float4 PlayerScale = Player::MainPlayer->GetRendererScale();

	float4 PlayerPosition = Player::MainPlayer->Transform.GetWorldPosition();
	
	PlayerPosition.Y += (PlayerScale.Y / 5.0f);

	float4 MousePos = GetLevel()->GetMainCamera()->GetWorldMousePos2D();
	float4 MousePlayerPos = MousePos - PlayerPosition;
	MouseDir = MousePlayerPos.NormalizeReturn();

	MouseDeg = MouseDir.Angle2DDeg();

	if (Player::MainPlayer->GetPlayerDir() == PlayerDir::Left)
	{
		HandCrossbowRenderer->LeftFlip();
		HandCrossbowRenderer->SetPivotValue({ 0.2f, 0.7f });
		//Transform.SetLocalPosition();
		PlayerPosition.X -= PlayerScale.X / 5.0f;

		MouseDeg += 180.0f;
		if (MousePlayerPos.Y < 0)
		{
			MouseDeg *= -1.0f;
		}

	}
	if (Player::MainPlayer->GetPlayerDir() == PlayerDir::Right)
	{
		HandCrossbowRenderer->RightFlip();
		HandCrossbowRenderer->SetPivotValue({ 0.8f, 0.7f });
		PlayerPosition.X += PlayerScale.X / 5.0f;

		if (MousePlayerPos.Y < 0)
		{
			MouseDeg *= -1.0f;
		}
	}
	Transform.SetLocalPosition(PlayerPosition);
	Transform.SetLocalRotation({ 0.0f, 0.0f, MouseDeg });

	if (AttackTime > (1.0f / AttackSpeed))
	{
		AttackReady = true;
	}

	if (GameEngineInput::IsPress(VK_LBUTTON, this) && AttackReady == true)
	{
		std::shared_ptr<Arrow> CrossbowArrow = GetLevel()->CreateActor<Arrow>(RenderOrder::WeaponProjectile);

		AttackReady = false;
		AttackTime = 0.0f;
	}

	// 공격속도 2.38
	// Time = 0;
	// Time += _Delta
	// (1 / 2,38) < Time 일때만 공격
	// 공격하고나면 Time = 0;
	

	


	//Transform.SetLocalRotation({ 0.0f, 0.0f, 45.0f });

	//float4 Pos1 = Player::MainPlayer->Transform.GetWorldPosition();
	int a = 0;


	//if (GameEngineInput::IsPress('1', this))
	//{
	//	Transform.SetLocalRotation({ 0.0f, 0.0f, 0.0f });
	//}
	//if (GameEngineInput::IsPress('2', this))
	//{
	//	Transform.SetLocalRotation({ 0.0f, 0.0f, 45.0f });
	//}
	//if (GameEngineInput::IsPress('3', this))
	//{
	//	Transform.SetLocalRotation({ 0.0f, 0.0f, 90.0f });
	//}
	//if (GameEngineInput::IsPress('4', this))
	//{
	//	HandCrossbowRenderer->SetPivotValue({ 0.0f, 0.5f });
	//}
	//if (GameEngineInput::IsPress('5', this))
	//{
	//	HandCrossbowRenderer->SetPivotValue({ 0.25f, 0.5f });
	//}
	//if (GameEngineInput::IsPress('6', this))
	//{
	//	HandCrossbowRenderer->SetPivotValue({ 0.5f, 0.5f });
	//}
	//if (GameEngineInput::IsPress('7', this))
	//{
	//	HandCrossbowRenderer->SetPivotValue({ 0.75f, 0.5f });
	//}

}