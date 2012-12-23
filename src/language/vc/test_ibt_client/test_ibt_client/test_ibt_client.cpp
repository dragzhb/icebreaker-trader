// test_ibt_client.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//���Ϳ�������
	int Policy_ID = 26;
	// ���뿪��
	/*int BuyOrSell = IBT_Enum_Buy;
	int EntryOrExit = IBT_Enum_Entry;
	int Lot = 1;*/

	// ����ƽ��
	int BuyOrSell = IBT_Enum_Sell;
	int EntryOrExit = IBT_Enum_ExitToday;
	int Lot = 0;

	i_ret = ibt_send_order(Policy_ID,BuyOrSell,EntryOrExit,Lot);
	if (0 != i_ret)
	{
		ibt_error("�Ʊ��ſͻ��˷�������ʧ�ܣ�");
	}
	else
	{
		ibt_info("�Ʊ��ſͻ��˷�������ɹ���");
	}

	ibt_debug("test_send_order end.");

	return i_ret;
}

int test_all()
{
	int i_ret = ibt_init();
	if (0 != i_ret)
	{
		ibt_error("��ʼ���Ʊ��ſͻ���ʧ�ܣ�");

		return 0;
	}

	ibt_debug("test_all start...");

	ibt_debug("��ʼ���Ʊ��ſͻ��˳ɹ���");

	cout << "ibt_is_debug : " << ibt_is_debug() << endl;
	cout << "ibt_is_info  : " << ibt_is_info() << endl;
	cout << "ibt_is_error : " << ibt_is_error() << endl;

	cout << "ibt_current_dir : " << ibt_current_dir() << endl;

	//���Ϳ�������
	int Policy_ID = 26;
	// ���뿪��
	/*int BuyOrSell = IBT_Enum_Buy;
	int EntryOrExit = IBT_Enum_Entry;
	int Lot = 1;*/

	// ����ƽ��
	int BuyOrSell = IBT_Enum_Sell;
	int EntryOrExit = IBT_Enum_ExitToday;
	int Lot = 0;

	i_ret = ibt_send_order(Policy_ID,BuyOrSell,EntryOrExit,Lot);
	if (0 != i_ret)
	{
		ibt_error("�Ʊ��ſͻ��˷�������ʧ�ܣ�");
	}
	else
	{
		ibt_info("�Ʊ��ſͻ��˷�������ɹ���");
	}
	
	ibt_debug("test_all end.");

	return 0;
}

