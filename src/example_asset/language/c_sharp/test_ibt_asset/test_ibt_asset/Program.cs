using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Runtime.InteropServices; // 用 DllImport 需用此 命名空间
using System.Reflection; // 使用 Assembly 类需用此 命名空间
using System.Reflection.Emit;
using System.Threading; // 使用 ILGenerator 需用此 命名空间

namespace test_ibt_asset
{
    [StructLayout(LayoutKind.Sequential,CharSet = CharSet.Ansi)]
    public struct IBTPosition 
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 11)]
        public string BrokerID; // 经纪公司代码
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 13)]
        public string InvestorID; // 投资者代码
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 31)]
        public string InstrumentID; // 合约代码
        
        public int Position; //总持仓 多头 > 0, 空头 < 0
        public int YdPosition; //昨日持仓 多头 > 0, 空头 < 0
        public int TodayPosition; //今日持仓 多头 > 0, 空头 < 0

        public double OpenPrice; //开仓均价
        public double PositionPrice; //持仓均价
        public double LastPrice; //最新价
        public double YdPositionProfit; //浮动盈亏
        public double PositionProfit; //持仓盈亏
        public double UseMargin; //占用的保证金
        public double Commission; //佣金	
    };

    //帐户汇总
    [StructLayout(LayoutKind.Sequential,CharSet = CharSet.Ansi)]
    public struct IBTAccountSum 
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 11)]
        public string BrokerID; // 经纪公司代码
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 13)]
        public string InvestorID; // 投资者代码

        public double PreBalance; //昨日结存
        public double CloseProfit; //平仓盈亏
        public double PositionProfit; //持仓盈亏
        public double DynamicProfit; //动态权益
        public double Available; //可用资金
        public double WithdrawQuota; //可取资金
        public double CurrMargin; //持仓保证金
        public double FrozenCash; //冻结的资金
        public double Deposit; //入金金额
        public double Withdraw; //出金金额
        public double Commission; //佣金
        public double Risk; //风险
    };

    class Program
    {
        [DllImport("libibt_client_ex.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        static extern int ibt_send_order(int Policy_ID, int BuyOrSell, int EntryOrExit, int Lot);
        [DllImport("libibt_client_ex.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        static extern void ibt_debug(string p_text);
        [DllImport("libibt_client_ex.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        static extern void ibt_info(string p_text);
        [DllImport("libibt_client_ex.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        static extern void ibt_error(string p_text);
        [DllImport("libibt_asset.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        static extern int ibt_connect(string p_server, string p_auth_id);
        [DllImport("libibt_asset.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        static extern IntPtr ibt_query_position(out int p_size,
            string p_BrokerID, string p_InvestorID,
            string p_InstrumentID,
            int PosiDirectionType);
        [DllImport("libibt_asset.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        static extern void release_position(IntPtr p_data);
        [DllImport("libibt_asset.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        static extern IntPtr ibt_query_account_sum(
	        out int p_size,string p_BrokerID, string p_InvestorID);
        [DllImport("libibt_asset.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        static extern void release_account_sum(IntPtr p_data);

        static void Main(string[] args)
        {
            ibt_info("test_ibt_asset start...");

            int i_ret = 0;

            string p_gbl_server = "localhost:7890";
            string p_gbl_auth_id = "888888";
            i_ret = ibt_connect(p_gbl_server, p_gbl_auth_id);
            if (0 != i_ret)
            {
                ibt_info("无法连接到服务器");

                return;
            }

            Thread.Sleep(1000);
            
            // 查询所有的仓位
            string p_BrokerID = null; // 经纪商ID "16377"; //
            string p_InvestorID = null; //期货帐号 "70108202"; //
            string p_InstrumentID = null; //合约ID,比如IF
            int PosiDirectionType = 0; //持仓方向 0, 1, -1

            int i_count = 1;
            int i_gbl_max_count = 0;

            string str_tip = "";
            int p_size_vect = 0;

            while (true)
            {
                //查询帐户汇总
                IntPtr p_account_sum = IntPtr.Zero;
                IntPtr p_account_sum_header = IntPtr.Zero;
                p_account_sum = ibt_query_account_sum(out p_size_vect,
                    p_BrokerID, p_InvestorID);
                int i_size_vect_account_sum = p_size_vect;
                p_account_sum_header = p_account_sum;
               
                str_tip = "帐户汇总 size = " + i_size_vect_account_sum +
                    ", i_ret=" + i_ret;
                ibt_info(str_tip);

                for (int i = 0; i < i_size_vect_account_sum; i++)
                {
                    IBTAccountSum sum_item = (IBTAccountSum)Marshal.PtrToStructure(p_account_sum, typeof(IBTAccountSum));
                    str_tip = "帐户汇总 index = " + i +
                        ", 经纪公司代码=" + sum_item.BrokerID +
                        ", 投资者代码=" + sum_item.InvestorID +
                        ", 昨日结存=" + sum_item.PreBalance +
                        ", 平仓盈亏=" + sum_item.CloseProfit +
                        ", 持仓盈亏=" + sum_item.PositionProfit +
                        ", 动态权益=" + sum_item.DynamicProfit +
                        ", 可用资金=" + sum_item.Available +
                        ", 可取资金=" + sum_item.WithdrawQuota +
                        ", 持仓保证金=" + sum_item.CurrMargin +
                        ", 冻结的资金=" + sum_item.FrozenCash +
                        ", 入金金额=" + sum_item.Deposit +
                        ", 出金金额=" + sum_item.Withdraw +
                        ", 佣金=" + sum_item.Commission +
                        ", 风险=" + sum_item.Risk;

                    ibt_info(str_tip);
                    p_account_sum = (IntPtr)(p_account_sum + Marshal.SizeOf(typeof(IBTAccountSum)));                   

                } // for (size_t i=0;i<i_size;i++)

                //记得释放，不然会有内存泄漏
                release_account_sum(p_account_sum_header);
                
                //查询仓位
                IntPtr p_position = IntPtr.Zero;
                IntPtr p_position_header = IntPtr.Zero;

                p_position = ibt_query_position(out p_size_vect,
                    p_BrokerID, p_InvestorID, p_InstrumentID, PosiDirectionType);

                p_position_header = p_position;
                int i_size_vect_position = p_size_vect;

                str_tip = "持仓统计 size = " + i_size_vect_position;
                ibt_info(str_tip);

                for (int i = 0; i < i_size_vect_position; i++)
                {                   
                    //将数据从托管对象封送到非托管内存块,该内存块开始地址为intPtr                    
                    IBTPosition item = (IBTPosition)Marshal.PtrToStructure(p_position, typeof(IBTPosition));
                   
                    str_tip = "持仓统计 index = " + i +
                        ", 经纪公司代码=" + item.BrokerID +
                        ", 投资者代码=" + item.InvestorID +
                        ", 合约代码=" + item.InstrumentID +
                        ", 总持仓=" + item.Position +
                        ", 昨日持仓=" + item.YdPosition +
                        ", 今日持仓=" + item.TodayPosition +
                        ", 开仓均价=" + item.OpenPrice +
                        ", 持仓均价=" + item.PositionPrice +
                        ", 最新价=" + item.LastPrice +
                        ", 浮动盈亏=" + item.YdPositionProfit +
                        ", 持仓盈亏=" + item.PositionProfit +
                        ", 占用的保证金=" + item.UseMargin +
                        ", 佣金=" + item.Commission;

                    ibt_info(str_tip);                   
                    p_position = (IntPtr)(p_position + Marshal.SizeOf(typeof(IBTPosition)));                   

                } // for (size_t i=0;i<i_size;i++)

                //记得释放，不然会有内存泄漏
                release_position(p_position_header);
                
                i_count++;

                //查询次数
                if (i_gbl_max_count > 0 && i_count > i_gbl_max_count)
                {
                    break;
                }

                Thread.Sleep(1000);

            } // while (true)

            //Marshal.FreeHGlobal(p_size_vect);
        } // static void Main(string[] args)
    } // class Program
}
