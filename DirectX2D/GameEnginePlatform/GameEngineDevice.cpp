#include "PreCompile.h"
#include "GameEngineDevice.h"
#include "GameEngineWindow.h"

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "DXGI")

GameEngineDevice::GameEngineDevice()
{
}

GameEngineDevice::~GameEngineDevice()
{
	if (nullptr != Context)
	{
		Context->Release();
		Context = nullptr;
	}

	if (nullptr != Device)
	{
		Device->Release();
		Device = nullptr;
	}
}

void GameEngineDevice::Initiallize(const class GameEngineWindow& _Window)
{
	if (nullptr == _Window.GetHWND())
	{
		MsgBoxAssert("�����찡 ��������� �ʾҴµ� ����̽��� �ʱ�ȭ �Ҽ��� �����ϴ�.");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	
	// ���̷�Ʈx ���� ��������ظ� �˾Ƴ��� ���� ����
	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	// �׷���ī���� �⺻������ �˷��ְ� �����Ҽ� �ִ� �������̽�.
	IDXGIAdapter* Adapter = GetHighPerformanceAdapter();

	if (nullptr == Adapter)
	{
		Adapter->Release();
		MsgBoxAssert("�׷���ī�尡 ���� ��ǻ���Դϴ�.");
		return;
	}

	// D11����̽��� �׷���ī�� ������ �޸𸮸� ������ �� �ִ� �������̽��Դϴ�.
	// ���߿� �������̽� => �޸�

	// �� ��ġ�� IDXGIAdapter* Adapter
	// �޸𸮿� �����ϴ� ���Ѱ� ID3D11Device* Device
	// �׸��� �׸��� �ִ� ������ �������. ID3D11DeviceContext* Context

	// 0������ �⺻���� ����.

	HRESULT Result = D3D11CreateDevice(
		Adapter, // ��ġ <= 
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN, // �� ��ġ�� �ϵ����� �����޶��ε�.
		nullptr, // ������
		iFlag, // �ʱ�ȭ �ɼ�
		nullptr, // ����Ҽ� �ִ� ��ó����
		0, // ���߿��� ���� ���ϴ� ��ó���� �Ҽ� �ִ� 
		D3D11_SDK_VERSION, // ���� ������ �������� ����.
		&Device,
		&Level,
		&Context
	);

	if (S_OK != Result)
	{
		MsgBoxAssert("����̽� ������ �����߽��ϴ�.");
		return;
	}

	Adapter->Release();
}

IDXGIAdapter* GameEngineDevice::GetHighPerformanceAdapter()
{
	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adapter = nullptr;

	// �ü������ ��Ź�ؼ� �ϵ���� ���� ����� �̿��� �� �ִ�
	// IDXGIFactory�� ������ ��.
	// ���� �����Ҽ� ���� ������ �Լ�
	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));

	if (nullptr == Factory)
	{
		MsgBoxAssert("�׷��� ī�忡�� ���丮 �������̽��� �������� ���߽��ϴ�.");
		return nullptr;
	}

	SIZE_T VideoMemory = 0;

	for (UINT Index = 0;; ++Index)
	{
		IDXGIAdapter* CurAdapter = nullptr;

		Factory->EnumAdapters(Index, &CurAdapter);

		if (nullptr == CurAdapter)
		{
			break;
		}

		DXGI_ADAPTER_DESC Desc;
		CurAdapter->GetDesc(&Desc);

		if (VideoMemory <= Desc.DedicatedVideoMemory)
		{
			// �� ū ���� �޸�.
			VideoMemory = Desc.DedicatedVideoMemory;

			if (nullptr != Adapter)
			{
				// ���ο� �ִ� �޸𸮸� �������ش�.
				Adapter->Release();
			}

			Adapter = CurAdapter;
			continue;
		}

		CurAdapter->Release();
	}

	Factory->Release();
	return Adapter;
}