
// ExeOpenDlg.h : файл заголовка
//

#pragma once
#include "afxwin.h"
#define ID_TIMER_1 100


// диалоговое окно CExeOpenDlg
class CExeOpenDlg : public CDialogEx
{
// Создание
public:
	CExeOpenDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_EXEOPEN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
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
