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
	PlayActor(const PlayActor & _Other) = delete;
	PlayActor(PlayActor && _Other) noexcept = delete;
	PlayActor& operator=(const PlayActor & _Other) = delete;
	PlayActor& operator=(PlayActor && _Other) noexcept = delete;



	void Gravity(float _Delta);

	void GravityState(float _Delta, float4 _CheckPos);

	void SetGravityForceY(float _GravityForceY)
	{
		GravityForce.Y = _GravityForceY;
	}

	void GravityForceReset()
	{
		GravityForce = float4::ZERO;
	}

protected:
	

private:
	float4 GravityForce = float4::ZERO;

	float GravityPower = 1000.0f;

	float4 ColorPosition = Transform.GetWorldPosition();
};

