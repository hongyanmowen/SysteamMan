
// SysteamManDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SysteamMan.h"
#include "SysteamManDlg.h"
#include "afxdialogex.h"

#include "afxwin.h"
#include "afxcmn.h"

#include "MyIsExit.h"
#include "AppData.h"
#include <algorithm>
#include <locale.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CSysteamManDlg 对话框



CSysteamManDlg::CSysteamManDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSysteamManDlg::IDD, pParent)
	, m_Editstr(_T(""))
	, m_idEdit(_T(""))
	, m_colorEdit(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	
	//CSystemList* pListSystem = new CSystemList;
}

CSysteamManDlg::~CSysteamManDlg()
	
{
	

	//delete pListSystem ;	//删过就不用再删了
}
void CSysteamManDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Editstr);
	DDX_Control(pDX, IDC_LIST1, m_listBoxShow);
	DDX_Text(pDX, IDC_EDIT2,   m_idEdit);
	DDX_Control(pDX, IDC_LIST1, m_listBoxShow);
	DDX_Control(pDX, IDC_COMBO1, m_pipeshapeCombox);
	DDX_Control(pDX, IDC_CHECK1, m_circulartube);
	DDX_Control(pDX, IDC_CHECK2, m_fanghan);
	DDX_Control(pDX, IDC_CHECK3, m_paiguan);
	DDX_Control(pDX, IDC_CHECK4, m_luoxaingaun);
	DDX_Control(pDX, IDC_RADIO1_Yes, m_IsorNoButton);
	DDX_Control(pDX, IDOK, m_Ok);
	DDX_Text(pDX, IDC_EDIT3, m_colorEdit);
}

BEGIN_MESSAGE_MAP(CSysteamManDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSysteamManDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CSysteamManDlg::OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CSysteamManDlg::OnNMClickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CSysteamManDlg::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSysteamManDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDCANCEL, &CSysteamManDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

//初始化静态对话框指针
CSysteamManDlg* CSysteamManDlg::pSysteamdlg = nullptr;	//初始化静态对话框指针
// CSysteamManDlg 消息处理程序
BOOL CSysteamManDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//初始保存为灰，默认不需要保存
	isOK = true;

	//CAppData *pAppdataDlg = CAppData::pAppdata;

	//更改默认字体为宋体、对话框边距
	CFont* pFont = new CFont;
	pFont->CreatePointFont(100, _T("宋体"));
	SetFont(pFont);
	CWnd* pWnd = GetWindow(GW_CHILD);
	while(pWnd != NULL)
	{
		pWnd->SetFont(pFont);
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}
	//pSysteamdlg = this;  //为这个之前定义的指针变量赋值为主对话框指针

	//初始读入系统名称
	CAppData m_appData;
	//读文件数据
	m_appData.ReadTxtFile();

	// 初始化插入系统名称
	StartInsertItem();

	// 选中第一个并刷新控件内容
	ChangeFousandView(0);

	UpdateData(TRUE);
	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSysteamManDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CSysteamManDlg::OnPaint()
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
HCURSOR CSysteamManDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//初始化插入系统名称
BOOL CSysteamManDlg::StartInsertItem()
{
	//AppDataSystemList *pm_appdataSystemList = ;
	//CAppData::m_appdataSystemList;
	CAppData *pStartInsertItem = CAppData::pAppdata;
	//int num1 = CAppData::m_appdataSystemList.size();
	int num = pStartInsertItem->m_appdataSystemList.size();
	//m_listSystem = paddTolist->m_appdataSystemList;
	//static_var.m_appdataSystemList;
	CAppData  m_appdataSystemList;

	int pnum = m_listSystem.size();

	if (pnum == 0)
	{
		//文件中没数据，直接显示空白界面
		return TRUE;
	}
	for (int i = 0; i < pnum; i++)
	{
		m_listBoxShow.InsertItem(i, m_listSystem[i]._name);
	}
	return FALSE;
}

//单击添加按钮
void CSysteamManDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);	// 更新控件到变量

	CAppData m_appData;
	//读文件数据
	m_appData.AddNewToList();

	//添加后,刷新
	int nAdd = m_listSystem.size();

	//界面更新 选中并刷新控件内容
	ChangeFousandView(nAdd -1);

	//添加数据后保存按钮变亮
	CWnd *pWnd = GetDlgItem(IDOK);
	pWnd->EnableWindow(TRUE);
	UpdateData(FALSE);

	isOK = false;

	
}


