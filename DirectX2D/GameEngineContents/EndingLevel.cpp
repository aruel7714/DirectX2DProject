#include "PreCompile.h"
#include "EndingLevel.h"

#include "EndingNPCHorse.h"
#include "TownSky.h"
#include "EndingFloor.h"
#include "EndingFrontGround.h"
#include "EndingBackGround.h"

EndingLevel::EndingLevel()
{
}

EndingLevel::~EndingLevel()
{
}

void EndingLevel::Start()
{
	std::shared_ptr<EndingNPCHorse> NPCHorse = CreateActor<EndingNPCHorse>(RenderOrder::FrontProp);
	NPCHorse->Transform.SetLocalPosition({ 288.0f, -512.0f });
	std::shared_ptr<Player> MainPlayer = CreateActor<Player>(RenderOrder::Player);
	MainPlayer->ChangeStateEnding();
	MainPlayer->Transform.SetLocalPosition({ 448.0f, -448.0f });
	std::shared_ptr<TownSky> BackSky = CreateActor<TownSky>(RenderOrder::BackGround);
	Floor = CreateActor<EndingFloor>(RenderOrder::FrontFloor);

	std::shared_ptr<EndingBackGround> BackGround = CreateActor<EndingBackGround>(RenderOrder::BackGround2);

	std::shared_ptr<EndingFrontGround> FrontGround = CreateActor<EndingFrontGround>(RenderOrder::BackUI);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y });
}
void EndingLevel::Update(float _Delta)
{

}

void EndingLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GlobalSound::Bgm = GameEngineSound::SoundPlay("Credit.wav");
	FadeOut = CreateActor<LevelFadeOut>(RenderOrder::Fade);

	FadeIn = CreateActor<LevelFadeIn>(RenderOrder::Fade);
	FadeIn->Off();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y });
	Floor->SetDebugBackGround();
}
void EndingLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	FadeIn->Death();
}