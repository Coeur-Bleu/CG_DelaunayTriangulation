
// cg2021ZYLDelaunayTriangulationView.cpp: Ccg2021ZYLDelaunayTriangulationView 类的实现
//

#include "pch.h"
#include "framework.h"

// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "cg2021ZYLDelaunayTriangulation.h"
#endif

#include "cg2021ZYLDelaunayTriangulationDoc.h"
#include "cg2021ZYLDelaunayTriangulationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <list>
#include<algorithm>
using namespace std;

// Ccg2021ZYLDelaunayTriangulationView

//class Triangle {
//public:
//
//	bool operator==(Triangle& p)
//	{
//		if (SameTriangle(*this,p))
//		{
//			return true;
//		}
//		return false;
//	}
//
//	bool operator!=(Triangle& p)
//	{
//		if (SameTriangle(*this, p))
//		{
//			return false;
//		}
//		return true;
//	}
//
//
//	CPoint p1;
//	CPoint p2;
//	CPoint p3;
//	
//};
struct Triangle{
	CPoint p1;
	CPoint p2;
	CPoint p3;
};

struct Line {
	CPoint start;
	CPoint end;
};

list<Line>Linepts;
list<Triangle>Tripts;

CPoint m_pAccord[N];
IMPLEMENT_DYNCREATE(Ccg2021ZYLDelaunayTriangulationView, CView)

BEGIN_MESSAGE_MAP(Ccg2021ZYLDelaunayTriangulationView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// Ccg2021ZYLDelaunayTriangulationView 构造/析构

Ccg2021ZYLDelaunayTriangulationView::Ccg2021ZYLDelaunayTriangulationView() noexcept
{
	// TODO: 在此处添加构造代码
	m_pDC = NULL;
	m_pNumbers = 0;

}

Ccg2021ZYLDelaunayTriangulationView::~Ccg2021ZYLDelaunayTriangulationView()
{
}

BOOL Ccg2021ZYLDelaunayTriangulationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// Ccg2021ZYLDelaunayTriangulationView 绘图

void Ccg2021ZYLDelaunayTriangulationView::OnDraw(CDC* /*pDC*/)
{
	Ccg2021ZYLDelaunayTriangulationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CDC* pDC = GetDC();

	//if (pDoc->m_opSelect == 1) {
		//Delaunay(m_pNumbers, m_pAccord, m_pDC);
	//}
	/*switch (pDoc->m_opSelect) {
	case 0: break;
	case 1:
		Delaunay(m_pNumbers, m_pAccord, m_pDC);
		break;
	}*/
}


// Ccg2021ZYLDelaunayTriangulationView 打印

BOOL Ccg2021ZYLDelaunayTriangulationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void Ccg2021ZYLDelaunayTriangulationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void Ccg2021ZYLDelaunayTriangulationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// Ccg2021ZYLDelaunayTriangulationView 诊断

#ifdef _DEBUG
void Ccg2021ZYLDelaunayTriangulationView::AssertValid() const
{
	CView::AssertValid();
}

void Ccg2021ZYLDelaunayTriangulationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ccg2021ZYLDelaunayTriangulationDoc* Ccg2021ZYLDelaunayTriangulationView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ccg2021ZYLDelaunayTriangulationDoc)));
	return (Ccg2021ZYLDelaunayTriangulationDoc*)m_pDocument;
}
#endif //_DEBUG


// Ccg2021ZYLDelaunayTriangulationView 消息处理程序


void Ccg2021ZYLDelaunayTriangulationView::OnLButtonDown(UINT nFlags, CPoint point)
{
	Ccg2021ZYLDelaunayTriangulationDoc* pDoc = GetDocument();


	
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_pNumbers < N) {
		m_mousePoint = point;
		m_pAccord[m_pNumbers] = point;
		m_pNumbers++;
	}
	
	m_pDC->SetPixel(point.x, point.y, (0, 0, 0));
	CView::OnLButtonDown(nFlags, point);
}

void Ccg2021ZYLDelaunayTriangulationView::OnRButtonDown(UINT nFlags, CPoint point)
{
	Ccg2021ZYLDelaunayTriangulationDoc* pDoc = GetDocument();
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (pDoc->m_opSelect == 1) {
		Delaunay(m_pNumbers, m_pAccord, m_pDC);
		m_pNumbers = 0;
	}
	CView::OnRButtonDown(nFlags, point);
}


