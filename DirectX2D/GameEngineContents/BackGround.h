#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	BackGround();
	~BackGround();

	// delete Function
	BackGround(const BackGround & _Other) = delete;
	BackGround(BackGround && _Other) noexcept = delete;
	BackGround& operator=(const BackGround & _Other) = delete;
	BackGround& operator=(BackGround && _Other) noexcept = delete;

	static BackGround* DebugBackGround;

	GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor = { 255, 255, 255, 255 });


protected:
	void Start() override;
	void Update(float _Delta) override;

	float4 WindowScale = float4::ZERO;

	float4 ImageScale = float4::ZERO;

	std::shared_ptr<class GameEngineSpriteRenderer> FloorRenderer = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugFloorRenderer = nullptr;

	//GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor = { 255, 255, 255, 255 });

	bool IsDebug = false;

private:
	
};

