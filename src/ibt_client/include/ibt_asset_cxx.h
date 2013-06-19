#ifdef LIBIBT_ASSET_STATIC_EXPORTS
#define LIBIBT_ASSET_API
#else
#ifdef LIBIBT_ASSET_EXPORTS
#define LIBIBT_ASSET_API __declspec(dllexport)
#else
#define LIBIBT_ASSET_API __declspec(dllimport)
#endif
#endif

#ifndef __IBT_ASSET_CXX_H__
#define __IBT_ASSET_CXX_H__

#include "ibt_asset_data.h"
#include "ibt_asset.h"

#include <vector>

/** ��ѯ��λ 
* std::vector<IBTPosition>& vect_position - ���ص�IBTPosition���飬
* const char* p_BrokerID - Ҫ��ѯ�ľ�����ID, NULL - ��ѯ����
* const char* p_InvestorID - Ҫ��ѯ�Ľ����ʻ�, NULL - ��ѯ����
* const char* p_InstrumentID - Ҫ��ѯ����Ʒ��ID������IF��NULL - ��ѯ����
* PosiDirectionType - 0 - ��ѯ��ֺͿղ֣� 1 - ֻ��ѯ��֣� -1 - ֻ��ѯ�ղ�
*
* @return int - 0 - �ɹ��� < 0 - ����
*/
LIBIBT_ASSET_API int ibt_query_position_cxx(
	std::vector<IBTPosition>& vect_position, //���صĳֲ�
	const char* p_BrokerID, // ������ID
	const char* p_InvestorID, //�ڻ��ʺ�
	const char* p_InstrumentID, //��ԼID
	int PosiDirectionType //�ֲַ���
	);

/** ��ѯ��λ ��չ
* std::vector<IBTPositionEx>& vect_position - ���ص�IBTPosition���飬
* const char* p_BrokerID - Ҫ��ѯ�ľ�����ID, NULL - ��ѯ����
* const char* p_InvestorID - Ҫ��ѯ�Ľ����ʻ�, NULL - ��ѯ����
* const char* p_InstrumentID - Ҫ��ѯ����Ʒ��ID������IF��NULL - ��ѯ����
* PosiDirectionType - 0 - ��ѯ��ֺͿղ֣� 1 - ֻ��ѯ��֣� -1 - ֻ��ѯ�ղ�
*
* @return int - 0 - �ɹ��� < 0 - ����
*/
LIBIBT_ASSET_API int ibt_query_position_ex_cxx(
	std::vector<IBTPositionEx>& vect_position, //���صĳֲ���չ
	const char* p_BrokerID, // ������ID
	const char* p_InvestorID, //�ڻ��ʺ�
	const char* p_InstrumentID, //��ԼID
	int PosiDirectionType //�ֲַ���
	);

/** ��ѯ�ʻ����� 
* std::vector<IBTAccountSum>& vect_account_sum - ���ص�IBTAccountSum���飬
* const char* p_BrokerID - Ҫ��ѯ�ľ�����ID, NULL - ��ѯ����
* const char* p_InvestorID - Ҫ��ѯ�Ľ����ʻ�, NULL - ��ѯ����
*
* @return int - 0 - �ɹ��� < 0 - ����
*/
LIBIBT_ASSET_API int ibt_query_account_sum_cxx(
	std::vector<IBTAccountSum>& vect_account_sum, //���ص��ʻ�����
	const char* p_BrokerID, // ������ID
	const char* p_InvestorID //�ڻ��ʺ�	
	);

#endif  /* #ifndef __IBT_ASSET_CXX_H__ */
