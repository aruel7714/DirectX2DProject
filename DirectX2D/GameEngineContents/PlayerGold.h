#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� : 
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
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineUIRenderer> GoldRenderer;
	std::shared_ptr<GameEngineUIRenderer> GoldText;
};

