#pragma once
#include "BackGround.h"

// Ό³Έν : 
class EndingFloor : public BackGround
{
public:
	// constrcuter destructer
	EndingFloor();
	~EndingFloor();

	// delete Function
	EndingFloor(const EndingFloor & _Other) = delete;
	EndingFloor(EndingFloor && _Other) noexcept = delete;
	EndingFloor& operator=(const EndingFloor & _Other) = delete;
	EndingFloor& operator=(EndingFloor && _Other) noexcept = delete;

	void SetDebugBackGround();

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	
};

