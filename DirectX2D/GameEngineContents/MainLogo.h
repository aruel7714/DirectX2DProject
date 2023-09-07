#pragma once
#include "BackGround.h"

// Ό³Έν : 
class MainLogo : public BackGround
{
public:
	// constrcuter destructer
	MainLogo();
	~MainLogo();

	// delete Function
	MainLogo(const MainLogo & _Other) = delete;
	MainLogo(MainLogo && _Other) noexcept = delete;
	MainLogo& operator=(const MainLogo & _Other) = delete;
	MainLogo& operator=(MainLogo && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;

};

