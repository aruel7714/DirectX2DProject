#pragma once
#include "BackGround.h"

// Ό³Έν : 
class BeforeBossEncounterFloor : public BackGround
{
public:
	// constrcuter destructer
	BeforeBossEncounterFloor();
	~BeforeBossEncounterFloor();

	// delete Function
	BeforeBossEncounterFloor(const BeforeBossEncounterFloor & _Other) = delete;
	BeforeBossEncounterFloor(BeforeBossEncounterFloor && _Other) noexcept = delete;
	BeforeBossEncounterFloor& operator=(const BeforeBossEncounterFloor & _Other) = delete;
	BeforeBossEncounterFloor& operator=(BeforeBossEncounterFloor && _Other) noexcept = delete;

	void SetDebugBackGround();

protected:
	void Start() override;
	void Update(float _Delta) override;
private:

};

