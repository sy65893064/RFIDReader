
// RFIDCardDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RFIDCard.h"
#include "RFIDCardDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRFIDCardDlg 对话框



CRFIDCardDlg::CRFIDCardDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RFIDCARD_DIALOG, pParent)
    , m_portNum(0)
    , m_curTab(0)
    , m_strPortStat(_T("请先打开端口后使用！"))
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


// CRFIDCardDlg 消息处理程序

BOOL CRFIDCardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    //为tabCtrl控件添加两个页面
    m_tabCtrl1.InsertItem(0, _T("管理员"));
    m_tabCtrl1.InsertItem(1, _T("用户"));
    //创建两个对话框
    m_dlgAdmin.Create(IDD_ADMIN_TAB, &m_tabCtrl1);
    m_dlgUser.Create(IDD_USER_TAB, &m_tabCtrl1);
    //在tabCtrl控件内部显示两个对话框
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRFIDCardDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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

        // 成功打开端口后设置子窗口可用
        m_dlgAdmin.ShowWindow(TRUE);
        m_dlgUser.ShowWindow(FALSE);
        CancelAutoRead();

        // 设置Tab控件可用
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
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    CString strPortStat;
    strPortStat.LoadStringW(IDS_OPENPORTSUCCESS);
    if (m_strPortStat != strPortStat) // 判断端口是否打开
    {
        return;
    }

    m_curTab = m_tabCtrl1.GetCurSel();
    switch (m_curTab)
    {
    case 0:
        m_dlgAdmin.ShowWindow(TRUE);
        m_dlgUser.ShowWindow(FALSE);
        CancelAutoRead(); // 管理员界面设置手动读卡
        m_dlgUser.KillTimer(TIMER_USER);
        break;
    case 1:
        m_dlgAdmin.ShowWindow(FALSE);
        m_dlgUser.ShowWindow(TRUE);
        SetAutoRead(); // 用户界面设置自动读卡
        m_dlgUser.SetTimer(TIMER_USER, 500, NULL);
        break;
    default:
        MessageBox(_T("选择错误！"));
        break;
    }

    *pResult = 0;
}


void CRFIDCardDlg::OnClose()
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    SetDefaultKayAB();

    CDialogEx::OnClose();
}


BOOL CRFIDCardDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: 在此添加专用代码和/或调用基类
    // enter键不会退出程序
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
    {
        return TRUE;
    }

    return CDialogEx::PreTranslateMessage(pMsg);
}


// 计算校验位
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


// 读取卡号
CString CRFIDCardDlg::ReadCardNum()
{
    UCHAR cmd[] = { 0x01, 0x08, 0xA1, 0x20, 0x00, 0x01, 0x00, 0x00 };
    CString strRecv;

    if (SendAndRecv(cmd, strRecv))
    {
        MessageBox(_T("读取卡号成功！"));
        return strRecv.Mid(12, 8);
    }
    else
    {
        MessageBox(_T("读取卡号失败！"));
        return _T("");
    }
}


// 获取权限状态
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


// 授权
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

// 取消授权
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

// 自动读卡号一次
void CRFIDCardDlg::ReadCardOnce(CString& strCardNum)
{
    UCHAR ch = ' ';
    CString strRecv;

    // 获取返回信息
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


// 设置自动读卡
void CRFIDCardDlg::SetAutoRead()
{
    UCHAR cmd[] = { 0x03, 0x08, 0xC1, 0x20, 0x02, 0x00, 0x00, 0x00 };
    CString strRecv;

    if (SendAndRecv(cmd, strRecv))
    {
        MessageBox(_T("现在工作模式为自动读卡模式！"));
    }
    else
    {
        MessageBox(_T("设置自动读卡模式失败，请使用按钮获取卡号！"));
    }
}


// 取消自动读卡
void CRFIDCardDlg::CancelAutoRead()
{
    UCHAR cmd[] = { 0x03, 0x08, 0xC1, 0x20, 0x01, 0x00, 0x00, 0x00 };
    CString strRecv;

    if (SendAndRecv(cmd, strRecv))
    {
        MessageBox(_T("现在工作模式为手动读卡模式！"));
    }
    else
    {
        MessageBox(_T("设置手动读卡模式失败，请使用按钮获取卡号！"));
    }
}


// 设置读卡器KayA KayB
void CRFIDCardDlg::SetKayAB()
{
    // 设置KayA 111111111111
    // 设置控制位 FF078069
    // 设置KayB 222222222222
    UCHAR cmd[] = { 0x03, 0x15, 0xC3, 0x20, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
        0xFF, 0x07, 0x80, 0x69, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00 };
    UCHAR ch = ' ';
    CString strRecv;
#ifdef _DEBUG
    if (SendAndRecv(cmd, strRecv))
    {
        MessageBox(_T("设置Kay成功！\n当前KayA为111111111111；\n当前KayB为222222222222。"));
    }
    else
    {
        MessageBox(_T("设置Kay失败！"));
    }
#else
    SendAndRecv(cmd, strRecv);
#endif
}


void CRFIDCardDlg::SetDefaultKayAB()
{
    // 设置KayA FFFFFFFFFFFF
    // 设置控制位 FF078069
    // 设置KayB FFFFFFFFFFFF
    UCHAR cmd[] = { 0x03, 0x15, 0xC3, 0x20, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0x07, 0x80, 0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00 };
    CString strRecv;
#ifndef _DEBUG
    SendAndRecv(cmd, strRecv);
#else
    if (SendAndRecv(cmd, strRecv))
    {
        MessageBox(_T("设置默认Kay成功！"));
    }
    else
    {
        MessageBox(_T("设置默认Kay失败！"));
    }
#endif
}


// 发送cmd返回结果字符串
bool CRFIDCardDlg::SendAndRecv(UCHAR cmd[], CString& strRecv)
{
    UCHAR ch = ' ';
    CString strCmd;

    CheckSumOut(cmd, cmd[1]);
    m_serialPort.WriteData(cmd, cmd[1]);
    Sleep(200); // 等待0.2秒保证能够读取到正确的返回信息

    // 获取返回信息
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
