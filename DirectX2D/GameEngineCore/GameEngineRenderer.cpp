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

// ī�޶� ���ο����� ���� ����
void GameEngineRenderer::SetRenderOrder(int _Order)
{

	if (nullptr == Camera)
	{
		MsgBoxAssert("ī�޶� �������� �ʴ� ������ �Դϴ�. ī�޶���� �������ּ���.");
		return;
	}

	Camera->Renderers[GetOrder()].remove(GetDynamic_Cast_This<GameEngineRenderer>());
	GameEngineObject::SetOrder(_Order);
	Camera->Renderers[GetOrder()].push_back(GetDynamic_Cast_This<GameEngineRenderer>());

}

// �� �ٶ󺸴� ī�޶� ����
void GameEngineRenderer::SetCameraOrder(int _Order)
{
	SetViewCameraSelect(_Order);
}

void GameEngineRenderer::Start()
{
	// ����ī�޶� ����.
	//SetViewCameraSelect(0);
	//DataTransform = &Transform;
	SetCameraOrder(ECAMERAORDER::Main);

	//GameEngineActor* Actor = GetActor();

	// ī�޶� ã�Ƽ� ���� �մϴ�.
	// ī�޸� ã������? GameEngineLevel
	// Level���� ã�ƾ���.
	// Level���� ��� ����? ���� ��� �ִ� Actor�� ��� �־�.

	// Level�� ����� �ۿ� �����ϴ�.
}

