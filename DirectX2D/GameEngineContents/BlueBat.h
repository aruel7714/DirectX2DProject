#pragma once
#include "Monster.h"

enum class BlueBatState
{
	Move,
	Death,
	Max,
};

enum class BlueBatDir
{
	Left,
	Right
};

// Ό³Έν : 
class BlueBat : public Monster
{
public:
	// constrcuter destructer
	BlueBat();
	~BlueBat();

	// delete Function
	BlueBat(const BlueBat& _Other) = delete;
	BlueBat(BlueBat&& _Other) noexcept = delete;
	BlueBat& operator=(const BlueBat& _Other) = delete;
	BlueBat& operator=(BlueBat&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> BlueBatRenderer;

	BlueBatState State = BlueBatState::Max;
	BlueBatDir Dir = BlueBatDir::Left;

	std::shared_ptr<GameEngineCollision> BlueBatCollision;

	GameEngineRandom Random;
	float RandomDir;

	float MoveTime = 0.0f;

	void ChangeState(BlueBatState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);

	void DirCheck();
};
