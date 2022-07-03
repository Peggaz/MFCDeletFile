
// MFCApplicationView.h : interface of the CMFCApplicationView class
//


//Zmeniæ umieszczenie funkcji odpowiadaj¹cej za kasowanie z doModal do przycisku na froncie i dodanie domyœlnych wartoœci

#pragma once
#include "ChoseCatalogDlg.h"
#include "MultiThreadDeletedFile.h"

class CMFCApplicationView : public CFormView
{
protected: // create from serialization only
	CMFCApplicationView() noexcept;
	DECLARE_DYNCREATE(CMFCApplicationView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MFCAPPLICATION_FORM };
#endif

// Attributes
public:
	CMFCApplicationDoc* GetDocument() const;
	void OnChosePath();
	void DeleteFile();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual ~CMFCApplicationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CMFCEditBrowseCtrl m_ctrl;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	
private:
	CStatic m_labelProgresCtrl;
	CProgressCtrl m_progressBarCtrl;

	int m_choseFilter;
	CString m_nameToDel;
	COleDateTime m_startFilterTime;
	COleDateTime m_endFilterTime;
	std::string m_pathToMainFolder;
	CString m_path;
	
public:
	afx_msg void OnBnClickedButtonDel();
	void DeleteFileMet();
	afx_msg void OnEnChangeMfceditbrowse();
	CStatic m_finishCtrl;
};

#ifndef _DEBUG  // debug version in MFCApplicationView.cpp
inline CMFCApplicationDoc* CMFCApplicationView::GetDocument() const
   { return reinterpret_cast<CMFCApplicationDoc*>(m_pDocument); }
#endif

