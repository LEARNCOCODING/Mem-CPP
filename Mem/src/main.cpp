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

	std::cout << "���μ��� �ڵ�: " << processHandle << std::endl;
	std::cout << "���μ��� ���̵�: " << processId << std::endl;
	std::cout << "��⺣�̽��ּ�: " << dwBaseModuleAddress << std::endl;

	return 0;
}