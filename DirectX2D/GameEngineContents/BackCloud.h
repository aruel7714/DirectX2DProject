#pragma once
#include "BackGround.h"

// Ό³Έν : 
class BackCloud : public BackGround
{
public:
	// constrcuter destructer
	BackCloud();
	~BackCloud();

	// delete Function
	BackCloud(const BackCloud & _Other) = delete;
	BackCloud(BackCloud && _Other) noexcept = delete;
	BackCloud& operator=(const BackCloud & _Other) = delete;
	BackCloud& operator=(BackCloud && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;

};

