#1.1) Search for:
	def OnTop(self):
		self.chatLine.SetFocus()
#1.2) Add after:
		if app.ENABLE_BADGE_NOTIFICATION_MANAGER:
			if self.targetName:
				chat.SeenWhisper(self.targetName)
				
#2.1) Search for:
		chat.CreateWhisper(targetName)
#2.2) Replace with:
		if app.ENABLE_BADGE_NOTIFICATION_MANAGER:
			if targetName != None:
				chat.CreateWhisper(targetName, self.chatLine.hWnd)
		else:
			chat.CreateWhisper(targetName)