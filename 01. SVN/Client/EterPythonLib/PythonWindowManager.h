//1.1) Search for:
			void		SetPickAlways(CWindow * pWindow);
//1.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
			CWindow * 	FindActiveWindow() const;
#endif