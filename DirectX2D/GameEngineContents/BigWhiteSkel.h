#pragma once
#include "PlayActor.h"

enum class BigWhiteSkelState
{
	Idle,
	Move,
	Attack,
	AttackReady,
	Max
};

enum class BigWhiteSkelDir
{
	Left,
	Right
};

// Ό³Έν : 
class BigWhiteSkel : public PlayActor
{
public:
	// constrcuter destructer
	BigWhiteSkel();
	~BigWhiteSkel();

	// delete Function
	BigWhiteSkel(const BigWhiteSkel & _Other) = delete;
	BigWhiteSkel(BigWhiteSkel && _Other) noexcept = delete;
	BigWhiteSkel& operator=(const BigWhiteSkel & _Other) = delete;
	BigWhiteSkel& operator=(BigWhiteSkel && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> BigWhiteSkelRenderer;

	BigWhiteSkelState State = BigWhiteSkelState::Max;
	BigWhiteSkelDir Dir = BigWhiteSkelDir::Left;

	void ChangeState(BigWhiteSkelState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void AttackReadyStart();
	void AttackReadyUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void DirCheck();
};

