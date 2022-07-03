// ChoseCatalogDlg.cpp: plik implementacji
//

#include "pch.h"
#include "MFCApplication.h"
#include "afxdialogex.h"
#include "ChoseCatalogDlg.h"


// Okno dialogowe ChoseCatalogDlg

IMPLEMENT_DYNAMIC(ChoseCatalogDlg, CDialogEx)

ChoseCatalogDlg::ChoseCatalogDlg(
	CString nameToDel /*= L""*/,
	COleDateTime startFilterTime /*= COleDateTime()*/,
	COleDateTime endFilterTime /*= COleDateTime()*/,
	int m_choseFilter /*= 0*/,
	CWnd* pParent /*= nullptr*/)  // konstruktor standardowy)
	: CDialogEx(IDD_DIALOG_CHOSE_VIEW, pParent)
	, m_choseFilter(m_choseFilter)
	, m_nameToDel(nameToDel)
	, m_startFilterTime(startFilterTime)
	, m_endFilterTime(endFilterTime)
{

}

ChoseCatalogDlg::~ChoseCatalogDlg()
{
}

void ChoseCatalogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_CREATE, m_choseFilter);
	DDX_Text(pDX, IDC_EDIT_NAME, m_nameToDel);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_START, m_startFilterTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIM_END, m_endFilterTime);
}


BEGIN_MESSAGE_MAP(ChoseCatalogDlg, CDialogEx)
END_MESSAGE_MAP()

int ChoseCatalogDlg::GetChoseFilter() {
	return m_choseFilter;
}

COleDateTime ChoseCatalogDlg::GetStartTime() {
	return m_startFilterTime;
}
COleDateTime ChoseCatalogDlg::GetEndTime() {
	return m_endFilterTime;
}

CString ChoseCatalogDlg::GetNameToDelete() {
	return m_nameToDel;
}
// Procedury obsługi komunikatów ChoseCatalogDlg
