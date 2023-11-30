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
	MonsterLifeBase,
	MonsterLifeBar,
	BossBackGround,
	BossBackParticle,
	BossBody,
	BossWallBackProjectile,
	BossWallBackProjectileEffect,
	DungeonWall,
	BossBody2,
	BossProjectile,
	NPC,
	NPCEventKey,
	WeaponProjectile,
	Weapon,
	Player,
	FrontBuilding,
	FrontProp,
	FrontFloor,

	BackUI,
	MiddleUI,
	FrontUI,
	Mouse,
};



enum class TitleRenderOrder
{
	BackCloud,
	MiddleCloud,
	TitleBird,
	FrontCloud,
	UI,
	Mouse,
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
	Weapon,
	Button,
	Mouse,
};