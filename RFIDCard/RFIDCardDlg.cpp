
// RFIDCardDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RFIDCard.h"
#include "RFIDCardDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRFIDCardDlg �Ի���



CRFIDCardDlg::CRFIDCardDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RFIDCARD_DIALOG, pParent)
    , m_portNum(0)
    , m_curTab(0)
    , m_strPortStat(_T("���ȴ򿪶˿ں�ʹ�ã�"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRFIDCardDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_PORT_EDIT, m_portNum);
    DDV_MinMaxInt(pDX, m_portNum, 0, 10);
    DDX_Control(pDX, IDC_TAB1, m_tabCtrl1);
    DDX_Text(pDX, IDC_PORT_STAT, m_strPortStat);
}

BEGIN_MESSAGE_MAP(CRFIDCardDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_OPEN_PORT, &CRFIDCardDlg::OnBnClickedOpenPort)
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CRFIDCardDlg::OnTcnSelchangeTab1)
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CRFIDCardDlg ��Ϣ�������

BOOL CRFIDCardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    //ΪtabCtrl�ؼ��������ҳ��
    m_tabCtrl1.InsertItem(0, _T("����Ա"));
    m_tabCtrl1.InsertItem(1, _T("�û�"));
    //���������Ի���
    m_dlgAdmin.Create(IDD_ADMIN_TAB, &m_tabCtrl1);
    m_dlgUser.Create(IDD_USER_TAB, &m_tabCtrl1);
    //��tabCtrl�ؼ��ڲ���ʾ�����Ի���
    CRect rc;
    m_tabCtrl1.GetClientRect(rc);
    rc.top += 25;
    rc.bottom -= 5;
    rc.left += 5;
    rc.right -= 5;
    m_dlgAdmin.MoveWindow(&rc);
    m_dlgUser.MoveWindow(&rc);

    m_dlgAdmin.ShowWindow(SW_HIDE);
    m_dlgUser.ShowWindow(SW_HIDE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRFIDCardDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRFIDCardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRFIDCardDlg::OnBnClickedOpenPort()
{
    UpdateData(TRUE);
    CString strInfo;
    if (m_serialPort.InitPort(m_portNum))
    {
        strInfo.LoadStringW(IDS_OPENPORTSUCCESS);
        MessageBox(strInfo);

        // �ɹ��򿪶˿ں������Ӵ��ڿ���
        m_dlgAdmin.ShowWindow(TRUE);
        m_dlgUser.ShowWindow(FALSE);
        CancelAutoRead();

        // ����Tab�ؼ�����
        m_tabCtrl1.EnableWindow(TRUE);
    }
    else
    {
        strInfo.LoadStringW(IDS_OPENPORTFAIL);
        MessageBox(strInfo);
    }
    m_strPortStat = strInfo;
    UpdateData(FALSE);
}


void CRFIDCardDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);
    CString strPortStat;
    strPortStat.LoadStringW(IDS_OPENPORTSUCCESS);
    if (m_strPortStat != strPortStat) // �ж϶˿��Ƿ��
    {
        return;
    }

    m_curTab = m_tabCtrl1.GetCurSel();
    switch (m_curTab)
    {
    case 0:
        m_dlgAdmin.ShowWindow(TRUE);
        m_dlgUser.ShowWindow(FALSE);
        CancelAutoRead(); // ����Ա���������ֶ�����
        m_dlgUser.KillTimer(TIMER_USER);
        break;
    case 1:
        m_dlgAdmin.ShowWindow(FALSE);
        m_dlgUser.ShowWindow(TRUE);
        SetAutoRead(); // �û����������Զ�����
        m_dlgUser.SetTimer(TIMER_USER, 500, NULL);
        break;
    default:
        MessageBox(_T("ѡ�����"));
        break;
    }

    *pResult = 0;
}


void CRFIDCardDlg::OnClose()
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    SetDefaultKayAB();

    CDialogEx::OnClose();
}


