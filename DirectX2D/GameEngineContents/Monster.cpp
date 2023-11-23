#include "PreCompile.h"
#include "Monster.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::DamageCheck()
{
	float PlayerDamage = Player::GetMainPlayer()->GetWeaponDamage();

	Hp -= PlayerDamage;
}