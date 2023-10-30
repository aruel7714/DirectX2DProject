#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class Weapon : public GameEngineActor
{
	friend class Player;
public:
	// constrcuter destructer
	Weapon();
	~Weapon();

	// delete Function
	Weapon(const Weapon & _Other) = delete;
	Weapon(Weapon && _Other) noexcept = delete;
	Weapon& operator=(const Weapon & _Other) = delete;
	Weapon& operator=(Weapon && _Other) noexcept = delete;
	
	void SetWeaponPosition(float4 _Pos);

protected:
	void Start();
	void Update(float _Delta);

	
private:

};

