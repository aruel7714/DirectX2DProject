#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineVertex.h"

#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineInputLayOut.h"
#include "GameEngineVertexShader.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineBlend.h"
#include "GameEngineConstantBuffer.h"

GameEngineRenderer::GameEngineRenderer()
{
	RenderBaseInfoValue.ScreenSize = GameEngineCore::MainWindow.GetScale();
}

GameEngineRenderer::~GameEngineRenderer()
{
}

// 카메라 내부에서의 순서 변경
void GameEngineRenderer::SetRenderOrder(int _Order)
{

	if (nullptr == Camera)
	{
		MsgBoxAssert("카메라가 존재하지 않는 랜더러 입니다. 카메라부터 지정해주세요.");
		return;
	}

	Camera->Renderers[GetOrder()].remove(GetDynamic_Cast_This<GameEngineRenderer>());
	GameEngineObject::SetOrder(_Order);
	Camera->Renderers[GetOrder()].push_back(GetDynamic_Cast_This<GameEngineRenderer>());

}

// 날 바라보는 카메라 변경
void GameEngineRenderer::SetCameraOrder(int _Order)
{
	SetViewCameraSelect(_Order);
}

void GameEngineRenderer::Start()
{
	// 메인카메라에 들어갔다.
	//SetViewCameraSelect(0);
	//DataTransform = &Transform;
	SetCameraOrder(ECAMERAORDER::Main);

	//GameEngineActor* Actor = GetActor();

	// 카메라를 찾아서 들어가야 합니다.
	// 카메를 찾으려면? GameEngineLevel
	// Level부터 찾아야해.
	// Level누가 들고 있죠? 나를 들고 있는 Actor가 들고 있어.

	// Level을 만들수 밖에 없습니다.
}

void GameEngineRenderer::SetViewCameraSelect(int _Order)
{
	GameEngineLevel* Level = GetLevel();

	std::shared_ptr<GameEngineCamera> FindCamera = Level->GetCamera(_Order);

	if (nullptr == FindCamera)
	{
		MsgBoxAssert("카메라가 존재하지 않는데 랜더러를 넣으려고 했습니다.");
		return;
	}

	if (nullptr != Camera)
	{
		Camera->Renderers[GetOrder()].remove(GetDynamic_Cast_This<GameEngineRenderer>());
	}

	Camera = FindCamera.get();
	Camera->Renderers[GetOrder()].push_back(GetDynamic_Cast_This<GameEngineRenderer>());
	//ViewInfo[Camera.get()] = _Order;
}

void GameEngineRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	//ResSetting();
	//Draw();

	RenderBaseInfoValue.RendererScreenPos = GetScreenPosition();

	for (size_t i = 0; i < Units.size(); i++)
	{
		Units[i]->ResSetting();
		Units[i]->Draw();
	}
}

void GameEngineRenderer::Update(float _Delta)
{
	RenderBaseInfoValue.DeltaTime = _Delta;
	RenderBaseInfoValue.AccDeltaTime += _Delta;
}


std::shared_ptr<GameEngineRenderUnit> GameEngineRenderer::CreateAndFindRenderUnit(int _Index)
{
	Units.resize(_Index + 1);

	// 있으면
	if (nullptr != Units[_Index])
	{
		//리턴
		return Units[_Index];
	}

	// 없으면 만든다.
	Units[_Index] = std::make_shared<GameEngineRenderUnit>();
	Units[_Index]->SetParentRenderer(this);
	return Units[_Index];
}

void GameEngineRenderer::SetMesh(std::string_view _Name, int _Index /*= 0*/)
{
	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(_Index);
	Unit->SetMesh(_Name);
}

void GameEngineRenderer::SetMaterial(std::string_view _Name, int _Index /*= 0*/)
{
	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(_Index);
	Unit->SetMaterial(_Name);

	if (Unit->ShaderResHelper.IsConstantBuffer("TransformData"))
	{
		Unit->ShaderResHelper.SetConstantBufferLink("TransformData", Transform.GetConstTransformDataRef());
	}

	if (Unit->ShaderResHelper.IsConstantBuffer("RenderBaseInfo"))
	{
		Unit->ShaderResHelper.SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
	}

	SetMaterialEvent(_Name, _Index);
}

