#pragma once
#include "BackGround.h"

// Ό³Έν : 
class TownSky : public BackGround
{
public:
	// constrcuter destructer
	TownSky();
	~TownSky();

	// delete Function
	TownSky(const TownSky & _Other) = delete;
	TownSky(TownSky && _Other) noexcept = delete;
	TownSky& operator=(const TownSky & _Other) = delete;
	TownSky& operator=(TownSky && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;

};

