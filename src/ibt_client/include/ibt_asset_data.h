#ifndef __IBT_ASSET_DATA_H__
#define __IBT_ASSET_DATA_H__

#ifdef __cplusplus
extern "C" {
#endif

//仓位结构
struct IBTPosition 
{	
	char BrokerID[11]; // 经纪公司代码
	char InvestorID[13]; //投资者代码
	char InstrumentID[31]; // 合约代码
	
	int	Position; //总持仓 多头 > 0, 空头 < 0
	int	YdPosition; //昨日持仓 多头 > 0, 空头 < 0
	int TodayPosition; //今日持仓 多头 > 0, 空头 < 0
	
	double OpenPrice; //开仓均价
	double PositionPrice; //持仓均价
	double LastPrice; //最新价
	double YdPositionProfit; //浮动盈亏
	double PositionProfit; //持仓盈亏
	double UseMargin; //占用的保证金
	double Commission; //佣金	
};

//帐户汇总
struct IBTAccountSum 
{	
	char BrokerID[11]; // 经纪公司代码
	char InvestorID[13]; //投资者代码
	double PreBalance; //昨日结存
	double CloseProfit; //平仓盈亏
	double PositionProfit; //持仓盈亏
	double DynamicProfit; //动态权益
	double Available; //可用资金
	double WithdrawQuota; //可取资金
	double CurrMargin; //持仓保证金
	double FrozenCash; //冻结的资金
	double Deposit; //入金金额
	double Withdraw; //出金金额
	double Commission; //佣金
	double Risk; //风险
};

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef __IBT_ASSET_DATA_H__ */
