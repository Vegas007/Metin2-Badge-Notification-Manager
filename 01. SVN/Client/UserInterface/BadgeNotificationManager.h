#pragma once
#include <cstdint>
#include <unordered_map>

static const auto BADGE_NOTIFICATION_MAX_NUM = 9;
static const auto BADGE_NOTIFICATION_FLASH_COUNT = 3;

#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
class CBadgeNotificationManager : public CSingleton < CBadgeNotificationManager >
{
	public:
		CBadgeNotificationManager();
		virtual ~CBadgeNotificationManager();

		auto			Initialize() -> void;
		auto			Destroy() -> void;
		
		auto			Create() -> bool;
		auto			Reset() -> void;

		auto			ReceiveWhisper(const std::string&) -> void;
		auto			SeenWhisper(const std::string&) -> void;
		auto			ActivateApp() -> void;

	protected:
		auto			UngroupTaskbar() -> void;
		
		auto			Update(const std::uint16_t) const -> void;
		auto			GetIcon(const std::uint16_t) const -> HICON__*;

		static auto		GetActiveWhisperWindow() -> const UI::CWindow*;
		static auto		Flash(const bool) -> void;
		static auto		IsWindowsCompatibleVersion() -> bool;

	private:
		using TBadgeNotificationMap = std::unordered_map<uint8_t, HICON__*>;
		TBadgeNotificationMap	m_BadgeNotificationMap;
		std::set<std::string>	m_WhisperSet;
		bool					m_isWindowsCompatible;
};
#endif
