
// ExeOpenDlg.h : ���� ���������
//

#pragma once
#include "afxwin.h"
#define ID_TIMER_1 100


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
	CString way_of_system;
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedTerminate();
	CListBox list_exe;
	CListBox open_exe;
	afx_msg void OnChangeEditWay();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
