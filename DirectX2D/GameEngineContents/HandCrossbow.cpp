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
	
}
void HandCrossbow::Update(float _Delta)
{
	
}