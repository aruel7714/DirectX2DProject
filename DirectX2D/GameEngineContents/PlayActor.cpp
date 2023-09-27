#include "PreCompile.h"
#include "PlayActor.h"


PlayActor::PlayActor()
{
}

PlayActor::~PlayActor()
{
}

void PlayActor::Gravity(float _Delta)
{
	GravityForce.Y -= GravityPower * _Delta;
	Transform.AddLocalPosition(GravityForce * _Delta);

	
}