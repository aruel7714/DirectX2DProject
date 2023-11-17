#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class LaserState
{
	Attack,
	End,
	Max
};

// Ό³Έν : 
class BelialLaser : public GameEngineActor
{
public:
	// constrcuter destructer
	BelialLaser();
	~BelialLaser();

	// delete Function
	BelialLaser(const BelialLaser & _Other) = delete;
	BelialLaser(BelialLaser && _Other) noexcept = delete;
	BelialLaser& operator=(const BelialLaser & _Other) = delete;
	BelialLaser& operator=(BelialLaser && _Other) noexcept = delete;

protected:
	LaserState State = LaserState::Max;
	
	int Count = 0;
private:

};

