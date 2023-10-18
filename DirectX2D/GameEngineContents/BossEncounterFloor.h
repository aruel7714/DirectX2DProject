#pragma once
#include "BackGround.h"

// Ό³Έν : 
class BossEncounterFloor : public BackGround
{
public:
	// constrcuter destructer
	BossEncounterFloor();
	~BossEncounterFloor();

	// delete Function
	BossEncounterFloor(const BossEncounterFloor & _Other) = delete;
	BossEncounterFloor(BossEncounterFloor && _Other) noexcept = delete;
	BossEncounterFloor& operator=(const BossEncounterFloor & _Other) = delete;
	BossEncounterFloor& operator=(BossEncounterFloor && _Other) noexcept = delete;

	void SetDebugBackGround();

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	
};

