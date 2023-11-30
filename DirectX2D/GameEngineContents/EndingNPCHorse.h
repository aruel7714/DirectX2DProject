#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class EndingNPCHorse : public GameEngineActor
{
public:
	// constrcuter destructer
	EndingNPCHorse();
	~EndingNPCHorse();

	// delete Function
	EndingNPCHorse(const EndingNPCHorse & _Other) = delete;
	EndingNPCHorse(EndingNPCHorse && _Other) noexcept = delete;
	EndingNPCHorse& operator=(const EndingNPCHorse & _Other) = delete;
	EndingNPCHorse& operator=(EndingNPCHorse && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> HorseRenderer;
};

