//1.1) Search for:
		CPythonTextTail::Instance().Initialize();
//1.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
		if (!m_BadgeNotificationManager.Create())
		{
			TraceError("CBadgeNotificationManager::Create - FAILURE");
			return false;
		}
#endif

//2.1) Search for:
	m_LightManager.Destroy();
//2.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
	m_BadgeNotificationManager.Destroy();
#endif