#ifndef __IBT_ASSET_DATA_H__
#define __IBT_ASSET_DATA_H__

#ifdef __cplusplus
extern "C" {
#endif

//��λ�ṹ
struct IBTPosition 
{	
	char BrokerID[11]; // ���͹�˾����
	char InvestorID[13]; //Ͷ���ߴ���
	char InstrumentID[31]; // ��Լ����
	
	int	Position; //�ֲܳ� ��ͷ > 0, ��ͷ < 0
	int	YdPosition; //���ճֲ� ��ͷ > 0, ��ͷ < 0
	int TodayPosition; //���ճֲ� ��ͷ > 0, ��ͷ < 0
	
	double OpenPrice; //���־���
	double PositionPrice; //�ֲ־���
	double LastPrice; //���¼�
	double YdPositionProfit; //����ӯ��
	double PositionProfit; //�ֲ�ӯ��
	double UseMargin; //ռ�õı�֤��
	double Commission; //Ӷ��	
};

//��λ�ṹ��չ
struct IBTPositionEx
{	
	char BrokerID[11]; // ���͹�˾����
	char InvestorID[13]; //Ͷ���ߴ���
	char InstrumentID[31]; // ��Լ����
	
	int	Position; //�ֲܳ� ��ͷ > 0, ��ͷ < 0
	int	YdPosition; //���ճֲ� ��ͷ > 0, ��ͷ < 0
	int TodayPosition; //���ճֲ� ��ͷ > 0, ��ͷ < 0
	
	double OpenPrice; //���־���
	double PositionPrice; //�ֲ־���
	double LastPrice; //���¼�
	double YdPositionProfit; //����ӯ��
	double PositionProfit; //�ֲ�ӯ��
	double UseMargin; //ռ�õı�֤��
	double Commission; //Ӷ��

	// ======== add Ver3.4.5 ====
	///��С�䶯��λ
	double PriceTick;
	///��Լ��������
	int VolumeMultiple;
	///��ͣ���
	double UpperLimitPrice;
	///��ͣ���
	double LowerLimitPrice;
	// ���ֺ����߼�
	double HighPrice;
	// ���ֺ����ͼ�
	double LowPrice;
};

//�ʻ�����
struct IBTAccountSum 
{	
	char BrokerID[11]; // ���͹�˾����
	char InvestorID[13]; //Ͷ���ߴ���
	double PreBalance; //���ս��
	double CloseProfit; //ƽ��ӯ��
	double PositionProfit; //�ֲ�ӯ��
	double DynamicProfit; //��̬Ȩ��
	double Available; //�����ʽ�
	double WithdrawQuota; //��ȡ�ʽ�
	double CurrMargin; //�ֱֲ�֤��
	double FrozenCash; //������ʽ�
	double Deposit; //�����
	double Withdraw; //������
	double Commission; //Ӷ��
	double Risk; //����
};

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef __IBT_ASSET_DATA_H__ */
