#pragma once
#include "BackGround.h"

// Ό³Έν : 
class DebugFloor : public BackGround
{
public:
	// constrcuter destructer
	DebugFloor();
	~DebugFloor();

	// delete Function
	DebugFloor(const DebugFloor & _Other) = delete;
	DebugFloor(DebugFloor && _Other) noexcept = delete;
	DebugFloor& operator=(const DebugFloor & _Other) = delete;
	DebugFloor& operator=(DebugFloor && _Other) noexcept = delete;

	static DebugFloor* MainDebugFloor;

	GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor = { 255, 255, 255, 255 });

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> DebugFloorRenderer;

};

