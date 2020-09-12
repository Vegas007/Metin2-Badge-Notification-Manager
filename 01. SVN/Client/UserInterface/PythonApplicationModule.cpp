//1.1) Search for:
	PyModule_AddIntConstant(poModule, "CAMERA_STOP",			CPythonApplication::CAMERA_STOP);
//1.2) Add after:
#ifdef ENABLE_BADGE_NOTIFICATION_MANAGER
	PyModule_AddIntConstant(poModule, "ENABLE_BADGE_NOTIFICATION_MANAGER", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_BADGE_NOTIFICATION_MANAGER", 0);
#endif