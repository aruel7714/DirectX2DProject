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
	
	static float4 MouseDir;
	static float MouseDeg;

protected:
	void Start();
	void Update(float _Delta);

	
private:
	
};

