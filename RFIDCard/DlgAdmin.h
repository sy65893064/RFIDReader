#pragma once

// CDlgAdmin 对话框

class CDlgAdmin : public CDialog
{
	DECLARE_DYNAMIC(CDlgAdmin)

public:
	CDlgAdmin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAdmin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMIN_TAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedCardNum();
    CString m_strCardNum;
    afx_msg void OnPaint();
};
