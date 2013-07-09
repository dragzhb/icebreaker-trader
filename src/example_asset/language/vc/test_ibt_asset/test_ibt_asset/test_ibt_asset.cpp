// libibt_asset_test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <sstream>
#include <iostream>

#include "ibt_client.h"
#include "ibt_asset_cxx.h"

#ifndef _DEBUG
#pragma comment(lib,"libibt_client_ex.lib")
#pragma comment(lib,"libibt_asset.lib")
#else
#pragma comment(lib,"libibt_client_ex_d.lib")
#pragma comment(lib,"libibt_asset_d.lib")
#endif

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
		cout << "�÷���" << argv[0] << " \"��������ַ\" ��ȨID  ����������0-ѭ������" << endl;
		cout << "������" << argv[0] << " \"localhost:7890\" 888888 1" << endl;
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
	//ibt_debug("���ӵ�������: localhost:7890");
	i_ret = ibt_connect(p_gbl_server,p_gbl_auth_id);
	if (0 != i_ret)
	{
		ibt_debug("�޷����ӵ�������");

		return;
	}

	//ibt_debug("���ӵ��������ɹ�...");
	Sleep(1000);

	/*const char* p_server1 = "localhost:7800";
	ibt_debug("���ӵ�������: localhost:7800");
	i_ret = ibt_connect(p_server1,p_auth_id);
	if (0 != i_ret)
	{
		ibt_debug("�޷����ӵ�������");

		return;
	}

	Sleep(5000);*/

	std::vector<IBTPosition> vect_position;
	std::vector<IBTAccountSum> vect_account_sum;

	long l_sleep = 1000;
	// ��ѯ���еĲ�λ
	const char* p_BrokerID = NULL; // ������ID
	const char* p_InvestorID = NULL; //�ڻ��ʺ�
	const char* p_InstrumentID = NULL; //��ԼID,����IF
	int PosiDirectionType = 0; //�ֲַ���
	
	int i_count = 1;
	//int i_max_count = 3;
	std::stringstream str_stream;
	str_stream.precision(2);
	str_stream << std::fixed;

	while (true)
	{
		//��ѯ
		str_stream.str("");
		str_stream << "call query cxx. index = " << i_count;				
		ibt_info(str_stream.str().c_str());		

		//��ѯ�ʻ�����
		i_ret = ibt_query_account_sum_cxx(vect_account_sum,
			p_BrokerID,p_InvestorID);
		size_t i_size_vect_account_sum = vect_account_sum.size();

		str_stream.str("");
		str_stream << "�ʻ����� size = " << i_size_vect_account_sum <<
			", i_ret=" << i_ret;				
		ibt_info(str_stream.str().c_str());

		for (size_t i=0;i<i_size_vect_account_sum;i++)
		{
			str_stream.str("");
			str_stream << "�ʻ����� index = " << i <<
				", ���͹�˾����=" << vect_account_sum[i].BrokerID <<
				", Ͷ���ߴ���=" << vect_account_sum[i].InvestorID <<
				", ���ս��=" << vect_account_sum[i].PreBalance <<
				", ƽ��ӯ��=" << vect_account_sum[i].CloseProfit <<
				", �ֲ�ӯ��=" << vect_account_sum[i].PositionProfit <<
				", ��̬Ȩ��=" << vect_account_sum[i].DynamicProfit <<
				", �����ʽ�=" << vect_account_sum[i].Available <<
				", ��ȡ�ʽ�=" << vect_account_sum[i].WithdrawQuota <<
				", �ֱֲ�֤��=" << vect_account_sum[i].CurrMargin <<
				", ������ʽ�=" << vect_account_sum[i].FrozenCash <<
				", �����=" << vect_account_sum[i].Deposit <<
				", ������=" << vect_account_sum[i].Withdraw <<
				", Ӷ��=" << vect_account_sum[i].Commission <<
				", ����=" << vect_account_sum[i].Risk;

			ibt_info(str_stream.str().c_str());

		} // for (size_t i=0;i<i_size;i++)

		//��ѯ��λ
		i_ret = ibt_query_position_cxx(vect_position,
			p_BrokerID,p_InvestorID,p_InstrumentID,PosiDirectionType);

		size_t i_size_vect_position = vect_position.size();
		str_stream.str("");
		str_stream << "�ֲ�ͳ�� size = " << i_size_vect_position <<
			", i_ret=" << i_ret;				
		ibt_info(str_stream.str().c_str());
		
		for (size_t i=0;i<i_size_vect_position;i++)
		{
			str_stream.str("");
			str_stream << "�ֲ�ͳ�� index = " << i <<
				", ���͹�˾����=" << vect_position[i].BrokerID <<
				", Ͷ���ߴ���=" << vect_position[i].InvestorID <<
				", ��Լ����=" << vect_position[i].InstrumentID <<
				", �ֲܳ�=" << vect_position[i].Position <<
				", ���ճֲ�=" << vect_position[i].YdPosition <<
				", ���ճֲ�=" << vect_position[i].TodayPosition <<
				", ���־���=" << vect_position[i].OpenPrice <<
				", �ֲ־���=" << vect_position[i].PositionPrice <<
				", ���¼�=" << vect_position[i].LastPrice <<
				", ����ӯ��=" << vect_position[i].YdPositionProfit <<
				", �ֲ�ӯ��=" << vect_position[i].PositionProfit <<
				", ռ�õı�֤��=" << vect_position[i].UseMargin <<
				", Ӷ��=" << vect_position[i].Commission;

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
	//ibt_debug("���ӵ�������: localhost:7890");
	i_ret = ibt_connect(p_gbl_server,p_gbl_auth_id);
	if (0 != i_ret)
	{
		ibt_debug("�޷����ӵ�������");

		return;
	}

	//ibt_debug("���ӵ��������ɹ�...");
	Sleep(1000);	

	long l_sleep = 1000; // 1��
	// ��ѯ���еĲ�λ
	const char* p_BrokerID = NULL; // ������ID "16377"; //
	const char* p_InvestorID = NULL; //�ڻ��ʺ� "70108202"; //
	const char* p_InstrumentID = NULL; //��ԼID,����IF
	int PosiDirectionType = 0; //�ֲַ��� 0, 1, -1
	
	int i_count = 1;
	//int i_max_count = 0; //����ѭ������
	std::stringstream str_stream;
	str_stream.precision(2);
	str_stream << std::fixed;
	int i_size_vect = 0;
	while (true)
	{
		//��ѯ
		str_stream.str("");
		str_stream << "call query(c). index = " << i_count;				
		ibt_info(str_stream.str().c_str());		

		//��ѯ�ʻ�����
		IBTAccountSum* p_account_sum = NULL;
		IBTAccountSum* p_account_sum_header = NULL;
		p_account_sum = ibt_query_account_sum(&i_size_vect,
			p_BrokerID,p_InvestorID);
		int i_size_vect_account_sum = i_size_vect;
		p_account_sum_header = p_account_sum;

		str_stream.str("");
		str_stream << "�ʻ����� size = " << i_size_vect_account_sum <<
			", i_ret=" << i_ret;				
		ibt_info(str_stream.str().c_str());

		for (int i=0;i<i_size_vect_account_sum;i++)
		{
			str_stream.str("");
			str_stream << "�ʻ����� index = " << i <<
				", ���͹�˾����=" << p_account_sum->BrokerID <<
				", Ͷ���ߴ���=" << p_account_sum->InvestorID <<
				", ���ս��=" << p_account_sum->PreBalance <<
				", ƽ��ӯ��=" << p_account_sum->CloseProfit <<
				", �ֲ�ӯ��=" << p_account_sum->PositionProfit <<
				", ��̬Ȩ��=" << p_account_sum->DynamicProfit <<
				", �����ʽ�=" << p_account_sum->Available <<
				", ��ȡ�ʽ�=" << p_account_sum->WithdrawQuota <<
				", �ֱֲ�֤��=" << p_account_sum->CurrMargin <<
				", ������ʽ�=" << p_account_sum->FrozenCash <<
				", �����=" << p_account_sum->Deposit <<
				", ������=" << p_account_sum->Withdraw <<
				", Ӷ��=" << p_account_sum->Commission <<
				", ����=" << p_account_sum->Risk;

			ibt_info(str_stream.str().c_str());
			p_account_sum++;

		} // for (size_t i=0;i<i_size;i++)

		//�ǵ��ͷţ���Ȼ�����ڴ�й©
		release_account_sum(p_account_sum_header);
		p_account_sum_header = NULL;

		//��ѯ��λ
		IBTPosition* p_position = NULL;
		IBTPosition* p_position_header = NULL;
		p_position = ibt_query_position(&i_size_vect,
			p_BrokerID,p_InvestorID,p_InstrumentID,PosiDirectionType);

		p_position_header = p_position;
		int i_size_vect_position = i_size_vect;
		str_stream.str("");
		str_stream << "�ֲ�ͳ�� size = " << i_size_vect_position <<
			", i_ret=" << i_ret;				
		ibt_info(str_stream.str().c_str());
		
		for (int i=0;i<i_size_vect_position;i++)
		{
			str_stream.str("");
			str_stream << "�ֲ�ͳ�� index = " << i <<
				", ���͹�˾����=" << p_position->BrokerID <<
				", Ͷ���ߴ���=" << p_position->InvestorID <<
				", ��Լ����=" << p_position->InstrumentID <<
				", �ֲܳ�=" << p_position->Position <<
				", ���ճֲ�=" << p_position->YdPosition <<
				", ���ճֲ�=" << p_position->TodayPosition <<
				", ���־���=" << p_position->OpenPrice <<
				", �ֲ־���=" << p_position->PositionPrice <<
				", ���¼�=" << p_position->LastPrice <<
				", ����ӯ��=" << p_position->YdPositionProfit <<
				", �ֲ�ӯ��=" << p_position->PositionProfit <<
				", ռ�õı�֤��=" << p_position->UseMargin <<
				", Ӷ��=" << p_position->Commission;

			p_position++;

			ibt_info(str_stream.str().c_str());

		} // for (size_t i=0;i<i_size;i++)		

		//�ǵ��ͷţ���Ȼ�����ڴ�й©
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
