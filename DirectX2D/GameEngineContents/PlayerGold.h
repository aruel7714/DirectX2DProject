#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class PlayerGold : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerGold();
	~PlayerGold();

	// delete Function
	PlayerGold(const PlayerGold & _Other) = delete;
	PlayerGold(PlayerGold && _Other) noexcept = delete;
	PlayerGold& operator=(const PlayerGold & _Other) = delete;
	PlayerGold& operator=(PlayerGold && _Other) noexcept = delete;

protected:

private:

};

