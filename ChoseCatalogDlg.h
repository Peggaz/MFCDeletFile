#pragma once
#include "afxdialogex.h"


// Okno dialogowe ChoseCatalogDlg

class ChoseCatalogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChoseCatalogDlg)

public:
	ChoseCatalogDlg(
		CString nameToDel = L"",
		COleDateTime startFilterTime = COleDateTime(),
		COleDateTime endFilterTime = COleDateTime(),
		int m_choseFilter = 0,
		CWnd* pParent = nullptr);   // konstruktor standardowy
	virtual ~ChoseCatalogDlg();

// Dane okna dialogowego
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHOSE_VIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // obsługa DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	

	int GetChoseFilter();

	COleDateTime GetStartTime();

	COleDateTime GetEndTime();

	CString GetNameToDelete();

private:
	int m_choseFilter;
	CString m_nameToDel;
	COleDateTime m_startFilterTime;
	COleDateTime m_endFilterTime;
};
