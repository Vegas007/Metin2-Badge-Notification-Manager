//1.1) Search for:
BOOL CPythonChat::GetWhisper(const char * c_szName, CWhisper ** ppWhisper)
{
	[...]
}
//1.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
void CPythonChat::SetUnreadAllWhispers(const std::string& target_name) const
{
	for (const auto& whisper: m_WhisperMap)
	{
		if (whisper.first == target_name || !whisper.second->IsRead())
			continue;

		whisper.second->SetUnread();
	}
}
#endif

//2.1) Search for:
	m_fcurPosition = 1.0f;
//2.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
	m_isRead = false;
#endif