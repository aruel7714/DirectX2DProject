#include "PreCompile.h"
#include "GameEngineSpriteRenderer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineConstantBuffer.h"

void GameEngineFrameAnimation::EventCall(int _Frame)
{
	if (true == FrameEventFunction.contains(Index[_Frame]))
	{
		FrameEventFunction[Index[_Frame]](Parent);
	}
}

void GameEngineFrameAnimation::Reset()
{
	CurTime = 0.0f;
	CurIndex = 0;
	IsEnd = false;
	EventCheck = true;
}

SpriteData GameEngineFrameAnimation::Update(float _DeltaTime)
{
	if (true == Parent->IsPause)
	{
		return Sprite->GetSpriteData(Index[CurIndex]);
	}

	if (true == Loop)
	{
		IsEnd = false;
	}

	if (true == EventCheck && false == IsEnd)
	{
		EventCall(CurIndex);
		EventCheck = false;
	}


	CurTime += _DeltaTime;

	//if (Inter <= CurTime)
	if (Inter[CurIndex] <= CurTime)
	{
		CurTime -= Inter[CurIndex];
		++CurIndex;

		//if (nullptr != FrameChangeFunction)
		//{
		//	SpriteData Data = Sprite->GetSpriteData(Index[CurIndex]);
		//	FrameChangeFunction(Data, CurIndex);
		//}

		EventCheck = true;
		//CurTime -= Inter;

		//if (CurIndex > End - Start)
		if (CurIndex > InterIndex)
		{
			if (nullptr != EndEvent && false == IsEnd)
			{
				EndEvent(Parent);
			}

			IsEnd = true;

			if (true == Loop)
			{
				CurIndex = 0;
			}
			else
			{
				--CurIndex;
			}
		}

		if (nullptr != FrameChangeFunction)
		{
			SpriteData Data = Sprite->GetSpriteData(Index[CurIndex]);
			FrameChangeFunction(Data, CurIndex);
		}
	}

	return Sprite->GetSpriteData(Index[CurIndex]);
}

GameEngineSpriteRenderer::GameEngineSpriteRenderer()
{
	//Sampler = GameEngineSampler::Find("LINEAR");
}

GameEngineSpriteRenderer::~GameEngineSpriteRenderer()
{
}

void GameEngineSpriteRenderer::Start()
{
	GameEngineRenderer::Start();

	//DataTransform = &ImageTransform;

	ImageTransform.SetParent(Transform);

	GameEngineRenderer::SetMesh("Rect");
	GameEngineRenderer::SetMaterial("2DTexture");

	//const TransformData& Data = ImageTransform.GetConstTransformDataRef();
	//GetShaderResHelper().SetConstantBufferLink("TransformData", Data);

	//GetShaderResHelper().SetConstantBufferLink("SpriteData", CurSprite.SpritePivot);
	////ShaderResHelper.SetTexture("DiffuseTex", "NSet.Png");
	//GetShaderResHelper().SetConstantBufferLink("SpriteRendererInfo", SpriteRendererInfoValue);

	SetSprite("NSet.Png");

	//std::shared_ptr<GameEngineConstantBuffer> Buffer = GameEngineConstantBuffer::CreateAndFind(sizeof(float4), "SpriteData");
	//if (nullptr != Buffer)
	//{
	//	Buffer->ChangeData(CurSprite.SpritePivot);
	//	Buffer->Setting(1);
	//}
	// CurSprite.Texture->PSSetting(0);


	//Sampler = GameEngineSampler::Find("LINEAR");

	// CreateChild<GameEngineComponent>(0);

	// CreateChild();

}

