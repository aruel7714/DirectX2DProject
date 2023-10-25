#pragma once
#include "BackGround.h"

// Ό³Έν : 
class Level1F_3_Floor : public BackGround
{
public:
	// constrcuter destructer
	Level1F_3_Floor();
	~Level1F_3_Floor();

	// delete Function
	Level1F_3_Floor(const Level1F_3_Floor & _Other) = delete;
	Level1F_3_Floor(Level1F_3_Floor && _Other) noexcept = delete;
	Level1F_3_Floor& operator=(const Level1F_3_Floor & _Other) = delete;
	Level1F_3_Floor& operator=(Level1F_3_Floor && _Other) noexcept = delete;

	void SetDebugBackGround();

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

};

