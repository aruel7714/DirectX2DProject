#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class TownNPCBlackSmith : public GameEngineActor
{
public:
	// constrcuter destructer
	TownNPCBlackSmith();
	~TownNPCBlackSmith();

	// delete Function
	TownNPCBlackSmith(const TownNPCBlackSmith & _Other) = delete;
	TownNPCBlackSmith(TownNPCBlackSmith && _Other) noexcept = delete;
	TownNPCBlackSmith& operator=(const TownNPCBlackSmith & _Other) = delete;
	TownNPCBlackSmith& operator=(TownNPCBlackSmith && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> HakenRenderer;
};

