#pragma once

// Ό³Έν : 
class BossSpawnText
{
public:
	// constrcuter destructer
	BossSpawnText();
	~BossSpawnText();

	// delete Function
	BossSpawnText(const BossSpawnText & _Other) = delete;
	BossSpawnText(BossSpawnText && _Other) noexcept = delete;
	BossSpawnText& operator=(const BossSpawnText & _Other) = delete;
	BossSpawnText& operator=(BossSpawnText && _Other) noexcept = delete;

protected:

private:

};

