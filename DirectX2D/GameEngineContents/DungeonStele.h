#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class SteleState
{
	Closed,
	Idle,
	Opened,
	Max
};

// Ό³Έν : 
class DungeonStele : public GameEngineActor
{
public:
	// constrcuter destructer
	DungeonStele();
	~DungeonStele();

	// delete Function
	DungeonStele(const DungeonStele & _Other) = delete;
	DungeonStele(DungeonStele && _Other) noexcept = delete;
	DungeonStele& operator=(const DungeonStele & _Other) = delete;
	DungeonStele& operator=(DungeonStele && _Other) noexcept = delete;

	void SetCollisionScale(float4 _Value)
	{
		SteleCollision->Transform.SetLocalScale(_Value);
		SteleCollision->Transform.SetLocalRotation({0.0f, 0.0f, 90.0f});
	}

	void SteleOpened();

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> SteleRenderer;

	SteleState State = SteleState::Max;

	std::shared_ptr<GameEngineCollision> SteleCollision;

	void ChangeState(SteleState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void ClosedStart();
	void ClosedUpdate(float _Delta);
	
	void IdleStart();
	void IdleUpdate(float _Delta);

	void OpenedStart();
	void OpenedUpdate(float _Delta);
};

