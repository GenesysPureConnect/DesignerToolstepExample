using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ToolStepDemoDotNetLibrary
{
    public class Demo
    {
        //simple addition

        public int add(int a, string b)
        {
            int op2;
            if (int.TryParse(b, out op2))
            {
                return a + op2;
            }
            throw new Exception("Unable to convert string to integer");
        }

        //more fun with strings

        public string updateLog(string log, string newMessage)
        {
           
            return String.Format("{0:MMddyy hhmmss}:  {1}\n{2}", DateTime.Now, newMessage, log);
        }

        //How about a stock quote?

        public string getStockQuote(string symbol)
        {
            try
            {
                var x = new stockQuote.StockQuoteSoapClient();
                return x.GetQuote("ININ");
            }
            catch (Exception ex)
            {
                return ex.Message;
            }
        }

    }
}
