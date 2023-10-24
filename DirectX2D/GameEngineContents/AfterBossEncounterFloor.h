#pragma once
#include "BackGround.h"

// Ό³Έν : 
class AfterBossEncounterFloor : public BackGround
{
public:
	// constrcuter destructer
	AfterBossEncounterFloor();
	~AfterBossEncounterFloor();

	// delete Function
	AfterBossEncounterFloor(const AfterBossEncounterFloor & _Other) = delete;
	AfterBossEncounterFloor(AfterBossEncounterFloor && _Other) noexcept = delete;
	AfterBossEncounterFloor& operator=(const AfterBossEncounterFloor & _Other) = delete;
	AfterBossEncounterFloor& operator=(AfterBossEncounterFloor && _Other) noexcept = delete;

	void SetDebugBackGround();

protected:
	void Start() override;
	void Update(float _Delta) override;
private:

};

