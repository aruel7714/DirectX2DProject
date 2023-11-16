#pragma once

// Ό³Έν : 
class BelialLeftHand
{
public:
	// constrcuter destructer
	BelialLeftHand();
	~BelialLeftHand();

	// delete Function
	BelialLeftHand(const BelialLeftHand & _Other) = delete;
	BelialLeftHand(BelialLeftHand && _Other) noexcept = delete;
	BelialLeftHand& operator=(const BelialLeftHand & _Other) = delete;
	BelialLeftHand& operator=(BelialLeftHand && _Other) noexcept = delete;

protected:

private:

};

