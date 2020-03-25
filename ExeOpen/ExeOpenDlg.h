
// ExeOpenDlg.h : файл заголовка
//

#pragma once
#include "afxwin.h"

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
	CListBox list_exe;	// переменная, связанная с левым списком (список файлов по указанному пути)
	CListBox open_exe;	// переменная, связанная с правым списком (список запущенных процессов)
	CString way_of_system;	// переменная, связанная с EditControl (путь)

	afx_msg void OnBnClickedStart();	// обработчик нажатия на кнопку "Start"
	afx_msg void OnBnClickedTerminate(); // обработчки нажатия на кнопку "Terminate"
	afx_msg void OnChangeEditWay();		// обработчик изменения текста в EditControl (путь)
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
