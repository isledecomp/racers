#include "duskwindbananarelic0x30.h"

#include "bronzefalcon0xc8770.h"
#include "golcommondrawstate.h"
#include "golerror.h"

#include <stdio.h>
#include <string.h>

DECOMP_SIZE_ASSERT(DuskwindBananaRelic0x30, 0x30)

// FUNCTION: GOLDP 0x10006280
DuskwindBananaRelic0x30::DuskwindBananaRelic0x30()
{
	m_unk0x24 = NULL;
	m_unk0x28 = 0;
	m_unk0x2c = NULL;
}

// FUNCTION: GOLDP 0x100062a0
DuskwindBananaRelic0x30::~DuskwindBananaRelic0x30()
{
	Destroy();
}

// FUNCTION: GOLDP 0x10006320
void DuskwindBananaRelic0x30::FUN_10006320(WhiteFalcon0x140& p_renderer)
{
	if (m_unk0x08 & c_flagBit0) {
		Destroy();
	}

	m_unk0x08 |= c_flagBit0;
	BronzeFalcon0xc8770* renderer = static_cast<BronzeFalcon0xc8770*>(p_renderer.GetDrawState()->m_currentRenderer);

	if (renderer->GetUnk0x04() & WhiteFalcon0x140::c_flagBit16) {
		LegoU32 textureCount;
		if (m_unk0x04 != NULL) {
			textureCount = m_unk0x04->GetUnk0x34();
		}
		else {
			textureCount = 1;
		}

		LegoU32 bufferSize = textureCount * 16;
		m_unk0x2c = new LegoU8[bufferSize];
		if (m_unk0x2c == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		::memset(m_unk0x2c, 0, bufferSize);
		if (m_unk0x04 == NULL) {
			renderer->GetSoftwareRenderer().FUN_100411b0(m_unk0x2c, this, 0);
			FUN_100064d0(renderer);
			return;
		}

		for (LegoU32 i = 0; i < m_unk0x04->GetUnk0x34(); i++) {
			renderer->GetSoftwareRenderer().FUN_100411b0(m_unk0x2c + i * 16, this, i);
		}
	}
	else {
		HRESULT result = renderer->GetDirect3D3()->CreateMaterial(&m_unk0x24, NULL);
		if (result != D3D_OK) {
			LegoChar errorMessage[64];
			::sprintf(errorMessage, "Unable to create material\nerrcode = %x", result);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}
	}

	FUN_100064d0(renderer);
}

// FUNCTION: GOLDP 0x10006490
void DuskwindBananaRelic0x30::Destroy()
{
	if (m_unk0x2c != NULL) {
		delete m_unk0x2c;
		m_unk0x2c = NULL;
	}
	if (m_unk0x24 != NULL) {
		m_unk0x24->Release();
		m_unk0x24 = NULL;
	}
	m_unk0x28 = 0;
	m_unk0x08 &= ~c_flagBit0;
}

// FUNCTION: GOLDP 0x100064d0
void DuskwindBananaRelic0x30::FUN_100064d0(BronzeFalcon0xc8770* p_renderer)
{
	D3DMATERIAL material;
	LegoChar errorMessage[64];

	material.dwSize = sizeof(D3DMATERIAL);
	material.ambient.r = static_cast<LegoFloat>(static_cast<double>(m_unk0x10.m_unk0x0 & 0xff) / 255.0);
	material.ambient.g = static_cast<LegoFloat>(static_cast<double>(m_unk0x10.m_unk0x1 & 0xff) / 255.0);
	material.ambient.b = static_cast<LegoFloat>(static_cast<double>(m_unk0x10.m_unk0x2 & 0xff) / 255.0);
	material.ambient.a = static_cast<LegoFloat>(static_cast<double>(m_unk0x10.m_unk0x3 & 0xff) / 255.0);
	material.diffuse.r = static_cast<LegoFloat>(static_cast<double>(m_unk0x0c.m_unk0x0 & 0xff) / 255.0);
	material.diffuse.g = static_cast<LegoFloat>(static_cast<double>(m_unk0x0c.m_unk0x1 & 0xff) / 255.0);
	material.diffuse.b = static_cast<LegoFloat>(static_cast<double>(m_unk0x0c.m_unk0x2 & 0xff) / 255.0);
	material.diffuse.a = static_cast<LegoFloat>(static_cast<double>(m_unk0x0c.m_unk0x3 & 0xff) / 255.0);
	material.specular.r = 0.0f;
	material.specular.g = 0.0f;
	material.specular.b = 0.0f;
	material.specular.a = 0.0f;
	material.emissive.r = 0.0f;
	material.emissive.g = 0.0f;
	material.emissive.b = 0.0f;
	material.emissive.a = 0.0f;
	material.power = 0.0f;
	material.hTexture = 0;
	material.dwRampSize = 16;

	if (m_unk0x24 != NULL) {
		HRESULT result = m_unk0x24->SetMaterial(&material);
		if (result != D3D_OK) {
			::sprintf(errorMessage, "Unable to set material\nerrcode = %x", result);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}

		result = m_unk0x24->GetHandle(p_renderer->GetDirect3DDevice(), &m_unk0x28);
		if (result != D3D_OK) {
			::sprintf(errorMessage, "Unable to get material handle\nerror %x", result);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}
	}
}
