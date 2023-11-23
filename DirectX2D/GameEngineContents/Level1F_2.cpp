#include "PreCompile.h"
#include "Level1F_2.h"
#include "Level1F_2_Floor.h"

#include "Banshee.h"
#include "RustyShortSwordSkel.h"
#include "SkelDog.h"

#include "DungeonStele.h"
#include "DungeonTorch.h"

Level1F_2::Level1F_2()
{
}

Level1F_2::~Level1F_2()
{
}

void Level1F_2::Start()
{
	GameEngineSprite::CreateSingle("Level1F_2.png");
	GameEngineSprite::CreateSingle("Level1F_2_Debug.png");

	Floor2 = CreateActor<class Level1F_2_Floor>(RenderOrder::Floor);

	MainPlayer = CreateActor<Player>(RenderOrder::Player);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Level1F_2.png");
	float4 MapScale = Texture->GetScale() * 4.0f;

	std::shared_ptr<Banshee> MonsterBanshee = CreateActor<Banshee>(RenderOrder::Monster);
	MonsterBanshee->Transform.SetLocalPosition({ 1344.0f, -256.0f });
	MonsterBanshee->SetName(std::string_view("MonsterBanshee"));
	AllMonsters.insert(std::pair<std::string, std::shared_ptr<GameEngineActor>>(MonsterBanshee->GetName(), MonsterBanshee));
	MonsterDeathCheck.insert(std::pair<std::string, bool>(MonsterBanshee->GetName(), false));

	std::shared_ptr<RustyShortSwordSkel> MonsterRustyShortSwordSkel = CreateActor<RustyShortSwordSkel>(RenderOrder::Monster);
	MonsterRustyShortSwordSkel->Transform.SetLocalPosition({ 1920.0f, -448.0f });
	MonsterRustyShortSwordSkel->SetName(std::string_view("MonsterRustyShortSwordSkel"));
	AllMonsters.insert(std::pair<std::string, std::shared_ptr<GameEngineActor>>(MonsterRustyShortSwordSkel->GetName(), MonsterRustyShortSwordSkel));
	MonsterDeathCheck.insert(std::pair<std::string, bool>(MonsterRustyShortSwordSkel->GetName(), false));

	std::shared_ptr<SkelDog> MonsterSkelDog = CreateActor<SkelDog>(RenderOrder::Monster);
	MonsterSkelDog->Transform.SetLocalPosition({ 1088.0f, -640.0f });
	MonsterSkelDog->SetName(std::string_view("MonsterSkelDog"));
	AllMonsters.insert(std::pair<std::string, std::shared_ptr<GameEngineActor>>(MonsterSkelDog->GetName(), MonsterSkelDog));
	MonsterDeathCheck.insert(std::pair<std::string, bool>(MonsterSkelDog->GetName(), false));

	Stele1 = CreateActor<DungeonStele>(RenderOrder::DungeonBuilding);
	Stele1->Transform.SetLocalPosition({ 64.0f + 32.0f, -(MapScale.Y - 256.0f) });
	Stele1->Transform.SetLocalRotation({ 0.0f, 0.0f, 90.0f });
	Stele1->SetCollisionScale({ 64.0f, 256.0f });

	Stele2 = CreateActor<DungeonStele>(RenderOrder::DungeonBuilding);
	Stele2->Transform.SetLocalPosition({ (MapScale.X - 64.0f - 32.0f), -(832.0f - 128.0f) });
	Stele2->Transform.SetLocalRotation({ 0.0f, 0.0f, -90.0f });
	Stele2->SetCollisionScale({ 64.0f, 256.0f });

	{
		std::shared_ptr<DungeonTorch> Torch1 = CreateActor<DungeonTorch>(RenderOrder::DungeonProp);
		Torch1->Transform.SetLocalPosition({ 672.0f, -640.0f });

		std::shared_ptr<DungeonTorch> Torch2 = CreateActor<DungeonTorch>(RenderOrder::DungeonProp);
		Torch2->Transform.SetLocalPosition({ 928.0f, -352.0f });

		std::shared_ptr<DungeonTorch> Torch3 = CreateActor<DungeonTorch>(RenderOrder::DungeonProp);
		Torch3->Transform.SetLocalPosition({ 1760.0f, -352.0f });

		std::shared_ptr<DungeonTorch> Torch4 = CreateActor<DungeonTorch>(RenderOrder::DungeonProp);
		Torch4->Transform.SetLocalPosition({ 2016.0f, -640.0f });
	}

	{
		TriggerLeft = CreateActor<DungeonMoveTrigger>(RenderOrder::DungeonBuilding);
		TriggerLeft->SetMoveTriggerPosition({ 16.0f, -(MapScale.Y - 128.0f - 128.0f) });
		TriggerLeft->SetMoveTriggerScale({ 64.0f, 256.0f });
	}

	{
		TriggerRight = CreateActor<DungeonMoveTrigger>(RenderOrder::DungeonBuilding);
		TriggerRight->SetMoveTriggerPosition({ MapScale.X - 16.0f, -(MapScale.Y - 384.0f - 128.0f) });
		TriggerRight->SetMoveTriggerScale({ 64.0f, 256.0f });
	}
}
void Level1F_2::Update(float _Delta)
{
	DeathOn();

	if (AllDeathCheck() == true)
	{
		Stele1->SteleOpened();
		Stele2->SteleOpened();
	}

	EventParameter ParameterLeft;
	ParameterLeft.Stay = [](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		GameEngineCore::ChangeLevel("Level1F");
	};

	EventParameter ParameterRight;
	ParameterRight.Stay = [](class GameEngineCollision* _This, class GameEngineCollision* _Other)
	{
		GameEngineCore::ChangeLevel("Level1F_Shop");
	};

	TriggerLeft->MoveTriggerCollision->CollisionEvent(CollisionType::Player, ParameterLeft);
	TriggerRight->MoveTriggerCollision->CollisionEvent(CollisionType::Player, ParameterRight);
}

void Level1F_2::LevelStart(GameEngineLevel* _PrevLevel)
{
	Floor2->SetDebugBackGround();

	if (FindLevel("Level1F") == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ 96.0f , -1088.0f });
	}

	if (FindLevel("Level1F_Shop") == _PrevLevel)
	{
		MainPlayer->Transform.SetLocalPosition({ TriggerRight->MoveTriggerCollision->Transform.GetLocalPosition().X - 96.0f , -832.0f });
	}
}
void Level1F_2::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Level1F_2::DeathOn()
{
	for (std::pair<std::string, std::shared_ptr<GameEngineActor>> Pair : AllMonsters)
	{
		if (Pair.second->IsDeath())
		{
			std::map<std::string, bool>::iterator Finditer = MonsterDeathCheck.find(Pair.first);
			Finditer->second = true;
		}
	}
}

bool Level1F_2::AllDeathCheck()
{
	for (std::pair<std::string, bool> Pair : MonsterDeathCheck)
	{
		if (Pair.second == false)
		{
			return false;
		}
	}

	return true;
}