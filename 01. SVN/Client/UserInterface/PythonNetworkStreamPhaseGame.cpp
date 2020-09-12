//1.1) Search for:
#include "InstanceBase.h"
//1.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
	#include "BadgeNotificationManager.h"
#endif

//2.1) Search for:
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnRecvWhisper", Py_BuildValue("(iss)", (int) whisperPacket.bType, whisperPacket.szNameFrom, line));
//2.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
		static auto& badge_notification_manager = CBadgeNotificationManager::Instance();
		badge_notification_manager.ReceiveWhisper(whisperPacket.szNameFrom);
#endif