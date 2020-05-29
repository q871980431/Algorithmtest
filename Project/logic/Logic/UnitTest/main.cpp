/*
 * File:	main.cpp
 * Author:	XuPing
 * 
 * Created On 2019/5/16 16:19:20
 */

#include "UnitTest.h"

//static IModule * g_module = nullptr; 
//class factroyUnitTest
//{
//public:
//	factroyUnitTest(IModule *&module)
//	{
//		IModule *tmp = new UnitTest();
//		tmp->SetName("UnitTest");
//		tmp->SetNext(module);
//		module = tmp;
//	}
//};
//extern "C" __declspec(dllexport) IModule * __cdecl GET_LOGIC_FUN() { 
//	factroyUnitTest temp(g_module);
//	return g_module; 
//}
//BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lovReserved) { return TRUE; }
//
GET_DLL_ENTRANCE;
CREATE_MODULE(UnitTest);