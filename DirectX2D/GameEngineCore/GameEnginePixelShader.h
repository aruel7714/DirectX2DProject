#pragma once
#include "GameEngineShader.h"
#include "GameEngineResources.h"

// ���� : 
class GameEnginePixelShader : public GameEngineResources<GameEnginePixelShader>, public GameEngineShader
{
	friend class GameEngineInputLayOut;
public:
	// constrcuter destructer
	GameEnginePixelShader();
	~GameEnginePixelShader();

	// delete Function
	GameEnginePixelShader(const GameEnginePixelShader & _Other) = delete;
	GameEnginePixelShader(GameEnginePixelShader && _Other) noexcept = delete;
	GameEnginePixelShader& operator=(const GameEnginePixelShader & _Other) = delete;
	GameEnginePixelShader& operator=(GameEnginePixelShader && _Other) noexcept = delete;

	static std::shared_ptr<GameEnginePixelShader> Load(const std::string_view& _Path, const std::string_view& _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0)
	{
		return Load(_Path, _EntryPoint, _EntryPoint, _VersionHight, _VersionLow);
	}
	static std::shared_ptr<GameEnginePixelShader> Load(const std::string_view& _Path, const std::string_view& _Name, const std::string_view& _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0)
	{
		std::shared_ptr<GameEnginePixelShader> Res = GameEnginePixelShader::CreateRes(_Name);
		Res->ShaderLoad(_Path, _EntryPoint, _VersionHight, _VersionLow);
		return Res;
	}

	void Setting();

protected:

private:
	std::string EntryName = "";
	ID3D11PixelShader* ShaderPtr = nullptr;

	void ShaderLoad(const std::string_view& _Path, const std::string_view& _EntryPoint, UINT _VersionHIGHT = 5, UINT _VersionLow = 0);

};

