#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class PlayerState
{
	Idle,
	Run,
	Jump,
	Max
};

// Ό³Έν : 
class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player & _Other) = delete;
	Player(Player && _Other) noexcept = delete;
	Player& operator=(const Player & _Other) = delete;
	Player& operator=(Player && _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta);

private:
	std::shared_ptr<class GameEngineSpriteRenderer> MainRenderer;

	PlayerState State = PlayerState::Max;
	
	void ChangeState(PlayerState _State);
	void StateUpdate(float _Delta);

	void ChangeAnimationState(const std::string& _State);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void RunStart();
	void RunUpdate(float _Delta);

	void JumpStart();
	void JumpUpdate(float _Delta);

};

