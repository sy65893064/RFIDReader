#pragma once


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
};
