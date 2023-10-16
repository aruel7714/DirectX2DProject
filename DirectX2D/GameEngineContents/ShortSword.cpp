#include "PreCompile.h"
#include "ShortSword.h"
#include "Player.h"

ShortSword* ShortSword::WeaponShortSword;

ShortSword::ShortSword()
{
}

ShortSword::~ShortSword()
{
}

void ShortSword::Start()
{
	WeaponShortSword = this;

	if (nullptr == GameEngineSprite::Find("ShortSword.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Weapon\\");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("ShortSword.png");
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\WeaponFX\\");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}

	}

	ShortSwordRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Weapon);

	ShortSwordRenderer->SetSprite("ShortSword.png");

	float4 Scale = ShortSwordRenderer->GetCurSprite().Texture->GetScale();
	Scale *= 4.0f;

	ShortSwordRenderer->SetImageScale(Scale);
	
}
void ShortSword::Update(float _Delta)
{

}