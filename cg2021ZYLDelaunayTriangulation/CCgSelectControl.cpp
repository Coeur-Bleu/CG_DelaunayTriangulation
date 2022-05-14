// CCgSelectControl.cpp: 实现文件
//

#include "pch.h"
#include "cg2021ZYLDelaunayTriangulation.h"
#include "CCgSelectControl.h"

#include "cg2021ZYLDelaunayTriangulationDoc.h"

// CCgSelectControl

IMPLEMENT_DYNCREATE(CCgSelectControl, CFormView)

CCgSelectControl::CCgSelectControl()
	: CFormView(IDD_SELECTCONTROL)
{

}

CCgSelectControl::~CCgSelectControl()
{
}

void CCgSelectControl::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCgSelectControl, CFormView)
	ON_BN_CLICKED(IDC_DELAUNAY, &CCgSelectControl::OnClickedDelaunay)
END_MESSAGE_MAP()


// CCgSelectControl 诊断

#ifdef _DEBUG
void CCgSelectControl::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCgSelectControl::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCgSelectControl 消息处理程序


void CCgSelectControl::OnClickedDelaunay()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2021ZYLDelaunayTriangulationDoc* pDoc = (Ccg2021ZYLDelaunayTriangulationDoc*)GetDocument();

	pDoc->m_opSelect = 1;
}
