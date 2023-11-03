#pragma once
#include "HandCrossbow.h"

// ���� : 
class Arrow : public HandCrossbow
{
public:
	// constrcuter destructer
	Arrow();
	~Arrow();

	// delete Function
	Arrow(const Arrow & _Other) = delete;
	Arrow(Arrow && _Other) noexcept = delete;
	Arrow& operator=(const Arrow & _Other) = delete;
	Arrow& operator=(Arrow && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> ArrowRenderer;

	float4 Dir = float4::ZERO;
};