BOOL CRFIDCardDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: �ڴ����ר�ô����/����û���
    // enter�������˳�����
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
    {
        return TRUE;
    }

    return CDialogEx::PreTranslateMessage(pMsg);
}


// ����У��λ
void CRFIDCardDlg::CheckSumOut(UCHAR *buf, UCHAR len)
{
    UCHAR i;
    UCHAR checksum;
    checksum = 0;
    for (i = 0; i < (len - 1); i++)
    {
        checksum ^= buf[i];
    }
    buf[len - 1] = (UCHAR)~checksum;
}


// ��ȡ����
CString CRFIDCardDlg::ReadCardNum()
{
    UCHAR cmd[] = { 0x01, 0x08, 0xA1, 0x20, 0x00, 0x01, 0x00, 0x00 };
    CString strRecv;

    if (SendAndRecv(cmd, strRecv))
    {
        MessageBox(_T("��ȡ���ųɹ���"));
        return strRecv.Mid(12, 8);
    }
    else
    {
        MessageBox(_T("��ȡ����ʧ�ܣ�"));
        return _T("");
    }
}


// ��ȡȨ��״̬
bool CRFIDCardDlg::GetAuthorizeStat()
{
    SetKayAB();
    UCHAR cmd[] = { 0x01, 0x08, 0xA3, 0x20, 0x01, 0x00, 0x00, 0x00 };
    CString strRecv;

    if (SendAndRecv(cmd, strRecv))
    {
        if (strRecv.Mid(10, 32) == _T("11111111111111111111111111111111"))
        {
            return true;
        }
    }
    return false;
}


// ��Ȩ
bool CRFIDCardDlg::Authorize()
{
    SetDefaultKayAB();
    if (WriteAllOneOrZero(1) &&
        ChangeOriginalKey(ALL_F))
    {
        SetKayAB();
        if (encrypt())
        {
            return true;
        }
    }
    return false;
}

// ȡ����Ȩ
bool CRFIDCardDlg::Deauthorize()
{
    SetKayAB();
    if (WriteAllOneOrZero(0) &&
        ChangeOriginalKey(ALL_1))
    {
        SetDefaultKayAB();
        if (encrypt())
        {
            return true;
        }
    }
    return false;
}

// �Զ�������һ��
void CRFIDCardDlg::ReadCardOnce(CString& strCardNum)
{
    UCHAR ch = ' ';
    CString strRecv;

    // ��ȡ������Ϣ
    int len = m_serialPort.GetBytesInCOM();
    for (int i = 0; i < len; ++i)
    {
        if (true == m_serialPort.ReadChar(ch))
        {
            strRecv.Format(_T("%s%02x"), strRecv, ch);
        }
    }

    strRecv.MakeUpper();
    if (strRecv.Left(14) == _T("040C0220000400"))
    {
        strCardNum = strRecv.Mid(14, 8);
    }
}


// �����Զ�����
void CRFIDCardDlg::SetAutoRead()
{
    UCHAR cmd[] = { 0x03, 0x08, 0xC1, 0x20, 0x02, 0x00, 0x00, 0x00 };
    CString strRecv;

    if (SendAndRecv(cmd, strRecv))
    {
        MessageBox(_T("���ڹ���ģʽΪ�Զ�����ģʽ��"));
    }
    else
    {
        MessageBox(_T("�����Զ�����ģʽʧ�ܣ���ʹ�ð�ť��ȡ���ţ�"));
    }
}


// ȡ���Զ�����
void CRFIDCardDlg::CancelAutoRead()
{
    UCHAR cmd[] = { 0x03, 0x08, 0xC1, 0x20, 0x01, 0x00, 0x00, 0x00 };
    CString strRecv;

    if (SendAndRecv(cmd, strRecv))
    {
        MessageBox(_T("���ڹ���ģʽΪ�ֶ�����ģʽ��"));
    }
    else
    {
        MessageBox(_T("�����ֶ�����ģʽʧ�ܣ���ʹ�ð�ť��ȡ���ţ�"));
    }
}


