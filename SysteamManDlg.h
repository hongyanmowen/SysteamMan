
// SysteamManDlg.h : ͷ�ļ�
//

#pragma once

#include <vector>
#include "afxwin.h"
#include "afxcmn.h"
#include "AppData.h"
 
// ���ݽṹ��
struct stuSystem
{
	CString _name;	// ϵͳ����
	CString _id ;	// ϵͳ����
	int _color;		// ��ɫ
	int _shield;	// �Ƿ��ڱ�
	CString _tubeshape;	// ����״
	int _pipeshape;	// ����״
};
typedef std ::vector<stuSystem> CSystemList;
typedef std ::vector<stuSystem>::iterator itr_iterSystemList ;
// CSysteamManDlg �Ի���
class CSysteamManDlg : public CDialogEx
{
// ����
public:
	CSysteamManDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CSysteamManDlg::~CSysteamManDlg();


	// ��������
	//CAppData *pAppdataDlg;
	CSystemList m_listSystem ;	


	static CSysteamManDlg *pSysteamdlg;
	//AppDataSystemList m_listSystem;

	//CSystemList* pListSystem;
	//CAppData mappData;	//�������ݴ��������
	//����bool ����isOK�������ж��Ƿ����˱��棬�޸����ݺ�Ϊfalse�������Ϊtrue
	bool isOK ;

	// �Ի�������
	enum { IDD = IDD_SYSTEAMMAN_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

// ʵ��
	public:
	

	//���ļ�
	//afx_msg virtual BOOL ReadTXTFile();

	//���浽�ļ�
	//virtual BOOL SaveToFile();

	//���ӻ��޸ĺ��б���ˢ��
	afx_msg void UpdateView();

	//��ʼ�����б���ѡ�������������
	virtual BOOL  StartInsertItem();

	//�����б���Ӧ�ҷ�����ˢ�£�pΪ��ȡ�ĵ���������
	virtual BOOL ChangeFousandView(int p);

	

public:
	//�����б���
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	//˫��
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);

	//���Ӱ�ť
	afx_msg void OnBnClickedButton1();
	//ɾ����ť
	afx_msg void OnBnClickedButton2();

	afx_msg void OnBnClickedCheck3();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnLbnSelchangeList1();
	
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();

//private:
	CString m_Editstr;
	CString m_idEdit;
	CListCtrl m_listBoxShow;
	int m_colorEdit;

	CButton m_IsorNoButton;

	CComboBox m_pipeshapeCombox;

	CButton m_circulartube;
	CButton m_fanghan;
	CButton m_paiguan;
	CButton m_luoxaingaun;

	CButton m_Ok;	

	//CAppData m_appData0;
	//stuSystem* m_pCurentSystem;
};
