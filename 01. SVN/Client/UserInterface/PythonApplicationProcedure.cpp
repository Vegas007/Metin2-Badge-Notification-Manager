//1.1) Search for:
#include "../eterlib/Camera.h"
//1.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
	#include "BadgeNotificationManager.h"
#endif

//2.1) Search for:
					m_SoundManager.RestoreVolume();
//2.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
					static auto& badge_notification_manager = CBadgeNotificationManager::Instance();
					badge_notification_manager.ActivateApp();
#endif