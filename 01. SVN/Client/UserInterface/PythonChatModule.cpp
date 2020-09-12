//1.1) Search for:
#include "PythonItem.h"
//1.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
	#include "../EterPythonLib/PythonWindow.h"
	#include "BadgeNotificationManager.h"
#endif

//2.1) Search for:
	CPythonChat::Instance().CreateWhisper(szName);
//2.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
	int window_handle;
	PyTuple_GetInteger(poArgs, 1, &window_handle);

	const auto& window = reinterpret_cast<UI::CWindow*>(window_handle);
	if (window)
		window->SetWhisperTargetName(szName);
	
	static auto& badge_notification_manager = CBadgeNotificationManager::Instance();
	badge_notification_manager.SeenWhisper(szName);
#endif

//3.1) Search for:
PyObject * chatInitWhisper(PyObject* poSelf, PyObject* poArgs)
{
	[...]
}
//3.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
auto chatSeenWhisper(PyObject* poSelf, PyObject* poArgs) -> PyObject *
{
	char* target_name;
	PyTuple_GetString(poArgs, 0, &target_name);
	
	static auto& badge_notification_manager = CBadgeNotificationManager::Instance();
	badge_notification_manager.SeenWhisper(target_name);
	return Py_BuildNone();
}
#endif

//4.1) Search for:
		{ "InitWhisper",			chatInitWhisper,			METH_VARARGS },
//4.2) Add after:
#if defined(ENABLE_BADGE_NOTIFICATION_MANAGER)
		{ "SeenWhisper",			chatSeenWhisper,			METH_VARARGS },
#endif