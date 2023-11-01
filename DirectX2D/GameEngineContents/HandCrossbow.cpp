#include "PreCompile.h"
#include "HandCrossbow.h"
#include "Player.h"

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
	float4 PlayerScale = Player::MainPlayer->GetRendererScale();

	float4 PlayerPosition = Player::MainPlayer->Transform.GetWorldPosition();
	
	PlayerPosition.Y += (PlayerScale.Y / 5.0f);

	float4 MousePos = GetLevel()->GetMainCamera()->GetWorldMousePos2D();
	float4 MousePlayerPos = MousePos - PlayerPosition;
	float4 MouseDir = MousePlayerPos.NormalizeReturn();

	float MouseDeg = MouseDir.Angle2DDeg();

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