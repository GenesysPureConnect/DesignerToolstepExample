using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ToolStepDemoDesignerDefinition
{
    public class ToolstepDefinition : ININ.Interop.IDTypeLib.II3IDToolSetAddOn
    {
        public void Initialize(ININ.Interop.IDTypeLib.II3ID Designer)
        {
            //throw new NotImplementedException();
        }

        public void InitializeEnvironment(ININ.Interop.IDTypeLib.II3ID Designer)
        {
            //throw new NotImplementedException();
        }

        public void InitializeTools(ININ.Interop.IDTypeLib.II3ID Designer)
        {
            var IntegerTypeSpecifier = "::" + Designer.QueryNativeTypeName(ININ.Interop.IDTypeLib.I3IDNativeDataType.ID_INTEGER);
            var StringTypeSpecifier = "::" + Designer.QueryNativeTypeName(ININ.Interop.IDTypeLib.I3IDNativeDataType.ID_STRING);

            ININ.Interop.IDTypeLib.II3IDTool AddValues;

            AddValues = Designer.Tools.RegisterTool(
                null,                                                       //event sink - it gets called when it is created? see API guide
                "TSD - Add Values",                                         //Label
                "ToolStepDemo",                                             //ToolModuleName 
                "TSD_Add",                                                  //Toolname - this should probably be unique
                "Implements adding a string to an integer",                 //Description
                "Tool Step Demo",                                           //Tool Category
                "ToolStepDemo",                                             //DLL Name
                "AddValues",                                                //Function name (in above DLL)
                3                                                           //number of parameters
                );

            AddValues.ParameterDefinitions.Item(0).SetAsInputComboBox(IntegerTypeSpecifier, "Operand 1", true);
            AddValues.ParameterDefinitions.Item(1).SetAsInputComboBox(StringTypeSpecifier, "Operand 2", true);
            AddValues.ParameterDefinitions.Item(2).SetAsOutput(IntegerTypeSpecifier, "Result", true);

            AddValues.ExitPaths.Add("Success", 3, false);
            AddValues.ExitPaths.Add("Convert Error", 1, true);
            AddValues.ExitPaths.Add("Failure", 2, true);

            AddValues.Commit();


            ININ.Interop.IDTypeLib.II3IDTool UpdateLog;

            UpdateLog = Designer.Tools.RegisterTool(
                null,                                                       //event sink - it gets called when it is created? see API guide
                "TSD - Update Log",                                         //Label
                "ToolStepDemo",                                             //ToolModuleName 
                "TSD_UpdateLog",                                            //Toolname - this should probably be unique
                "Implements adding a log message with date/timestamp",      //Description
                "Tool Step Demo",                                           //Tool Category
                "ToolStepDemo",                                             //DLL Name
                "updateLog",                                                //Function name (in above DLL)
                2                                                           //number of parameters
                );


            UpdateLog.ParameterDefinitions.Item(0).SetAsOutput(StringTypeSpecifier, "Log", true);
            UpdateLog.ParameterDefinitions.Item(1).SetAsInputComboBox(StringTypeSpecifier, "Message", true);

            UpdateLog.ExitPaths.Add("Next", 1, false);

            UpdateLog.Commit();

            ININ.Interop.IDTypeLib.II3IDTool StockQuote;

            StockQuote = Designer.Tools.RegisterTool(
                null,                                                       //event sink - it gets called when it is created? see API guide
                "TSD - Stock Quote",                                         //Label
                "ToolStepDemo",                                             //ToolModuleName 
                "TSD_StockQuote",                                            //Toolname - this should probably be unique
                "Implements getting a stock quote via a web service",      //Description
                "Tool Step Demo",                                           //Tool Category
                "ToolStepDemo",                                             //DLL Name
                "getStockQuote",                                                //Function name (in above DLL)
                2                                                           //number of parameters
                );


            StockQuote.ParameterDefinitions.Item(0).SetAsInputComboBox(StringTypeSpecifier, "Stock Symbol", true);
            StockQuote.ParameterDefinitions.Item(1).SetAsOutput(StringTypeSpecifier, "Stock Quote", true);

            StockQuote.ExitPaths.Add("Next", 1, false);

            StockQuote.Commit();

        }

        public void InitializeTypes(ININ.Interop.IDTypeLib.II3ID Designer)
        {
            //throw new NotImplementedException();
        }

        public void ShutDown(ININ.Interop.IDTypeLib.II3ID Designer)
        {
            //throw new NotImplementedException();
        }
    }
}
