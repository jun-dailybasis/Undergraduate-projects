// TestDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Bjy_HexTriS.h"
#include "TestDlg.h"
#include "afxdialogex.h"


// CTestDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTestDlg, CDialogEx)

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestDlg::IDD, pParent)
	, user(_T(""))
{

}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CTestDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CTestDlg �޽��� ó�����Դϴ�.


void CTestDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	GetDlgItemText(IDC_EDIT1, user);

}
