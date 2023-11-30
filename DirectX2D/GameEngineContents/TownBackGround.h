#pragma once
#include "BackGround.h"

// Ό³Έν : 
class TownBackGround : public BackGround
{
public:
	// constrcuter destructer
	TownBackGround();
	~TownBackGround();

	// delete Function
	TownBackGround(const TownBackGround & _Other) = delete;
	TownBackGround(TownBackGround && _Other) noexcept = delete;
	TownBackGround& operator=(const TownBackGround & _Other) = delete;
	TownBackGround& operator=(TownBackGround && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> BackGroundRenderer;
};

