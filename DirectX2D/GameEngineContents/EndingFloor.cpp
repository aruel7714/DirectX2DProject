#include "PreCompile.h"
#include "EndingFloor.h"

EndingFloor::EndingFloor()
{
}

EndingFloor::~EndingFloor()
{
}

void EndingFloor::Start()
{
	if (nullptr == GameEngineSprite::Find("EndingFloor.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Ending");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
	}
	GameEngineSprite::CreateSingle("EndingFloor.png");

	FloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::FrontFloor);
	FloorRenderer->SetSampler("EngineBaseWRAPSampler");
	FloorRenderer->SetSprite("EndingFloor.png");
	

	DebugFloorRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Floor);
	DebugFloorRenderer->SetSprite("EndingFloor.png");
	DebugFloorRenderer->Off();

	float4 Scale = FloorRenderer->GetCurSprite().Texture->GetScale() * 4.0f;
	FloorRenderer->SetImageScale(Scale);
	Transform.SetLocalPosition({ Scale.X / 2.0f, -(Scale.Y / 2.0f) });

	SetSpeed(50.0f);
}
void EndingFloor::Update(float _Delta)
{
	FloorRenderer->RenderBaseInfoValue.VertexUVPlus += Speed * _Delta;

	float4 Pos = Transform.GetLocalPosition();
	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetLocalPosition();
	int a = 0;
}

void EndingFloor::SetDebugBackGround()
{
	DebugBackGround = this;
}

void EndingFloor::SetSpeed(float _Speed)
{
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();
	Speed = -_Speed / WindowScale.X;
}