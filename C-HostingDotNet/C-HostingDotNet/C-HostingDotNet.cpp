// C-HostingDotNet.cpp : main project file.

#include "stdafx.h"
#include "stdio.h"

#include <metahost.h>
#pragma comment(lib, "mscoree.lib")

using namespace System;



void StartRunTime(void );
void LoadCsharpDllIntoRunTime();
void CallReverseMethodInCsharpDllIntoRunTime(char * str, char * messageOut);

void CleanUp();

ICLRRuntimeHost* GetRuntimeHost(LPCWSTR dotNetVersion);
int ExecuteClrCode(ICLRRuntimeHost* host, LPCWSTR assemblyPath, LPCWSTR typeName,
	LPCWSTR function, LPCWSTR param);


ICLRMetaHost       *pMetaHost = NULL;
ICLRMetaHostPolicy *pMetaHostPolicy = NULL;
ICLRDebugging      *pCLRDebugging = NULL;


int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Hello World");
	StartRunTime();
	LoadCsharpDllIntoRunTime();

	char messageIn[] = "This string is to be reversed.";


	char * messageOut;
	CallReverseMethodInCsharpDllIntoRunTime(messageIn,messageOut);
	printf(messageIn);

	if (messageOut != NULL)
	{
		printf(messageOut);
	}
	
	Console::ReadKey();
    return 0;
}



void StartRunTime()
{

	Console::Write(L"Starting RunTime: ");


/*
	
	HRESULT hr;
	hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost,
		(LPVOID*)&pMetaHost);
	hr = CLRCreateInstance(CLSID_CLRMetaHostPolicy, IID_ICLRMetaHostPolicy,
		(LPVOID*)&pMetaHostPolicy);
	hr = CLRCreateInstance(CLSID_CLRDebugging, IID_ICLRDebugging,
		(LPVOID*)&pCLRDebugging);



	pMetaHost->GetRuntime(pszVersion, IID_PPV_ARGS(&pRuntimeInfo));*/







	Console::ForegroundColor = ConsoleColor::Red;
	
	Console::WriteLine(L"FAil");

	Console::ResetColor();

}


void LoadCsharpDllIntoRunTime()
{

	Console::Write(L"Loading C# Dll Into RunTime: ");
	Console::ForegroundColor = ConsoleColor::Red;

	Console::WriteLine(L"FAil");

	Console::ResetColor();

}

void CallReverseMethodInCsharpDllIntoRunTime(char *  message, char *  messageOut)
{

	Console::Write(L"Calling Reverse method in the  C# Dll Into RunTime: ");

	Console::ForegroundColor = ConsoleColor::Red;

	Console::WriteLine(L"FAil");

	Console::ResetColor();

	
}

void CleanUp()
{
	Console::Write(L"Cleaning up: ");

	Console::ForegroundColor = ConsoleColor::Red;

	Console::WriteLine(L"FAil");

	Console::ResetColor();

}


/// <summary>
/// Executes some code in the CLR. The function must have the signature: public static int Function(string param)
/// </summary>
/// <param name="host">A started instance of the CLR</param>
/// <param name="assemblyPath">The full path to your compiled code file.
/// i.e. "C:\MyProject\MyCode.dll"</param>
/// <param name="typeName">The full type name of the class to be called, including the
/// namespace. i.e. "MyCode.MyClass"</param>
/// <param name="function">The name of the function to be called. i.e. "MyFunction"</param>
/// <param name="param">A string parameter to pass to the function.</param>
/// <returns>The integer return code from the function or -1 if the function did not run</returns>
int ExecuteClrCode(ICLRRuntimeHost* host, LPCWSTR assemblyPath, LPCWSTR typeName,
	LPCWSTR function, LPCWSTR param)
{
	if (NULL == host)
		return -1;

	DWORD result = -1;
	if (S_OK != host->ExecuteInDefaultAppDomain(assemblyPath, typeName, function, param, &result))
		return -1;

	return result;
}



/// <summary>
/// Returns a pointer to a running CLR host of the specified version
/// </summary>
/// <param name="dotNetVersion">The exact version number of the CLR you want to
/// run. This can be obtained by looking in the C:\Windows\Microsoft.NET\Framework
/// directory and copy the name of the last directory.</param>
/// <returns>A running CLR host or NULL. You are responsible for calling Release() on it.</returns>
ICLRRuntimeHost* GetRuntimeHost(LPCWSTR dotNetVersion)
{
	ICLRMetaHost* metaHost = NULL;
	ICLRRuntimeInfo* info = NULL;
	ICLRRuntimeHost* runtimeHost = NULL;

	// Get the CLRMetaHost that tells us about .NET on this machine
	if (S_OK == CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, (LPVOID*)&metaHost))
	{
		// Get the runtime information for the particular version of .NET
		if (S_OK == metaHost->GetRuntime(dotNetVersion, IID_ICLRRuntimeInfo, (LPVOID*)&info))
		{
			// Get the actual host
			if (S_OK == info->GetInterface(CLSID_CLRRuntimeHost, IID_ICLRRuntimeHost, (LPVOID*)&runtimeHost))
			{
				// Start it. This is okay to call even if the CLR is already running
				runtimeHost->Start();
			}
		}
	}
	if (NULL != info)
		info->Release();
	if (NULL != metaHost)
		metaHost->Release();

	return runtimeHost;
}
