// ToolStepDemo.h : main header file for the ToolStepDemo DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CToolStepDemoApp
// See ToolStepDemo.cpp for the implementation of this class
//

class CToolStepDemoApp : public CWinApp
{
public:
	CToolStepDemoApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
