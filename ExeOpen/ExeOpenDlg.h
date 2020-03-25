
// ExeOpenDlg.h : ���� ���������
//

#pragma once
#include "afxwin.h"

// ���������� ���� CExeOpenDlg
class CExeOpenDlg : public CDialogEx
{
	// ��������
public:
	CExeOpenDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
	enum { IDD = IDD_EXEOPEN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox list_exe;	// ����������, ��������� � ����� ������� (������ ������ �� ���������� ����)
	CListBox open_exe;	// ����������, ��������� � ������ ������� (������ ���������� ���������)
	CString way_of_system;	// ����������, ��������� � EditControl (����)

	afx_msg void OnBnClickedStart();	// ���������� ������� �� ������ "Start"
	afx_msg void OnBnClickedTerminate(); // ���������� ������� �� ������ "Terminate"
	afx_msg void OnChangeEditWay();		// ���������� ��������� ������ � EditControl (����)
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
