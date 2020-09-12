/***********************************************************
* title_name        : Badge Notification Manager
* date_created      : 2020.09.08
* file_name         : BadgeNotification.cpp
* author            : VegaS
* version           : Version 1.0
*/

#include "StdAfx.h"
#include "resource.h"
#include "PythonApplication.h"
#include "../EterLib/MSWindow.h"
#include "../EterPythonLib/PythonSlotWindow.h"
#include "../EterPythonLib/PythonWindowManager.h"
#include <ShlObj.h>

#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
#include "BadgeNotificationManager.h"

/**
 * \brief When an application displays a window, its taskbar button is created by the system.
 * An implementation of this interface is provided in windows as CLSID_TaskbarList.
 */
static ITaskbarList3* m_TaskBarApp = nullptr;

/**
 * \brief Called when the singleton is initialized.
 */
CBadgeNotificationManager::CBadgeNotificationManager()
{
	Initialize();

	if (IsWindowsCompatibleVersion())
		UngroupTaskbar();
}

CBadgeNotificationManager::~CBadgeNotificationManager()
= default;

/**
 * \brief Compares a set of operating system version requirements to the corresponding values
 * for the currently running version of the system.
 * \return bool
 */
auto CBadgeNotificationManager::IsWindowsCompatibleVersion() -> bool
{
	OSVERSIONINFOEXW osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	osvi.dwMajorVersion = HIBYTE(_WIN32_WINNT_WIN7);
	osvi.dwMinorVersion = LOBYTE(_WIN32_WINNT_WIN7);

	const auto& condition_mask = VerSetConditionMask(VerSetConditionMask(VerSetConditionMask(0, VER_MAJORVERSION, VER_GREATER_EQUAL), VER_MINORVERSION, VER_GREATER_EQUAL), VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);
	return VerifyVersionInfoW(&osvi, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, condition_mask) > 0;
}

/**
 * \brief This identifier allows an application to group its associated processes and windows under a single taskbar button.
 * This method must be called during an application's initial startup routine before
 * the application presents any UI or makes any manipulation of its jump lists.
 * Minimum supported client: Windows 7
 */
auto CBadgeNotificationManager::UngroupTaskbar() -> void
{
	wchar_t app_id[64];
	swprintf(app_id, sizeof(app_id), L"Metin2ClientPID%u", GetCurrentProcessId());
	if (SUCCEEDED(SetCurrentProcessExplicitAppUserModelID(app_id)))
		m_isWindowsCompatible = true;
}

/**
 * \brief Load all resources and create only one object on the local system for m_pkTaskBar.
 * \return bool
 */
auto CBadgeNotificationManager::Create() -> bool
{
	if (!m_isWindowsCompatible)
		return true;

	auto badge_id = 1;
	for (auto resource_id = IDI_BADGE_1; resource_id <= IDI_BADGE_10; ++resource_id, ++badge_id)
	{
		// Converts an integer value to a resource type compatible with the resource-management functions.
		// This macro is used in @resource.h containing the name of the resource.
		const auto& icon = LoadImage(CMSWindow::GetInstance(), MAKEINTRESOURCE(resource_id), IMAGE_ICON, 32, 32, LR_DEFAULTSIZE);
		if (!icon)
			return false;

		m_BadgeNotificationMap.insert({ badge_id, static_cast<HICON__*>(icon) });
	}

	// Creates a single uninitialized object of the class associated with a specified CLSID.
	return SUCCEEDED(CoCreateInstance(CLSID_TaskbarList, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_TaskBarApp)));
}

/**
 * \brief Receive a whisper message from server, ignore the badge notification if one window is focused.
 * \param target_name string
 */
auto CBadgeNotificationManager::ReceiveWhisper(const std::string& target_name) -> void
{
	if (m_isWindowsCompatible)
	{
		static auto& app = CPythonApplication::Instance();
		static auto& chat = CPythonChat::Instance();

		CWhisper* whisper = nullptr;
		if (chat.GetWhisper(target_name.c_str(), &whisper))
		{
			if (app.IsActive() && whisper->IsRead() && GetActiveWhisperWindow())
				return;

			Flash(true);
			whisper->SetUnread();
		}

		if (m_WhisperSet.find(target_name) == m_WhisperSet.end())
		{
			m_WhisperSet.emplace(target_name);
			Update(m_WhisperSet.size());
		}
	}
}

