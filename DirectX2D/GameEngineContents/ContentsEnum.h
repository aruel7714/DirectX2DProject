#pragma once

enum class RenderOrder
{
	Debug,
	BackGround,
	BackGround2,
	BackGround3,
	BackProp,
	BackBuilding,
	SecondFloor,
	MiddleFloor,
	Building,
	BuildingProp,
	MiddleProp,
	Floor,
	DungeonProp,
	DungeonBuilding,
	MonsterProjectile,
	MonsterWeapon,
	Monster,
	MonsterFrontWeapon,
	BossBackGround,
	BossBackParticle,
	BossBody,
	BossWallBackProjectile,
	BossWallBackProjectileEffect,
	DungeonWall,
	BossProjectile,
	NPC,
	WeaponProjectile,
	Weapon,
	Player,
	FrontBuilding,
	FrontProp,
};

enum class RenderOrderDungeon
{
	BackGround,
	Floor,
	Prop,
	Building,
	NPC,
	Player
};

enum class TitleRenderOrder
{
	BackCloud,
	MiddleCloud,
	TitleBird,
	FrontCloud,
	MainLogo,
};

enum class CollisionType
{
	Player,
	Trigger,
	DungeonTrigger,
	LevelChangeTrigger,
	Monster,
	MonsterAttack,
	NPC,
	Stele,
};