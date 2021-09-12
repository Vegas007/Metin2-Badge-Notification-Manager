
# Metin2 Badge Notification Manager
 Badge notifications based on activity.
 
https://www.youtube.com/watch?v=1wjsp6gdp-Y
------------

###### 1. Compatibility
Most of you know that for applying a badge to the parent icon we need to have the application ungrouped.
So, basically for this we need to use Win32 API -> SetCurrentProcessExplicitAppUserModelID, which must be called during application initial startup routine, before presents any UI, basically in the initialization of singleton class would be fine.

Before doing the ungroup of taskbar, we've to check the operating system version, since there're many players in metin2 who still using XP/Vista and this feature is working since Windows 7+. So there's a function called IsWindowsCompatibleVersion which check if the version is at least Windows7 then trying to doing the ungroup and if successful then set a variable m_isWindowsCompatible to true, so we can check later other functions with it, that means the feature will be totally disabled for those who aren't compatible.

### 2. Cache features
When the application is created it's loading all resources and create only one object on the local system for taskbar interface.
### 3. Features
###### - Show badges on taskbar (ON/OFF)  Show badges on taskbar (ON/OFF) 
![](https://i.gyazo.com/7a2ae99f4822e5b3f8905465aa422e12.gif)
###### - Flash notification + badge
![](https://i.gyazo.com/1dd5c802ab6dbcf197923baa593084c2.gif)
###### - Counted flashes, using small taskbar icons + badge option
![](https://i.gyazo.com/5d59d75aa8cd5e6fa36826e4e2b09624.gif)

### 4. Activity
**Free version:**

> **Whisper messages**
There are many scenarios related about application active, whisper windoow opened and focused +++.

**Premium version:**

> **Exchange**
> -   When an exchange window is opened.
> 
> **Fishing**
> 
> -   When you catch a fish.
> 
> **Big notice**
> -   When the staff makes a big notice announcement.
> 
> **Duel request**
> -   When a player sends a duel request.
> 
> **Friend request**
> -   When you receive a friend request.
> -   Added multi friend request as well. [(Click here)](https://www.vegas-projects.com/wp-content/uploads/2021/07/multi_friend_add.mp4)
> 
> **Party/Guild/Guild war request**
> -   When you receive a request.
> 
> #### **Settings**
> -   You can add how many activities you want.
> -   Play a sound specified by the given file name, resource, or system event, the sound is played asynchronously.
> -   Available a python module that you can use where you want just by calling:
> 
> `import badge badge.Notification(badge.ACTIVITY_OFFLINESHOP_SEEN,
> True)`
> 
> **Free support and custom changes.**
> [Click here!](https://www.vegas-projects.com/product/badge-notification-manager)
## Author:
[@VegaS](https://metin2.dev/board/profile/22505-vegas™/ "@VegaS")
## Contributors
| name  | contribution  |
| ------------ | ------------ |
| arves100  | testing  |
| metin2team  | image icons pack  |
| masodikbela  | future ideas  |
