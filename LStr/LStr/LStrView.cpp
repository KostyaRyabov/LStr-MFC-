
// LStrView.cpp: реализация класса CLStrView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "LStr.h"
#endif

#include "LStrDoc.h"
#include "LStrView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLStrView

IMPLEMENT_DYNCREATE(CLStrView, CView)

BEGIN_MESSAGE_MAP(CLStrView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLStrView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CHAR()
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()

// Создание или уничтожение CLStrView

CLStrView::CLStrView() noexcept
{
	// TODO: добавьте код создания

}

CLStrView::~CLStrView()
{
}

BOOL CLStrView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CLStrView

void CLStrView::OnDraw(CDC* pDC)
{
	CLStrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect pRect;
	GetClientRect(&pRect);
	pDC->Rectangle(&pRect);

	CSize s = pDC->GetTextExtent(pDoc->TMP);
	int len = s.cx;
	
	pDoc->STR = pDoc->TMP;

	int rightDist = 12;
	int lastID = 0;

	for (int i = 0; i < pDoc->TMP.GetLength(); i++) {
		if (pDoc->STR[i] == L'\r\n') lastID = i;
		
		if (pDC->GetTextExtent(pDoc->TMP.Mid(lastID, i - lastID)).cx >= (pDoc->x - rightDist)) {
			pDoc->STR.Insert(i, L'\r\n');
			lastID = i;
		}
	}

	pDC->DrawText(pDoc->STR, &pRect, DT_EXPANDTABS);
}


// Печать CLStrView


void CLStrView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CLStrView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CLStrView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CLStrView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CLStrView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLStrView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CLStrView

#ifdef _DEBUG
void CLStrView::AssertValid() const
{
	CView::AssertValid();
}

void CLStrView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLStrDoc* CLStrView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLStrDoc)));
	return (CLStrDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CLStrView


void CLStrView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CLStrDoc *pDoc = GetDocument();
	if (nChar == 8)
		pDoc->TMP.Delete(pDoc->TMP.GetLength() - 1);
	else
		pDoc->TMP += (wchar_t)nChar;

	

	Invalidate();
	
	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CLStrView::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CView::OnWindowPosChanging(lpwndpos);
	
	CLStrDoc *pDoc = GetDocument();
	pDoc->x = lpwndpos->cx;

	// TODO: добавьте свой код обработчика сообщений
}