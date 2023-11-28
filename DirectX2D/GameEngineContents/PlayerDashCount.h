#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class PlayerDashCount : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerDashCount();
	~PlayerDashCount();

	// delete Function
	PlayerDashCount(const PlayerDashCount & _Other) = delete;
	PlayerDashCount(PlayerDashCount && _Other) noexcept = delete;
	PlayerDashCount& operator=(const PlayerDashCount & _Other) = delete;
	PlayerDashCount& operator=(PlayerDashCount && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineUIRenderer> DashCountBase;
	std::shared_ptr<GameEngineUIRenderer> DashCount;
};

