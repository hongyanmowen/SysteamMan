#include "stdafx.h"
#include "AppData.h"
#include "SysteamMan.h"
#include "SysteamManDlg.h"
#include "afxdialogex.h"
#include <cstring>
#include <algorithm>
#include <locale.h>


CAppData::CAppData()
{
}

CAppData::~CAppData()
{
}


//���ļ�����ṹ��������
void CAppData::ReadTxtFile( )
{
	CStdioFile file;
	CFileException exp;

	char* old_locale=_strdup( setlocale(LC_CTYPE,NULL) ); 
	setlocale(LC_CTYPE, "chs");

	if(file.Open(_T("SystemManager.txt"),CFile::typeText|CFile::modeRead,&exp) == FALSE)
	{
		CString sMsg;
		exp.GetErrorMessage(sMsg.GetBuffer(1024),1024);
		sMsg.ReleaseBuffer();
		//MessageBox(sMsg,_T("����"),MB_OK|MB_ICONERROR);
		return ;
	}
	CString strText;
	CStringArray strArry;
	while(file.ReadString(strText))
	{
		//�ļ���ע�ͻ��߿�������
		if (strText == ""||(strText[0] == '/'))
		{
			continue;
		}
		strArry.Add(strText);
	}

	//������д��vector�ṹ��
	//CSystemList listSystem;
	CString  strcolor, strshield, strpipeshape;
	stuAppDataSystem stusystem;

	for (int i = 0; i < strArry.GetCount(); i++)
	{
		CString strTemp = strArry.GetAt(i);
		int n = strTemp.Find(',');

		if (n != -1)
		{  
			//ϵͳ��
			stusystem._name = strTemp.Left(n);
			strTemp = strTemp.TrimLeft(stusystem._name + _T(","));
			n = strTemp.Find(',');

			//ϵͳ����
			stusystem._id = strTemp.Left(n);
			strTemp = strTemp.TrimLeft(stusystem._id + _T(","));
			n = strTemp.Find(',');

			//��ɫ
			strcolor = strTemp.Left(n);
			stusystem._color = _ttoi(strcolor);
			strTemp = strTemp.Mid(n + 1);
			n = strTemp.Find(',');

			//�ڱ�
			strshield = strTemp.Left(n);
			stusystem._shield = _ttoi(strshield);
			strTemp = strTemp.TrimLeft(strshield + _T(","));
			n = strTemp.Find(',');
			//����״��
			stusystem._tubeshape = strTemp.Left(n);
			//strTemp.Right(n);
			stusystem._pipeshape = _ttoi(strTemp.Right(1));//����״

			m_appdataSystemList.push_back(stusystem);


		}
	}
	setlocale(LC_CTYPE, old_locale);        // ��ԭ�������������
	free(old_locale);                          // ��ԭ�����趨
	file.Close();
	return ;
}

void CAppData:: ReadTxtFile666( )
{
	CStdioFile file;
	CFileException exp;

	char* old_locale=_strdup( setlocale(LC_CTYPE,NULL) ); 
	setlocale(LC_CTYPE, "chs");

	if(file.Open(_T("SystemManager.txt"),CFile::typeText|CFile::modeRead,&exp) == FALSE)
	{
		CString sMsg;
		exp.GetErrorMessage(sMsg.GetBuffer(1024),1024);
		sMsg.ReleaseBuffer();
		//MessageBox(sMsg,_T("����"),MB_OK|MB_ICONERROR);
		return ;
	}
	CString strText;
	CStringArray strArry;
	while(file.ReadString(strText))
	{
		//�ļ���ע�ͻ��߿�������
		if (strText == ""||(strText[0] == '/'))
		{
			continue;
		}
		strArry.Add(strText);
	}

	//������д��vector�ṹ��
	//CSystemList listSystem;
	CString  strcolor, strshield, strpipeshape;
	stuSystem stusystem;

	for (int i = 0; i < strArry.GetCount(); i++)
	{
		CString strTemp = strArry.GetAt(i);
		int n = strTemp.Find(',');

		if (n != -1)
		{  
			//ϵͳ��
			stusystem._name = strTemp.Left(n);
			strTemp = strTemp.TrimLeft(stusystem._name + _T(","));
			n = strTemp.Find(',');

			//ϵͳ����
			stusystem._id = strTemp.Left(n);

			//tempstusystem->_id = strTemp.Left(n);

			strTemp = strTemp.TrimLeft(stusystem._id + _T(","));
			n = strTemp.Find(',');

			//��ɫ
			strcolor = strTemp.Left(n);
			stusystem._color = _ttoi(strcolor);
			strTemp = strTemp.Mid(n + 1);
			n = strTemp.Find(',');

			//�ڱ�
			strshield = strTemp.Left(n);
			stusystem._shield = _ttoi(strshield);
			strTemp = strTemp.TrimLeft(strshield + _T(","));
			n = strTemp.Find(',');
			//����״��
			stusystem._tubeshape = strTemp.Left(n);
			//strTemp.Right(n);
			stusystem._pipeshape = _ttoi(strTemp.Right(1));//����״

			//m_listSystem.push_back(stusystem);
			//pReadtxt.push_back(stusystem);
			//m_listSystem->push_back(stusystem);

			//tempstusystem = ;

			//temp->push_back(*tempstusystem);
		}
	}
	setlocale(LC_CTYPE, old_locale);        // ��ԭ�������������
	free(old_locale);                          // ��ԭ�����趨
	file.Close();
	return ;
}