// ���ö�����KayA KayB
void CRFIDCardDlg::SetKayAB()
{
    // ����KayA 111111111111
    // ���ÿ���λ FF078069
    // ����KayB 222222222222
    UCHAR cmd[] = { 0x03, 0x15, 0xC3, 0x20, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
        0xFF, 0x07, 0x80, 0x69, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00 };
    UCHAR ch = ' ';
    CString strRecv;
#ifdef _DEBUG
    if (SendAndRecv(cmd, strRecv))
    {
        MessageBox(_T("����Kay�ɹ���\n��ǰKayAΪ111111111111��\n��ǰKayBΪ222222222222��"));
    }
    else
    {
        MessageBox(_T("����Kayʧ�ܣ�"));
    }
#else
    SendAndRecv(cmd, strRecv);
#endif
}


void CRFIDCardDlg::SetDefaultKayAB()
{
    // ����KayA FFFFFFFFFFFF
    // ���ÿ���λ FF078069
    // ����KayB FFFFFFFFFFFF
    UCHAR cmd[] = { 0x03, 0x15, 0xC3, 0x20, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0x07, 0x80, 0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00 };
    CString strRecv;
#ifndef _DEBUG
    SendAndRecv(cmd, strRecv);
#else
    if (SendAndRecv(cmd, strRecv))
    {
        MessageBox(_T("����Ĭ��Kay�ɹ���"));
    }
    else
    {
        MessageBox(_T("����Ĭ��Kayʧ�ܣ�"));
    }
#endif
}


// ����cmd���ؽ���ַ���
bool CRFIDCardDlg::SendAndRecv(UCHAR cmd[], CString& strRecv)
{
    UCHAR ch = ' ';
    CString strCmd;

    CheckSumOut(cmd, cmd[1]);
    m_serialPort.WriteData(cmd, cmd[1]);
    Sleep(200); // �ȴ�0.2�뱣֤�ܹ���ȡ����ȷ�ķ�����Ϣ

    // ��ȡ������Ϣ
    int len = m_serialPort.GetBytesInCOM();
    for (int i = 0; i < len; ++i)
    {
        if (true == m_serialPort.ReadChar(ch))
        {
            strRecv.Format(_T("%s%02x"), strRecv, ch);
        }
    }

    for (int i = 0; i < cmd[1]; ++i)
    {
        strCmd.Format(_T("%s%02X"), strCmd, cmd[i]);
    }

    strRecv.MakeUpper();
    strCmd.MakeUpper();
    if (strRecv.Mid(8, 2) == _T("00")
        && strRecv.Left(2) == strCmd.Left(2)
        && strRecv.Mid(4, 4) == strCmd.Mid(4, 4))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CRFIDCardDlg::WriteAllOneOrZero(int data)
{
    CString strRecv;

    if (1 == data)
    {
        UCHAR cmd[] = { 0x01, 0x17, 0xA4, 0x20, 0x01, 0x01, 0x11, 0x11, 0x11, 0x11,
            0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x00 };
        if (!SendAndRecv(cmd, strRecv))
        {
            return false;
        }
    }
    else if (0 == data)
    {
        UCHAR cmd[] = { 0x01, 0x17, 0xA4, 0x20, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        if (!SendAndRecv(cmd, strRecv))
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool CRFIDCardDlg::ChangeOriginalKey(int key)
{
    CString strRecv;

    if (key == ALL_1)
    {
        UCHAR cmd[] = { 0x03, 0x0B, 0xC4, 0x20, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x00 };
        if (!SendAndRecv(cmd, strRecv))
        {
            return false;
        }
    }
    else if (key == ALL_F)
    {
        UCHAR cmd[] = { 0x03, 0x0B, 0xC4, 0x20, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00 };
        if (!SendAndRecv(cmd, strRecv))
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool CRFIDCardDlg::encrypt()
{
    CString strRecv;

    UCHAR cmd[] = { 0x01, 0x08, 0xA5, 0x20, 0x03, 0x01, 0x00, 0x71 };
    if (SendAndRecv(cmd, strRecv))
    {
        return true;
    }
    else
    {
        return false;
    }
}
