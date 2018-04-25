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
END_MESSAGE_MAP()


// CDlgAdmin 消息处理程序


void CDlgAdmin::OnBnClickedCardNum()
{
    // TODO: 在此添加控件通知处理程序代码
    // 获取主窗口
    CRFIDCardDlg* cwnd = (CRFIDCardDlg *)(/*this->GetParent()->GetParent()*/AfxGetMainWnd());
    CString strPortStat;
    strPortStat.LoadStringW(IDS_OPENPORTSUCCESS);
    // 判断端口是否正常打开
    if (cwnd->m_strPortStat == strPortStat)
    {
        // 调取主窗口函数获取卡号
        m_strCardNum = cwnd->ReadCardNum();
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
