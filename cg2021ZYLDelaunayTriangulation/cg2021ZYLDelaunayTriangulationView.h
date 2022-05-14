
// cg2021ZYLDelaunayTriangulationView.h: Ccg2021ZYLDelaunayTriangulationView 类的接口
//

#pragma once
#define N 100
//CPoint m_pAccord[N];
class Ccg2021ZYLDelaunayTriangulationView : public CView
{
protected: // 仅从序列化创建
	Ccg2021ZYLDelaunayTriangulationView() noexcept;
	DECLARE_DYNCREATE(Ccg2021ZYLDelaunayTriangulationView)

// 特性
public:
	Ccg2021ZYLDelaunayTriangulationDoc* GetDocument() const;

	CClientDC* m_pDC;
	int m_pNumbers;
	CPoint m_mousePoint;

// 操作
public:
	//int cmp(CPoint a, CPoint b);
	void Delaunay(int pNumbers, CPoint* points, CDC* pDC);

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~Ccg2021ZYLDelaunayTriangulationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // cg2021ZYLDelaunayTriangulationView.cpp 中的调试版本
inline Ccg2021ZYLDelaunayTriangulationDoc* Ccg2021ZYLDelaunayTriangulationView::GetDocument() const
   { return reinterpret_cast<Ccg2021ZYLDelaunayTriangulationDoc*>(m_pDocument); }
#endif

