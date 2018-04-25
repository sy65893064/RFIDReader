#pragma once


// CDlgUser 对话框

class CDlgUser : public CDialog
{
	DECLARE_DYNAMIC(CDlgUser)

public:
	CDlgUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgUser();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USER_TAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
