#pragma once
#include "BackGround.h"

// Ό³Έν : 
class DungeonBuildingShop : public BackGround
{
public:
	// constrcuter destructer
	DungeonBuildingShop();
	~DungeonBuildingShop();

	// delete Function
	DungeonBuildingShop(const DungeonBuildingShop & _Other) = delete;
	DungeonBuildingShop(DungeonBuildingShop && _Other) noexcept = delete;
	DungeonBuildingShop& operator=(const DungeonBuildingShop & _Other) = delete;
	DungeonBuildingShop& operator=(DungeonBuildingShop && _Other) noexcept = delete;

	void SetBuildingPosition(float4 _Pos);

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> DungeonShopRenderer;
};

