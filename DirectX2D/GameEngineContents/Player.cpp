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
	CreateChild<GameEngineRenderer>();
}

void Player::Update(float _Delta)
{
	int a = 0;
}