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

/********** 返回的错误列表 **************/
/* 超时 */
#define IBT_ERROR_TIMEOUT -1
/* 鉴权ID不匹配 */
#define IBT_ERROR_AUTH_ID -2
/* 发送的请求数据格式错误 */
#define IBT_ERROR_REQ -3
/********** 返回的错误列表 **************/

/** 
* 初始化 IBT_ASSET 连接,如果不调用ibt_connect，则缺省使用
* p_server = "localhost:7890" p_auth_id = "888888" 连接
*/
LIBIBT_ASSET_API int ibt_connect(const char* p_server,const char* p_auth_id);

/** 查询仓位 
* int* p_size - 返回的IBTPosition数组长度， < 0 - 出错，
* const char* p_BrokerID - 要查询的经纪商ID, NULL - 查询所有
* const char* p_InvestorID - 要查询的交易帐户, NULL - 查询所有
* const char* p_InstrumentID - 要查询的商品名ID，比如IF，NULL - 查询所有
* PosiDirectionType - 0 - 查询多仓和空仓， 1 - 只查询多仓， -1 - 只查询空仓
*
* @return IBTPosition* - 返回的IBTPosition数组,没有值，则 = NULL
*/
LIBIBT_ASSET_API IBTPosition* ibt_query_position(int* p_size,
	const char* p_BrokerID,const char* p_InvestorID,
	const char* p_InstrumentID,
	int PosiDirectionType);

/**
* 释放IBTPosition数组
* 调用ibt_query_position后，必须调用该函数，不然会发生内存泄漏。
*/
LIBIBT_ASSET_API void release_position(IBTPosition* p_data);

/** 查询仓位 
* int* p_size - 返回的IBTPositionEx数组长度， < 0 - 出错，
* const char* p_BrokerID - 要查询的经纪商ID, NULL - 查询所有
* const char* p_InvestorID - 要查询的交易帐户, NULL - 查询所有
* const char* p_InstrumentID - 要查询的商品名ID，比如IF，NULL - 查询所有
* PosiDirectionType - 0 - 查询多仓和空仓， 1 - 只查询多仓， -1 - 只查询空仓
*
* @return IBTPositionEx* - 返回的IBTPositionEx数组,没有值，则 = NULL
*/
LIBIBT_ASSET_API IBTPositionEx* ibt_query_position_ex(int* p_size,
	const char* p_BrokerID,const char* p_InvestorID,
	const char* p_InstrumentID,
	int PosiDirectionType);

/**
* 释放IBTPosition数组
* 调用ibt_query_position后，必须调用该函数，不然会发生内存泄漏。
*/
LIBIBT_ASSET_API void release_position_ex(IBTPositionEx* p_data);

/** 查询帐户汇总 
* int* p_size - 返回的IBTAccountSum数组长度， < 0 - 出错，
* const char* p_BrokerID - 要查询的经纪商ID, NULL - 查询所有
* const char* p_InvestorID - 要查询的交易帐户, NULL - 查询所有
*
* @return IBTAccountSum* - 返回的IBTAccountSum数组,没有值，则 = NULL
*/
LIBIBT_ASSET_API IBTAccountSum* ibt_query_account_sum(
	int* p_size,
	const char* p_BrokerID, // 经纪商ID
	const char* p_InvestorID //期货帐号	
	);

/**
* 释放IBTAccountSum数组
* 调用ibt_query_account_sum后，必须调用该函数，不然会发生内存泄漏。
*/
LIBIBT_ASSET_API void release_account_sum(IBTAccountSum* p_data);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef __IBT_ASSET_H__ */
