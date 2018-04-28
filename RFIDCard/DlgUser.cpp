// DlgUser.cpp : 实现文件
//

#include "stdafx.h"
#include "RFIDCard.h"
#include "DlgUser.h"
#include "afxdialogex.h"


// CDlgUser 对话框

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


// CDlgUser 消息处理程序


void CDlgUser::OnPaint()
{
    CPaintDC dc(this);
    // 修改窗口背景颜色
    CRect rect;
    GetClientRect(rect);
    dc.FillSolidRect(rect, RGB(255, 255, 255));
    CDialog::OnPaint();
}
