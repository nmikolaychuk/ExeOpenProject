
// ExeOpenDlg.cpp : файл реализации
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

// диалоговое окно CExeOpenDlg

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


// обработчики сообщений CExeOpenDlg

BOOL CExeOpenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	OnChangeEditWay();
	SetTimer(1, 500, NULL);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CExeOpenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CExeOpenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CExeOpenDlg::OnBnClickedStart()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(TRUE);

	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	int nSel = list_exe.GetCurSel();
	CString ProcessName = NULL;
	list_exe.GetText(nSel, ProcessName);

	// склеиваем строки, содержащие путь и имя файла
	CString truepath = NULL;
	for (int i = 0; i < way_of_system.GetLength(); i++)
	{
		if (way_of_system[i] != '*')		// условие на "удаление" ненужной части пути (*.exe)
		{
			truepath.Insert(way_of_system.GetLength(), way_of_system[i]);	// записываем это в новую строку
		}
		else break;
	}
	truepath.Insert(way_of_system.GetLength(), ProcessName);	// полученный путь склеиваем с именем файла, результат передаем в CreateProcess


	//MessageBox(truepath, L"Путь", MB_OK | MB_ICONASTERISK);		** MessageBox как проверка результата абсолютного пути
	
	BOOL bSuccess = CreateProcess(NULL, truepath.GetBuffer(), NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
	if (!bSuccess) {
		MessageBox(L"Процесс не найден!", L"ERROR", MB_OK | MB_ICONERROR);
	}
	else {
		int index = open_exe.AddString(ProcessName);
		open_exe.SetItemData(index, (DWORD_PTR)pi.hProcess);	// связываем имя процесса с его handle
	}
}

void CExeOpenDlg::OnBnClickedTerminate()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(TRUE);

	int index = open_exe.GetCurSel();
	CString ProcessName;
	open_exe.GetText(index, ProcessName);

	DWORD process = open_exe.GetItemData(index);

	BOOL close = TerminateProcess((HANDLE)process, index);

	if (!close)
	{
		MessageBox(L"Ошибка!", L"Error", MB_OK | MB_ICONERROR);
	}
}

void CExeOpenDlg::OnChangeEditWay()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
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
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

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
