
// RFIDCardDlg.h : ͷ�ļ�
//

#pragma once

#include "SerialPort.h"
#include "DlgAdmin.h"
#include "DlgUser.h"
#include "afxcmn.h"

// CRFIDCardDlg �Ի���
class CRFIDCardDlg : public CDialogEx
{
// ����
public:
	CRFIDCardDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RFIDCARD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
    SerialPort m_serialPort;
    CDlgAdmin m_dlgAdmin;
    CDlgUser m_dlgUser;
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    // ����У��λ
    void CheckSumOut(UCHAR *buf, UCHAR len);
    // �����Զ�����
    void SetAutoRead();
    // ȡ���Զ�����
    void CancelAutoRead();
    // ���ö�����KayA KayB
    void SetKayAB();
    void SetDefaultKayAB();
    // ����cmd���ؽ���ַ���
    bool SendAndRecv(UCHAR cmd[], CString& strRecv);
    // ���ݿ�1��д��ȫ1��ȫ0
    bool WriteAllOneOrZero(int data);
    // �޸�ԭʼ����ȫ1��ȫF
    bool ChangeOriginalKey(int key);
    // ��������0
    bool encrypt();


public:
    // �˿ں�
    int m_portNum;
    CTabCtrl m_tabCtrl1;
    // ��ǰѡ���tabҳ
    int m_curTab;
	// ���ɵ���Ϣӳ�亯��
    afx_msg void OnBnClickedOpenPort();
    afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnClose();
    // ��ȡ����
    CString ReadCardNum();
    // ��ȡȨ��״̬
    bool GetAuthorizeStat();
    // ��Ȩ
    bool Authorize();
    // ȡ����Ȩ
    bool Deauthorize();
    // �Զ�������һ��
    void ReadCardOnce(CString& strCardNum);
    // �˿�״̬
    CString m_strPortStat;
};