GameEngineShaderResHelper& GameEngineRenderer::GetShaderResHelper(int _Index /*= 0*/)
{
	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(_Index);
	return Unit->ShaderResHelper;
}

void GameEngineRenderer::SetMaterialEvent(std::string_view _Name, int _Index)
{

}

float4 GameEngineRenderer::GetScreenPosition()
{
	float4x4 ViewPort;
	float4 ScreenPos = Transform.GetWorldPosition();
	float4 Scale = GameEngineCore::MainWindow.GetScale();
	ViewPort.ViewPort(Scale.X, Scale.Y, 0, 0);
	ScreenPos *= ViewPort.InverseReturn();
	ScreenPos *= Transform.GetConstTransformDataRef().ProjectionMatrix.InverseReturn();
	ScreenPos *= Transform.GetConstTransformDataRef().ViewMatrix.InverseReturn();
	return ScreenPos;
}


//void GameEngineRenderer::ResSetting()
//{
//	Mesh->InputAssembler1();
//	Material->VertexShader();
//	LayOut->Setting();
//	Mesh->InputAssembler2();
//	Material->Rasterizer();
//	Material->PixelShader();
//	Material->Blend();
//
//	ShaderResHelper.AllShaderResourcesSetting();
//
//	// 애는 솔직히 랜더 타겟이 가져가야 합니다.
//	D3D11_VIEWPORT ViewPort = {};
//	ViewPort.Width = GameEngineCore::MainWindow.GetScale().X;
//	ViewPort.Height = GameEngineCore::MainWindow.GetScale().Y;
//	ViewPort.MinDepth = 0.0f;
//	ViewPort.MaxDepth = 1.0f;
//	ViewPort.TopLeftX = 0.0f;
//	ViewPort.TopLeftY = 0.0f;
//	GameEngineCore::GetContext()->RSSetViewports(1, &ViewPort);
//
//	std::shared_ptr<class GameEngineRenderTarget> BackBufferRenderTarget = GameEngineCore::GetBackBufferRenderTarget();
//	if (nullptr != BackBufferRenderTarget)
//	{
//		BackBufferRenderTarget->Setting();
//	}
//
//
//	//	float4x4 WorldViewProjection = Transform.GetWorldViewProjectionMatrix();
//	//	//std::shared_ptr<GameEngineConstantBuffer> Buffer = GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData", _shader);
//	//	//if (nullptr != Buffer)
//	//	//{
//	//	//	const TransformData& Data = DataTransform->GetConstTransformDataRef();
//	//	//	Buffer->ChangeData(Data);
//	//	//	Buffer->Setting(0);
//	//	//}
//
//}

//void GameEngineRenderer::Draw()
//{
//	Mesh->Draw();
//}

//void GameEngineRenderer::SetMesh(std::string_view _Name)
//{
//	Mesh = GameEngineMesh::Find(_Name);
//
//	if (nullptr == Mesh)
//	{
//		MsgBoxAssert("존재하지 않는 매쉬를 세팅하려고 했습니다.");
//	}
//
//	if (nullptr == LayOut && nullptr != Material)
//	{
//		LayOut = std::make_shared<GameEngineInputLayOut>();
//		LayOut->ResCreate(Mesh->GetVertexBuffer(), Material->GetVertexShader());
//	}
//
//}
//
//void GameEngineRenderer::SetMaterial(std::string_view _Name)
//{
//	Material = GameEngineMaterial::Find(_Name);
//
//	ShaderResHelper.ResClear();
//
//	if (nullptr == Material)
//	{
//		MsgBoxAssert("존재하지 않는 매쉬를 세팅하려고 했습니다.");
//	}
//
//	if (nullptr == LayOut && nullptr != Mesh)
//	{
//		LayOut = std::make_shared<GameEngineInputLayOut>();
//		LayOut->ResCreate(Mesh->GetVertexBuffer(), Material->GetVertexShader());
//	}
//
//	// 버텍스 쉐이더와 픽셀쉐이더가 다 들어있는 상태다.
//
//	// 랜더러의 쉐이더 리소스 헬퍼에
//	// 버텍스와 픽셀쉐이더의 리소스정보들을 복사 받습니다.
//	ShaderResHelper.ShaderResCopy(Material->GetVertexShader().get());
//	ShaderResHelper.ShaderResCopy(Material->GetPixelShader().get());
//
//	// 이걸 회사의 약속.
//
//	if (ShaderResHelper.IsConstantBuffer("TransformData"))
//	{
//		const TransformData& Data = Transform.GetConstTransformDataRef();
//		ShaderResHelper.SetConstantBufferLink("TransformData", Data);
//	}
//
//	//	//std::shared_ptr<GameEngineConstantBuffer> Buffer = GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData", _shader);
////	//if (nullptr != Buffer)
////	//{
////	//	const TransformData& Data = DataTransform->GetConstTransformDataRef();
////	//	Buffer->ChangeData(Data);
////	//	Buffer->Setting(0);
////	//}
//
//}

