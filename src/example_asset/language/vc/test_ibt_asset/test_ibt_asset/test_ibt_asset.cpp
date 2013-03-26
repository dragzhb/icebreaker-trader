// libibt_asset_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <sstream>
#include <iostream>

#include "ibt_client.h"
#include "ibt_asset_cxx.h"

#pragma comment(lib,"libibt_client_ex.lib")
#pragma comment(lib,"libibt_asset.lib")

static void test_c_func();
static void test_cxx_func();

using namespace std;

char p_gbl_server[64];
char p_gbl_auth_id[64];
int i_gbl_max_count;

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc <= 3)
	{
		cout << "用法：" << argv[0] << " \"服务器地址\" 鉴权ID  发送条数（0-循环发）" << endl;
		cout << "举例：" << argv[0] << " \"localhost:7890\" 888888 1" << endl;
		return 0;
	}

	memset(p_gbl_server,0,sizeof(p_gbl_server));
	memset(p_gbl_auth_id,0,sizeof(p_gbl_auth_id));

	if (argc > 1)
	{
		strcpy_s(p_gbl_server,(const char*)argv[1]);
	}

	if (argc > 2)
	{
		strcpy_s(p_gbl_auth_id,(const char*)argv[2]);
	}

	if (argc > 3)
	{
		i_gbl_max_count = atoi((const char*)argv[3]);
	}

	if (i_gbl_max_count < 0)
	{
		i_gbl_max_count = 0;
	}

	bool is_test_cxx = false;

	if (is_test_cxx)
	{
		test_cxx_func();
	}
	else
	{
		test_c_func();
	}

	return 0;
}


void test_cxx_func()
{
	int i_ret = 0;
	
	//const char* p_server = "localhost:7890";
	//const char* p_auth_id = "888888";
	//ibt_debug("连接到服务器: localhost:7890");
	i_ret = ibt_connect(p_gbl_server,p_gbl_auth_id);
	if (0 != i_ret)
	{
		ibt_debug("无法连接到服务器");

		return;
	}

	//ibt_debug("连接到服务器成功...");
	Sleep(1000);

	/*const char* p_server1 = "localhost:7800";
	ibt_debug("连接到服务器: localhost:7800");
	i_ret = ibt_connect(p_server1,p_auth_id);
	if (0 != i_ret)
	{
		ibt_debug("无法连接到服务器");

		return;
	}

	Sleep(5000);*/

	std::vector<IBTPosition> vect_position;
	std::vector<IBTAccountSum> vect_account_sum;

	long l_sleep = 1000;
	// 查询所有的仓位
	const char* p_BrokerID = NULL; // 经纪商ID
	const char* p_InvestorID = NULL; //期货帐号
	const char* p_InstrumentID = NULL; //合约ID,比如IF
	int PosiDirectionType = 0; //持仓方向
	
	int i_count = 1;
	//int i_max_count = 3;
	std::stringstream str_stream;
	str_stream.precision(2);
	str_stream << std::fixed;

	while (true)
	{
		//查询
		str_stream.str("");
		str_stream << "call query cxx. index = " << i_count;				
		ibt_info(str_stream.str().c_str());		

		//查询帐户汇总
		i_ret = ibt_query_account_sum_cxx(vect_account_sum,
			p_BrokerID,p_InvestorID);
		size_t i_size_vect_account_sum = vect_account_sum.size();

		str_stream.str("");
		str_stream << "帐户汇总 size = " << i_size_vect_account_sum <<
			", i_ret=" << i_ret;				
		ibt_info(str_stream.str().c_str());

		for (size_t i=0;i<i_size_vect_account_sum;i++)
		{
			str_stream.str("");
			str_stream << "帐户汇总 index = " << i <<
				", 经纪公司代码=" << vect_account_sum[i].BrokerID <<
				", 投资者代码=" << vect_account_sum[i].InvestorID <<
				", 昨日结存=" << vect_account_sum[i].PreBalance <<
				", 平仓盈亏=" << vect_account_sum[i].CloseProfit <<
				", 持仓盈亏=" << vect_account_sum[i].PositionProfit <<
				", 动态权益=" << vect_account_sum[i].DynamicProfit <<
				", 可用资金=" << vect_account_sum[i].Available <<
				", 可取资金=" << vect_account_sum[i].WithdrawQuota <<
				", 持仓保证金=" << vect_account_sum[i].CurrMargin <<
				", 冻结的资金=" << vect_account_sum[i].FrozenCash <<
				", 入金金额=" << vect_account_sum[i].Deposit <<
				", 出金金额=" << vect_account_sum[i].Withdraw <<
				", 佣金=" << vect_account_sum[i].Commission <<
				", 风险=" << vect_account_sum[i].Risk;

			ibt_info(str_stream.str().c_str());

		} // for (size_t i=0;i<i_size;i++)

		//查询仓位
		i_ret = ibt_query_position_cxx(vect_position,
			p_BrokerID,p_InvestorID,p_InstrumentID,PosiDirectionType);

		size_t i_size_vect_position = vect_position.size();
		str_stream.str("");
		str_stream << "持仓统计 size = " << i_size_vect_position <<
			", i_ret=" << i_ret;				
		ibt_info(str_stream.str().c_str());
		
		for (size_t i=0;i<i_size_vect_position;i++)
		{
			str_stream.str("");
			str_stream << "持仓统计 index = " << i <<
				", 经纪公司代码=" << vect_position[i].BrokerID <<
				", 投资者代码=" << vect_position[i].InvestorID <<
				", 合约代码=" << vect_position[i].InstrumentID <<
				", 总持仓=" << vect_position[i].Position <<
				", 昨日持仓=" << vect_position[i].YdPosition <<
				", 今日持仓=" << vect_position[i].TodayPosition <<
				", 开仓均价=" << vect_position[i].OpenPrice <<
				", 持仓均价=" << vect_position[i].PositionPrice <<
				", 最新价=" << vect_position[i].LastPrice <<
				", 浮动盈亏=" << vect_position[i].YdPositionProfit <<
				", 持仓盈亏=" << vect_position[i].PositionProfit <<
				", 占用的保证金=" << vect_position[i].UseMargin <<
				", 佣金=" << vect_position[i].Commission;

			ibt_info(str_stream.str().c_str());

		} // for (size_t i=0;i<i_size;i++)		

		i_count++;

		if (i_gbl_max_count > 0 && i_count > i_gbl_max_count)
		{
			break;
		}

		Sleep(l_sleep);
	}
}