/**
 * \brief Sets the seen the whisper when the whisper's window is OnTop or when the user opens it manually.
 * \param target_name string
 */
auto CBadgeNotificationManager::SeenWhisper(const std::string& target_name) -> void
{
	if (m_isWindowsCompatible)
	{
		static auto& chat = CPythonChat::Instance();
		chat.SetUnreadAllWhispers(target_name);

		const auto& it = m_WhisperSet.find(target_name);
		if (it != m_WhisperSet.end())
		{
			CWhisper* whisper = nullptr;
			if (chat.GetWhisper(target_name.c_str(), &whisper))
				whisper->SetRead();

			m_WhisperSet.erase(it);
			Update(m_WhisperSet.size());
		}
	}
}

/**
 * \brief Get the focused whisper window.
 * \return CWindow
 */
auto CBadgeNotificationManager::GetActiveWhisperWindow() -> const UI::CWindow*
{
	static auto& window_manager = UI::CWindowManager::Instance();
	const auto& window = window_manager.FindActiveWindow();
	return window && !strcmp(window->GetName(), "chatline") ? window : nullptr;
}

/**
 * \brief Flashes continuously the specified window until the window comes to the foreground.
 */
auto CBadgeNotificationManager::Flash(const bool isShow) -> void
{
	static auto& app = CPythonApplication::Instance();
	if (isShow && app.IsActive())
		return;
	
	FLASHWINFO info;
	ZeroMemory(&info, sizeof(info));
	info.cbSize = sizeof(info);
	info.hwnd = app.GetWindowHandle();
	info.dwFlags = isShow ? FLASHW_CAPTION | FLASHW_TRAY | FLASHW_TIMERNOFG : FLASHW_STOP;
	if (isShow)
		info.uCount = BADGE_NOTIFICATION_FLASH_COUNT;

	FlashWindowEx(&info);
}

/**
 * \brief Sent when a window belonging to a different application than the active window is about to be activated.
 * The message is sent to the application whose window is being activated and to the
 * application whose window is being deactivated.
 */
auto CBadgeNotificationManager::ActivateApp() -> void
{
	if (m_isWindowsCompatible)
	{
		const auto& window = GetActiveWhisperWindow();
		if (window)
			SeenWhisper(window->GetWhisperTargetName());
	}
}

/**
 * \brief Get the handle icon based on badge count.
 * badge_count [0] -> no badge
 * badge_count [1-9] -> badge_[1-9].ico
 * badge_count [9+] -> badge_limit.ico
 * \param badge_count uint16_t
 * \return HICON
 */
auto CBadgeNotificationManager::GetIcon(const std::uint16_t badge_count) const -> HICON__*
{
	const auto& it = m_BadgeNotificationMap.find(badge_count);
	return it != m_BadgeNotificationMap.end() ? it->second : nullptr;
}

/**
 * \brief Applies an overlay to the taskbar button to indicate an application status or a notification to the user.
 * Allowing dynamic updates for many activities implemented, by sending directly the count calculated from different vectors.
 * Ex: Update(m_WhisperSet.size() + m_AnotherActivityVec.size() + [...]);
 * \param badge_count uint16_t
 */
auto CBadgeNotificationManager::Update(const std::uint16_t badge_count) const -> void
{
	if (!m_TaskBarApp)
		return;

	static auto& app = CPythonApplication::Instance();
	m_TaskBarApp->SetOverlayIcon(app.GetWindowHandle(), GetIcon(badge_count <= BADGE_NOTIFICATION_MAX_NUM ? badge_count : BADGE_NOTIFICATION_MAX_NUM + 1), nullptr);
}

/**
 * \brief Called when switching the character instance or disconnecting from the server.
 */
auto CBadgeNotificationManager::Reset() -> void
{
	if (m_isWindowsCompatible)
	{
		if (!m_WhisperSet.empty())
		{
			Update(0);
			Flash(false);
		}
		m_WhisperSet.clear();
	}
}

/**
 * \brief Called when the singleton is initialized.
 */
auto CBadgeNotificationManager::Initialize() -> void
{
	m_TaskBarApp = nullptr;
	m_BadgeNotificationMap.clear();
	m_WhisperSet.clear();
}

/**
 * \brief Called when the singleton is destroyed.
 */
auto CBadgeNotificationManager::Destroy() -> void
{
	for (const auto& it : m_BadgeNotificationMap)
		DestroyIcon(it.second);

	Initialize();
}
#endif