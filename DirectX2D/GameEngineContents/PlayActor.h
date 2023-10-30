#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class PlayActor : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayActor();
	~PlayActor();

	// delete Function
	PlayActor(const PlayActor& _Other) = delete;
	PlayActor(PlayActor&& _Other) noexcept = delete;
	PlayActor& operator=(const PlayActor& _Other) = delete;
	PlayActor& operator=(PlayActor&& _Other) noexcept = delete;



	void Gravity(float _Delta);

	void GravityState(float _Delta, float4 _CheckPos, float4 _CheckScale);

	void SetGravityForce(float4 _GravityForce)
	{
		GravityForce = _GravityForce;
	}

	void SetGravityForceY(float _GravityForceY)
	{
		GravityForce.Y = _GravityForceY;
	}

	void GravityForceReset()
	{
		GravityForce = float4::ZERO;
	}

protected:
	float4 GravityForce = float4::ZERO;

	bool CheckBlue = false;
	bool PassBlue = true;

	float JumpPower = 900.0f;

private:

	float GravityPower = 2000.0f;

	float4 ColorPosition = Transform.GetWorldPosition();

};

