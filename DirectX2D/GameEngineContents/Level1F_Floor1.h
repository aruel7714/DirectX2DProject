#pragma once
#include "BackGround.h"

// Ό³Έν : 
class Level1F_Floor1 : public BackGround
{
public:
	// constrcuter destructer
	Level1F_Floor1();
	~Level1F_Floor1();

	// delete Function
	Level1F_Floor1(const Level1F_Floor1 & _Other) = delete;
	Level1F_Floor1(Level1F_Floor1 && _Other) noexcept = delete;
	Level1F_Floor1& operator=(const Level1F_Floor1 & _Other) = delete;
	Level1F_Floor1& operator=(Level1F_Floor1 && _Other) noexcept = delete;

	void SetDebugBackGround();

protected:
	void Start() override;
	void Update(float _Delta) override;
private:

};

