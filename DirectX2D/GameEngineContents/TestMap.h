#pragma once
#include "BackGround.h"

// Ό³Έν : 
class TestMap : public BackGround
{
public:
	// constrcuter destructer
	TestMap();
	~TestMap();

	// delete Function
	TestMap(const TestMap & _Other) = delete;
	TestMap(TestMap && _Other) noexcept = delete;
	TestMap& operator=(const TestMap & _Other) = delete;
	TestMap& operator=(TestMap && _Other) noexcept = delete;

	static TestMap* DebugFloor;

	GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor = { 255, 255, 255, 255 });

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> TestRenderer;
};