void test_c_func()
{
	int i_ret = 0;
	
	//const char* p_server = "localhost:7890";
	//const char* p_auth_id = "888888"; 
	//ibt_debug("连接到服务器: localhost:7890");
	i_ret = ibt_connect(p_gbl_server,p_gbl_auth_id);
	if (0 != i_ret)
	{
		ibt_debug("无法连接到服务器");

		return;
	}

	//ibt_debug("连接到服务器成功...");
	Sleep(1000);	

	long l_sleep = 1000;
	// 查询所有的仓位
	const char* p_BrokerID = NULL; // 经纪商ID "16377"; //
	const char* p_InvestorID = NULL; //期货帐号 "70108202"; //
	const char* p_InstrumentID = NULL; //合约ID,比如IF
	int PosiDirectionType = 0; //持仓方向 0, 1, -1
	
	int i_count = 1;
	//int i_max_count = 0; //控制循环次数
	std::stringstream str_stream;
	str_stream.precision(2);
	str_stream << std::fixed;
	int i_size_vect = 0;
	while (true)
	{
		//查询
		str_stream.str("");
		str_stream << "call query(c). index = " << i_count;				
		ibt_info(str_stream.str().c_str());		

		//查询帐户汇总
		IBTAccountSum* p_account_sum = NULL;
		IBTAccountSum* p_account_sum_header = NULL;
		p_account_sum = ibt_query_account_sum(&i_size_vect,
			p_BrokerID,p_InvestorID);
		int i_size_vect_account_sum = i_size_vect;
		p_account_sum_header = p_account_sum;

		str_stream.str("");
		str_stream << "帐户汇总 size = " << i_size_vect_account_sum <<
			", i_ret=" << i_ret;				
		ibt_info(str_stream.str().c_str());

		for (int i=0;i<i_size_vect_account_sum;i++)
		{
			str_stream.str("");
			str_stream << "帐户汇总 index = " << i <<
				", 经纪公司代码=" << p_account_sum->BrokerID <<
				", 投资者代码=" << p_account_sum->InvestorID <<
				", 昨日结存=" << p_account_sum->PreBalance <<
				", 平仓盈亏=" << p_account_sum->CloseProfit <<
				", 持仓盈亏=" << p_account_sum->PositionProfit <<
				", 动态权益=" << p_account_sum->DynamicProfit <<
				", 可用资金=" << p_account_sum->Available <<
				", 可取资金=" << p_account_sum->WithdrawQuota <<
				", 持仓保证金=" << p_account_sum->CurrMargin <<
				", 冻结的资金=" << p_account_sum->FrozenCash <<
				", 入金金额=" << p_account_sum->Deposit <<
				", 出金金额=" << p_account_sum->Withdraw <<
				", 佣金=" << p_account_sum->Commission <<
				", 风险=" << p_account_sum->Risk;

			ibt_info(str_stream.str().c_str());
			p_account_sum++;

		} // for (size_t i=0;i<i_size;i++)

		//记得释放，不然会有内存泄漏
		release_account_sum(p_account_sum_header);
		p_account_sum_header = NULL;

		//查询仓位
		IBTPosition* p_position = NULL;
		IBTPosition* p_position_header = NULL;
		p_position = ibt_query_position(&i_size_vect,
			p_BrokerID,p_InvestorID,p_InstrumentID,PosiDirectionType);

		p_position_header = p_position;
		int i_size_vect_position = i_size_vect;
		str_stream.str("");
		str_stream << "持仓统计 size = " << i_size_vect_position <<
			", i_ret=" << i_ret;				
		ibt_info(str_stream.str().c_str());
		
		for (int i=0;i<i_size_vect_position;i++)
		{
			str_stream.str("");
			str_stream << "持仓统计 index = " << i <<
				", 经纪公司代码=" << p_position->BrokerID <<
				", 投资者代码=" << p_position->InvestorID <<
				", 合约代码=" << p_position->InstrumentID <<
				", 总持仓=" << p_position->Position <<
				", 昨日持仓=" << p_position->YdPosition <<
				", 今日持仓=" << p_position->TodayPosition <<
				", 开仓均价=" << p_position->OpenPrice <<
				", 持仓均价=" << p_position->PositionPrice <<
				", 最新价=" << p_position->LastPrice <<
				", 浮动盈亏=" << p_position->YdPositionProfit <<
				", 持仓盈亏=" << p_position->PositionProfit <<
				", 占用的保证金=" << p_position->UseMargin <<
				", 佣金=" << p_position->Commission;

			p_position++;

			ibt_info(str_stream.str().c_str());

		} // for (size_t i=0;i<i_size;i++)		

		//记得释放，不然会有内存泄漏
		release_position(p_position_header);
		p_position_header = NULL;

		i_count++;

		if (i_gbl_max_count > 0 && i_count > i_gbl_max_count)
		{
			break;
		}

		Sleep(l_sleep);
	}
}
