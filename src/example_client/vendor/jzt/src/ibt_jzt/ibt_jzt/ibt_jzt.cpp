// ibt_jzt.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "ibt_jzt.h"

#include "ibt_client.h"
#pragma comment(lib,"libibt_client_ex.lib")

//DLL��ʽ������ģʽ��ϵͳϵͳ���ø�DLLʱ����֪��ʽϵͳ��DLL��ʽ�����ں���ģʽ��
//����ֵ:	  0��DLL��������ģʽ 1��DLL����������ģʽ
__declspec(dllexport) int WINAPI RUNMODE()
{
	//��DLL��������ģʽ�����������K��ģʽ���˺�������1����ʱÿִ��һ��K�߶��ǵ��ñ��ӿ�һ�Ρ�
//	return 1;
	return 0;
}

//�������̼۵ľ���,һ����������,��ʾ��������
//���÷���:
//	"STOCKFUNC@MYMACLOSE"(5)

__declspec(dllexport) int WINAPI IBT_ORDER(CALCINFO* pData)
{
	if ( pData->m_pfParam1 &&				//����1��Ч
		 pData->m_nParam1Start<0 &&			//����1Ϊ����
		 pData->m_pfParam2 != NULL && 
		 pData->m_pfParam3 != NULL &&
		 pData->m_pfParam4 != NULL)			
	{
		float fParam1 = *pData->m_pfParam1;
		float fParam2 = *pData->m_pfParam2;
		float fParam3 = *pData->m_pfParam3;
		float fParam4 = *pData->m_pfParam4;
		int Policy_ID = (int)fParam1;			//����1
		int BuyOrSell = (int)fParam2;
		int EntryOrExit = (int)fParam3;
		int Lot = (int)fParam4;		

		int i_ret = ibt_send_order(Policy_ID,BuyOrSell,EntryOrExit,Lot);

		return Policy_ID;
	}

	return -1;
}

