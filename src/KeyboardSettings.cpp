
#include <Windows.h>
#include <thread>

enum {
	caplock = 0x14,
	numlock = 0x90,
	scrolllock = 0x91,
	esc = 0x1B,
};

void setKey(int key, short targetValue = 0) {
	if (GetKeyState(key) != targetValue) {
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
	}
}

void backgroundOnOff(bool* run) {

	int downCounter = 0;

	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		if (GetAsyncKeyState(esc))
			downCounter++;
		else
			downCounter = 0;

		if (downCounter > 5) {
			*run = !*run;
			std::this_thread::sleep_for(std::chrono::seconds(5));
		}
	}
}

int main() {

	// hide console
	std::this_thread::sleep_for(std::chrono::seconds(5));
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	bool run = true;

	std::thread onOffThread(backgroundOnOff, &run);

	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		if (!run)
			continue;

		setKey(numlock, 1);
		setKey(caplock, 0);
		setKey(scrolllock, 0);
	}

}
