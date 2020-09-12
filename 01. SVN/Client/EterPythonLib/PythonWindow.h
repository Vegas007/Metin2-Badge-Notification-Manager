//1.1) Search for:
			std::string			m_strName;
//1.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
			std::string			m_whisperTargetName;
#endif

//2.2) Search for:
			void			Render();
//2.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
			void SetWhisperTargetName(const std::string& target_name)
			{
				m_whisperTargetName = target_name;
			};
			
			const std::string& GetWhisperTargetName() const
			{
				return m_whisperTargetName;
			}
#endif