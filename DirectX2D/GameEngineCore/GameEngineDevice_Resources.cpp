#include "PreCompile.h"
#include "GameEngineDevice.h"
#include "GameEngineTransform.h"

#include "GameEngineVertex.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineShader.h"
#include "GameEngineRasterizer.h"
#include "GameEngineSampler.h"
#include "GameEngineVertexShader.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSprite.h"

void GameEngineDevice::ResourcesInit()
{
	// 엔진수준에서 지원해주는 가장 기초적인 리소스들은 여기에서 만들어질 겁니다.
	// 기본 매쉬
	// 기본 텍스처
	// 기본 쉐이더
	// 여기에서 자기 텍스처 로드하지 마세요.

	// 아래있는 이녀석들이 리소스라면

		// 로컬과 월드의 차이입니다.
		// 사각형을 만들기 위해서 점을 4개 만들었습니다.
		// 바로 월드로 바로만든것
		// 로컬이 존재하지 않는다.

		// 로컬상태
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineCoreShader");
		Dir.MoveChild("GameEngineCoreShader");
		std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".fx" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			//GameEngineVertexShader::Load(Files[i].GetStringPath(), "ColorShader_VS");

			// GameEngineShader::AutoCompile();

			GameEngineFile& File = Files[i];
			GameEngineShader::AutoCompile(File);
		}
	}

	{
		// 엔진용 쉐이더를 전부다 전부다 로드하는 코드를 친다.
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("GameEngineResources");
		Dir.MoveChild("Textrure");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("NSet.png");
	}

	{
		std::vector<GameEngineVertex2D> Vertex;
		Vertex.resize(4 * 6);

		GameEngineVertex2D BaseVertexs[4];

		BaseVertexs[0] = { { -0.5f, -0.5f, -0.5f, 1.0f } };
		BaseVertexs[1] = { { 0.5f, -0.5f, -0.5f, 1.0f } };
		BaseVertexs[2] = { { 0.5f, 0.5f, -0.5f, 1.0f } };
		BaseVertexs[3] = { { -0.5f, 0.5f, -0.5f, 1.0f } };

		// 앞면
		Vertex[0] = BaseVertexs[0];
		Vertex[1] = BaseVertexs[1];
		Vertex[2] = BaseVertexs[2];
		Vertex[3] = BaseVertexs[3];

		// 뒷면
		Vertex[4].POSITION = float4::VectorRotationToDegX(BaseVertexs[0].POSITION, 180.0f);
		Vertex[5].POSITION = float4::VectorRotationToDegX(BaseVertexs[1].POSITION, 180.0f);
		Vertex[6].POSITION = float4::VectorRotationToDegX(BaseVertexs[2].POSITION, 180.0f);
		Vertex[7].POSITION = float4::VectorRotationToDegX(BaseVertexs[3].POSITION, 180.0f);

		// 왼쪽이나 오른쪽
		Vertex[8].POSITION = float4::VectorRotationToDegY(BaseVertexs[0].POSITION, 90.0f);
		Vertex[9].POSITION = float4::VectorRotationToDegY(BaseVertexs[1].POSITION, 90.0f);
		Vertex[10].POSITION = float4::VectorRotationToDegY(BaseVertexs[2].POSITION, 90.0f);
		Vertex[11].POSITION = float4::VectorRotationToDegY(BaseVertexs[3].POSITION, 90.0f);

		// 왼쪽이나 오른쪽
		Vertex[12].POSITION = float4::VectorRotationToDegY(BaseVertexs[0].POSITION, -90.0f);
		Vertex[13].POSITION = float4::VectorRotationToDegY(BaseVertexs[1].POSITION, -90.0f);
		Vertex[14].POSITION = float4::VectorRotationToDegY(BaseVertexs[2].POSITION, -90.0f);
		Vertex[15].POSITION = float4::VectorRotationToDegY(BaseVertexs[3].POSITION, -90.0f);

		// 위거나 아래
		Vertex[16].POSITION = float4::VectorRotationToDegX(BaseVertexs[0].POSITION, 90.0f);
		Vertex[17].POSITION = float4::VectorRotationToDegX(BaseVertexs[1].POSITION, 90.0f);
		Vertex[18].POSITION = float4::VectorRotationToDegX(BaseVertexs[2].POSITION, 90.0f);
		Vertex[19].POSITION = float4::VectorRotationToDegX(BaseVertexs[3].POSITION, 90.0f);

		Vertex[20].POSITION = float4::VectorRotationToDegX(BaseVertexs[0].POSITION, -90.0f);
		Vertex[21].POSITION = float4::VectorRotationToDegX(BaseVertexs[1].POSITION, -90.0f);
		Vertex[22].POSITION = float4::VectorRotationToDegX(BaseVertexs[2].POSITION, -90.0f);
		Vertex[23].POSITION = float4::VectorRotationToDegX(BaseVertexs[3].POSITION, -90.0f);

		GameEngineVertexBuffer::Create("Box", Vertex);
	}

	{
		std::vector<GameEngineVertex2D> Vertex;
		Vertex.resize(4);

		//GameEngineVertex2D BaseVertexs[4];

		//BaseVertexs[0] = { { -0.5f, -0.5f, -0.5f, 1.0f } };
		//BaseVertexs[1] = { { 0.5f, -0.5f, -0.5f, 1.0f } };
		//BaseVertexs[2] = { { 0.5f, 0.5f, -0.5f, 1.0f } };
		//BaseVertexs[3] = { { -0.5f, 0.5f, -0.5f, 1.0f } };

		// 이미지를 자르려면 TEXCOORD값이 바뀌어야 하는데.
		Vertex[0] = { { -0.5f, 0.5f, 0.0f, 1.0f }, {0.0f, 0.0f} };
		Vertex[1] = { { 0.5f, 0.5f, 0.0f, 1.0f } , {1.0f, 0.0f} };
		Vertex[2] = { { 0.5f, -0.5f, 0.0f, 1.0f }  , {1.0f, 1.0f} };
		Vertex[3] = { { -0.5f, -0.5f, 0.0f, 1.0f } , {0.0f, 1.0f} };

		GameEngineVertexBuffer::Create("Rect", Vertex);

		std::vector<unsigned int> Index =
		{
			0, 1, 2,
			0, 2, 3
		};
		
		GameEngineIndexBuffer::Create("Rect", Index);
	}

	{
		std::vector<GameEngineVertex2D> Vertex;
		Vertex.resize(4);

		Vertex[0] = { { -1.0f, -1.0f, 0.0f, 1.0f }, {0.0f, 0.0f} };
		Vertex[1] = { { 1.0f, -1.0f, 0.0f, 1.0f },  {1.0f, 0.0f} };
		Vertex[2] = { { 1.0f, 1.0f, 0.0f, 1.0f },   {1.0f, 1.0f} };
		Vertex[3] = { { -1.0f, 1.0f, 0.0f, 1.0f },  {0.0f, 1.0f} };

		GameEngineVertexBuffer::Create("FullRect", Vertex);

		std::vector<unsigned int> Index =
		{
			0, 1, 2,
			0, 2, 3
		};

		GameEngineIndexBuffer::Create("FullRect", Index);
	}

	// 나중에 사라질거임.
	{
		// 약간위험할수 있다.
		// 그래픽카드에서의 바이트 패딩 규칙과
		// sizeof(TransformData) 바이트패딩 규칙이
		// 달라서 그림이 다르다고 인식할수 있다.
		// 주의해야 한다.
		GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData", ShaderType::Vertex, 0);
	}

	{

		//D3D11_FILL_MODE FillMode;
		// 랜더링 할때 채우기 모드를 결정한다.

		// 외적했는데 z방향이 어디냐?
		// D3D11_CULL_NONE => 방향이 어디든 건져낸다.
		// D3D11_CULL_BACK => z가 앞쪽인 픽셀들은 안건져 낸다.
		// D3D11_CULL_FRONT => z가 뒤쪽인 픽셀들은 안건져 낸다.
		// 
		// 0, 1, 2,
		// 0, 2, 3
		// 인덱스 버퍼의 그리는 순서와 연관이 크다.

		// 이녀석은 인덱스 버퍼

		//D3D11_CULL_MODE CullMode;
		//BOOL FrontCounterClockwise;
		//INT DepthBias;
		//FLOAT DepthBiasClamp;
		//FLOAT SlopeScaledDepthBias;
		//BOOL DepthClipEnable;
		//BOOL ScissorEnable;
		//BOOL MultisampleEnable;
		//BOOL AntialiasedLineEnable;

		D3D11_RASTERIZER_DESC Desc = {};
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		// Desc.DepthClipEnable = TRUE;
		std::shared_ptr<GameEngineRasterizer> Rasterizer = GameEngineRasterizer::Create("EngineRasterizer", Desc);
	}

	{

		D3D11_SAMPLER_DESC Desc = {};
		// 일반적인 보간형식 <= 뭉개진다.
		// D3D11_FILTER_MIN_MAG_MIP_
		// 그 밉맵에서 색상가져올때 다 뭉개는 방식으로 가져오겠다.
		Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		std::shared_ptr<GameEngineSampler> Rasterizer = GameEngineSampler::Create("LINEAR", Desc);
	}


	{

		D3D11_SAMPLER_DESC Desc = {};
		// 일반적인 보간형식 <= 뭉개진다.
		// D3D11_FILTER_MIN_MAG_MIP_
		// 그 밉맵에서 색상가져올때 다 뭉개는 방식으로 가져오겠다.
		Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		std::shared_ptr<GameEngineSampler> Rasterizer = GameEngineSampler::Create("POINT", Desc);
	}
}