#pragma once

//���ݴ���
#include "stdafx.h"
#include "SysteamMan.h"
#include "SysteamManDlg.h"
#include "afxdialogex.h"

// ���ݽṹ��
 struct stuAppDataSystem
{
	CString _name;	// ϵͳ����
	CString _id ;	// ϵͳ����
	int _color;		// ��ɫ
	int _shield;	// �Ƿ��ڱ�
	CString _tubeshape;	// ����״
	int _pipeshape;	// ����״
};
typedef std ::vector<stuAppDataSystem> CAppDataSystemList;

typedef std ::vector<stuAppDataSystem*> pCAppDataSystemList;
//
 class CAppData 
{
public:
	CAppData();
	~CAppData();

protected:
	
public:
	// ��������
	 CAppDataSystemList m_appdataSystemList;

	 pCAppDataSystemList pAppdataList;
	  
	// �����ṹ��
	//stuAppDataSystem stusystem;
	stuAppDataSystem* tempstusystem;


	// ���ļ�����ṹ��������
	void ReadTxtFile( );

	void ReadTxtFile666();

	// ��ʼ�����б���
	//void StartShow(AppDataSystemList *m_listSystem);
	void StartInsertItem0();

	// ��ȡ����ؼ�������
	void GetContent();

	// ���������ݵ�����
	//BOOL AddNewToList(AppDataSystemList *m_listSystem);
	BOOL AddNewToList();
	// ɾ��������ѡ�е�����
	BOOL DeleteList();

	// �������ݵ��ļ�
	BOOL SaveToFile(CAppDataSystemList *m_listSystem);
};
