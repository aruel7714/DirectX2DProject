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
		MsgBoxAssert("윈도우가 만들어지지 않았는데 디바이스를 초기화 할수는 없습니다.");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	
	// 다이렉트x 버전 몇까지원해를 알아내기 위한 변수
	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	// 그래픽카드의 기본정보를 알려주고 제어할수 있는 인터페이스.
	IDXGIAdapter* Adapter = GetHighPerformanceAdapter();

	if (nullptr == Adapter)
	{
		Adapter->Release();
		MsgBoxAssert("그래픽카드가 없는 컴퓨터입니다.");
		return;
	}

	// D11디바이스는 그래픽카드 랜더링 메모리를 제어할 수 있는 인터페이스입니다.
	// 최중요 인터페이스 => 메모리

	// 이 장치의 IDXGIAdapter* Adapter
	// 메모리에 접근하는 권한과 ID3D11Device* Device
	// 그림을 그릴수 있는 권한을 만들어줘. ID3D11DeviceContext* Context

	// 0넣으면 기본으로 해줘.

	HRESULT Result = D3D11CreateDevice(
		Adapter, // 장치 <= 
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN, // 이 장치의 하드웨어로 만들어달라인데.
		nullptr, // 뭔지모름
		iFlag, // 초기화 옵션
		nullptr, // 사용할수 있는 펙처레벨
		0, // 그중에서 내가 원하는 펙처레벨 할수 있는 
		D3D11_SDK_VERSION, // 지금 윈도우 버전으로 해줘.
		&Device,
		&Level,
		&Context
	);

	if (S_OK != Result)
	{
		MsgBoxAssert("디바이스 생성에 실패했습니다.");
		return;
	}

	Adapter->Release();
}

IDXGIAdapter* GameEngineDevice::GetHighPerformanceAdapter()
{
	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adapter = nullptr;

	// 운영체제에게 부탁해서 하드웨어 관련 기능을 이용할 수 있는
	// IDXGIFactory를 얻어오는 것.
	// 내가 이해할수 없는 영역의 함수
	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));

	if (nullptr == Factory)
	{
		MsgBoxAssert("그래픽 카드에서 팩토리 인터페이스를 생성하지 못했습니다.");
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
			// 더 큰 비디오 메모리.
			VideoMemory = Desc.DedicatedVideoMemory;

			if (nullptr != Adapter)
			{
				// 내부에 있는 메모리를 정리해준다.
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