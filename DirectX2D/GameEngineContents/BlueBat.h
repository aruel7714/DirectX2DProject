#pragma once
#include "PlayActor.h"

// Ό³Έν : 
class BlueBat : public PlayActor
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

};

