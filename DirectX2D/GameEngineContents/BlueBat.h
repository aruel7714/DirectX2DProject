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
	BlueBat(const BlueBat & _Other) = delete;
	BlueBat(BlueBat && _Other) noexcept = delete;
	BlueBat& operator=(const BlueBat & _Other) = delete;
	BlueBat& operator=(BlueBat && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> BlueBatRenderer;

	BlueBatState State = BlueBatState::Max;
	BlueBatDir Dir = BlueBatDir::Left;


};