// Update Order에 영향을 받는다.
void GameEngineSpriteRenderer::Update(float _Delta)
{
	if (nullptr != CurFrameAnimations)
	{
		Sprite = CurFrameAnimations->Sprite;
		CurSprite = CurFrameAnimations->Update(_Delta);
	}

	if (true == IsImageSize)
	{
		float4 Scale = float4(CurSprite.GetScale());
		Scale.Z = 1.0f;
		Scale.W = 0.0f;
		//Transform.SetLocalScale(Scale * AutoScaleRatio);
		SetImageScale(Scale * AutoScaleRatio);
	}

	RenderBaseInfoValue.RenderScreenScale = CurSprite.GetScale();
}

void GameEngineSpriteRenderer::SetImageScale(const float4& _Scale)
{
	ImageTransform.SetLocalScale(_Scale);
}

void GameEngineSpriteRenderer::AddImageScale(const float4& _Scale)
{
	ImageTransform.AddLocalScale(_Scale);
}

void GameEngineSpriteRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	float4 ParentScale = Transform.GetLocalScale();
	float4 Scale = ImageTransform.GetLocalScale();

	float4 CalPivot = Pivot;
	CalPivot.X -= 0.5f;
	CalPivot.Y -= 0.5f;

	float4 PivotPos;
	PivotPos.X = Scale.X * CalPivot.X;
	PivotPos.Y = Scale.Y * CalPivot.Y;

	ImageTransform.SetLocalPosition(PivotPos);

	ImageTransform.TransformUpdate();
	ImageTransform.CalculationViewAndProjection(Transform.GetConstTransformDataRef());

	// 랜더러는 뭐든지 그릴수 있어 니가 세팅만 잘해주면

	//GetShaderResHelper().SetTexture("DiffuseTex", CurSprite.Texture);
	GetShaderResHelper().SetTexture("DiffuseTex", CurSprite.Texture, IsUserSampler);

	GameEngineRenderer::Render(_Camera, _Delta);

	// 부모쪽에서 대부분의 일은 해주고
	//GameEngineRenderer::ResSetting();

	// 용도에 의해서
	// 여기에서 세팅되는것이 순서상 여기가 맞아.
	//std::shared_ptr<GameEngineTexture> TestTexture = GameEngineTexture::Find("nset.png");
	//if (nullptr == TestTexture)
	//{
	//	MsgBoxAssert("존재하지 않는 텍스처를 사용하려고 했습니다.");
	//}
	//TestTexture->PSSetting(0);

	//std::shared_ptr<GameEngineConstantBuffer> Buffer = GameEngineConstantBuffer::CreateAndFind(sizeof(float4), "SpriteData", ShaderType::Vertex);
	//std::shared_ptr<GameEngineConstantBuffer> Buffer = GameEngineConstantBuffer::CreateAndFind(sizeof(float4), "SpriteData");

	//if (nullptr != Buffer)
	//{
	//	Buffer->ChangeData(CurSprite.SpritePivot);
	//	Buffer->Setting(1);
	//}


	//CurSprite.Texture->PSSetting(0);

	// std::shared_ptr<GameEngineSampler> Sampler = GameEngineSampler::Find("EngineBaseSampler");
	//if (nullptr == Sampler)
	//{
	//	MsgBoxAssert("존재하지 않는 샘플러를 사용하려고 했습니다.");
	//}
	//Sampler->PSSetting(0);


	// 내꺼 쪼금더 넣고 

	//GameEngineRenderer::Draw();
}

void GameEngineSpriteRenderer::SetSprite(std::string_view _Name, unsigned int index /*= 0*/)
{
	CurFrameAnimations = nullptr;

	Sprite = GameEngineSprite::Find(_Name);

	if (nullptr == Sprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트를 사용하려고 했습니다.");
	}

	CurSprite = Sprite->GetSpriteData(index);
	//Transform.SetLocalScale(CurSprite.GetScale() * AutoScaleRatio);
	float4 Check = CurSprite.GetScale();
	SetImageScale(CurSprite.GetScale() * AutoScaleRatio);
}

