#pragma once
#include "GameEngineObject.h"
#include "GameEngineComponent.h"

// Ό³Έν : 
class GameEngineRenderer : public GameEngineComponent
{
public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer & _Other) = delete;
	GameEngineRenderer(GameEngineRenderer && _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer & _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer && _Other) noexcept = delete;

	void SetCameraOrder(int _Order);

protected:
	void Start();

private:
	int CameraOrder = 0;
};

