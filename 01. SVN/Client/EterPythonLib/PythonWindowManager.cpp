//1.1) Search for:
	void CWindowManager::GetMousePosition(long & rx, long & ry)
	{
		rx = m_lMouseX;
		ry = m_lMouseY;
	}
//1.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
	CWindow * CWindowManager::FindActiveWindow() const
	{
		return m_pActiveWindow;
	}
#endif