//void GameEngineSpriteRenderer::ChangeCurSprite(int _Index)
//{
//	CurFrameAnimations = nullptr;
//
//	if (nullptr == Sprite)
//	{
//		MsgBoxAssert("존재하지 않는 스프라이트를 사용하려고 했습니다.");
//	}
//
//	CurSprite = Sprite->GetSpriteData(_Index);
//}

void GameEngineSpriteRenderer::ChangeCurSprite(int _Index /*= 0*/)
{
	CurFrameAnimations = nullptr;

	if (nullptr == Sprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트를 사용하려고 했습니다.");
	}

	CurSprite = Sprite->GetSpriteData(_Index);
}

void GameEngineSpriteRenderer::CreateAnimation(
	std::string_view _AnimationName,
	std::string_view _SpriteName,
	float _Inter /*= 0.1f*/,
	unsigned int _Start /*= -1*/,
	unsigned int _End /*= -1*/,
	bool _Loop /*= true*/
)
{
	std::string SpriteName = GameEngineString::ToUpperReturn(_SpriteName);

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find(SpriteName);
	if (nullptr == Sprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트로 애니메이션을 만들려고 했습니다.");
		return;
	}

	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);
	if (true == FrameAnimations.contains(UpperName))
	{
		MsgBoxAssert("이미 존재하는 애니메이션을 또 만들려고 했습니다.");
		return;
	}

	std::shared_ptr<GameEngineFrameAnimation> NewAnimation = std::make_shared<GameEngineFrameAnimation>();
	FrameAnimations[UpperName] = NewAnimation;
	NewAnimation->AnimationName = _AnimationName;
	NewAnimation->SpriteName = _SpriteName;
	NewAnimation->Sprite = Sprite;
	NewAnimation->Loop = _Loop;
	//NewAnimation->Inter = _Inter;
	NewAnimation->Parent = this;

	if (_Start != -1)
	{
		NewAnimation->Start = _Start;
	}
	else
	{
		NewAnimation->Start = 0;
	}

	if (_End != -1)
	{
		NewAnimation->End = _End;
	}
	else
	{
		NewAnimation->End = Sprite->GetSpriteCount() - 1;
	}

	int Plus = 1;

	if (NewAnimation->Start > NewAnimation->End)
	{
		for (
			int i = NewAnimation->Start;
			i >= NewAnimation->End;
			i--
			)
		{
			NewAnimation->Index.push_back(i);
		}

		NewAnimation->InterIndex = NewAnimation->Start - NewAnimation->End;
	}
	else
	{
		for (int i = NewAnimation->Start; i <= NewAnimation->End; i++)
		{
			NewAnimation->Index.push_back(i);
		}

		NewAnimation->InterIndex = NewAnimation->End - NewAnimation->Start;
	}

	NewAnimation->Inter.resize(NewAnimation->Index.size());
	for (size_t i = 0; i < NewAnimation->Index.size(); i++)
	{
		NewAnimation->Inter[i] = _Inter;
	}

	NewAnimation->CurIndex = 0;

}

void GameEngineSpriteRenderer::ChangeAnimation(std::string_view _AnimationName, bool _Force /*= false*/, unsigned int _FrameIndex /*= 0*/)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<GameEngineFrameAnimation>>::iterator FindIter
		= FrameAnimations.find(UpperName);

	if (FindIter == FrameAnimations.end())
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지하려고 했습니다.");
		return;
	}

	if (_Force == false && FindIter->second == CurFrameAnimations)
	{
		return;
	}

	CurFrameAnimations = FrameAnimations[UpperName];
	CurFrameAnimations->Reset();
	CurFrameAnimations->CurIndex = _FrameIndex;
	CurSprite = CurFrameAnimations->Sprite->GetSpriteData(CurFrameAnimations->CurIndex);

	if (nullptr != CurFrameAnimations->FrameChangeFunction)
	{
		SpriteData Data = Sprite->GetSpriteData(CurFrameAnimations->Index[CurFrameAnimations->CurIndex]);
		CurFrameAnimations->FrameChangeFunction(Data, CurFrameAnimations->CurIndex);
	}
}

