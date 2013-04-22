#ifdef LIBIBT_CLIENT_STATIC_EXPORTS
#define LIBIBT_CLIENT_API
#else
#ifdef LIBIBT_CLIENT_EXPORTS
#define LIBIBT_CLIENT_API __declspec(dllexport)
#else
#define LIBIBT_CLIENT_API __declspec(dllimport)
#endif
#endif

#ifndef __IBT_CLIENT_H__
#define __IBT_CLIENT_H__

#ifdef __cplusplus
extern "C" {
#endif

/* 买入 */
#ifndef IBT_Enum_Buy
#define IBT_Enum_Buy 0
#endif 

/* 卖出 */
#ifndef IBT_Enum_Sell
#define IBT_Enum_Sell 1
#endif

/* 开仓 */
#ifndef IBT_Enum_Entry
#define IBT_Enum_Entry 0
#endif

/* 平昨 */
#ifndef IBT_Enum_Exit
#define IBT_Enum_Exit 1
#endif

/* 平今 */
#ifndef IBT_Enum_ExitToday
#define IBT_Enum_ExitToday 2
#endif

/* 初始化 ibt_client */
LIBIBT_CLIENT_API int ibt_init(void);
/* 初始化 ibt_client 并且指定日志的配置文件 */
LIBIBT_CLIENT_API int ibt_init_ex(const char* p_log_config_file);

/* 发送下单命令*/
LIBIBT_CLIENT_API int ibt_send_order(int Policy_ID,
		int BuyOrSell,
		int EntryOrExit,
		int Lot);

/* 扩展发送下单命令
* PriceType  0 - 限价单， 1 - 市价单
* InstrumentID - 商品名 大小写敏感 比如IF1305或rb1310
*/
LIBIBT_CLIENT_API int ibt_send_order_ex(int Policy_ID,
		int BuyOrSell,
		int EntryOrExit,
		int Lot,
		int PriceType,
		const char* InstrumentID);

/* =========== 下面的是辅助工具 =========== */

/* 获得当前路径 */
LIBIBT_CLIENT_API const char* ibt_current_dir();

/* 检查是否已打开DEBUG信息开关, 0 - 没有打开， 1 - 打开 */
LIBIBT_CLIENT_API int ibt_is_debug();

/* 检查是否已打开INFO信息开关, 0 - 没有打开， 1 - 打开 */
LIBIBT_CLIENT_API int ibt_is_info();

/* 检查是否已打开ERROR信息开关, 0 - 没有打开， 1 - 打开 */
LIBIBT_CLIENT_API int ibt_is_error();

/* 打印DEBUG信息 */
LIBIBT_CLIENT_API void ibt_debug(const char* p_text);
/* 打印INFO信息 */
LIBIBT_CLIENT_API void ibt_info(const char* p_text);
/* 打印ERROR信息 */
LIBIBT_CLIENT_API void ibt_error(const char* p_text);

/* =========== 下面的是R语言 =========== */

/* 初始化 ibt_client R语言 */
LIBIBT_CLIENT_API void ibt_init_r(int* i_ret);
/* 初始化 ibt_client 并且指定日志的配置文件 R语言 */
LIBIBT_CLIENT_API void ibt_init_ex_r(const char** p_log_config_file,int* i_ret);

/* 发送下单命令 专门为R语言的接口 */
LIBIBT_CLIENT_API void ibt_send_order_r(int* p_Policy_ID,
		int* p_BuyOrSell,
		int* p_EntryOrExit,
		int* p_Lot,
		int* i_ret);

/* 扩展发送下单命令 专门为R语言的接口 
* PriceType  0 - 限价单， 1 - 市价单
* InstrumentID - 商品名 大小写敏感 比如IF1305或rb1310
*/
LIBIBT_CLIENT_API void ibt_send_order_ex_r(int* p_Policy_ID,
		int* p_BuyOrSell,
		int* p_EntryOrExit,
		int* p_Lot,		
		int* PriceType,
		const char** InstrumentID,
		int* i_ret);

/* =========== 下面的是辅助工具 =========== */

/* 获得当前路径 R语言 */
LIBIBT_CLIENT_API void ibt_current_dir_r(const char** p_dir );

/* 检查是否已打开DEBUG信息开关, 0 - 没有打开， 1 - 打开 R语言 */
LIBIBT_CLIENT_API void ibt_is_debug_r(int* i_ret);

/* 检查是否已打开INFO信息开关, 0 - 没有打开， 1 - 打开 R语言 */
LIBIBT_CLIENT_API void ibt_is_info_r(int* i_ret);

/* 检查是否已打开ERROR信息开关, 0 - 没有打开， 1 - 打开 R语言 */
LIBIBT_CLIENT_API void ibt_is_error_r(int* i_ret);

/* 打印DEBUG信息 R语言 */
LIBIBT_CLIENT_API void ibt_debug_r(const char** p_text);
/* 打印INFO信息 R语言 */
LIBIBT_CLIENT_API void ibt_info_r(const char** p_text);

/* 打印ERROR信息 R语言*/
LIBIBT_CLIENT_API void ibt_error_r(const char** p_text);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef __IBT_CLIENT_H__ */
