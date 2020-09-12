//1.1) Search for:
		HINSTANCE GetInstance();
//1.2) Replace with:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
		static HINSTANCE GetInstance();
#else
		HINSTANCE GetInstance();
#endif