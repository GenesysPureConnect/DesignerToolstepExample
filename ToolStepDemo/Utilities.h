
#include "stdafx.h"
#include "ToolStepDemo.h"
#include "inc\javadll.h"
#include <string>
using namespace std;
using namespace System;

void MarshalString(String ^ s, string& os);

String^ GetStringParameter(Parameter &p_paParm);

void SetStringParameter(Parameter &p_paParm, String^ newValue);

