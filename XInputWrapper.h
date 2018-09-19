#pragma once
#ifndef XINPUT_WRAPPER_H
#define XINPUT_WRAPPER_H

#include <XInput.h>
#include <errno.h>

class XInputWrapper {
public:
	XInputWrapper() = default;
	~XInputWrapper() = default;

	virtual DWORD XInputGetState(DWORD dwUserIndex, XINPUT_STATE *pState) {
#ifdef _WIN32
		return ::XInputGetState(dwUserIndex, pState);
#else
		return EPERM;
#endif
	}

	virtual DWORD XInputSetState(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration) {
#ifdef _WIN32
		return ::XInputSetState(dwUserIndex, pVibration);
#else
		return EPERM;
#endif
	}

	virtual DWORD XInputGetCapabilities(DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES* pCapabilities) {
#ifdef _WIN32
		return ::XInputGetCapabilities(dwUserIndex, dwFlags, pCapabilities);
#else
		return EPERM;
#endif
	}

	virtual DWORD XInputGetBatteryInformation(DWORD dwUserIndex, BYTE devType, XINPUT_BATTERY_INFORMATION* pBatteryInformation) {
#ifdef _WIN32
		return ::XInputGetBatteryInformation(dwUserIndex, devType, pBatteryInformation);
#else
		return EPERM;
#endif
	}

	virtual DWORD XInputGetKeystroke(DWORD dwUserIndex, DWORD dwReserved, PXINPUT_KEYSTROKE pKeyStroke) {
#ifdef _WIN32
		return ::XInputGetKeystroke(dwUserIndex, dwReserved, pKeyStroke);
#else
		return EPERM;
#endif
	}
};

#endif // XINPUT_WRAPPER_H
#pragma once
