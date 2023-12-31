#pragma once
#include "GameEngineResources.h"
#include "GameEngineDirectBuffer.h"

enum class StructuredBufferType
{
	NONE,
	SRV_ONLY, // => 쉐이더 리소스로만 사용하겠다.
	UAV_INC, // => 컴퓨트 쉐이더에 넣어서 사용하고 결과값을 적용 받겠다.
};


// 스트럭처드 버퍼는 동적으로 데이터의 크기도 변경할수 있어요.
// 메모리를 아껴야 한다.
// 이녀석도 상수버퍼랑 비슷하게 기본 설계가 달라져야 합니다.

// 설명 :
class GameEngineStructuredBuffer : public GameEngineResources<GameEngineStructuredBuffer>, public GameEngineDirectBuffer
{
public:
	// constrcuter destructer
	GameEngineStructuredBuffer();
	~GameEngineStructuredBuffer();

	// delete Function
	GameEngineStructuredBuffer(const GameEngineStructuredBuffer& _Other) = delete;
	GameEngineStructuredBuffer(GameEngineStructuredBuffer&& _Other) noexcept = delete;
	GameEngineStructuredBuffer& operator=(const GameEngineStructuredBuffer& _Other) = delete;
	GameEngineStructuredBuffer& operator=(GameEngineStructuredBuffer&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineStructuredBuffer> Find(int _Byte)
	{
		if (false == StructuredBufferRes.contains(_Byte))
		{
			return nullptr;
		}

		return StructuredBufferRes[_Byte];
	}

	static std::shared_ptr<GameEngineStructuredBuffer> CreateAndFind(int _Byte, std::string_view _Name, D3D11_SHADER_BUFFER_DESC _BufferDesc)
	{
		std::shared_ptr<GameEngineStructuredBuffer> FindBuffer = Find(_Byte);

		if (nullptr != FindBuffer)
		{
			return FindBuffer;
		}

		std::shared_ptr<GameEngineStructuredBuffer> NewBuffer = CreateRes();
		NewBuffer->DataSize = _Byte;
		return NewBuffer;
	}

	void CreateResize(int _Byte, int _Count, StructuredBufferType _Type);

	void Release();

protected:


private:
	ID3D11ShaderResourceView* SRV = nullptr; // 쉐이더에 세팅해줄수 있는 권한이다.
	unsigned int DataSize = 0;
	unsigned int DataCount = 0;
	StructuredBufferType Type = StructuredBufferType::NONE;

	// 
	//                         전체크기가 x
	//                        40바이트크기의 10개 버퍼
	//                        40바이트만 의미한다.
	static std::map<int, std::shared_ptr < GameEngineStructuredBuffer>> StructuredBufferRes;

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);
};

