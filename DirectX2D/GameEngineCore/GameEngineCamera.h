#pragma once
#include "GameEngineActor.h"
#include <map>
#include <list>
#include <memory>

// ī�޶�� ������ ������ �迭�Դϴ�.
// ���� : 
class GameEngineCamera
{
	friend class GameEngineRenderer;
	friend class GameEngineActor;
	friend class GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineCamera();
	~GameEngineCamera();

	// delete Function
	GameEngineCamera(const GameEngineCamera & _Other) = delete;
	GameEngineCamera(GameEngineCamera && _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera & _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera && _Other) noexcept = delete;

protected:

private:
	// ���� �Ȱ��� ī�޶� �������� �����Ѵ�.
	std::map<int, std::list<std::shared_ptr<class GameEngineRenderer>>> Renderers;
};
