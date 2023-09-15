#pragma once
#include "BackGround.h"

// Ό³Έν : 
class TownFloor : public BackGround
{
	friend class Player;
public:
	// constrcuter destructer
	TownFloor();
	~TownFloor();

	// delete Function
	TownFloor(const TownFloor & _Other) = delete;
	TownFloor(TownFloor && _Other) noexcept = delete;
	TownFloor& operator=(const TownFloor & _Other) = delete;
	TownFloor& operator=(TownFloor && _Other) noexcept = delete;

	//void SwitchRenderer();

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> FloorRenderer;

	//bool SwitchRenderValue = true;
	
};

