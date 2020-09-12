//1.1) Search for:
#include "PythonNetworkStream.h"
//1.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
	#include "BadgeNotificationManager.h"
#endif

//2.1) Search for:
	m_phaseLeaveFunc.Set(this, &CPythonNetworkStream::__LeaveSelectPhase);
//2.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
	static auto& badge_notification_manager = CBadgeNotificationManager::Instance();
	badge_notification_manager.Reset();
#endif