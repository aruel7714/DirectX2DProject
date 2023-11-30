#include "PreCompile.h"
#include "EndingFrontGround.h"

EndingFrontGround::EndingFrontGround()
{
}

EndingFrontGround::~EndingFrontGround()
{
}

void EndingFrontGround::Start()
{
	if (nullptr == GameEngineSprite::Find("FrontGround.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Texture\\Ending");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
	}
	GameEngineSprite::CreateSingle("FrontGround.png");
	
	FrontGroundRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BackUI);
	FrontGroundRenderer->SetSprite("FrontGround.png");

	Transform.SetLocalPosition({1216.0f, -360.0f});
}
void EndingFrontGround::Update(float _Delta)
{

}