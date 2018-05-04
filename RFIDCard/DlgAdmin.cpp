// DlgAdmin.cpp : 实现文件
//

#include "stdafx.h"
#include "RFIDCard.h"
#include "DlgAdmin.h"
#include "afxdialogex.h"
#include "RFIDCardDlg.h"


// CDlgAdmin 对话框

IMPLEMENT_DYNAMIC(CDlgAdmin, CDialog)

CDlgAdmin::CDlgAdmin(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ADMIN_TAB, pParent)
    , m_strCardNum(_T(""))
{

}

CDlgAdmin::~CDlgAdmin()
{
}

void CDlgAdmin::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_CARDNUM_EDIT, m_strCardNum);
}


BEGIN_MESSAGE_MAP(CDlgAdmin, CDialog)
    ON_BN_CLICKED(IDC_CARD_NUM, &CDlgAdmin::OnBnClickedCardNum)
    ON_WM_PAINT()
    ON_BN_CLICKED(IDC_AUTHORIZE, &CDlgAdmin::OnBnClickedAuthorize)
    ON_BN_CLICKED(IDC_DEAUTHORIZE, &CDlgAdmin::OnBnClickedDeauthorize)
    ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CDlgAdmin 消息处理程序


void CDlgAdmin::OnBnClickedCardNum()
{
    // TODO: 在此添加控件通知处理程序代码
    // 获取主窗口
    CRFIDCardDlg *cWnd = (CRFIDCardDlg *)(AfxGetMainWnd());
    CString strPortStat;
    strPortStat.LoadStringW(IDS_OPENPORTSUCCESS);
    // 判断端口是否正常打开
    if (cWnd->m_strPortStat == strPortStat)
    {
        // 调取主窗口函数获取卡号
        m_strCardNum = cWnd->ReadCardNum();

        // 获取卡授权状态，并改变按钮显示状态
        if (!m_strCardNum.IsEmpty())
        {
            if (cWnd->GetAuthorizeStat())
            {
                GetDlgItem(IDC_AUTHORIZE)->EnableWindow(FALSE);
                GetDlgItem(IDC_DEAUTHORIZE)->EnableWindow(TRUE);
            }
            else
            {
                GetDlgItem(IDC_AUTHORIZE)->EnableWindow(TRUE);
                GetDlgItem(IDC_DEAUTHORIZE)->EnableWindow(FALSE);
            }
        }

        UpdateData(FALSE);
    }
    else
    {
        MessageBox(_T("没有打开端口或打开端口失败，请重新打开端口！"));
    }
}


void CDlgAdmin::OnPaint()
{
    CPaintDC dc(this);
    // 修改窗口背景颜色
    CRect rect;
    GetClientRect(rect);
    dc.FillSolidRect(rect, RGB(255, 255, 255));
    CDialog::OnPaint();
}


void CDlgAdmin::OnBnClickedAuthorize()
{
    // TODO: 在此添加控件通知处理程序代码
    if (((CRFIDCardDlg *)AfxGetMainWnd())->Authorize())
    {
        GetDlgItem(IDC_AUTHORIZE)->EnableWindow(FALSE);
        GetDlgItem(IDC_DEAUTHORIZE)->EnableWindow(TRUE);
    }
}


void CDlgAdmin::OnBnClickedDeauthorize()
{
    // TODO: 在此添加控件通知处理程序代码
    if (((CRFIDCardDlg *)AfxGetMainWnd())->Deauthorize())
    {
        GetDlgItem(IDC_AUTHORIZE)->EnableWindow(TRUE);
        GetDlgItem(IDC_DEAUTHORIZE)->EnableWindow(FALSE);
    }
}


void CDlgAdmin::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);
    if (bShow)
    {
        m_strCardNum = _T("");
        GetDlgItem(IDC_AUTHORIZE)->EnableWindow(FALSE);
        GetDlgItem(IDC_DEAUTHORIZE)->EnableWindow(FALSE);
        UpdateData(FALSE);
    }

    // TODO: 在此处添加消息处理程序代码
}
