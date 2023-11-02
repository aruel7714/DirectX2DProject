#pragma once
#include "PlayActor.h"

enum class LittleGhostState
{
	Idle,
	Move,
	Attack,
	Max
};

enum class LittleGhostDir
{
	Left,
	Right,
};

// Ό³Έν : 
class LittleGhost : public PlayActor
{
public:
	// constrcuter destructer
	LittleGhost();
	~LittleGhost();

	// delete Function
	LittleGhost(const LittleGhost & _Other) = delete;
	LittleGhost(LittleGhost && _Other) noexcept = delete;
	LittleGhost& operator=(const LittleGhost & _Other) = delete;
	LittleGhost& operator=(LittleGhost && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delat) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> LittleGhostRenderer;
	
	LittleGhostState State = LittleGhostState::Max;
	LittleGhostDir Dir = LittleGhostDir::Left;

	void ChangeState(LittleGhostState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void IdleStart();
	void idleUpdate(float _Delta);
	
	void MoveStart();
	void MoveUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void DirCheck();
};

