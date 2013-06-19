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

/** 查询仓位 
* std::vector<IBTPosition>& vect_position - 返回的IBTPosition数组，
* const char* p_BrokerID - 要查询的经纪商ID, NULL - 查询所有
* const char* p_InvestorID - 要查询的交易帐户, NULL - 查询所有
* const char* p_InstrumentID - 要查询的商品名ID，比如IF，NULL - 查询所有
* PosiDirectionType - 0 - 查询多仓和空仓， 1 - 只查询多仓， -1 - 只查询空仓
*
* @return int - 0 - 成功， < 0 - 出错
*/
LIBIBT_ASSET_API int ibt_query_position_cxx(
	std::vector<IBTPosition>& vect_position, //返回的持仓
	const char* p_BrokerID, // 经纪商ID
	const char* p_InvestorID, //期货帐号
	const char* p_InstrumentID, //合约ID
	int PosiDirectionType //持仓方向
	);

/** 查询仓位 扩展
* std::vector<IBTPositionEx>& vect_position - 返回的IBTPosition数组，
* const char* p_BrokerID - 要查询的经纪商ID, NULL - 查询所有
* const char* p_InvestorID - 要查询的交易帐户, NULL - 查询所有
* const char* p_InstrumentID - 要查询的商品名ID，比如IF，NULL - 查询所有
* PosiDirectionType - 0 - 查询多仓和空仓， 1 - 只查询多仓， -1 - 只查询空仓
*
* @return int - 0 - 成功， < 0 - 出错
*/
LIBIBT_ASSET_API int ibt_query_position_ex_cxx(
	std::vector<IBTPositionEx>& vect_position, //返回的持仓扩展
	const char* p_BrokerID, // 经纪商ID
	const char* p_InvestorID, //期货帐号
	const char* p_InstrumentID, //合约ID
	int PosiDirectionType //持仓方向
	);

/** 查询帐户汇总 
* std::vector<IBTAccountSum>& vect_account_sum - 返回的IBTAccountSum数组，
* const char* p_BrokerID - 要查询的经纪商ID, NULL - 查询所有
* const char* p_InvestorID - 要查询的交易帐户, NULL - 查询所有
*
* @return int - 0 - 成功， < 0 - 出错
*/
LIBIBT_ASSET_API int ibt_query_account_sum_cxx(
	std::vector<IBTAccountSum>& vect_account_sum, //返回的帐户汇总
	const char* p_BrokerID, // 经纪商ID
	const char* p_InvestorID //期货帐号	
	);

#endif  /* #ifndef __IBT_ASSET_CXX_H__ */
