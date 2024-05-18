#include "mem.h"
#include <iostream>

int main()
{
	Mem mem{};
	HANDLE processHandle = mem.ProcessHandle("Counter-Strike 2");
	DWORD processId = mem.ProcessId();
	uintptr_t dwBaseModuleAddress = mem.GetModuleBaseAddress(processId, "client.dll");

	int ReadEx = mem.Read<int>(0x1);//ReadEx
	mem.Write<int>(0x1,10);//WriteEx

	std::cout << "프로세스 핸들: " << processHandle << std::endl;
	std::cout << "프로세스 아이디: " << processId << std::endl;
	std::cout << "모듈베이스주소: " << dwBaseModuleAddress << std::endl;

	return 0;
}