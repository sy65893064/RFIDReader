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
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgUser ��Ϣ�������


void CDlgUser::OnPaint()
{
    CPaintDC dc(this);
    // �޸Ĵ��ڱ�����ɫ
    CRect rect;
    GetClientRect(rect);
    dc.FillSolidRect(rect, RGB(255, 255, 255));
    CDialog::OnPaint();
}