//添加或删除后，刷新系统名称列表框界面
void CSysteamManDlg::UpdateView()
{
	int temp = m_listSystem.size();
	m_listBoxShow.DeleteAllItems();
	UpdateData(FALSE);
	for (int i = 0; i < temp; i++)
	{
		m_listBoxShow.InsertItem(i,  m_listSystem[i]._name);
	}
	//GetDlgItem(IDC_BUTTON1)->PostMessage(WM_KILLFOCUS,0,0);
	UpdateData(FALSE);
}

//删除按钮实现
void CSysteamManDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CAppData m_appData;

	// 删除容器中选中的数据
	m_appData.DeleteList();

	// 保存按钮变亮
	CWnd *pWnd = GetDlgItem(IDOK);
	pWnd->EnableWindow(TRUE);
	UpdateData(FALSE);

	isOK = false;
}

//单击列表更新界面
void CSysteamManDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	//调用界面更新
	int np = m_listBoxShow.GetSelectionMark();

	// 选中并刷新控件内容
	ChangeFousandView(np);
	
	//单击时清空系统名称编辑框
	CString TEMP = '\0';
	m_Editstr = TEMP;
	UpdateData(FALSE);
	*pResult = 0;
}

//双击获取系统名称到编辑框
void CSysteamManDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_listBoxShow.GetSelectionMark();//双击了哪个 Item
	CString strName = m_listSystem[nIndex]._name;
	m_Editstr = strName;

	UpdateData(FALSE);
	*pResult = 0;
}

//界面更新实现
BOOL CSysteamManDlg::ChangeFousandView(int p)
{
	m_idEdit = m_listSystem[p]._id ;
	m_colorEdit = m_listSystem[p]._color ;

	//是否遮蔽
	if (m_listSystem[p]._shield == 1)
	{	CheckRadioButton(IDC_RADIO1_Yes,IDC_RADIO2_No,IDC_RADIO1_Yes);	} 
	else
	{	CheckRadioButton(IDC_RADIO1_Yes,IDC_RADIO2_No,IDC_RADIO2_No);	}

	//井形状
	int npipeshape = m_listSystem[p]._pipeshape;
	switch(npipeshape)
	{
	case 0:
		m_pipeshapeCombox.SetCurSel(0);
		break;
	case 1:
		m_pipeshapeCombox.SetCurSel(1);
		break;
	case 2:
		m_pipeshapeCombox.SetCurSel(2);
		break;
	default:
		
		break;
	}

	//管形状复选框
	//每次刷新前先置零
	m_circulartube.SetCheck(0);
	m_fanghan.SetCheck(0);
	m_paiguan.SetCheck(0);
	m_luoxaingaun.SetCheck(0);

	//判断管形状最多四种
	CString strTube;
	strTube = m_listSystem[p]._tubeshape;
	int ntube1,ntube2, ntube3, ntube4, nTemp;
	ntube1 = _ttoi(strTube.Mid(1, 1));
	ntube2 = _ttoi(strTube.Mid(3, 1));
	ntube3 = _ttoi(strTube.Mid(5, 1));
	ntube4 = _ttoi(strTube.Mid(7, 1));
	for(int i = 0; i < 4; i++)
	{
		if(i == 0){ nTemp = ntube1; }
		else if( i == 1 && ntube2 != 0){ nTemp = ntube2;}
		else if( i == 2 && ntube3 != 0){ nTemp = ntube3;}
		else if( i == 3 && ntube4 != 0){ nTemp = ntube4;}
		switch(nTemp)
		{
		case 1:
			m_circulartube.SetCheck(1);
			break;
		case 2:
			m_fanghan.SetCheck(1);
			break;
		case 3:
			m_paiguan.SetCheck(1);
			break;
		case 4:
			m_luoxaingaun.SetCheck(1);
			break;
		default:
			break;
		}	
	}
	UpdateData(FALSE);

	m_listBoxShow.SetFocus();      // 获取焦点在列表上面
	m_listBoxShow.SetItemState(p, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
	return FALSE;
	
}

//单击保存按钮
void CSysteamManDlg::OnBnClickedOk()
{
	//保存文件
	CAppData mappData;
	//mappData.SaveToFile();

	//点击保存后按钮变灰
	CWnd *pWnd = GetDlgItem(IDOK);
	pWnd->EnableWindow(FALSE);
	UpdateData(FALSE);
	MessageBox(TEXT(" 保存成功！！!"));

	//记录保存
	isOK = true;
}

//取消按钮
void CSysteamManDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//判断是否保存
	if (isOK == false)
	{
		CMyIsExit Dlg;
		Dlg.DoModal();
	}
	else{ CDialogEx::OnCancel();}
}


void CSysteamManDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnClose();
}
