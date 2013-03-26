using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Runtime.InteropServices; // 用 DllImport 需用此 命名空间
using System.Reflection; // 使用 Assembly 类需用此 命名空间
using System.Reflection.Emit; // 使用 ILGenerator 需用此 命名空间

namespace test_ibt_client
{
    class Program
    {
        [DllImport("libibt_client_ex.dll")]
        static extern int ibt_send_order(int Policy_ID,int BuyOrSell,int EntryOrExit,int Lot);
        [DllImport("libibt_client_ex.dll")]
        static extern void ibt_debug(string p_text);
        [DllImport("libibt_client_ex.dll")]
        static extern void ibt_info(string p_text);
        [DllImport("libibt_client_ex.dll")]
        static extern void ibt_error(string p_text);
        

        static void Main(string[] args)
        {
            ibt_debug("test_send_order start...");

	        int i_ret = 0;
	        //发送开仓命令
	        int Policy_ID = 26;
	        // 买入开仓
	        /*int BuyOrSell = IBT_Enum_Buy;
	        int EntryOrExit = IBT_Enum_Entry;
	        int Lot = 1;*/

	        // 卖出平仓
            const int IBT_Enum_Sell = 1;
            const int IBT_Enum_ExitToday = 2;

	        int BuyOrSell = IBT_Enum_Sell;
	        int EntryOrExit = IBT_Enum_ExitToday;
	        int Lot = 0;

	        i_ret = ibt_send_order(Policy_ID,BuyOrSell,EntryOrExit,Lot);
	        if (0 != i_ret)
	        {
		        ibt_error("破冰号客户端发送命令失败！");
	        }   
	        else
	        {
		        ibt_info("破冰号客户端发送命令成功！");
	        }

	        ibt_debug("test_send_order end.");
        }
    }
}