void GameEngineSpriteRenderer::AutoSpriteSizeOn()
{
	IsImageSize = true;
}

void GameEngineSpriteRenderer::AutoSpriteSizeOff()
{
	IsImageSize = false;
}

//void GameEngineSpriteRenderer::SetSamplerState(SamplerOption _Option)
//{
//	switch (_Option)
//	{
//	case SamplerOption::LINEAR:
//		Sampler = GameEngineSampler::Find("LINEAR");
//		break;
//	case SamplerOption::POINT:
//		Sampler = GameEngineSampler::Find("POINT");
//		break;
//	default:
//		break;
//	}
//}

void GameEngineSpriteRenderer::SetFrameEvent(std::string_view _AnimationName, int _Frame, std::function<void(GameEngineSpriteRenderer*)> _Function)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<GameEngineFrameAnimation>>::iterator FindIter = FrameAnimations.find(UpperName);

	std::shared_ptr<GameEngineFrameAnimation> Animation = FindIter->second;

	if (nullptr == Animation)
	{
		MsgBoxAssert("존재하지 않는 애니메이션에 이벤트를 만들려고 했습니다.");
	}

	Animation->FrameEventFunction[_Frame] = _Function;
}

void GameEngineSpriteRenderer::SetStartEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<GameEngineFrameAnimation>>::iterator FindIter = FrameAnimations.find(UpperName);

	std::shared_ptr<GameEngineFrameAnimation> Animation = FindIter->second;

	if (nullptr == Animation)
	{
		MsgBoxAssert("존재하지 않는 애니메이션에 이벤트를 만들려고 했습니다.");
	}

	Animation->FrameEventFunction[Animation->Index[0]] = _Function;
}

void GameEngineSpriteRenderer::SetEndEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<GameEngineFrameAnimation>>::iterator FindIter = FrameAnimations.find(UpperName);

	std::shared_ptr<GameEngineFrameAnimation> Animation = FindIter->second;

	if (nullptr == Animation)
	{
		MsgBoxAssert("존재하지 않는 애니메이션에 이벤트를 만들려고 했습니다.");
	}

	Animation->EndEvent = _Function;
}

void GameEngineSpriteRenderer::SetFrameChangeFunctionAll(std::function<void(const SpriteData& CurSprite, int _SpriteIndex)> _Function)
{
	for (std::pair<const std::string, std::shared_ptr<GameEngineFrameAnimation>>& _Pair : FrameAnimations)
	{
		_Pair.second->FrameChangeFunction = _Function;
	}
}

void GameEngineSpriteRenderer::SetFrameChangeFunction(std::string_view _AnimationName, std::function<void(const SpriteData& CurSprite, int _SpriteIndex)> _Function)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<GameEngineFrameAnimation>>::iterator FindIter = FrameAnimations.find(UpperName);

	std::shared_ptr<GameEngineFrameAnimation> Animation = FindIter->second;

	if (nullptr == Animation)
	{
		MsgBoxAssert("존재하지 않는 애니메이션에 이벤트를 만들려고 했습니다.");
	}

	Animation->FrameChangeFunction = _Function;
}

void GameEngineSpriteRenderer::AnimationPauseSwitch()
{
	IsPause = !IsPause;
}

void GameEngineSpriteRenderer::AnimationPauseOn()
{
	IsPause = true;
}

void GameEngineSpriteRenderer::AnimationPauseOff()
{
	IsPause = false;
}

