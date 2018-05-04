// DlgAdmin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RFIDCard.h"
#include "DlgAdmin.h"
#include "afxdialogex.h"
#include "RFIDCardDlg.h"


// CDlgAdmin �Ի���

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


// CDlgAdmin ��Ϣ�������


void CDlgAdmin::OnBnClickedCardNum()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    // ��ȡ������
    CRFIDCardDlg *cWnd = (CRFIDCardDlg *)(AfxGetMainWnd());
    CString strPortStat;
    strPortStat.LoadStringW(IDS_OPENPORTSUCCESS);
    // �ж϶˿��Ƿ�������
    if (cWnd->m_strPortStat == strPortStat)
    {
        // ��ȡ�����ں�����ȡ����
        m_strCardNum = cWnd->ReadCardNum();

        // ��ȡ����Ȩ״̬�����ı䰴ť��ʾ״̬
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
        MessageBox(_T("û�д򿪶˿ڻ�򿪶˿�ʧ�ܣ������´򿪶˿ڣ�"));
    }
}


void CDlgAdmin::OnPaint()
{
    CPaintDC dc(this);
    // �޸Ĵ��ڱ�����ɫ
    CRect rect;
    GetClientRect(rect);
    dc.FillSolidRect(rect, RGB(255, 255, 255));
    CDialog::OnPaint();
}


void CDlgAdmin::OnBnClickedAuthorize()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    if (((CRFIDCardDlg *)AfxGetMainWnd())->Authorize())
    {
        GetDlgItem(IDC_AUTHORIZE)->EnableWindow(FALSE);
        GetDlgItem(IDC_DEAUTHORIZE)->EnableWindow(TRUE);
    }
}


void CDlgAdmin::OnBnClickedDeauthorize()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
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

    // TODO: �ڴ˴������Ϣ����������
}
