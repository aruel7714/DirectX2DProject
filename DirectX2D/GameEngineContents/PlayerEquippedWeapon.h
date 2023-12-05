#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class PlayerEquippedWeapon : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerEquippedWeapon();
	~PlayerEquippedWeapon();

	// delete Function
	PlayerEquippedWeapon(const PlayerEquippedWeapon & _Other) = delete;
	PlayerEquippedWeapon(PlayerEquippedWeapon && _Other) noexcept = delete;
	PlayerEquippedWeapon& operator=(const PlayerEquippedWeapon & _Other) = delete;
	PlayerEquippedWeapon& operator=(PlayerEquippedWeapon && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineUIRenderer> WeaponUIBase;
	std::shared_ptr<GameEngineUIRenderer> WeaponTexture;
};

