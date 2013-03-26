#ifdef LIBIBT_ASSET_STATIC_EXPORTS
#define LIBIBT_ASSET_API
#else
#ifdef LIBIBT_ASSET_EXPORTS
#define LIBIBT_ASSET_API __declspec(dllexport)
#else
#define LIBIBT_ASSET_API __declspec(dllimport)
#endif
#endif

#ifndef __IBT_ASSET_H__
#define __IBT_ASSET_H__

#include "ibt_asset_data.h"

#ifdef __cplusplus
extern "C" {
#endif

/********** ���صĴ����б� **************/
/* ��ʱ */
#define IBT_ERROR_TIMEOUT -1
/* ��ȨID��ƥ�� */
#define IBT_ERROR_AUTH_ID -2
/* ���͵��������ݸ�ʽ���� */
#define IBT_ERROR_REQ -3
/********** ���صĴ����б� **************/

/** 
* ��ʼ�� IBT_ASSET ����,���������ibt_connect����ȱʡʹ��
* p_server = "localhost:7890" p_auth_id = "888888" ����
*/
LIBIBT_ASSET_API int ibt_connect(const char* p_server,const char* p_auth_id);

/** ��ѯ��λ 
* int* p_size - ���ص�IBTPosition���鳤�ȣ� < 0 - ����
* const char* p_BrokerID - Ҫ��ѯ�ľ�����ID, NULL - ��ѯ����
* const char* p_InvestorID - Ҫ��ѯ�Ľ����ʻ�, NULL - ��ѯ����
* const char* p_InstrumentID - Ҫ��ѯ����Ʒ��ID������IF��NULL - ��ѯ����
* PosiDirectionType - 0 - ��ѯ��ֺͿղ֣� 1 - ֻ��ѯ��֣� -1 - ֻ��ѯ�ղ�
*
* @return IBTPosition* - ���ص�IBTPosition����,û��ֵ���� = NULL
*/
LIBIBT_ASSET_API IBTPosition* ibt_query_position(int* p_size,
	const char* p_BrokerID,const char* p_InvestorID,
	const char* p_InstrumentID,
	int PosiDirectionType);

/**
* �ͷ�IBTPosition����
* ����ibt_query_position�󣬱�����øú�������Ȼ�ᷢ���ڴ�й©��
*/
LIBIBT_ASSET_API void release_position(IBTPosition* p_data);

/** ��ѯ�ʻ����� 
* int* p_size - ���ص�IBTAccountSum���鳤�ȣ� < 0 - ����
* const char* p_BrokerID - Ҫ��ѯ�ľ�����ID, NULL - ��ѯ����
* const char* p_InvestorID - Ҫ��ѯ�Ľ����ʻ�, NULL - ��ѯ����
*
* @return IBTAccountSum* - ���ص�IBTAccountSum����,û��ֵ���� = NULL
*/
LIBIBT_ASSET_API IBTAccountSum* ibt_query_account_sum(
	int* p_size,
	const char* p_BrokerID, // ������ID
	const char* p_InvestorID //�ڻ��ʺ�	
	);

/**
* �ͷ�IBTAccountSum����
* ����ibt_query_account_sum�󣬱�����øú�������Ȼ�ᷢ���ڴ�й©��
*/
LIBIBT_ASSET_API void release_account_sum(IBTAccountSum* p_data);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef __IBT_ASSET_H__ */
