#pragma once
#include "BackGround.h"

// ���� : 
class TownFloor : public BackGround
{
	friend class Player;
public:
	// constrcuter destructer
	TownFloor();
	~TownFloor();

	// delete Function
	TownFloor(const TownFloor & _Other) = delete;
	TownFloor(TownFloor && _Other) noexcept = delete;
	TownFloor& operator=(const TownFloor & _Other) = delete;
	TownFloor& operator=(TownFloor && _Other) noexcept = delete;

	static TownFloor* DebugFloor;

	void SetDebugMode();

	void SetDebugBackGround();

	//GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor = { 255, 255, 255, 255 });

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	

	//bool SwitchRenderValue = true;
	
};

