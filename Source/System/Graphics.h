#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <memory>
#include <mutex>
#include "RenderState.h"
#include "ShapeRenderer.h"
#include "ModelRenderer.h"

// �O���t�B�b�N�X
class Graphics
{
private:
	Graphics() = default;
	~Graphics() = default;

public:
	// �C���X�^���X�擾
	static Graphics& Instance()
	{
		static Graphics instance;
		return instance;
	}

	// ������
	void Initialize(HWND hWnd);

	// �N���A
	void Clear(float r, float g, float b, float a);

	// �����_�[�^�[�Q�b�g�ݒ�
	void SetRenderTargets();

	// ��ʕ\��
	void Present(UINT syncInterval);

	// �E�C���h�E�n���h���擾
	HWND GetWindowHandle() { return hWnd; }

	// �f�o�C�X�擾
	ID3D11Device* GetDevice() { return device.Get(); }

	// �f�o�C�X�R���e�L�X�g�擾
	ID3D11DeviceContext* GetDeviceContext() { return immediateContext.Get(); }

	// �X�N���[�����擾
	float GetScreenWidth() const { return screenWidth; }

	// �X�N���[�������擾
	float GetScreenHeight() const { return screenHeight; }

	// �����_�[�X�e�[�g�擾
	RenderState* GetRenderState() { return renderState.get(); }

	// �V�F�C�v�����_���擾
	ShapeRenderer* GetShapeRenderer() const { return shapeRenderer.get(); }

	// ���f�������_���擾
	ModelRenderer* GetModelRenderer() const { return modelRenderer.get(); }

	//�~���[�e�b�N�X�擾
	std::mutex& GetMutex() { return mutex; }

private:
	HWND											hWnd = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Device>			device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>		immediateContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain>			swapchain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	depthStencilView;
	D3D11_VIEWPORT									viewport;

	float	screenWidth = 0;
	float	screenHeight = 0;

	std::unique_ptr<RenderState>					renderState;
	std::unique_ptr<ShapeRenderer>					shapeRenderer;
	std::unique_ptr<ModelRenderer>	
				modelRenderer;
	std::mutex mutex;
};