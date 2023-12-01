#pragma once
#include "BackGround.h"

// Ό³Έν : 
class EndingBackGround : public BackGround
{
public:
	// constrcuter destructer
	EndingBackGround();
	~EndingBackGround();

	// delete Function
	EndingBackGround(const EndingBackGround & _Other) = delete;
	EndingBackGround(EndingBackGround && _Other) noexcept = delete;
	EndingBackGround& operator=(const EndingBackGround & _Other) = delete;
	EndingBackGround& operator=(EndingBackGround && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> BackGroundRenderer;

	float Speed = 0.0f;

	void SetSpeed(float _Speed);
};

