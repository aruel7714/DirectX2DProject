#pragma once
#include "PlayActor.h"

// Ό³Έν : 
class Monster : public PlayActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster & _Other) = delete;
	Monster(Monster && _Other) noexcept = delete;
	Monster& operator=(const Monster & _Other) = delete;
	Monster& operator=(Monster && _Other) noexcept = delete;

protected:
	float Hp = 0.0f;
	float Damage = 0.0f;
	float MoveSpeed = 0.0f;

	void DamageCheck();

	void AirWallCheck(float _Delta, float4 _CheckPos, float4 _CheckScale);
private:
	
};

