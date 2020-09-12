//1.1) Search for:
		void Render(float fx, float fy);
//1.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
		void SetRead() { m_isRead = true; }
		void SetUnread() { m_isRead = false; }
		bool IsRead() const { return m_isRead; }
#endif

//2.1) Search for:
		float m_fcurPosition;
//2.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
		bool m_isRead;
#endif

//3.1) Search for:
		void InitWhisper(PyObject * ppyObject);
//3.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
		void SetUnreadAllWhispers(const std::string& target_name) const;
#endif