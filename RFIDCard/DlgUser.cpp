// DlgUser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RFIDCard.h"
#include "DlgUser.h"
#include "afxdialogex.h"


// CDlgUser �Ի���

IMPLEMENT_DYNAMIC(CDlgUser, CDialog)

CDlgUser::CDlgUser(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_USER_TAB, pParent)
{

}

CDlgUser::~CDlgUser()
{
}

void CDlgUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgUser, CDialog)
END_MESSAGE_MAP()


// CDlgUser ��Ϣ�������
