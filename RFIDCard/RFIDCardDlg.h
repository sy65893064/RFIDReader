
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
    // �����Զ�����
    void SetAutoRead();
    // ȡ���Զ�����
    void CancelAutoRead();

public:
    // �˿ں�
    int m_portNum;
    CTabCtrl m_tabCtrl1;
    // ��ǰѡ���tabҳ
    int m_curTab;
	// ���ɵ���Ϣӳ�亯��
    afx_msg void OnBnClickedOpenPort();
    afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
    // ��ȡ����
    CString ReadCardNum();
    // �˿�״̬
    CString m_strPortStat;
};
