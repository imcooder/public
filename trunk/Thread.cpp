
#include "StdAfx.h"
#include "Thread.h"
#include <assert.h>
#include <tlhelp32.h>
#include <Winternl.h>
//#include <winnt.h>

BOOL ListProcessThreads( DWORD dwOwnerPID ) 
{ 
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE; 
	THREADENTRY32 te32; 

	// Take a snapshot of all running threads  
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0); 
	if( hThreadSnap == INVALID_HANDLE_VALUE ) 
	{
		return FALSE; 
	}

	// Fill in the size of the structure before using it. 
	te32.dwSize = sizeof(THREADENTRY32 ); 

	// Retrieve information about the first thread,
	// and exit if unsuccessful
	if( !Thread32First( hThreadSnap, &te32 ) ) 
	{		
		CloseHandle( hThreadSnap );			// Must clean up the		
		return FALSE;
	}
	// Now walk the thread list of the system,
	// and display information about each thread
	// associated with the specified process
	do 
	{ 
		if( te32.th32OwnerProcessID == dwOwnerPID )
		{
			//printf( "\n\n     THREAD ID      = 0x%08X",	te32.th32ThreadID ); 
			//printf( "\n     base priority  = %d", te32.tpBasePri ); 
			//printf( "\n     delta priority = %d", te32.tpDeltaPri ); 
		}
	} 
	while( Thread32Next(hThreadSnap, &te32 ) ); 

	//  Don't forget to clean up the snapshot object.
	CloseHandle( hThreadSnap );
	return TRUE;
}
typedef struct _CLIENT_ID
{
	DWORD UniqueProcess; 
	DWORD UniqueThread;
} CLIENT_ID, *PCLIENT_ID;
typedef LONG NTSTATUS;
#define STATUS_SUCCESS ((NTSTATUS) 0x00000000)

typedef LONG KPRIORITY;
typedef struct _THREAD_BASIC_INFORMATION
{
	NTSTATUS   ExitStatus;
	PVOID      TebBaseAddress;
	CLIENT_ID  ClientId;
	KAFFINITY  AffinityMask;
	KPRIORITY  Priority;
	KPRIORITY  BasePriority;
} THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;

/*

DWORD WINAPI GetThreadID( HANDLE hThread )
{
	DWORD dwThreadId = 0;
#if (WINVER >= 0x0600)	
	{
		dwThreadId = ::GetThreadId(hThread);
	}
#else
	{
		HMODULE hModule = NULL;
		if (!(hModule=LoadLibrary(TEXT("ntdll.dll"))))
		{
			return 0;
		}
		//È¡º¯ÊýµØÖ·
		typedef __kernel_entry NTSTATUS	(*LPNtQueryInformationThread)(IN HANDLE,IN THREADINFOCLASS,OUT PVOID,	IN ULONG,	OUT PULONG OPTIONAL	);
		LPNtQueryInformationThread pQueryInfo = (LPNtQueryInformationThread) GetProcAddress(hModule, "NtQueryInformationThread");


		HANDLE hProcess = GetCurrentProcess();
		if (!hProcess)
		{
			return 0;
		}
		THREAD_BASIC_INFORMATION tbi;
		if (STATUS_SUCCESS == pQueryInfo(hThread, (THREADINFOCLASS)0, &tbi, sizeof(tbi), NULL))
		{
			dwThreadId = tbi.ClientId.UniqueThread;	
		}
		FreeLibrary(hModule);
		hModule = NULL;
	}
#endif
	return dwThreadId;
}

*/
