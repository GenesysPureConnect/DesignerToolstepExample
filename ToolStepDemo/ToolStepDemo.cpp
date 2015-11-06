// ToolStepDemo.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "ToolStepDemo.h"
#include "inc\javadll.h"
#include "Utilities.h"
#include <msclr\auto_gcroot.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
using namespace System;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CToolStepDemoApp

BEGIN_MESSAGE_MAP(CToolStepDemoApp, CWinApp)
END_MESSAGE_MAP()


extern "C" {

	//----------------------------------------------------------------------------
	//Let's get crazy and add an int to a string
	//We'll return an int
	//If the string won't convert to an int, we'll return 1
	//If there is a general failure, we'll return 2
	//Success (output is set) we'll return 3
	//No method to the madness and this is obviously a contrived example, but 
	//it illustrates working with strings, which is the hardest thing to do
	//----------------------------------------------------------------------------
	long __declspec(dllexport) AddValues(
		Parameter * p_paParms,
		int p_nParms
		)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		// Parameter 0: Int input operand 1			IN
		// Parameter 1: String input operand 2      IN
		// Parameter 2: Int output result			OUT

		int operand1;

		// if somehow the value wasn't specified, we'll default to
		// 0
		if (p_paParms[0].m_EmptyParameter) {
			operand1 = 0;
		}
		else {
			operand1 = p_paParms[0].m_Integer;
		}

		System::String^ operand2 = GetStringParameter(p_paParms[1]);

		ToolStepDemoDotNetLibrary::Demo ^dotnet = gcnew ToolStepDemoDotNetLibrary::Demo();
		
		//we can catch .net exceptions in c++ -- probably best to do it in .net, but it is kind of cool
		try
		{
			int result = dotnet->add(operand1, operand2);

			if (p_paParms[2].m_ParameterType == I3Integer)
			{
				p_paParms[2].m_Integer = result;
				//it worked!!!!
				return 3;
			}
		}
		catch (System::Exception^)  //this is a .net exception
		{
			//the only exception is if we can't convert string to int
			return 1;
		}
		catch (...) //any exception
		{
			//silently eat any c++ exceptions
		}

		//something went wrong
		return 2;
	}

	//----------------------------------------------------------------------------
	//Now we'll show updating a string like we are logging something
	//We'll only have 1 output and we'll use exit code of 1
	//----------------------------------------------------------------------------
	long __declspec(dllexport) updateLog(
		Parameter * p_paParms,
		int p_nParms
		)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		// Parameter 0: String in/out current log	IN/OUT
		// Parameter 1: String input message to add IN
		
		System::String^ log = GetStringParameter(p_paParms[0]);
		
		System::String^ message = GetStringParameter(p_paParms[1]);

		ToolStepDemoDotNetLibrary::Demo ^dotnet = gcnew ToolStepDemoDotNetLibrary::Demo();

		try
		{
			SetStringParameter(p_paParms[0], dotnet->updateLog(log, message));
			return 1;
		}
		catch (...) //any exception
		{
			//silently eat any c++ exceptions
		}

		return 1;
	}

}





// CToolStepDemoApp construction

CToolStepDemoApp::CToolStepDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CToolStepDemoApp object

CToolStepDemoApp theApp;


// CToolStepDemoApp initialization

BOOL CToolStepDemoApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