// ��ʼ�����б���
void StartInsertItem0()
{

}

// ���������ݵ�����
BOOL CAppData::AddNewToList()
{
	CSysteamManDlg* paddTolist = CSysteamManDlg::pSysteamdlg;

	if (paddTolist->m_Editstr.GetLength() == 0)
	{
		paddTolist->MessageBox(TEXT("����Ϊ�գ���"));
		return FALSE;
	}
	//�ж������Ƿ��ظ�
	int num = m_appdataSystemList.size();
	for (int i = 0; i < num; i++)
	{
		if (paddTolist->m_Editstr == m_appdataSystemList[i]._name)
		{
			paddTolist->MessageBox(TEXT("��ϵͳ�����Ѵ��ڣ�����"));
			//ѡ�������
			paddTolist->ChangeFousandView(i);
			return FALSE;
		}
	}
	stuAppDataSystem stuGetthings;
	stuGetthings._name = paddTolist->m_Editstr;

	//�жϴ���m_idEdit�Ƿ񳬹��ĸ��ַ�
	if (paddTolist->m_idEdit.GetLength() > 4)
	{
		paddTolist->MessageBox(TEXT("���ų��Ȳ��ܳ��� 4 ������"));
		return FALSE;
	}
	stuGetthings._id = paddTolist->m_idEdit;

	//�ж���ɫ���Ƿ���0 - 256
	if (paddTolist->m_colorEdit > 256 || paddTolist->m_colorEdit < 0)
	{
		paddTolist->MessageBox(TEXT("��ɫ��Ӧ����0 - 256 ������"));
		return FALSE;
	}
	stuGetthings._color = paddTolist->m_colorEdit;

	//�Ƿ��ڱ�,���� 1 ѡ���ǣ�0Ϊ��
	int nIsorNo = paddTolist->m_IsorNoButton.GetCheck() ;	
	stuGetthings._shield = nIsorNo;

	//������(���ܿ�ѡ���޸�)
	int nPipeShapeComx = paddTolist->m_pipeshapeCombox.GetCurSel();
	stuGetthings._pipeshape = nPipeShapeComx;
	if (stuGetthings._pipeshape != 0 && stuGetthings._pipeshape != 1 && stuGetthings._pipeshape != 2)
	{
		paddTolist->MessageBox(TEXT("������ѡ����״����ֻ��ѡ��һ�����"));
		return FALSE;
	}
	//������
	CString strcombox;
	int state1 = paddTolist->m_circulartube.GetCheck();
	int state2 = paddTolist->m_fanghan.GetCheck();
	int state3 = paddTolist->m_paiguan.GetCheck();
	int state4 = paddTolist->m_luoxaingaun.GetCheck();

	stuGetthings._tubeshape = "[";
	for(int i = 0; i < 4; i++)
	{
		if(i == 0 && state1 == 1)
		{
			strcombox = "1";
			if (state2 == 1 || state3 == 1 || state4 == 1)
			{
				strcombox += "-";
			}
		}
		else if( i == 1 && state2 == 1)
		{
			strcombox += "2";
			if (state3 == 1|| state4 == 1)
			{
				strcombox += "-";
			}
		}
		else if( i == 2 && state3 == 1)
		{
			strcombox += "3";
			if (state4 == 1)
			{
				strcombox += "-";
			}
		}
		else if( i == 3 && state4 == 1){ strcombox += "4";}
	}
	stuGetthings._tubeshape += strcombox ;
	stuGetthings._tubeshape += "]";
	m_appdataSystemList.push_back(stuGetthings);

	//����ϵͳ�����б���
	paddTolist->UpdateView();

	//paddTolist->UpdateData(FALSE);
	return TRUE;
}

