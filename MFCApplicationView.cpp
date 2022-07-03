
// MFCApplicationView.cpp : implementation of the CMFCApplicationView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplication.h"
#endif

#include "MFCApplicationDoc.h"
#include "MFCApplicationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CMFCApplicationView

IMPLEMENT_DYNCREATE(CMFCApplicationView, CFormView)

BEGIN_MESSAGE_MAP(CMFCApplicationView, CFormView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplicationView::OnFilePrintPreview)
	ON_COMMAND(ID_SETTING, &CMFCApplicationView::OnChosePath)

	
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CMFCApplicationView::OnBnClickedButtonDel)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE, &CMFCApplicationView::OnEnChangeMfceditbrowse)
END_MESSAGE_MAP()

// CMFCApplicationView construction/destruction

CMFCApplicationView::CMFCApplicationView() noexcept
	: CFormView(IDD_MFCAPPLICATION_FORM)
{
	m_path = L"C:/Users/pegga/Desktop/TEL-STER/Main";
	OnEnChangeMfceditbrowse();
	m_choseFilter = 0;
	m_nameToDel = L"del";
	m_startFilterTime = COleDateTime();
	m_endFilterTime = COleDateTime();
	
}

CMFCApplicationView::~CMFCApplicationView()
{
}

void CMFCApplicationView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PROGRESS, m_labelProgresCtrl);
	DDX_Control(pDX, IDC_PROGRESS_DELETE, m_progressBarCtrl);
	DDX_Text(pDX, IDC_MFCEDITBROWSE, m_path);
	DDX_Control(pDX, IDC_STATIC_FINISH, m_finishCtrl);
}

BOOL CMFCApplicationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMFCApplicationView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
}


// CMFCApplicationView printing


void CMFCApplicationView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplicationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCApplicationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCApplicationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCApplicationView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

void CMFCApplicationView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplicationView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplicationView diagnostics

#ifdef _DEBUG
void CMFCApplicationView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFCApplicationView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFCApplicationDoc* CMFCApplicationView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplicationDoc)));
	return (CMFCApplicationDoc*)m_pDocument;
}
#endif //_DEBUG

void CMFCApplicationView::OnChosePath()
{
	m_finishCtrl.ShowWindow(SW_HIDE);
	ChoseCatalogDlg dlg(m_nameToDel, m_startFilterTime, m_endFilterTime, m_choseFilter);
	if (dlg.DoModal() == IDOK) {
		m_choseFilter = dlg.GetChoseFilter();
		m_nameToDel = dlg.GetNameToDelete();
		m_startFilterTime = dlg.GetStartTime();
		m_endFilterTime = dlg.GetEndTime();
	}
}

// CMFCApplicationView message handle

void CMFCApplicationView::OnBnClickedButtonDel()
{
	m_labelProgresCtrl.ShowWindow(SW_SHOW);
	m_progressBarCtrl.ShowWindow(SW_SHOW);
	UpdateWindow();
	UpdateData(true);
	OnEnChangeMfceditbrowse();
	DeleteFileMet();
}

void CMFCApplicationView::DeleteFileMet() {
	if (m_nameToDel.GetLength() <= 0) {
		m_labelProgresCtrl.ShowWindow(SW_HIDE);
		m_progressBarCtrl.ShowWindow(SW_HIDE);
		return;
	}
	MultiThreadDeletedFile mtdf(&m_progressBarCtrl);


	CT2CA Convert1(m_nameToDel);
	std::string nameToDelete(Convert1);


	mtdf.make_threads_to_deleted_folders(m_pathToMainFolder, nameToDelete, m_choseFilter, m_startFilterTime, m_endFilterTime);

	m_labelProgresCtrl.ShowWindow(SW_HIDE);
	m_progressBarCtrl.ShowWindow(SW_HIDE);
	m_finishCtrl.ShowWindow(SW_SHOW);

}



void CMFCApplicationView::OnEnChangeMfceditbrowse()
{
	CT2CA Convert1(m_path);
	m_pathToMainFolder = std::string(Convert1);
}
