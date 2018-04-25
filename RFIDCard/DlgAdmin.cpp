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
END_MESSAGE_MAP()


// CDlgAdmin ��Ϣ�������


void CDlgAdmin::OnBnClickedCardNum()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    // ��ȡ������
    CRFIDCardDlg* cwnd = (CRFIDCardDlg *)(/*this->GetParent()->GetParent()*/AfxGetMainWnd());
    CString strPortStat;
    strPortStat.LoadStringW(IDS_OPENPORTSUCCESS);
    // �ж϶˿��Ƿ�������
    if (cwnd->m_strPortStat == strPortStat)
    {
        // ��ȡ�����ں�����ȡ����
        m_strCardNum = cwnd->ReadCardNum();
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
