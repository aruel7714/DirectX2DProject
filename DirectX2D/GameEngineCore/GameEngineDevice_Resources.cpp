#include "PreCompile.h"
#include "GameEngineDevice.h"

#include "GameEngineVertex.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineShader.h"
#include "GameEngineVertexShader.h"

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
			GameEngineVertexShader::Load(Files[i].GetStringPath(), "ColorShader_VS");

			// GameEngineShader::AutoCompile();
		}
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

		GameEngineVertex2D BaseVertexs[4];

		BaseVertexs[0] = { { -0.5f, -0.5f, -0.5f, 1.0f } };
		BaseVertexs[1] = { { 0.5f, -0.5f, -0.5f, 1.0f } };
		BaseVertexs[2] = { { 0.5f, 0.5f, -0.5f, 1.0f } };
		BaseVertexs[3] = { { -0.5f, 0.5f, -0.5f, 1.0f } };

		GameEngineVertexBuffer::Create("Rect", Vertex);
	}
}