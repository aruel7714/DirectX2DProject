#include "PreCompile.h"
#include "GameEngineSpriteRenderer.h"

GameEngineSpriteRenderer::GameEngineSpriteRenderer()
{
}

GameEngineSpriteRenderer::~GameEngineSpriteRenderer()
{
}

void GameEngineSpriteRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	// 랜더러는 뭐든지 그릴수 있어 니가 세팅만 잘해주면

	// 부모쪽에서 대부분의 일은 해주고
	GameEngineRenderer::ResSetting();

	GameEngineRenderer::Draw();
}