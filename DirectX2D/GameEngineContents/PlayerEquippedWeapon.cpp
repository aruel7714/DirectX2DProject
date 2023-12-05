#include "PreCompile.h"
#include "PlayerEquippedWeapon.h"

PlayerEquippedWeapon::PlayerEquippedWeapon()
{
}

PlayerEquippedWeapon::~PlayerEquippedWeapon()
{
}

void PlayerEquippedWeapon::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\UI\\EquippedWeaponBase");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
	}
	GameEngineSprite::CreateSingle("EquippedWeaponBase.png");

	WeaponUIBase = CreateComponent<GameEngineUIRenderer>(RenderOrder::BackUI);
	WeaponUIBase->SetSprite("EquippedWeaponBase.png");
	float4 BaseScale = WeaponUIBase->GetCurSprite().Texture->GetScale() * 4.0f;
	WeaponUIBase->SetImageScale(BaseScale);

	WeaponTexture = CreateComponent<GameEngineUIRenderer>(RenderOrder::MiddleUI);
	WeaponTexture->SetSprite("Crossbow0.png");
	float4 WeaponScale = WeaponTexture->GetCurSprite().Texture->GetScale() * 4.0f;
	WeaponTexture->SetImageScale(WeaponScale);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X - 64.0f - 32.0f, -HalfWindowScale.Y + 64.0f });
}
void PlayerEquippedWeapon::Update(float _Delta)
{

}