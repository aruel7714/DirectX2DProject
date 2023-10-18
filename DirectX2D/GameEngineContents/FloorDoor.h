#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class FloorDoor : public GameEngineActor
{
public:
	// constrcuter destructer
	FloorDoor();
	~FloorDoor();

	// delete Function
	FloorDoor(const FloorDoor & _Other) = delete;
	FloorDoor(FloorDoor && _Other) noexcept = delete;
	FloorDoor& operator=(const FloorDoor & _Other) = delete;
	FloorDoor& operator=(FloorDoor && _Other) noexcept = delete;

	void SetDoorPosition(float4 _Pos);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> DoorRenderer;
};

