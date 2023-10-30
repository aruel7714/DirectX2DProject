#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class DownDoor : public GameEngineActor
{
public:
	// constrcuter destructer
	DownDoor();
	~DownDoor();

	// delete Function
	DownDoor(const DownDoor & _Other) = delete;
	DownDoor(DownDoor && _Other) noexcept = delete;
	DownDoor& operator=(const DownDoor & _Other) = delete;
	DownDoor& operator=(DownDoor && _Other) noexcept = delete;

	void SetDoorPosition(float4 _Pos);

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> DoorRenderer;
	std::shared_ptr<class GameEngineCollision> DoorCollision;
};

