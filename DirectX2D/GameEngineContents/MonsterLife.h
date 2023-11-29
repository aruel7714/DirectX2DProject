#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class MonsterLife : public GameEngineActor
{
public:
	// constrcuter destructer
	MonsterLife();
	~MonsterLife();

	// delete Function
	MonsterLife(const MonsterLife & _Other) = delete;
	MonsterLife(MonsterLife && _Other) noexcept = delete;
	MonsterLife& operator=(const MonsterLife & _Other) = delete;
	MonsterLife& operator=(MonsterLife && _Other) noexcept = delete;

	void SetLifeBarScale(float _Per);

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> MonsterLifeBase;
	std::shared_ptr<GameEngineSpriteRenderer> MonsterLifeBar;

	float MaxLifeBarScaleX = 64.0f;
};

