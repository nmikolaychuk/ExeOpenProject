
// ExeOpenDlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "ExeOpen.h"
#include "ExeOpenDlg.h"
#include "afxdialogex.h"

#include <TlHelp32.h>
#include <Windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���������� ���� CExeOpenDlg

CExeOpenDlg::CExeOpenDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExeOpenDlg::IDD, pParent)
	, way_of_system(L"C:\\Windows\\System32\\*.exe")
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExeOpenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WAY, way_of_system);
	DDX_Control(pDX, IDC_LIST_EXEOPEN, list_exe);
	DDX_Control(pDX, IDC_LIST_EXE_CLOSE, open_exe);
}

BEGIN_MESSAGE_MAP(CExeOpenDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CExeOpenDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_TERMINATE, &CExeOpenDlg::OnBnClickedTerminate)
	ON_EN_CHANGE(IDC_EDIT_WAY, &CExeOpenDlg::OnChangeEditWay)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// ����������� ��������� CExeOpenDlg

BOOL CExeOpenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ������ ������ ��� ����� ����������� ����.  ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// TODO: �������� �������������� �������������

	OnChangeEditWay();
	SetTimer(1, 500, NULL);

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������.  ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CExeOpenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR CExeOpenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CExeOpenDlg::OnBnClickedStart()
{
	// TODO: �������� ���� ��� ����������� �����������
	UpdateData(TRUE);

	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	int nSel = list_exe.GetCurSel();
	CString ProcessName = NULL;
	list_exe.GetText(nSel, ProcessName);

	// ��������� ������, ���������� ���� � ��� �����
	CString truepath = NULL;
	for (int i = 0; i < way_of_system.GetLength(); i++)
	{
		if (way_of_system[i] != '*')		// ������� �� "��������" �������� ����� ���� (*.exe)
		{
			truepath.Insert(way_of_system.GetLength(), way_of_system[i]);	// ���������� ��� � ����� ������
		}
		else break;
	}
	truepath.Insert(way_of_system.GetLength(), ProcessName);	// ���������� ���� ��������� � ������ �����, ��������� �������� � CreateProcess


	//MessageBox(truepath, L"����", MB_OK | MB_ICONASTERISK);		** MessageBox ��� �������� ���������� ����������� ����
	
	BOOL bSuccess = CreateProcess(NULL, truepath.GetBuffer(), NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
	if (!bSuccess) {
		MessageBox(L"������� �� ������!", L"ERROR", MB_OK | MB_ICONERROR);
	}
	else {
		int index = open_exe.AddString(ProcessName);
		open_exe.SetItemData(index, (DWORD_PTR)pi.hProcess);	// ��������� ��� �������� � ��� handle
	}
}

void CExeOpenDlg::OnBnClickedTerminate()
{
	// TODO: �������� ���� ��� ����������� �����������
	UpdateData(TRUE);

	int index = open_exe.GetCurSel();
	CString ProcessName;
	open_exe.GetText(index, ProcessName);

	DWORD process = open_exe.GetItemData(index);

	BOOL close = TerminateProcess((HANDLE)process, index);

	if (!close)
	{
		MessageBox(L"������!", L"Error", MB_OK | MB_ICONERROR);
	}
}

void CExeOpenDlg::OnChangeEditWay()
{
	// TODO:  ���� ��� ������� ���������� RICHEDIT, �� ������� ���������� �� �����
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  �������� ��� �������� ����������
	UpdateData(TRUE);
	CFileFind find_file;
	BOOL bWorking = find_file.FindFile(way_of_system);
	list_exe.ResetContent();
	while (bWorking)
	{
		bWorking = find_file.FindNextFile();
		CString filename = find_file.GetFileName();
		list_exe.AddString(filename);
	}
}

void CExeOpenDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������

	CDialogEx::OnTimer(nIDEvent);

	for (int i = 0; i < open_exe.GetCount(); i++)
	{
		DWORD ExitCode = STILL_ACTIVE;
		HANDLE process = (HANDLE)open_exe.GetItemData(i);
		::GetExitCodeProcess(process, &ExitCode);
		if (ExitCode != STILL_ACTIVE)
		{
			::CloseHandle(process);
			open_exe.DeleteString(i);
		}
	}
}
