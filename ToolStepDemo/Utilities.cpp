
#include "stdafx.h"
#include "ToolStepDemo.h"
#include "inc\javadll.h"
#include <msclr\auto_gcroot.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
using namespace System;

//this converts a c# string to a c string

void MarshalString(String ^ s, string& os) {
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

//probably don't have to pass it by reference as it seems to work either way.
String^ GetStringParameter(Parameter &p_paParm){
	if (!p_paParm.m_EmptyParameter) {
		return gcnew System::String(p_paParm.m_String);
	}
	return System::String::Empty;
}

//have to pass this by reference otherwise it screws up the variables
void SetStringParameter(Parameter &p_paParm, String^ newValue){
	
	//maybe we should throw an exception here
	//scratch that!  It doesn't look like m_OutParameter does what I thought it should, namely: be set to true if this is an output parameter.  Checking 
	//this results in it returning every time for out parameters as opposed to setting them as it should 

	/*if (!p_paParm.m_OutParameter)
		return;*/
	
	pin_ptr<const wchar_t> wch = PtrToStringChars(newValue);

	int YOURSTRINGLEN = newValue->Length + 1; //don't forget the termination character (+1)

	if (p_paParm.m_String != NULL) {
		// clean up whatever was passed to you
		::free(p_paParm.m_String);
	}
	int nBytes = (YOURSTRINGLEN)* sizeof(WCHAR);
	p_paParm.m_String = (WCHAR *) ::malloc(nBytes);
	if (p_paParm.m_String != NULL) {
		::memcpy(p_paParm.m_String, wch, nBytes);
	}

}