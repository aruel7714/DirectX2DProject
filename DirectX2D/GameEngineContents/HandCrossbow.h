#pragma once
#include "Weapon.h"

// Ό³Έν : 
class HandCrossbow : public Weapon
{
public:
	// constrcuter destructer
	HandCrossbow();
	~HandCrossbow();

	// delete Function
	HandCrossbow(const HandCrossbow & _Other) = delete;
	HandCrossbow(HandCrossbow && _Other) noexcept = delete;
	HandCrossbow& operator=(const HandCrossbow & _Other) = delete;
	HandCrossbow& operator=(HandCrossbow && _Other) noexcept = delete;

	void SetPosition(float4 _Position)
	{
		WeaponPosition = _Position;
	}

	float GetDamage()
	{
		return Damage;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;


private:
	std::shared_ptr<GameEngineSpriteRenderer> HandCrossbowRenderer;

	float4 WeaponPosition = float4::ZERO;

	float AttackTime = 0.0f;
	float AttackSpeed = 2.38f;
	bool AttackReady = true;

	float Damage = 12.0f;
};