// ɾ��������ѡ�е�����
BOOL CAppData::DeleteList()
{
	CSysteamManDlg* paddTolist = CSysteamManDlg::pSysteamdlg;
	//�жϱ༭���Ƿ�������
	if (paddTolist->m_Editstr.GetLength() == 0)
	{
		paddTolist->MessageBox(TEXT("����Ϊ�գ���"));
		return FALSE;
	}
	//�ж������Ƿ����
	int num = paddTolist->m_listSystem.size();
	int nDel = 1024;
	for (int i = 0; i < (num); i++)
	{
		while(paddTolist->m_Editstr == paddTolist->m_listSystem[i]._name)
		{ 
			nDel = i;
			break;
		}
	}
	if (nDel > num)
	{
		paddTolist->MessageBox(TEXT("��ϵͳ���Ʋ����ڣ�����"));
		return FALSE;
	}

	//��ϵͳ����ɾ��
	itr_iterSystemList  _iter;
	int ntemp = 0;
	for ( _iter = paddTolist->m_listSystem.begin(); _iter !=paddTolist->m_listSystem.end();_iter++)
	{
		if (ntemp == nDel)
		{
			paddTolist->m_listSystem.erase(_iter);
			break;
		}		
		ntemp++;
	}

	//����ɾ����Ľ���
	//ˢ��ϵͳ�����б���
	paddTolist->UpdateView();
	//ѡ�е�ǰ�������һ��c
	if (nDel == num-1)
	{
		// ѡ�в�ˢ�¿ؼ�����
		paddTolist->ChangeFousandView(nDel-1);
		// ���µ��༭��
		paddTolist->m_Editstr = paddTolist->m_listSystem[nDel-1]._name;
	}
	else
	{
		// ѡ�в�ˢ�¿ؼ�����
		paddTolist->ChangeFousandView(nDel);

		//���µ��༭��
		paddTolist->m_Editstr = paddTolist->m_listSystem[nDel]._name;
	}
	return FALSE;
}

// �������ݵ��ļ�
BOOL CAppData::SaveToFile(CAppDataSystemList *m_listSystem)
{
	CStdioFile pfile;
	CFileException exp;
	// ��ʾ����
	char* old_locale=_strdup( setlocale(LC_CTYPE,NULL) ); 
	setlocale(LC_CTYPE, "chs");

	if(pfile.Open(_T("SystemManager.txt"),CFile::typeText|CFile::modeReadWrite,&exp) == FALSE)
	{
		CString sMsg;
		exp.GetErrorMessage(sMsg.GetBuffer(1024),1024);
		sMsg.ReleaseBuffer();
		//MessageBox(sMsg,_T("����"),MB_OK|MB_ICONERROR);
		return FALSE;
	}

	CString strList, strListTemp;
	int nList = 0;

	//����ע��
	while(pfile.ReadString(strList))
	{
		//�ļ���ע�ͻ��߿�������
		if (strList == ""||(strList[0] == '/'))
		{
			strListTemp += strList + '\n';
			continue;	
		}
		else
		{
			pfile.Close();
			break;
		}
	}
	//��д�ļ�
	CStdioFile file;
	file.Open(_T("SystemManager.txt"), CFile::modeCreate | CFile::modeWrite);
	int nlen = strListTemp.GetLength();
	
	//����д��ע��
	file.WriteString(strListTemp);

	//��ʼ�����ļ��е�����
	CString strText, strTemp, strColor, strIsorNo, strPipe;
	int nColor, nIsorNo, nPipe;

	int numSize = m_listSystem->size();
	for (int i = 0; i < numSize; i++)
	{
		strText = m_listSystem->at(i)._name + ',';
		strText += m_listSystem->at(i)._id + ',';

		nColor = m_listSystem->at(i)._color;
		strColor.Format(_T("%d"), nColor);	//intתCstring 
		strText += strColor + ',';

		nIsorNo = m_listSystem->at(i)._shield;
		strIsorNo.Format(_T("%d"), nIsorNo);
		strText += strIsorNo + ',';

		strText += m_listSystem->at(i)._tubeshape + ',';

		nPipe = m_listSystem->at(i)._pipeshape;
		strPipe.Format(_T("%d"), nPipe);
		strText += strPipe + '\n';

		file.WriteString(strText);
	}

	setlocale(LC_CTYPE, old_locale );	// ��ԭ�������������
	free(old_locale);					// ��ԭ�����趨
	file.Close();
	return TRUE;
}
