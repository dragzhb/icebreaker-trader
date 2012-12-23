// test_ibt_client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>

#include "ibt_client.h"

#pragma comment(lib,"libibt_client_ex.lib")

using namespace std;

static int test_send_order();

int _tmain(int argc, _TCHAR* argv[])
{	
	test_send_order();
	//test_all();

	return 0;
}

int test_send_order()
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

	return i_ret;
}

int test_all()
{
	int i_ret = ibt_init();
	if (0 != i_ret)
	{
		ibt_error("初始化破冰号客户端失败！");

		return 0;
	}

	ibt_debug("test_all start...");

	ibt_debug("初始化破冰号客户端成功！");

	cout << "ibt_is_debug : " << ibt_is_debug() << endl;
	cout << "ibt_is_info  : " << ibt_is_info() << endl;
	cout << "ibt_is_error : " << ibt_is_error() << endl;

	cout << "ibt_current_dir : " << ibt_current_dir() << endl;

	//发送开仓命令
	int Policy_ID = 26;
	// 买入开仓
	/*int BuyOrSell = IBT_Enum_Buy;
	int EntryOrExit = IBT_Enum_Entry;
	int Lot = 1;*/

	// 卖出平仓
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
	
	ibt_debug("test_all end.");

	return 0;
}

