
// GDI_LineDrawingView.h: CGDILineDrawingView 클래스의 인터페이스
//

#pragma once
#include "Shape.h"

class CGDILineDrawingView : public CView
{
protected: // serialization에서만 만들어집니다.
	CGDILineDrawingView() noexcept;
	DECLARE_DYNCREATE(CGDILineDrawingView)

// 특성입니다.
public:
	CGDILineDrawingDoc* GetDocument() const;

// 작업입니다.
public:
	BOOL L_MouseDown;
	CList<CShape> list_Shape;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CGDILineDrawingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // GDI_LineDrawingView.cpp의 디버그 버전
inline CGDILineDrawingDoc* CGDILineDrawingView::GetDocument() const
   { return reinterpret_cast<CGDILineDrawingDoc*>(m_pDocument); }
#endif

