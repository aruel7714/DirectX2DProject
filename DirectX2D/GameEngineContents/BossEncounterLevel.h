#pragma once

// Ό³Έν : 
class BossEncounterLevel
{
public:
	// constrcuter destructer
	BossEncounterLevel();
	~BossEncounterLevel();

	// delete Function
	BossEncounterLevel(const BossEncounterLevel & _Other) = delete;
	BossEncounterLevel(BossEncounterLevel && _Other) noexcept = delete;
	BossEncounterLevel& operator=(const BossEncounterLevel & _Other) = delete;
	BossEncounterLevel& operator=(BossEncounterLevel && _Other) noexcept = delete;

protected:

private:

};

