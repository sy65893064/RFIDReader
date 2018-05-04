// DlgUser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RFIDCard.h"
#include "DlgUser.h"
#include "afxdialogex.h"
#include "RFIDCardDlg.h"


// CDlgUser �Ի���

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
            m_strAuth = _T("����Ȩ�ޣ����Խ��ţ�");
        }
        else
        {
            m_strAuth = _T("��û��Ȩ�ޣ������Խ��ţ�");
        }
        UpdateData(FALSE);
        m_strCardNum = _T("");
        SetTimer(TIMER_USER, 500, NULL);
    }
}


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


void CDlgUser::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

    // TODO: �ڴ˴������Ϣ����������
}
