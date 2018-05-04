#pragma once
#include "afxwin.h"


// CDlgUser �Ի���

class CDlgUser : public CDialog
{
	DECLARE_DYNAMIC(CDlgUser)

public:
	CDlgUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgUser();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USER_TAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
    void ReadCard();

public:
    afx_msg void OnPaint();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    CString m_strCardNum;
    CString m_strAuth;
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