/*void GameEngineRenderer::ResSetting()
{
	{
		float4x4 WorldViewProjection = Transform.GetWorldViewProjectionMatrix();
		// 인풋어셈블러1 버텍스 버퍼 세팅
		std::shared_ptr<GameEngineVertexBuffer> VertexBuffer = GameEngineVertexBuffer::Find("Rect");
		if (nullptr != VertexBuffer)
		{
			VertexBuffer->Setting();
		}

		std::shared_ptr<GameEngineVertexShader> VertexShader = GameEngineVertexShader::Find("TextureShader_VS");

		if (nullptr != VertexShader && nullptr != VertexBuffer && nullptr == LayOut)
		{
			LayOut = std::make_shared<GameEngineInputLayOut>();
			LayOut->ResCreate(VertexBuffer, VertexShader);

			//std::vector<D3D11_INPUT_ELEMENT_DESC> ArrLayOutInfo;

			//{
			//	D3D11_INPUT_ELEMENT_DESC Data;
			//	Data.SemanticName = "POSITION";
			//	// 0바이트부터 시작하는
			//	Data.AlignedByteOffset = 0;
			//	// 16바이트짜리 자료형이야.
			//	Data.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
			//	// 버텍스 데이터용 레이아웃이야.
			//	// 점세팅의 구조를 설명하기 위한 레이아웃이야.
			//	Data.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;

			//	// 지금은 알아도 크게 의미 없음
			//	Data.SemanticIndex = 0;
			//	Data.InputSlot = 0;
			//	Data.InstanceDataStepRate = 0;
			//	ArrLayOutInfo.push_back(Data);
			//}

			//{
			//	D3D11_INPUT_ELEMENT_DESC Data;
			//	Data.SemanticName = "COLOR";
			//	// 0바이트부터 시작하는
			//	Data.AlignedByteOffset = 16;
			//	// 16바이트짜리 자료형이야.
			//	Data.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
			//	// 버텍스 데이터용 레이아웃이야
			//	// 점세팅의 구조를 설명하기 위한 레이아웃이야.
			//	Data.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;

			//	// 지금은 알아도 크게 의미 없음
			//	Data.SemanticIndex = 0;
			//	Data.InputSlot = 0;
			//	Data.InstanceDataStepRate = 0;
			//	ArrLayOutInfo.push_back(Data);
			//}

			//LayOut->ResCreate(ArrLayOutInfo, VertexShader);

			// 레이아웃
		}

		//std::shared_ptr<GameEngineConstantBuffer> Buffer = GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData", ShaderType::Vertex);
		//std::shared_ptr<GameEngineConstantBuffer> Buffer = GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData");

		//if (nullptr != Buffer)
		//{
		//	const TransformData& Data = DataTransform->GetConstTransformDataRef();
		//	Buffer->ChangeData(Data);
		//	Buffer->Setting(0);
		//}



		if (nullptr != LayOut)
		{
			LayOut->Setting();
		}

		// 버텍스 쉐이더 세팅
		if (nullptr != VertexShader)
		{
			VertexShader->Setting();
		}


		std::shared_ptr<GameEngineIndexBuffer> IndexBuffer = GameEngineIndexBuffer::Find("Rect");
		if (nullptr != IndexBuffer)
		{
			IndexBuffer->Setting();
		}

		// 인덱스버퍼를 어떻게 사용할 것이냐에 대한 옵션이다.
		// 삼각형의 배열로 보고 그려라.
		// D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		// 선의 배열로 보고 그려라.
		// D3D11_PRIMITIVE_TOPOLOGY_LINELIST
		GameEngineCore::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


		// 나중에 아웃풋 머저 때문에 그렇습니다.
		D3D11_VIEWPORT ViewPort = {};

		// 좀더 식이 있어야 하는데 그건 다이렉트가 알아서 해준다.
		// 우리 viewport들어가 
		ViewPort.Width = GameEngineCore::MainWindow.GetScale().X;
		ViewPort.Height = GameEngineCore::MainWindow.GetScale().Y;
		ViewPort.MinDepth = 0.0f;
		ViewPort.MaxDepth = 1.0f;
		ViewPort.TopLeftX = 0.0f;
		ViewPort.TopLeftY = 0.0f;

		GameEngineCore::GetContext()->RSSetViewports(1, &ViewPort);


		std::shared_ptr<GameEngineRasterizer> Rasterizer = GameEngineRasterizer::Find("EngineRasterizer");
		if (nullptr != Rasterizer)
		{
			Rasterizer->Setting();
		}

		std::shared_ptr<GameEnginePixelShader> PixelShader = GameEnginePixelShader::Find("TextureShader_PS");
		if (nullptr != PixelShader)
		{
			PixelShader->Setting();
		}

		std::shared_ptr<class GameEngineBlend> Blend = GameEngineBlend::Find("EngineBlend");
		if (nullptr != Blend)
		{
			Blend->Setting();
		}


		std::shared_ptr<class GameEngineRenderTarget> BackBufferRenderTarget = GameEngineCore::GetBackBufferRenderTarget();
		if (nullptr != BackBufferRenderTarget)
		{
			BackBufferRenderTarget->Setting();
		}

		// 세팅된 버텍스 버퍼로 그려라
		// 그린다라는 버튼을 누르지는 않은것.
		// 이게 찍는 버튼이다.

		// 그걸 다시 옵션을 줄수 있는데.
		// 인덱스버퍼를 사용하는 경우 호출하는 DRAW함수 이다.
		// GameEngineCore::GetContext()->DrawIndexed(6, 0, 0);

		//std::vector<GameEngineVertex2D> Vertex;
		//Vertex.resize(4 * 6);

		//GameEngineVertex2D BaseVertexs[4];

		//BaseVertexs[0] = { { -0.5f, -0.5f, -0.5f, 1.0f } };
		//BaseVertexs[1] = { { 0.5f, -0.5f, -0.5f, 1.0f } };
		//BaseVertexs[2] = { { 0.5f, 0.5f, -0.5f, 1.0f } };
		//BaseVertexs[3] = { { -0.5f, 0.5f, -0.5f, 1.0f } };

		//// 앞면
		//Vertex[0] = BaseVertexs[0];
		//Vertex[1] = BaseVertexs[1];
		//Vertex[2] = BaseVertexs[2];
		//Vertex[3] = BaseVertexs[3];

		//// 뒷면
		//Vertex[4].POSITION = float4::VectorRotationToDegX(BaseVertexs[0].POSITION, 180.0f);
		//Vertex[5].POSITION = float4::VectorRotationToDegX(BaseVertexs[1].POSITION, 180.0f);
		//Vertex[6].POSITION = float4::VectorRotationToDegX(BaseVertexs[2].POSITION, 180.0f);
		//Vertex[7].POSITION = float4::VectorRotationToDegX(BaseVertexs[3].POSITION, 180.0f);

		//// 왼쪽이나 오른쪽
		//Vertex[8].POSITION = float4::VectorRotationToDegY(BaseVertexs[0].POSITION, 90.0f);
		//Vertex[9].POSITION = float4::VectorRotationToDegY(BaseVertexs[1].POSITION, 90.0f);
		//Vertex[10].POSITION = float4::VectorRotationToDegY(BaseVertexs[2].POSITION, 90.0f);
		//Vertex[11].POSITION = float4::VectorRotationToDegY(BaseVertexs[3].POSITION, 90.0f);

		//// 왼쪽이나 오른쪽
		//Vertex[12].POSITION = float4::VectorRotationToDegY(BaseVertexs[0].POSITION, -90.0f);
		//Vertex[13].POSITION = float4::VectorRotationToDegY(BaseVertexs[1].POSITION, -90.0f);
		//Vertex[14].POSITION = float4::VectorRotationToDegY(BaseVertexs[2].POSITION, -90.0f);
		//Vertex[15].POSITION = float4::VectorRotationToDegY(BaseVertexs[3].POSITION, -90.0f);

		//// 위거나 아래
		//Vertex[16].POSITION = float4::VectorRotationToDegX(BaseVertexs[0].POSITION, 90.0f);
		//Vertex[17].POSITION = float4::VectorRotationToDegX(BaseVertexs[1].POSITION, 90.0f);
		//Vertex[18].POSITION = float4::VectorRotationToDegX(BaseVertexs[2].POSITION, 90.0f);
		//Vertex[19].POSITION = float4::VectorRotationToDegX(BaseVertexs[3].POSITION, 90.0f);

		//Vertex[20].POSITION = float4::VectorRotationToDegX(BaseVertexs[0].POSITION, -90.0f);
		//Vertex[21].POSITION = float4::VectorRotationToDegX(BaseVertexs[1].POSITION, -90.0f);
		//Vertex[22].POSITION = float4::VectorRotationToDegX(BaseVertexs[2].POSITION, -90.0f);
		//Vertex[23].POSITION = float4::VectorRotationToDegX(BaseVertexs[3].POSITION, -90.0f);


		//std::vector<int> Index =
		//{
		//	0, 1, 2,
		//	0, 2, 3,
		//	0 + 4, 1 + 4, 2 + 4,
		//	0 + 4, 2 + 4, 3 + 4,
		//	0 + 8, 1 + 8, 2 + 8,
		//	0 + 8, 2 + 8, 3 + 8,
		//	0 + 12, 1 + 12, 2 + 12,
		//	0 + 12, 2 + 12, 3 + 12,
		//	0 + 16, 1 + 16, 2 + 16,
		//	0 + 16, 2 + 16, 3 + 16,
		//	0 + 20, 1 + 20, 2 + 20,
		//	0 + 20, 2 + 20, 3 + 20,
		//};

		////// 0   1
		////// 3   2


		////// 첫번째 방법
		////// Vertex[0] = { -0.5f, -0.5f }; 16
		////// Vertex[1] = { 0.5f, -0.5f }; 16
		////// Vertex[2] = { 0.5f, 0.5f }; 16
		////// 
		////// Vertex1[0] = { -0.5f, -0.5f }; 16
		////// Vertex1[1] = { 0.5f, -0.5f }; 16
		////// Vertex1[2] = { 0.5f, 0.5f }; 16 
		////// 
		////// 두번째 방법
		////// Vertex[0] = { -0.5f, -0.5f }; 16
		////// Vertex[1] = { 0.5f, -0.5f }; 16
		////// Vertex[2] = { 0.5f, 0.5f }; 16
		////// Vertex[3] = { -0.5f, 0.5f }; 16
		////// 
		////// short Arr[2][3] = {{0, 1, 2}, {0, 2, 3}}; 24

		////// 월드의 영역
		////// 물체로서의 크기 회전 위치
		////static float4 Scale = { 100.0f, 100.0f, 100.0f }; // 크기
		////static float4 Rotation = { 0, 0, 0 }; // 회전
		////static float4 Position = { 0.0f, 0.0f, 0.0f }; // 이동

		//////Rotation.X += 360.0f * _Delta;
		//////Rotation.Y += 360.0f * _Delta;
		//////Rotation.Z += 360.0f * _Delta;

		////float CamSpeed = 300.0f;
		////if (GameEngineInput::IsPress('A'))
		////{
		////	Position += float4::LEFT * _Delta * CamSpeed;
		////}

		////if (GameEngineInput::IsPress('D'))
		////{
		////	Position += float4::RIGHT * _Delta * CamSpeed;
		////}

		////if (GameEngineInput::IsPress('W'))
		////{
		////	Position += float4::UP * _Delta * CamSpeed;
		////}

		////if (GameEngineInput::IsPress('S'))
		////{
		////	Position += float4::DOWN * _Delta * CamSpeed;
		////}

		////if (GameEngineInput::IsPress('Q'))
		////{
		////	Rotation.Z += 360.0f * _Delta;
		////}

		////if (GameEngineInput::IsPress('E'))
		////{
		////	Rotation.Z -= 360.0f * _Delta;
		////}

		////float4x4 Scale4x4;
		////float4x4 Rotation4x4X;
		////float4x4 Rotation4x4Y;
		////float4x4 Rotation4x4Z;
		////float4x4 Rotation4x4;
		////float4x4 Position4x4;

		////Scale4x4.Scale(Scale);

		////Rotation4x4X.RotationXDeg(Rotation.X);
		////Rotation4x4Y.RotationYDeg(Rotation.Y);
		////Rotation4x4Z.RotationZDeg(Rotation.Z);
		////Rotation4x4 = Rotation4x4X * Rotation4x4Y * Rotation4x4Z;
		////Position4x4.Position(Position);

		////// 행렬의 곱셈은 교환법칙이 성립하지 않습니다.
		////float4x4 World4x4 = Scale4x4 * Rotation4x4 * Position4x4;

		////// 카메라의 영역

		////static float4 EyePos = { 0.0f, 0.0f, -500.0f, 1.0f };
		////static float4 EyeDir = { 0.0f, 0.0f, 1.0f, 1.0f };
		////// View4x4.LookToLH
		////// float4 EyeLookPos = {0.0f, 0.0f, 0.0f, 1.0f};
		////// 내부에서 계산된다.
		////// float4 EyeDir = EyePos - EyeLookPos;
		////static float4 EyeUp = { 0.0f, 1.0f, 0.0f, 1.0f };

		////float MoveSpeed = 300.0f;
		////if (GameEngineInput::IsPress('J'))
		////{
		////	EyePos += float4::LEFT * _Delta * MoveSpeed;
		////}

		////if (GameEngineInput::IsPress('L'))
		////{
		////	EyePos += float4::RIGHT * _Delta * MoveSpeed;
		////}

		////if (GameEngineInput::IsPress('I'))
		////{
		////	EyePos += float4::FORWARD * _Delta * MoveSpeed;
		////}

		////if (GameEngineInput::IsPress('K'))
		////{
		////	EyePos += float4::BACKWARD * _Delta * MoveSpeed;
		////}

		////if (GameEngineInput::IsPress('U'))
		////{
		////	EyeDir.VectorRotationToDegY(360.0f * _Delta);
		////}

		////if (GameEngineInput::IsPress('O'))
		////{
		////	EyeDir.VectorRotationToDegY(-360.0f * _Delta);
		////}

		////float4x4 View4x4;
		////View4x4.LookToLH(EyePos, EyeDir, EyeUp);


		////// 보고싶은 화면의 너비
		////// 12800	7200
		////// 윈도우 크기가 아니라 내가 세상을 바라보고 싶은 크기
		////// 줌인 줌아웃을 아주 쉽게 만들수 있을것이다.

		//////static float Zoom = 1.0f;

		////// Zoom += _Delta;
		//////									Width						Height						Far		Near
		////float4x4 Projection4x4;
		////Projection4x4.OrthographicLH(1280.0f, 720.0f, 1000.0f, 0.1f);

		//////Projection4x4.PerspectiveFovLH(60.0f, GetStartWindowSize().X, GetStartWindowSize().Y, 0.1f, 1000.0f);

		//float4x4 ViewPort4x4;
		//// 확장시키려는 화면 크기고, 이건 윈도우의 크기
		//ViewPort4x4.ViewPort(1280.0f, 720.0f, 0.0f, 0.0f);

		////float4x4 WorldView4x4 = World4x4 * View4x4;
		////float4x4 WorldViewProjection4x4 = World4x4 * View4x4 * Projection4x4;

		//HDC DC = GameEngineCore::MainWindow.GetBackBuffer()->GetImageDC();

		//for (size_t indexCount = 0; indexCount < Index.size() / 3; indexCount++)
		//{
		//	int ArrIndex[3];
		//	ArrIndex[0] = Index[indexCount * 3 + 0];
		//	ArrIndex[1] = Index[indexCount * 3 + 1];
		//	ArrIndex[2] = Index[indexCount * 3 + 2];

		//	const TransformData& TransDataRef = Transform.GetConstTransformDataRef();

		//	float4 Trifloat4[3];
		//	std::vector<POINT> Tri;
		//	Tri.resize(3);
		//	for (size_t VertexCount = 0; VertexCount < Tri.size(); VertexCount++)
		//	{
		//		// 위치를 더해줌으로해서 월드 상태로 이전시켰다고 한다.
		//		float4 WorldPoint = Vertex[ArrIndex[VertexCount]].POSITION;

		//		// 위치 크기 회전을 적용시킬때 수학적으로 증명된
		//		// 절대적인 기준이 있습니다.
		//		// 크기 회전 위치 순서대로 적용시켜야 합니다.

		//		// 모든걸 다 행렬이라는 것으로 처리합니다.
		//		// 이렇게 벡터식으로 처리하지 않고 
		//		// 전부다 행렬이라는것을 사용해서 복잡한 변환을 수행합니다.
		//		// 그럼 행렬은 뭐냐?
		//		// x열 y행의 숫자가 모여있는 2차원 배열입니다.
		//		// 우리가 사용하는 float4 4열 1행 행렬이다.
		//		// 행렬의 기준으로 본다면 행렬이 아닌게 없다.
		//		// 1 <= 숫자하나가 덩그러니 있으면 1행 1열짜리 행렬일 것이다.

		//		// 당연히 float4 행렬이 다른 행렬끼리 연산이 되므로
		//		// 더 큰 행렬도 이에 사용될수 있을 것이다.

		//		// 보통은 4x4 행렬을 사용해서
		//		// 크기 회전 위치를 표현하는 변환행렬을 만듭니다.

		//		// 로컬 => 월드 => 뷰 => 투영 => 뷰포트 => 모니터

		//		// 일단 연산량의 차이.
		//		// 행렬이 훨씬 연산이 작아요.
		//		// 다양한 변환을 한번에 할수가 있다.

		//		// WorldPoint *= World;

		//		//WorldPoint *= Scale;
		//		//WorldPoint = WorldPoint.VectorRotationToDegX(Rotation.X);
		//		//WorldPoint = WorldPoint.VectorRotationToDegY(Rotation.Y);
		//		//WorldPoint = WorldPoint.VectorRotationToDegZ(Rotation.Z);
		//		//WorldPoint += Position;

		//		// 변환식은 이제 딱 한가지 인것.
		//		// 버텍스 쉐이더
		//		//WorldPoint = WorldPoint * World4x4;
		//		//WorldPoint = WorldPoint * WorldView4x4;
		//		//WorldPoint = WorldPoint * WorldViewProjection4x4;
		//		//WorldPoint = WorldPoint * TransDataRef.WorldViewProjectionMatrix;

		//		WorldPoint /= WorldPoint.W;
		//		WorldPoint.W = 1.0f;

		//		WorldPoint = WorldPoint * ViewPort4x4;

		//		Trifloat4[VertexCount] = WorldPoint;
		//		Tri[VertexCount] = WorldPoint.WindowPOINT();
		//	}
		//	float4 Dir0 = Trifloat4[0] - Trifloat4[1];
		//	float4 Dir1 = Trifloat4[1] - Trifloat4[2];
		//	float4 Check = float4::Cross3D(Dir1, Dir0);
		//	if (Check.Z < 1.0f)
		//	{
		//		continue;
		//	}
		//	Polygon(DC, &Tri[0], static_cast<int>(Tri.size()));
		//}

		//// 화면에 3d물체를 구별하고 선별하기 위한 변환은 다 끝났고
		//// 어떤 모니터에 뿌릴까만이 남게된다.
		//// 최종적으로 화면에 어떻게 뿌릴것인가만이 남아있다.
	}
}
*/

//void GameEngineRenderer::Draw()
//{
//	std::shared_ptr<GameEngineIndexBuffer> IndexBuffer = GameEngineIndexBuffer::Find("Rect");
//	if (nullptr == IndexBuffer)
//	{
//		return;
//	}
//	GameEngineCore::GetContext()->DrawIndexed(IndexBuffer->GetIndexCount(), 0, 0);
//}