void GameEngineSpriteRenderer::SetPivotType(PivotType _Type)
{
	switch (_Type)
	{
	case PivotType::Center:
		Pivot = { 0.5f, 0.5f };
		break;
	case PivotType::Top:
		Pivot = { 0.5f, 0.0f };
		break;
	case PivotType::RightUp:
		Pivot = { 0.0f, 0.0f };
		break;
	case PivotType::Right:
		Pivot = { 0.0f, 0.5f };
		break;
	case PivotType::RightBottom:
		Pivot = { 0.0f, 1.0f };
		break;
	case PivotType::Bottom:
		Pivot = { 0.5f, 1.0f };
		break;
	case PivotType::LeftBottom:
		Pivot = { 1.0f, 1.0f };
		break;
	case PivotType::Left:
		Pivot = { 1.0f, 0.5f };
		break;
	case PivotType::LeftTop:
		Pivot = { 1.0f, 0.0f };
		break;
	default:
		break;
	}
}

void GameEngineSpriteRenderer::SetMaterialEvent(std::string_view _Name, int _Index)
{
	const TransformData& Data = ImageTransform.GetConstTransformDataRef();
	GetShaderResHelper().SetConstantBufferLink("TransformData", Data);
	GetShaderResHelper().SetConstantBufferLink("SpriteData", CurSprite.SpritePivot);
	// ShaderResHelper.SetTexture("DiffuseTex", "NSet.Png");
	GetShaderResHelper().SetConstantBufferLink("SpriteRendererInfo", SpriteRendererInfoValue);
	GetShaderResHelper().SetConstantBufferLink("ColorData", ColorDataValue);

	SetSprite("NSet.png");
}

//void GameEngineSpriteRenderer::SetMaskTexture(std::string_view _Texture)
//{
//	// 바뀌기 전에 
//	// 스프라이트 이름이나 애니메이션이나 이런것들을 저장했다가
//	
//	// 이녀석한테 있는
//	GameEngineRenderer::SetMaterial("2DTextureMask");
//
//	// 다시 세팅해주면 
//	// SetSprite("NSet.png");
//
//	GetShaderResHelper().SetTexture("MaskTex", _Texture);
//}

void GameEngineSpriteRenderer::SetMaskTexture(std::string_view _Texture, MaskMode _Mask)
{
	//std::shared_ptr<GameEngineFrameAnimation> TempCurFrameAnimation = CurFrameAnimations;
	//std::shared_ptr<GameEngineSprite> TempSprite = Sprite;
	//SpriteData TempCurSprite = CurSprite;

	//GameEngineRenderer::SetMaterial("2DTextureMask");

	//if (CurFrameAnimations != TempCurFrameAnimation)
	//{
	//	CurFrameAnimations = TempCurFrameAnimation;
	//}

	//if (Sprite != TempSprite)
	//{
	//	Sprite = TempSprite;
	//	CurSprite = TempCurSprite;
	//}

	RenderBaseInfoValue.IsMask = 1;
	RenderBaseInfoValue.MaskMode = static_cast<int>(_Mask);
	GetShaderResHelper().SetTexture("MaskTex", _Texture);
	std::shared_ptr<GameEngineTexture> Ptr = GameEngineTexture::Find(_Texture);
	RenderBaseInfoValue.MaskScreeneScale = Ptr->GetScale();
}

void GameEngineSpriteRenderer::SetText(const std::string& _Font, const std::string& _Text, float _Scale /*= 20.0f*/, float4 Color /*= float4::RED*/, FW1_TEXT_FLAG Flag /*= FW1_LEFT*/)
{
	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(0);
	Unit->SetText(_Font, _Text, _Scale, Color, Flag);
}

void GameEngineSpriteRenderer::SetTextColor(const float4& _Color /*= float4::RED*/, unsigned int _Index /*= 0*/)
{
	std::weak_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(_Index);
	Unit.lock()->SetTextColor(_Color);
}

void GameEngineSpriteRenderer::SetTextAlpha(float _AlphaValue /*= 1.0f*/, unsigned int _Index /*= 0*/)
{
	std::weak_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(_Index);
	Unit.lock()->SetTextAlpha(_AlphaValue);
}

void GameEngineSpriteRenderer::SetSampler(std::string_view _Name)
{
	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(0);
	Unit->ShaderResHelper.SetSampler("DiffuseTexSampler", _Name);
	IsUserSampler = false;
}