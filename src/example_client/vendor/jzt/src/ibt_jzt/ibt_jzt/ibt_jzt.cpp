// ibt_jzt.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "ibt_jzt.h"

#include "ibt_client.h"
#pragma comment(lib,"libibt_client_ex.lib")

//DLL公式的运行模式，系统系统调用该DLL时，告知公式系统该DLL公式运行在何种模式下
//返回值:	  0本DLL运行序列模式 1本DLL运行逐周期模式
__declspec(dllexport) int WINAPI RUNMODE()
{
	//本DLL运行序列模式，如果运行逐K线模式将此函数返回1，此时每执行一个K线都是调用本接口一次。
//	return 1;
	return 0;
}

//计算收盘价的均价,一个常数参数,表示计算周期
//调用方法:
//	"STOCKFUNC@MYMACLOSE"(5)

__declspec(dllexport) int WINAPI IBT_ORDER(CALCINFO* pData)
{
	if ( pData->m_pfParam1 &&				//参数1有效
		 pData->m_nParam1Start<0 &&			//参数1为常数
		 pData->m_pfParam2 != NULL && 
		 pData->m_pfParam3 != NULL &&
		 pData->m_pfParam4 != NULL)			
	{
		float fParam1 = *pData->m_pfParam1;
		float fParam2 = *pData->m_pfParam2;
		float fParam3 = *pData->m_pfParam3;
		float fParam4 = *pData->m_pfParam4;
		int Policy_ID = (int)fParam1;			//参数1
		int BuyOrSell = (int)fParam2;
		int EntryOrExit = (int)fParam3;
		int Lot = (int)fParam4;		

		int i_ret = ibt_send_order(Policy_ID,BuyOrSell,EntryOrExit,Lot);

		return Policy_ID;
	}

	return -1;
}

