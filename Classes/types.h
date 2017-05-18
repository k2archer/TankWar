
#ifndef __TYPES__H__
#define __TYPES__H__

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <windows.h>
#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)
#define KEY_UP(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1)
#endif

enum { PLAYER_START_TAG = 100,  ENEMY_START_TAG = 102, PLAYER_NUM = 2, ENEMY_NUM = 4 };

enum { VK_W = 87, VK_S = 83, VK_A = 65, VK_D =68, VK_K = 75 };

enum DIRECTION { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };
enum { K_LCONTROL = 0, K_UP = 1, K_DOWN = 2, K_LEFT = 3, K_RIGHT = 4 };

enum OWNER { PLAYER = 0, ENEMY = 1 };

#endif // __TYPES__H__
