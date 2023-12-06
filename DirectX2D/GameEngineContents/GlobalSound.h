#pragma once

// Ό³Έν : 
class GlobalSound
{
public:
	// constrcuter destructer
	GlobalSound();
	~GlobalSound();

	// delete Function
	GlobalSound(const GlobalSound & _Other) = delete;
	GlobalSound(GlobalSound && _Other) noexcept = delete;
	GlobalSound& operator=(const GlobalSound & _Other) = delete;
	GlobalSound& operator=(GlobalSound && _Other) noexcept = delete;

	static GameEngineSoundPlayer Bgm;

protected:

private:

};

