#pragma once
#include "BackGround.h"

// Ό³Έν : 
class DungeonBuildingInn : public BackGround
{
public:
	// constrcuter destructer
	DungeonBuildingInn();
	~DungeonBuildingInn();

	// delete Function
	DungeonBuildingInn(const DungeonBuildingInn & _Other) = delete;
	DungeonBuildingInn(DungeonBuildingInn && _Other) noexcept = delete;
	DungeonBuildingInn& operator=(const DungeonBuildingInn & _Other) = delete;
	DungeonBuildingInn& operator=(DungeonBuildingInn && _Other) noexcept = delete;

	void SetBuildingPosition(float4 _Pos);

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> DungeonInnRenderer;
};

