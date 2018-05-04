// DlgUser.cpp : 实现文件
//

#include "stdafx.h"
#include "RFIDCard.h"
#include "DlgUser.h"
#include "afxdialogex.h"
#include "RFIDCardDlg.h"


// CDlgUser 对话框

IMPLEMENT_DYNAMIC(CDlgUser, CDialog)

CDlgUser::CDlgUser(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_USER_TAB, pParent)
    , m_strCardNum(_T(""))
    , m_strAuth(_T(""))
{

}

CDlgUser::~CDlgUser()
{
}

void CDlgUser::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_CARDNUM_EDIT, m_strCardNum);
    DDX_Text(pDX, IDC_STR_AUTH, m_strAuth);
}


BEGIN_MESSAGE_MAP(CDlgUser, CDialog)
    ON_WM_PAINT()
    ON_WM_TIMER()
    ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


void CDlgUser::ReadCard()
{
    CRFIDCardDlg *cWnd = (CRFIDCardDlg *)AfxGetMainWnd();
    cWnd->ReadCardOnce(m_strCardNum);
    if (m_strCardNum != _T(""))
    {
        KillTimer(TIMER_USER);
        if (cWnd->GetAuthorizeStat())
        {
            m_strAuth = _T("你有权限，可以进门！");
        }
        else
        {
            m_strAuth = _T("你没有权限，不可以进门！");
        }
        UpdateData(FALSE);
        m_strCardNum = _T("");
        SetTimer(TIMER_USER, 500, NULL);
    }
}


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


void CDlgUser::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    switch (nIDEvent)
    {
    case TIMER_USER:
        ReadCard();
        break;
    }

    CDialog::OnTimer(nIDEvent);
}


void CDlgUser::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);
    if (bShow)
    {
        m_strCardNum = _T("");
        m_strAuth = _T("");
        UpdateData(FALSE);
    }

    // TODO: 在此处添加消息处理程序代码
}
