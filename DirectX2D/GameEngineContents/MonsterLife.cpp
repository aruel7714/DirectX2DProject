#include "PreCompile.h"
#include "MonsterLife.h"

MonsterLife::MonsterLife()
{
}

MonsterLife::~MonsterLife()
{
}

void MonsterLife::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\UI\\MonsterLife");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
	}
	GameEngineSprite::CreateSingle("MonsterLifeBack.png");

	MonsterLifeBase = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MonsterLifeBase);
	MonsterLifeBase->SetSprite("MonsterLifeBack.png");
	float4 Scale = MonsterLifeBase->GetCurSprite().Texture->GetScale() * 4.0f;
	MonsterLifeBase->SetImageScale(Scale);

	MonsterLifeBar = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MonsterLifeBar);
	MonsterLifeBar->SetSprite("LifeBar.png");
	MonsterLifeBar->SetPivotType(PivotType::Left);
	MonsterLifeBar->SetImageScale({ 64.0f, 12.0f });

	MonsterLifeBar->Transform.SetLocalPosition({ -32.0f, 0.0f });
}
void MonsterLife::Update(float _Delta)
{

}

void MonsterLife::SetLifeBarScale(float _Per)
{
	float LifeBarScale = MaxLifeBarScaleX / 100.0f * _Per;

	if (0 >= _Per)
	{
		MonsterLifeBar->SetImageScale({ 0.0f, 12.0f });
	}
	else
	{
		MonsterLifeBar->SetImageScale({ LifeBarScale, 12.0f });
	}
}