void GameEngineRenderer::SetViewCameraSelect(int _Order)
{
	GameEngineLevel* Level = GetLevel();

	std::shared_ptr<GameEngineCamera> FindCamera = Level->GetCamera(_Order);

	if (nullptr == FindCamera)
	{
		MsgBoxAssert("ī�޶� �������� �ʴµ� �������� �������� �߽��ϴ�.");
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

	// ������
	if (nullptr != Units[_Index])
	{
		//����
		return Units[_Index];
	}

	// ������ �����.
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
//	// �ִ� ������ ���� Ÿ���� �������� �մϴ�.
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
//		MsgBoxAssert("�������� �ʴ� �Ž��� �����Ϸ��� �߽��ϴ�.");
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
//		MsgBoxAssert("�������� �ʴ� �Ž��� �����Ϸ��� �߽��ϴ�.");
//	}
//
//	if (nullptr == LayOut && nullptr != Mesh)
//	{
//		LayOut = std::make_shared<GameEngineInputLayOut>();
//		LayOut->ResCreate(Mesh->GetVertexBuffer(), Material->GetVertexShader());
//	}
//
//	// ���ؽ� ���̴��� �ȼ����̴��� �� ����ִ� ���´�.
//
//	// �������� ���̴� ���ҽ� ���ۿ�
//	// ���ؽ��� �ȼ����̴��� ���ҽ��������� ���� �޽��ϴ�.
//	ShaderResHelper.ShaderResCopy(Material->GetVertexShader().get());
//	ShaderResHelper.ShaderResCopy(Material->GetPixelShader().get());
//
//	// �̰� ȸ���� ���.
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
		// ��ǲ�����1 ���ؽ� ���� ����
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
			//	// 0����Ʈ���� �����ϴ�
			//	Data.AlignedByteOffset = 0;
			//	// 16����Ʈ¥�� �ڷ����̾�.
			//	Data.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
			//	// ���ؽ� �����Ϳ� ���̾ƿ��̾�.
			//	// �������� ������ �����ϱ� ���� ���̾ƿ��̾�.
			//	Data.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;

			//	// ������ �˾Ƶ� ũ�� �ǹ� ����
			//	Data.SemanticIndex = 0;
			//	Data.InputSlot = 0;
			//	Data.InstanceDataStepRate = 0;
			//	ArrLayOutInfo.push_back(Data);
			//}

			//{
			//	D3D11_INPUT_ELEMENT_DESC Data;
			//	Data.SemanticName = "COLOR";
			//	// 0����Ʈ���� �����ϴ�
			//	Data.AlignedByteOffset = 16;
			//	// 16����Ʈ¥�� �ڷ����̾�.
			//	Data.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
			//	// ���ؽ� �����Ϳ� ���̾ƿ��̾�
			//	// �������� ������ �����ϱ� ���� ���̾ƿ��̾�.
			//	Data.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;

			//	// ������ �˾Ƶ� ũ�� �ǹ� ����
			//	Data.SemanticIndex = 0;
			//	Data.InputSlot = 0;
			//	Data.InstanceDataStepRate = 0;
			//	ArrLayOutInfo.push_back(Data);
			//}

			//LayOut->ResCreate(ArrLayOutInfo, VertexShader);

			// ���̾ƿ�
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

		// ���ؽ� ���̴� ����
		if (nullptr != VertexShader)
		{
			VertexShader->Setting();
		}


		std::shared_ptr<GameEngineIndexBuffer> IndexBuffer = GameEngineIndexBuffer::Find("Rect");
		if (nullptr != IndexBuffer)
		{
			IndexBuffer->Setting();
		}

		// �ε������۸� ��� ����� ���̳Ŀ� ���� �ɼ��̴�.
		// �ﰢ���� �迭�� ���� �׷���.
		// D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		// ���� �迭�� ���� �׷���.
		// D3D11_PRIMITIVE_TOPOLOGY_LINELIST
		GameEngineCore::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


		// ���߿� �ƿ�ǲ ���� ������ �׷����ϴ�.
		D3D11_VIEWPORT ViewPort = {};

		// ���� ���� �־�� �ϴµ� �װ� ���̷�Ʈ�� �˾Ƽ� ���ش�.
		// �츮 viewport�� 
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

		// ���õ� ���ؽ� ���۷� �׷���
		// �׸��ٶ�� ��ư�� �������� ������.
		// �̰� ��� ��ư�̴�.

		// �װ� �ٽ� �ɼ��� �ټ� �ִµ�.
		// �ε������۸� ����ϴ� ��� ȣ���ϴ� DRAW�Լ� �̴�.
		// GameEngineCore::GetContext()->DrawIndexed(6, 0, 0);

		//std::vector<GameEngineVertex2D> Vertex;
		//Vertex.resize(4 * 6);

		//GameEngineVertex2D BaseVertexs[4];

		//BaseVertexs[0] = { { -0.5f, -0.5f, -0.5f, 1.0f } };
		//BaseVertexs[1] = { { 0.5f, -0.5f, -0.5f, 1.0f } };
		//BaseVertexs[2] = { { 0.5f, 0.5f, -0.5f, 1.0f } };
		//BaseVertexs[3] = { { -0.5f, 0.5f, -0.5f, 1.0f } };

		//// �ո�
		//Vertex[0] = BaseVertexs[0];
		//Vertex[1] = BaseVertexs[1];
		//Vertex[2] = BaseVertexs[2];
		//Vertex[3] = BaseVertexs[3];

		//// �޸�
		//Vertex[4].POSITION = float4::VectorRotationToDegX(BaseVertexs[0].POSITION, 180.0f);
		//Vertex[5].POSITION = float4::VectorRotationToDegX(BaseVertexs[1].POSITION, 180.0f);
		//Vertex[6].POSITION = float4::VectorRotationToDegX(BaseVertexs[2].POSITION, 180.0f);
		//Vertex[7].POSITION = float4::VectorRotationToDegX(BaseVertexs[3].POSITION, 180.0f);

		//// �����̳� ������
		//Vertex[8].POSITION = float4::VectorRotationToDegY(BaseVertexs[0].POSITION, 90.0f);
		//Vertex[9].POSITION = float4::VectorRotationToDegY(BaseVertexs[1].POSITION, 90.0f);
		//Vertex[10].POSITION = float4::VectorRotationToDegY(BaseVertexs[2].POSITION, 90.0f);
		//Vertex[11].POSITION = float4::VectorRotationToDegY(BaseVertexs[3].POSITION, 90.0f);

		//// �����̳� ������
		//Vertex[12].POSITION = float4::VectorRotationToDegY(BaseVertexs[0].POSITION, -90.0f);
		//Vertex[13].POSITION = float4::VectorRotationToDegY(BaseVertexs[1].POSITION, -90.0f);
		//Vertex[14].POSITION = float4::VectorRotationToDegY(BaseVertexs[2].POSITION, -90.0f);
		//Vertex[15].POSITION = float4::VectorRotationToDegY(BaseVertexs[3].POSITION, -90.0f);

		//// ���ų� �Ʒ�
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


		////// ù��° ���
		////// Vertex[0] = { -0.5f, -0.5f }; 16
		////// Vertex[1] = { 0.5f, -0.5f }; 16
		////// Vertex[2] = { 0.5f, 0.5f }; 16
		////// 
		////// Vertex1[0] = { -0.5f, -0.5f }; 16
		////// Vertex1[1] = { 0.5f, -0.5f }; 16
		////// Vertex1[2] = { 0.5f, 0.5f }; 16 
		////// 
		////// �ι�° ���
		////// Vertex[0] = { -0.5f, -0.5f }; 16
		////// Vertex[1] = { 0.5f, -0.5f }; 16
		////// Vertex[2] = { 0.5f, 0.5f }; 16
		////// Vertex[3] = { -0.5f, 0.5f }; 16
		////// 
		////// short Arr[2][3] = {{0, 1, 2}, {0, 2, 3}}; 24

		////// ������ ����
		////// ��ü�μ��� ũ�� ȸ�� ��ġ
		////static float4 Scale = { 100.0f, 100.0f, 100.0f }; // ũ��
		////static float4 Rotation = { 0, 0, 0 }; // ȸ��
		////static float4 Position = { 0.0f, 0.0f, 0.0f }; // �̵�

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

		////// ����� ������ ��ȯ��Ģ�� �������� �ʽ��ϴ�.
		////float4x4 World4x4 = Scale4x4 * Rotation4x4 * Position4x4;

		////// ī�޶��� ����

		////static float4 EyePos = { 0.0f, 0.0f, -500.0f, 1.0f };
		////static float4 EyeDir = { 0.0f, 0.0f, 1.0f, 1.0f };
		////// View4x4.LookToLH
		////// float4 EyeLookPos = {0.0f, 0.0f, 0.0f, 1.0f};
		////// ���ο��� ���ȴ�.
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


		////// ������� ȭ���� �ʺ�
		////// 12800	7200
		////// ������ ũ�Ⱑ �ƴ϶� ���� ������ �ٶ󺸰� ���� ũ��
		////// ���� �ܾƿ��� ���� ���� ����� �������̴�.

		//////static float Zoom = 1.0f;

		////// Zoom += _Delta;
		//////									Width						Height						Far		Near
		////float4x4 Projection4x4;
		////Projection4x4.OrthographicLH(1280.0f, 720.0f, 1000.0f, 0.1f);

		//////Projection4x4.PerspectiveFovLH(60.0f, GetStartWindowSize().X, GetStartWindowSize().Y, 0.1f, 1000.0f);

		//float4x4 ViewPort4x4;
		//// Ȯ���Ű���� ȭ�� ũ���, �̰� �������� ũ��
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
		//		// ��ġ�� �����������ؼ� ���� ���·� �������״ٰ� �Ѵ�.
		//		float4 WorldPoint = Vertex[ArrIndex[VertexCount]].POSITION;

		//		// ��ġ ũ�� ȸ���� �����ų�� ���������� �����
		//		// �������� ������ �ֽ��ϴ�.
		//		// ũ�� ȸ�� ��ġ ������� ������Ѿ� �մϴ�.

		//		// ���� �� ����̶�� ������ ó���մϴ�.
		//		// �̷��� ���ͽ����� ó������ �ʰ� 
		//		// ���δ� ����̶�°��� ����ؼ� ������ ��ȯ�� �����մϴ�.
		//		// �׷� ����� ����?
		//		// x�� y���� ���ڰ� ���ִ� 2���� �迭�Դϴ�.
		//		// �츮�� ����ϴ� float4 4�� 1�� ����̴�.
		//		// ����� �������� ���ٸ� ����� �ƴѰ� ����.
		//		// 1 <= �����ϳ��� ���׷��� ������ 1�� 1��¥�� ����� ���̴�.

		//		// �翬�� float4 ����� �ٸ� ��ĳ��� ������ �ǹǷ�
		//		// �� ū ��ĵ� �̿� ���ɼ� ���� ���̴�.

		//		// ������ 4x4 ����� ����ؼ�
		//		// ũ�� ȸ�� ��ġ�� ǥ���ϴ� ��ȯ����� ����ϴ�.

		//		// ���� => ���� => �� => ���� => ����Ʈ => �����

		//		// �ϴ� ���귮�� ����.
		//		// ����� �ξ� ������ �۾ƿ�.
		//		// �پ��� ��ȯ�� �ѹ��� �Ҽ��� �ִ�.

		//		// WorldPoint *= World;

		//		//WorldPoint *= Scale;
		//		//WorldPoint = WorldPoint.VectorRotationToDegX(Rotation.X);
		//		//WorldPoint = WorldPoint.VectorRotationToDegY(Rotation.Y);
		//		//WorldPoint = WorldPoint.VectorRotationToDegZ(Rotation.Z);
		//		//WorldPoint += Position;

		//		// ��ȯ���� ���� �� �Ѱ��� �ΰ�.
		//		// ���ؽ� ���̴�
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

		//// ȭ�鿡 3d��ü�� �����ϰ� �����ϱ� ���� ��ȯ�� �� ������
		//// � ����Ϳ� �Ѹ���� ���Եȴ�.
		//// ���������� ȭ�鿡 ��� �Ѹ����ΰ����� �����ִ�.
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