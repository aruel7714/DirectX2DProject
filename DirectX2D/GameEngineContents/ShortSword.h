#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class ShortSword : public GameEngineActor
{
	friend class Player;
private:
	static ShortSword* WeaponShortSword;
public:
	// constrcuter destructer
	ShortSword();
	~ShortSword();

	// delete Function
	ShortSword(const ShortSword & _Other) = delete;
	ShortSword(ShortSword && _Other) noexcept = delete;
	ShortSword& operator=(const ShortSword & _Other) = delete;
	ShortSword& operator=(ShortSword && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> ShortSwordRenderer;
};

