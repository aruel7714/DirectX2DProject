#pragma once
#include "PlayActor.h"

enum class RedBatState
{
	Idle,
	Attack,
	Max,
};

enum class RedBatDir
{
	Left,
	Right
};

// ���� : 
class RedBat : public PlayActor
{
public:
	// constrcuter destructer
	RedBat();
	~RedBat();

	// delete Function
	RedBat(const RedBat & _Other) = delete;
	RedBat(RedBat && _Other) noexcept = delete;
	RedBat& operator=(const RedBat & _Other) = delete;
	RedBat& operator=(RedBat && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> RedBatRenderer;
};
