
#include <thread>

#if __linux__
  #include <X11/Xlib.h>
  #include <X11/extensions/XTest.h>
  #include <X11/keysym.h>
  #include <X11/XKBlib.h>
  #include <cstdlib>
#else
  #include <Windows.h>
#endif

enum {
#ifdef __linux__
	caplock = XK_Caps_Lock,
	numlock = XK_Num_Lock,
	scrolllock = XK_Scroll_Lock,
#else
	caplock = 0x14,
	numlock = 0x90,
	scrolllock = 0x91,
#endif
};


#ifdef __linux__
Display* g_DISPLAY;
#endif


bool is_key_active(int key) {
#ifdef __linux__

	XkbStateRec state{};
	XkbGetState(g_DISPLAY, XkbUseCoreKbd, &state);

	if (key == XK_Caps_Lock)
        return state.locked_mods & LockMask;
    if (key == XK_Num_Lock)
        return state.locked_mods & Mod2Mask;
    if (key == XK_Scroll_Lock)
        return state.locked_mods & Mod3Mask;

    return false;

#else
	return GetKeyState(key)
#endif
}


void simulate_key_press(int key) {

#ifdef __linux__
	KeyCode code = XKeysymToKeycode(g_DISPLAY, key);
	XTestFakeKeyEvent(g_DISPLAY, code, True,  0);
    XTestFakeKeyEvent(g_DISPLAY, code, False, 0);
    XFlush(g_DISPLAY);
#else
	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.wVk = key;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
#endif
}


void set_key_status(int key, short targetValue = 0) {
	if (is_key_active(key) != targetValue) {
		simulate_key_press(key);
	}
}


void hide_console() {
#ifdef __linux__
#else
	std::this_thread::sleep_for(std::chrono::seconds(3));
	FreeConsole();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
}


int main() {

	hide_console();

#ifdef __linux__
	g_DISPLAY = XOpenDisplay(nullptr);
    if (!g_DISPLAY) {
		exit(1);
	}
#endif
	
	while (true) { 
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		set_key_status(numlock, 1);
		set_key_status(caplock, 0);
		set_key_status(scrolllock, 0);
	}

}
