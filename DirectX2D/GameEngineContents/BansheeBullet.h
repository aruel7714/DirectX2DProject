#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class BansheeBullet : public GameEngineActor
{
public:
	// constrcuter destructer
	BansheeBullet();
	~BansheeBullet();

	// delete Function
	BansheeBullet(const BansheeBullet & _Other) = delete;
	BansheeBullet(BansheeBullet && _Other) noexcept = delete;
	BansheeBullet& operator=(const BansheeBullet & _Other) = delete;
	BansheeBullet& operator=(BansheeBullet && _Other) noexcept = delete;

protected:

private:

};

