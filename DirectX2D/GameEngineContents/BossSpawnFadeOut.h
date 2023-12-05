#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class BossSpawnFadeOut : public GameEngineActor
{
public:
	// constrcuter destructer
	BossSpawnFadeOut();
	~BossSpawnFadeOut();

	// delete Function
	BossSpawnFadeOut(const BossSpawnFadeOut & _Other) = delete;
	BossSpawnFadeOut(BossSpawnFadeOut && _Other) noexcept = delete;
	BossSpawnFadeOut& operator=(const BossSpawnFadeOut & _Other) = delete;
	BossSpawnFadeOut& operator=(BossSpawnFadeOut && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineUIRenderer> TopRenderer;
	std::shared_ptr<GameEngineUIRenderer> BottomRenderer;
};

