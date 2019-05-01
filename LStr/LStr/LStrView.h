
// LStrView.h: интерфейс класса CLStrView
//

#pragma once


class CLStrView : public CView
{
protected: // создать только из сериализации
	CLStrView() noexcept;
	DECLARE_DYNCREATE(CLStrView)

// Атрибуты
public:
	CLStrDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CLStrView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
//	afx_msg void OnSetFocus(CWnd* pOldWnd);
//	afx_msg void OnKillFocus(CWnd* pNewWnd);
};

#ifndef _DEBUG  // версия отладки в LStrView.cpp
inline CLStrDoc* CLStrView::GetDocument() const
   { return reinterpret_cast<CLStrDoc*>(m_pDocument); }
#endif

