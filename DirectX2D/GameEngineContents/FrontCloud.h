#pragma once
#include "BackGround.h"

// Ό³Έν : 
class FrontCloud : public BackGround
{
public:
	// constrcuter destructer
	FrontCloud();
	~FrontCloud();

	// delete Function
	FrontCloud(const FrontCloud & _Other) = delete;
	FrontCloud(FrontCloud && _Other) noexcept = delete;
	FrontCloud& operator=(const FrontCloud & _Other) = delete;
	FrontCloud& operator=(FrontCloud && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;

};

