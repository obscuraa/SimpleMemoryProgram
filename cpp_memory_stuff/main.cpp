#include <iostream>
#include <Windows.h>

using namespace std;

int main() {
	int read_mem_value = 0;
	int mem_value = 3000;
	int mem_value2 = 100;

	HWND hwnd = FindWindowA(NULL, "Fallout: New Vegas"); //Name of an .exe file as a second parameter.

	if (hwnd == NULL) {
		cout << "Window not found.";
		Sleep(5000);
		exit(-1);
	}
	else {
		DWORD processID;
		GetWindowThreadProcessId(hwnd, &processID);

		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);

		if (processID == NULL) {
			cout << "Process ID is not found";
			Sleep(5000);
			exit(-1);
		}
		else {
			ReadProcessMemory(handle, (LPVOID)0x0B14C10C, &read_mem_value, sizeof(int), NULL); //I've used memory editor to find an address of memory.
			cout << read_mem_value;
			WriteProcessMemory(handle, (LPVOID)0x0B14C10C, &mem_value, sizeof(int), NULL);
			for (;;) {
				if (GetAsyncKeyState(VK_F1)) {
					WriteProcessMemory(handle, (LPVOID)0x0C0FFDB4, &mem_value2, sizeof(int), NULL);
					mem_value2++;
					cout << mem_value2;
				}
			}
		}
	}
}