int Ccg2021ZYLDelaunayTriangulationView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_pDC = new CClientDC(this);
	return 0;
}

bool cmp1(CPoint a, CPoint b)//排序找第一个点
{
	if (a.y == b.y)
		return a.x < b.x;
	else
		return a.y < b.y;
}

int cross(CPoint a, CPoint b, CPoint c)//计算叉积
{
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

double dis(CPoint a, CPoint b)//计算距离
{
	return sqrt((a.x - b.x) * (a.x - b.x) * 1.0 + (a.y - b.y) * (a.y - b.y));
}

int cmp(CPoint a,CPoint b) {//极角排序
	int m = (a.x - m_pAccord[0].x) * (b.y - m_pAccord[0].y) - (b.x - m_pAccord[0].x) * (a.y - m_pAccord[0].y);
	if (m > 0)
		return 1;
	else if (m == 0 && dis(m_pAccord[0], a) - dis(m_pAccord[0], b) <= 0)
		return 1;
	else return 0;
}

//获取面积
double GetSquare(double line_1, double line_2, double line_3) {
	double p = (line_1 + line_2 + line_3)/2;
	return sqrt(p * (p - line_1) * (p - line_2) * (p - line_3));
}

//判断点与三角形的位置关系
int IsInTriangle(Triangle tri, CPoint point) {
	CPoint a = tri.p1;
	CPoint b = tri.p2;
	CPoint c = tri.p3;
	double Triangle_edge1 = dis(a, b), Triangle_edge2 = dis(a, c), Triangle_edge3 = dis(b, c);
	double S_0, s_1, s_2, s_3, S_sum;
	int sum;
	//int flag = 0;
		double edge1 = dis(a, point);
		double edge2 = dis(b, point);
		double edge3 = dis(c, point);
		S_0 = GetSquare(Triangle_edge1, Triangle_edge2, Triangle_edge3);
		s_1 = GetSquare(Triangle_edge1, edge1, edge2);
		s_2 = GetSquare(Triangle_edge2, edge1, edge3);
		s_3 = GetSquare(Triangle_edge3, edge2, edge3);
		S_sum = s_1 + s_2 + s_3;

		//在靠近a点对应边位置
		int sum1_1= s_1 + s_2;
		int sum1_2 = s_3 + S_0;
		//在靠近b点对应边位置
		int sum2_1 = s_1 + s_3;
		int sum2_2 = s_2 + S_0;
		//在靠近c点对应边位置
		int sum3_1 = s_2 + s_3;
		int sum3_2 = s_1 + S_0;

		sum = (int)(S_sum/10);
	if ((sum == (int)(S_0/10)) && (s_1 != 0) && (s_2 != 0) && (s_3 != 0)) {
		return 1;
	}
	else if (((int)(sum1_1/10)== (int)(sum1_2 / 10)) && (s_1 != 0) && (s_2 != 0) && (s_3 != 0)) {//在靠近a点对应边位置
		return 2;
	}
	else if (((int)(sum2_1 / 10) == (int)(sum2_2 / 10)) && (s_1 != 0) && (s_2 != 0) && (s_3 != 0)) {//在靠近b点对应边位置
		return 3;
	}
	else if (((int)(sum3_1 / 10) == (int)(sum3_2 / 10)) && (s_1 != 0) && (s_2 != 0) && (s_3 != 0)) {//在靠近c点对应边位置
		return 4;
	}
	else {
		return 0;
	}
}

//求解三角形外心位置
CPoint FindCircumcenter(Triangle triangle) {
	int x1 = triangle.p1.x, y1 = triangle.p1.y;
	int x2 = triangle.p2.x, y2 = triangle.p2.y;
	int x3 = triangle.p3.x, y3 = triangle.p3.y;

	int d1 = (x2 * x2 + y2 * y2) - (x1 * x1 + y1 * y1);
	int d2 = (x3 * x3 + y3 * y3) - (x2 * x2 + y2 * y2);
	int fm = 2 * ((y3 - y2) * (x2 - x1) - (y2 - y1) * (x3 - x2));

	int x = (int)(((y3 - y2) * d1 - (y2 - y1) * d2) / fm);
	int y = (int)(((x2 - x1) * d2 - (x3 - x2) * d1) / fm);

	CPoint Circumcenter = {x,y};
	return Circumcenter;
}

//判断点是否位于三角形的外接圆上
bool IsPtsBuildTriangle(Triangle triangle,CPoint point) {
	//求解三角形外心位置

	CPoint Circumcenter= FindCircumcenter(triangle);

	//计算外心距点的距离
	double distance = dis(Circumcenter, point);
	//i计算外接圆半径
	double R = dis(Circumcenter, triangle.p1);
	//判断
	if (distance < R) {
		return true;
	}
	else {
		return false;
	}
}

//判断两条线是否相同
bool SameLine(Line L1, Line L2) {
	if ((L1.start == L2.start) && (L1.end == L2.end)) {
		return true;
	}
	else if ((L1.start == L2.end) && (L1.end == L2.start)) {
		return true;
	}
	else return false;
}

//判断两三角形是否相同
bool SameTriangle(Triangle triangle_1, Triangle triangle_2) {
	Line t1_L1 = { triangle_1.p1,triangle_1.p2 };
	Line t1_L2 = { triangle_1.p2,triangle_1.p3 };
	Line t1_L3 = { triangle_1.p1,triangle_1.p3 };

	Line t2_L1 = { triangle_2.p1,triangle_2.p2 };
	Line t2_L2 = { triangle_2.p2,triangle_2.p3 };
	Line t2_L3 = { triangle_2.p1,triangle_2.p3 };
	if (SameLine(t1_L1, t2_L1) && SameLine(t1_L2, t2_L2) && SameLine(t1_L3, t2_L3)) {
		return true;
	}
	else if (SameLine(t1_L1, t2_L1) && SameLine(t1_L2, t2_L3) && SameLine(t1_L3, t2_L2)) {
		return true;
	}
	else if (SameLine(t1_L1, t2_L2) && SameLine(t1_L2, t2_L3) && SameLine(t1_L3, t2_L1)) {
		return true;
	}
	else if (SameLine(t1_L1, t2_L2) && SameLine(t1_L2, t2_L1) && SameLine(t1_L3, t2_L3)) {
		return true;
	}
	else if (SameLine(t1_L1, t2_L3) && SameLine(t1_L2, t2_L1) && SameLine(t1_L3, t2_L2)) {
		return true;
	}
	else if (SameLine(t1_L1, t2_L3) && SameLine(t1_L2, t2_L2) && SameLine(t1_L3, t2_L1)) {
		return true;
	}
	else return false;
}

//二、环切边界法凸包三角剖分
void CircumscribedBoundary(list<CPoint>hull_pts, int pNumbers, CPoint* points, CDC* pDC) {
	CPoint point_1 = hull_pts.front();
	hull_pts.pop_front();
	CPoint point_2 = hull_pts.front();
	hull_pts.pop_front();
	CPoint point_3 = hull_pts.front();
	hull_pts.pop_front();
	//若三点所构成的三角形内不含其余点 且 该三个点不是凸包最后三个点
	//if (!(IsPtsBuildTriangle(point_1, point_2, point_3, points, pNumbers))&&(hull_pts.size()>0)) {
	//	//绘制点1到点3的直线
	//	pDC->MoveTo(point_1.x, point_1.y);
	//	pDC->LineTo(point_3.x, point_3.y);
	//	//将点2从凸包中去除
	//	hull_pts.push_front(point_3);
	//	hull_pts.push_front(point_1);

	//	pDC->MoveTo(point_1.x, point_1.y);
	//	pDC->LineTo(point_3.x, point_3.y);

	//	CircumscribedBoundary(hull_pts, pNumbers, points, pDC);
	//}
	//else if ((IsPtsBuildTriangle(point_1, point_2, point_3, points, pNumbers))&&(hull_pts.size() > 0)) {
	//	if (hull_pts.front() != basepoint) {
	//		hull_pts.push_front(point_3);
	//		hull_pts.push_front(point_2);
	//		hull_pts.push_back(point_1);
	//		CircumscribedBoundary(hull_pts, pNumbers, points, pDC);
	//	}
	//}
	if (hull_pts.size() > 0) {
		//绘制点1到点3的直线
		//pDC->MoveTo(point_1.x, point_1.y);
		//pDC->LineTo(point_3.x, point_3.y);
		//将点2从凸包中去除
		hull_pts.push_front(point_3);
		hull_pts.push_back(point_1);
		//将点1，2，3作为三角形保存
		Triangle tri = {point_1,point_2,point_3};
		Tripts.push_back(tri);
		//递归循环
		CircumscribedBoundary(hull_pts, pNumbers, points, pDC);
	}
	else {
		Triangle tri = { point_1,point_2,point_3 };
		Tripts.push_back(tri);
	}
	
	int x = Tripts.size();
}

//三、离散点内插
void DiscretePointInsertion(int pNumbers, CPoint* points, CDC* pDC) {
	//Triangle first = Tripts.front();
	//Tripts.pop_front();
	Triangle temp ;
	//Tripts.push_back(temp);
	for (int i = 0; i < pNumbers; i++) {
		CPoint pptt = points[i];
		int size = Tripts.size();
		int j = 1;
		while (j<=Tripts.size()) {
			temp = Tripts.front();

			if (!IsPtsBuildTriangle(temp, points[i])) {//points[i]不在此三角形外接圆内
				//temp = Tripts.front();
				Tripts.pop_front();
				Tripts.push_back(temp);
				//处理下一个三角形
				j++;
			}
			else {//points[i]在此三角形外接圆内
				//删去该三角形
				Tripts.pop_front();
				//重构新三角形
				if (IsInTriangle(temp, points[i])==1) {//点在三角形内，获得三个新三角形加入
					Triangle new_1 = { temp.p1,temp.p2,points[i] };
					Triangle new_2 = { temp.p1,points[i],temp.p3 };
					Triangle new_3 = { points[i],temp.p2,temp.p3 };
					Tripts.push_back(new_1);
					Tripts.push_back(new_2);
					Tripts.push_back(new_3);
				}
				else if (IsInTriangle(temp, points[i]) == 2) {//在靠近 p1对应边 位置
					//tripts中存在与 p1对应边 相邻三角形
					//list<Triangle>tri(Tripts);
					list<Triangle>::iterator iter;
					//循环查找三角形链表中是否存在  相邻三角形 点在三角形内部
					for (iter = Tripts.begin(); iter != Tripts.end(); iter++) {
						Line l1 = { iter->p1,iter->p2 };
						Line l2 = { iter->p2,iter->p3 };
						Line l3 = { iter->p3,iter->p1 };
						Line l_p1 = { temp.p2,temp.p3 };
						if (!(SameTriangle(temp, (*iter))) && (IsInTriangle(*iter, points[i]) == 1) && (SameLine(l1, l_p1) || SameLine(l2, l_p1) || SameLine(l3, l_p1)))
						{//1、非同一三角形 2、points[i]点在三角形内 3、有相同边
							//加入全新的四个三角形
							Triangle new_1 = { temp.p1,temp.p2,points[i] };
							Triangle new_2 = { temp.p1,points[i],temp.p3 };
							Tripts.push_back(new_1);
							Tripts.push_back(new_2);
							if (SameLine(l1, l_p1)) {
								Triangle new_3 = { iter->p3,temp.p2,points[i] };
								Triangle new_4 = { iter->p3,points[i],temp.p3 };
								Tripts.push_back(new_3);
								Tripts.push_back(new_4);
								iter = Tripts.erase(iter);//链表中删去点在其内部的外部三角形
								break;
							}
							else if (SameLine(l2, l_p1)) {
								Triangle new_3 = { iter->p1,temp.p2,points[i] };
								Triangle new_4 = { iter->p1,points[i],temp.p3 };
								Tripts.push_back(new_3);
								Tripts.push_back(new_4);
								iter = Tripts.erase(iter);//链表中删去点在其内部的外部三角形
								break;
							}
							else if (SameLine(l3, l_p1)) {
								Triangle new_3 = { iter->p2,temp.p2,points[i] };
								Triangle new_4 = { iter->p2,points[i],temp.p3 };
								Tripts.push_back(new_3);
								Tripts.push_back(new_4);
								iter = Tripts.erase(iter);//链表中删去点在其内部的外部三角形
								break;
							}

							//iter = Tripts.erase(iter);//链表中删去点在其内部的外部三角形
							//iter--;
							
						}
						else if(!(SameTriangle(temp, (*iter))) && (IsInTriangle(*iter, points[i]) != 1) && (SameLine(l1, l_p1) || SameLine(l2, l_p1) || SameLine(l3, l_p1))){
							Tripts.push_back(temp);
						}
					}
				}
				else if (IsInTriangle(temp, points[i]) == 3) {//在靠近 p2对应边 位置,
					//tripts中存在与 p2对应边 相邻三角形
					//list<Triangle>tri(Tripts);
					list<Triangle>::iterator iter;
					//循环查找三角形链表中是否存在  相邻三角形 点在三角形内部
					for (iter = Tripts.begin(); iter != Tripts.end(); iter++) {
						Line l1 = { iter->p1,iter->p2 };
						Line l2 = { iter->p2,iter->p3 };
						Line l3 = { iter->p3,iter->p1 };
						Line l_p2 = { temp.p1,temp.p3 };
						if (!(SameTriangle(temp, (*iter))) && (IsInTriangle(*iter, points[i]) == 1)&& (SameLine(l1, l_p2) || SameLine(l2, l_p2) || SameLine(l3, l_p2)))
						{//1、非同一三角形 2、points[i]点在三角形内 3、有相同边 
							//加入全新的四个三角形
							Triangle new_1 = { temp.p2,temp.p1,points[i] };
							Triangle new_2 = { temp.p2,points[i],temp.p3 };
							Tripts.push_back(new_1);
							Tripts.push_back(new_2);
							if (SameLine(l1, l_p2)) {
								Triangle new_3 = { iter->p3,temp.p1,points[i] };
								Triangle new_4 = { iter->p3,points[i],temp.p3 };
								Tripts.push_back(new_3);
								Tripts.push_back(new_4);
								iter = Tripts.erase(iter);//链表中删去点在其内部的外部三角形
								break;
							}
							else if (SameLine(l2, l_p2)) {
								Triangle new_3 = { iter->p1,temp.p1,points[i] };
								Triangle new_4 = { iter->p1,points[i],temp.p3 };
								Tripts.push_back(new_3);
								Tripts.push_back(new_4);
								iter = Tripts.erase(iter);//链表中删去点在其内部的外部三角形
								break;
							}
							else if (SameLine(l3, l_p2)) {
								Triangle new_3 = { iter->p2,temp.p1,points[i] };
								Triangle new_4 = { iter->p2,points[i],temp.p3 };
								Tripts.push_back(new_3);
								Tripts.push_back(new_4);
								iter = Tripts.erase(iter);//链表中删去点在其内部的外部三角形
								break;
							}
						}
						else if (!(SameTriangle(temp, (*iter))) && (IsInTriangle(*iter, points[i]) != 1) && (SameLine(l1, l_p2) || SameLine(l2, l_p2) || SameLine(l3, l_p2))) {
							Tripts.push_back(temp);
						}
					}
				}
				else if (IsInTriangle(temp, points[i]) == 4) {//在靠近 p3对应边 位置,获得2个新三角形加入
					//tripts中存在与 p3对应边 相邻三角形
					//list<Triangle>tri(Tripts);
					list<Triangle>::iterator iter;
					//循环查找三角形链表中是否存在  相邻三角形 点在三角形内部
					for (iter = Tripts.begin(); iter != Tripts.end(); iter++) {
						Line l1 = { iter->p1,iter->p2 };
						Line l2 = { iter->p2,iter->p3 };
						Line l3 = { iter->p3,iter->p1 };
						Line l_p3 = { temp.p1,temp.p2 };
						if (!(SameTriangle(temp, (*iter))) && (IsInTriangle(*iter, points[i]) == 1) && (SameLine(l1, l_p3) || SameLine(l2, l_p3) || SameLine(l3, l_p3)))
						{//1、非同一三角形 2、points[i]点在三角形内 3、有相同边 
							//加入全新的四个三角形
							Triangle new_1 = { temp.p3,temp.p1,points[i] };
							Triangle new_2 = { temp.p3,points[i],temp.p2 };
							Tripts.push_back(new_1);
							Tripts.push_back(new_2);
							if (SameLine(l1, l_p3)) {
								Triangle new_3 = { iter->p3,temp.p1,points[i] };
								Triangle new_4 = { iter->p3,points[i],temp.p2 };
								Tripts.push_back(new_3);
								Tripts.push_back(new_4);
								iter = Tripts.erase(iter);//链表中删去点在其内部的外部三角形
								break;
							}
							else if (SameLine(l2, l_p3)) {
								Triangle new_3 = { iter->p1,temp.p1,points[i] };
								Triangle new_4 = { iter->p1,points[i],temp.p2 };
								Tripts.push_back(new_3);
								Tripts.push_back(new_4);
								iter = Tripts.erase(iter);//链表中删去点在其内部的外部三角形
								break;
							}
							else if (SameLine(l3, l_p3)) {
								Triangle new_3 = { iter->p2,temp.p1,points[i] };
								Triangle new_4 = { iter->p2,points[i],temp.p2 };
								Tripts.push_back(new_3);
								Tripts.push_back(new_4);
								iter = Tripts.erase(iter);//链表中删去点在其内部的外部三角形
								break;
							}

							//iter = Tripts.erase(iter);//链表中删去点在其内部的外部三角形
						}
						else if (!(SameTriangle(temp, (*iter))) && (IsInTriangle(*iter, points[i]) != 1) && (SameLine(l1, l_p3) || SameLine(l2, l_p3) || SameLine(l3, l_p3))) {
							Tripts.push_back(temp);
						}
					}
				}
				else  {//点在三角形上if (IsInTriangle(temp, points[i]) == 0)
					//再次放回
					Tripts.push_back(temp);
				}
				//处理下一个三角形
				j++;
				
			}
			
		}
	}
}


//四、三角形局部优化
void LocalOptimization() {
	//list<Triangle>::iterator i;
	list<Triangle>::iterator i;
	for ( i = Tripts.begin(); i != Tripts.end();i++) {
		//寻找与三角形i相邻的三角形
		list<Triangle>::iterator j;
		for (j = Tripts.begin(); j != Tripts.end(); j++) {
			Line i_l3 = { i->p1,i->p2 };
			Line i_l1 = { i->p2,i->p3 };
			Line i_l2 = { i->p3,i->p1 };
			int size = Tripts.size();
			Line j_l3 = { j->p1,j->p2 };
			Line j_l1 = { j->p2,j->p3 };
			Line j_l2 = { j->p3,j->p1 };
			if ((SameLine(i_l1, j_l1) || SameLine(i_l2, j_l1) || SameLine(i_l3, j_l1)) && (!(SameTriangle((*j), (*i))))) {
				if (SameLine(i_l1, j_l1) && (IsPtsBuildTriangle(*i, j->p1))) {//三角形j的p1点对应边  与三角形i的p1点对应边相同  且p1在三角形i的外接圆内

					//加入更换对角线后的全新的三角形
					Triangle new1 = { j->p1,i->p2,i->p1 };
					Triangle new2 = { j->p1,i->p3,i->p1 };
					Tripts.push_back(new1);
					Tripts.push_back(new2);
					//删去原有的i，j
					i = Tripts.erase(i);
					if (i != Tripts.begin()) {
						i--;
					}
					else {
						i = Tripts.begin();
					}
					
					j = Tripts.erase(j);
					//break;

				}
				else if (SameLine(i_l2, j_l1) && (IsPtsBuildTriangle(*i, j->p1))) {//三角形j的p1点对应边  与三角形i的p2点对应边相同  且p1在三角形i的外接圆内

					//加入更换对角线后的全新的三角形
					Triangle new1 = { j->p1,i->p1,i->p2 };
					Triangle new2 = { j->p1,i->p3,i->p2 };
					Tripts.push_back(new1);
					Tripts.push_back(new2);
					//删去原有的i，j
					i = Tripts.erase(i);
					if (i != Tripts.begin()) {
						i--;
					}
					else {
						i = Tripts.begin();
					}

					j = Tripts.erase(j);
				}
				else if (SameLine(i_l3, j_l1) && (IsPtsBuildTriangle(*i, j->p1))) {//三角形j的p1点对应边  与三角形i的p3点对应边相同  且p1在三角形i的外接圆内

					//加入更换对角线后的全新的三角形
					Triangle new1 = { j->p1,i->p2,i->p3 };
					Triangle new2 = { j->p1,i->p1,i->p3 };
					Tripts.push_back(new1);
					Tripts.push_back(new2);
					//删去原有的i，j
					i = Tripts.erase(i);
					if (i != Tripts.begin()) {
						i--;
					}
					else {
						i = Tripts.begin();
					}

					j = Tripts.erase(j);
				}

			}

			else if ((SameLine(i_l1, j_l2) || SameLine(i_l2, j_l2) || SameLine(i_l3, j_l2)) && (!(SameTriangle((*j), (*i))))) {
				if (SameLine(i_l1, j_l2) && (IsPtsBuildTriangle(*i, j->p2))) {//三角形j的p2点对应边  与三角形i的p1点对应边相同  且p1在三角形i的外接圆内

					//加入更换对角线后的全新的三角形
					Triangle new1 = { j->p2,i->p2,i->p1 };
					Triangle new2 = { j->p2,i->p3,i->p1 };
					Tripts.push_back(new1);
					Tripts.push_back(new2);
					//删去原有的i，j
					i = Tripts.erase(i);
					if (i != Tripts.begin()) {
						i--;
					}
					else {
						i = Tripts.begin();
					}

					j = Tripts.erase(j);
				}
				else if (SameLine(i_l2, j_l2) && (IsPtsBuildTriangle(*i, j->p2))) {//三角形j的p2点对应边  与三角形i的p2点对应边相同  且p1在三角形i的外接圆内

					//加入更换对角线后的全新的三角形
					Triangle new1 = { j->p2,i->p1,i->p2 };
					Triangle new2 = { j->p2,i->p3,i->p2 };
					Tripts.push_back(new1);
					Tripts.push_back(new2);
					//删去原有的i，j
					i = Tripts.erase(i);
					if (i != Tripts.begin()) {
						i--;
					}
					else {
						i = Tripts.begin();
					}

					j = Tripts.erase(j);
				}
				else if (SameLine(i_l3, j_l2) && (IsPtsBuildTriangle(*i, j->p2))) {//三角形j的p2点对应边  与三角形i的p3点对应边相同  且p1在三角形i的外接圆内

					//加入更换对角线后的全新的三角形
					Triangle new1 = { j->p2,i->p2,i->p3 };
					Triangle new2 = { j->p2,i->p1,i->p3 };
					Tripts.push_back(new1);
					Tripts.push_back(new2);
					//删去原有的i，j
					i = Tripts.erase(i);
					if (i != Tripts.begin()) {
						i--;
					}
					else {
						i = Tripts.begin();
					}

					j = Tripts.erase(j);
				}

			}

			else if ((SameLine(i_l1, j_l3) || SameLine(i_l2, j_l3) || SameLine(i_l3, j_l3)) && (!(SameTriangle((*j), (*i))))) {
				if (SameLine(i_l1, j_l3) && (IsPtsBuildTriangle(*i, j->p3))) {//三角形j的p3点对应边  与三角形i的p1点对应边相同  且p1在三角形i的外接圆内

					//加入更换对角线后的全新的三角形
					Triangle new1 = { j->p3,i->p2,i->p1 };
					Triangle new2 = { j->p3,i->p3,i->p1 };
					Tripts.push_back(new1);
					Tripts.push_back(new2);
					//删去原有的i，j
					i = Tripts.erase(i);
					if (i != Tripts.begin()) {
						i--;
					}
					else {
						i = Tripts.begin();
					}

					j = Tripts.erase(j);
				}
				else if (SameLine(i_l2, j_l3) && (IsPtsBuildTriangle(*i, j->p3))) {//三角形j的p3点对应边  与三角形i的p2点对应边相同  且p1在三角形i的外接圆内

					//加入更换对角线后的全新的三角形
					Triangle new1 = { j->p3,i->p1,i->p2 };
					Triangle new2 = { j->p3,i->p3,i->p2 };
					Tripts.push_back(new1);
					Tripts.push_back(new2);
					//删去原有的i，j
					i = Tripts.erase(i);
					if (i !=Tripts.begin()) {
						i--;
					}
					else {
						i = Tripts.begin();
					}

					j = Tripts.erase(j);
				}
				else if (SameLine(i_l3, j_l3) && (IsPtsBuildTriangle(*i, j->p3))) {//三角形j的p3点对应边  与三角形i的p3点对应边相同  且p1在三角形i的外接圆内

					//加入更换对角线后的全新的三角形
					Triangle new1 = { j->p3,i->p2,i->p3 };
					Triangle new2 = { j->p3,i->p1,i->p3 };
					Tripts.push_back(new1);
					Tripts.push_back(new2);
					//删去原有的i，j
					i = Tripts.erase(i);
					if (i != Tripts.begin()) {
						i--;
					}
					else {
						i = Tripts.begin();
					}

					j = Tripts.erase(j);
				}
			}
		}
		//if (Tripts.begin() == Tripts.end()) break;
	}
}



//五、三角形绘制
void DrawTriangle(CDC* pDC) {
	CPoint p1 ;
	CPoint p2 ;
	CPoint p3 ;
	while (Tripts.size()!=0) {
		Triangle tri_temp = Tripts.front();
		Tripts.pop_front();
		int size = Tripts.size();
		p1 = tri_temp.p1;
		p2 = tri_temp.p2;
		p3 = tri_temp.p3;
		

		//声明两个CPen对象
		CPen m_newPen, * m_oldPen;
		//创建新画笔
		m_newPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		//将新画笔选入设备上下文，并且保存旧画笔
		m_oldPen = pDC->SelectObject(&m_newPen);
		pDC->MoveTo(p1.x, p1.y);
		pDC->LineTo(p2.x, p2.y);

		pDC->MoveTo(p2.x, p2.y);
		pDC->LineTo(p3.x, p3.y);

		pDC->MoveTo(p3.x, p3.y);
		pDC->LineTo(p1.x, p1.y);
		//将备份的旧画笔赋值给设备上下文
		pDC->SelectObject(m_oldPen);

	}

}


void Ccg2021ZYLDelaunayTriangulationView::Delaunay(int pNumbers, CPoint* points, CDC* pDC) {
	//一、凸包生成
	list<CPoint>hullpts;
	list<CPoint>pts;
	sort(points, points + pNumbers,cmp1);//找y值最小点做基点
	CPoint basepoint = points[0];
	sort(points + 1, points + pNumbers, cmp);//将后面部分按与basepoint极角大小由小到大排序
	hullpts.push_back(basepoint);//将已知的basepoint点放入链表
	hullpts.push_back(points[1]);//将已知的第一个需要判断的极角点放入链表

	for (int i = 2; i < pNumbers; i++) {
		CPoint lastOne = hullpts.back();
		hullpts.pop_back();

		CPoint penultimateOne=hullpts.back();
		hullpts.push_back(lastOne);
		while (i >= 1 && cross(penultimateOne, lastOne, points[i]) < 0) {
			hullpts.pop_back();

			lastOne = hullpts.back();
			hullpts.pop_back();
			penultimateOne = hullpts.back();
			hullpts.push_back(lastOne);
		}
		hullpts.push_back(points[i]);
	}

	list<CPoint>hull_pts;
	//将存入hullpts链表的凸包点进行连接
	CPoint first = hullpts.front();
	hullpts.pop_front();
	hull_pts.push_back(first);
	while (!hullpts.empty()) {
		CPoint next = hullpts.front();
		pDC->MoveTo(first.x, first.y);
		pDC->LineTo(next.x, next.y);
		first = next;
		hullpts.pop_front();

		hull_pts.push_back(first);
	}
	pDC->MoveTo(first.x, first.y);
	pDC->LineTo(basepoint.x, basepoint.y);
	
	//二、环切边界法凸包三角剖分
	CircumscribedBoundary(hull_pts, pNumbers, points, pDC);

	//三、离散点内插
	DiscretePointInsertion(pNumbers, points, pDC);

	//四、三角形局部优化
    LocalOptimization();

	//五、三角形绘制
	DrawTriangle(pDC);
}


