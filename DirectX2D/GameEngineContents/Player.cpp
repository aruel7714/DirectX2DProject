#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineRenderer.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	std::shared_ptr<GameEngineRenderer> Renderer = CreateComponent<GameEngineRenderer>(0);
	// Renderer->SetCameraOreder(0);
	//CreateChild<GameEngineRenderer>();
}

void Player::Update(float _Delta)
{
	int a = 0;
}