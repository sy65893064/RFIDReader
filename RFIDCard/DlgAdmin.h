#pragma once

// CDlgAdmin �Ի���

class CDlgAdmin : public CDialog
{
	DECLARE_DYNAMIC(CDlgAdmin)

public:
	CDlgAdmin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAdmin();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMIN_TAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedCardNum();
    CString m_strCardNum;
    afx_msg void OnPaint();
};
