
// RFIDCardDlg.h : 头文件
//

#pragma once

#include "SerialPort.h"
#include "DlgAdmin.h"
#include "DlgUser.h"
#include "afxcmn.h"

// CRFIDCardDlg 对话框
class CRFIDCardDlg : public CDialogEx
{
// 构造
public:
	CRFIDCardDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RFIDCARD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
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

public:
    // 端口号
    int m_portNum;
    CTabCtrl m_tabCtrl1;
    // 当前选择的tab页
    int m_curTab;
	// 生成的消息映射函数
    afx_msg void OnBnClickedOpenPort();
    afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
    // 读取卡号
    CString ReadCardNum();
    void SetAutoReadCardNum();
    CString m_strPortStat;
};
