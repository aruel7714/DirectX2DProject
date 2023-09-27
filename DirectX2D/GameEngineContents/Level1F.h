#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν : 
class Level1F : public GameEngineLevel
{
public:
	// constrcuter destructer
	Level1F();
	~Level1F();

	// delete Function
	Level1F(const Level1F & _Other) = delete;
	Level1F(Level1F && _Other) noexcept = delete;
	Level1F& operator=(const Level1F & _Other) = delete;
	Level1F& operator=(Level1F && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:

};

