#pragma once
#include "PlayActor.h"

enum class ArcherSkelState
{
	Idle,
	AttackReady,
	Attack,
	Max,
};

enum class ArcherSkelDir
{
	Left,
	Right,
};

// Ό³Έν : 
class ArcherSkel : public PlayActor
{
public:
	// constrcuter destructer
	ArcherSkel();
	~ArcherSkel();

	// delete Function
	ArcherSkel(const ArcherSkel & _Other) = delete;
	ArcherSkel(ArcherSkel && _Other) noexcept = delete;
	ArcherSkel& operator=(const ArcherSkel & _Other) = delete;
	ArcherSkel& operator=(ArcherSkel && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta);
private:
	std::shared_ptr<GameEngineSpriteRenderer> ArcherSkelRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> BowRenderer;

	
};

