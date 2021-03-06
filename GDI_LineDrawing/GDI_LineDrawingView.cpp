
// GDI_LineDrawingView.cpp: CGDILineDrawingView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GDI_LineDrawing.h"
#endif

#include "GDI_LineDrawingDoc.h"
#include "GDI_LineDrawingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDILineDrawingView

IMPLEMENT_DYNCREATE(CGDILineDrawingView, CView)

BEGIN_MESSAGE_MAP(CGDILineDrawingView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CGDILineDrawingView 생성/소멸
//버튼 초기화
CGDILineDrawingView::CGDILineDrawingView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	L_MouseDown = false;
}

CGDILineDrawingView::~CGDILineDrawingView()
{
}

BOOL CGDILineDrawingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGDILineDrawingView 그리기

void CGDILineDrawingView::OnDraw(CDC* /*pDC*/)
{
	CGDILineDrawingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CGDILineDrawingView 인쇄

BOOL CGDILineDrawingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGDILineDrawingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGDILineDrawingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGDILineDrawingView 진단

#ifdef _DEBUG
void CGDILineDrawingView::AssertValid() const
{
	CView::AssertValid();
}

void CGDILineDrawingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDILineDrawingDoc* CGDILineDrawingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDILineDrawingDoc)));
	return (CGDILineDrawingDoc*)m_pDocument;
}
#endif //_DEBUG


// CGDILineDrawingView 메시지 처리기

//왼쪽 버튼 클릭
void CGDILineDrawingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	L_MouseDown = true;//왼쪽 버튼 클릭

	list_Shape.AddTail(CShape(point));//시작점 추가

	CView::OnLButtonDown(nFlags, point);
}

//선 그리기 시작
void CGDILineDrawingView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (L_MouseDown)
	{
		list_Shape.GetTail().End = point;

		Invalidate(false);//화면 갱신
	}

	CView::OnMouseMove(nFlags, point);
}

//선 그리기 종료
void CGDILineDrawingView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	list_Shape.GetTail().End = point;

	L_MouseDown = false;

	Invalidate(false);

	CView::OnLButtonUp(nFlags, point);
}

//뷰
void CGDILineDrawingView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	//화면의 크기를 구한다.
	CRect rect;
	GetClientRect(&rect);

	//더블 버퍼링
	CDC memDC;
	CBitmap myBitmap;
	CBitmap *pOldBitmap;

	memDC.CreateCompatibleDC(&dc);

	myBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	pOldBitmap = memDC.SelectObject(&myBitmap);

	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

	POSITION position = list_Shape.GetHeadPosition();
	while (position)
	{
		CShape shape = list_Shape.GetNext(position);//리스트 호출

		memDC.MoveTo(shape.Start);//시작점으로 좌표 이동
		memDC.LineTo(shape.End);//이동한 시점부터 끝지점까지 직선 긋기
	}

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	dc.SelectObject(pOldBitmap);
	myBitmap.DeleteObject();
	ReleaseDC(&memDC);
	DeleteDC(memDC);
}
