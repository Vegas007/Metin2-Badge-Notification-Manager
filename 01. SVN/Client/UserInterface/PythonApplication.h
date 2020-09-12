//1.1) Search for:
#include "MovieMan.h"
//1.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
	#include "BadgeNotificationManager.h"
#endif

//2.1) Search for:
		CPythonSystem				m_pySystem;
//2.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
		CBadgeNotificationManager 	m_BadgeNotificationManager;
#endif