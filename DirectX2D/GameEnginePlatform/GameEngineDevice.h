#pragma once

// ���̷�Ʈx�� ������ ����.
// �׷���ī�带 �̿��ؼ� 3D ������ ��� �ñ�°�.
// �׷���ī��� 3D������ ���� ������ ����ȭ�� ������ġ�̴�.
// �ȼ�������ŭ�� ���ÿ����� �����ϴ�. 1+1 ���ÿ� 1280x720
// �츮�� �̰� C++�� ¥��
// for(int i = 0; i < 1280 x 720 ; i++)
// {
// }

// ���� : 
class GameEngineDevice
{
public:
	// constrcuter destructer
	GameEngineDevice();
	~GameEngineDevice();

	// delete Function
	GameEngineDevice(const GameEngineDevice & _Other) = delete;
	GameEngineDevice(GameEngineDevice && _Other) noexcept = delete;
	GameEngineDevice& operator=(const GameEngineDevice & _Other) = delete;
	GameEngineDevice& operator=(GameEngineDevice && _Other) noexcept = delete;

	// �����쿡�� ������� ������
	// �ٰ��� HWND�� ���� �䱸�դ���.
	// �׷��� ������ ������ �� window�� �� ���Ѵ�.
	void Initiallize(const class GameEngineWindow& _Window);

protected:

private:
	IDXGIAdapter* GetHighPerformanceAdapter();

	// �׷���ī���� �޸𸮰��� ���ٱ��� �������̽�
	// Ex) �̹��� ������ ����� ����� �ִ� �����̴�.

	ID3D11Device* Device = nullptr;

	// �׷���ī���� ����(�׸���)���� ���ٱ��� �������̽�
	// �ε�� �̹����� ������� ������ ȭ�鿡 �׷���

	ID3D11DeviceContext* Context = nullptr;

};

