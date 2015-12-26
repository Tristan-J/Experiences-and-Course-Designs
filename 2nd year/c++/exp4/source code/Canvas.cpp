// Canvas.cpp : 实现文件
//
#pragma once
#include "stdafx.h"
#include "experiment.h"
#include "Canvas.h"

//{{ 外部说明添加到这里
extern List <qPtr> list;
//}}

// Canvas
Canvas * Canvas::pCanvas = NULL;
bool Canvas::isLearning = false;

IMPLEMENT_DYNCREATE(Canvas, CScrollView)

Canvas::Canvas()
{
	pCanvas = this;

	quadMap.insert(KV("Parallelogram", para));
	quadMap.insert(KV("Rectangle", rect));
	quadMap.insert(KV("Square", sqr));
	quadMap.insert(KV("Diamond", diam));
	quadMap.insert(KV("Trapezoid", trap));
}

static CString formatString[] = 
{ 
	_T("宽=%lf, 高=%lf, 面积="),
	_T("对角线1=%lf, 对角线2=%lf, 面积="),
	_T("平行边1=%lf, 平行边2=%lf, 高=%lf, 面积=")
};

Canvas::~Canvas()
{
}


BEGIN_MESSAGE_MAP(Canvas, CScrollView)

END_MESSAGE_MAP()


// Canvas 绘图

void Canvas::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	//CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	//sizeTotal.cx = sizeTotal.cy = 100;
	//SetScrollSizes(MM_TEXT, sizeTotal);
}

union _QUADPTR_
{
	Quadrangle *q;
	Parallelogram *p;
	Rect *r;
	Diamond *d;
	Square *s;
	Trapezoid *t;
};
void Canvas::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码

	CRect rect;
	GetClientRect(&rect);

	CBrush br(RGB(220, 200, 170));
	CBrush * oldBrush = reinterpret_cast<CBrush*>(pDC->SelectObject (&br));
	
	int xc, yc;
	int vw = rect.Width (), vh = rect.Height ();
	int sw = static_cast<int>(vw * 0.75 / 2.0), sh = static_cast<int>(vh * 0.75 / 2.0);
	SIZE ad[5][4] = 
	{	{ { -sw + 50, -sh }, { sw + 50, -sh }, { sw - 50, sh }, { -sw - 50, sh } },
		{ { -sw, -sh }, { sw, -sh }, { sw, sh }, { -sw, sh } }, 
		{ { -sh, -sh }, { sh, -sh }, { sh, sh }, { -sh, sh } },
		{ { 0, -sh }, { sw, 0 }, { 0, sh }, { -sw, 0 } },
		{ { -sw + 120, -sh }, { sw - 80, -sh }, { sw, sh }, { -sw, sh } },
	};

	double ratio = 1.0;
	int yOffset = 120;
	if (isLearning)
	{
		xc = vw / 2;
		yc = vh / 2;
	}
	else
	{
		xc = 80;
		yc = 60;
		ratio = 0.3;
	}
	
	POINT vert[4];
	int shape;
	List<qPtr>::Iterator itr;
	List<qPtr>::Iterator end = list.end();
	List<qPtr>::Iterator begin = list.begin();
	if (isLearning) begin = begin + (list.size() - 1);
	_QUADPTR_ quad;
	string name;
	CString msg, msg2;
	for (itr = begin; itr != end; ++itr)
	{
		quad.q = *itr;
		name = quad.q->what();
		area = quad.q->area ();

		shape = quadMap[name];
		switch (shape)
		{
		case trap:
			msg.Format(formatString[2], quad.t->Width(), quad.t->Width2(), quad.t->Height());
			break;

		case diam: 
			msg.Format(formatString[1], quad.p->Width(), quad.p->Height());
			break;

		default:
			msg.Format(formatString[0], quad.p->Width(), quad.p->Height());
		}

		if (isLearning) msg2 = _T("？");
		else msg2.Format (_T("%.1lf"), area);
		msg += msg2;

		for (int i = 0; i < 4; ++i)
		{
			vert[i].x = static_cast<int>(xc + (ad[shape][i].cx * ratio)); 
			vert[i].y = static_cast<int>(yc + (ad[shape][i].cy * ratio));
		}
		
		int tx, ty;
		if (isLearning) 
		{
			tx = xc - sw;
			ty = yc + sh + 8;
		}
		else
		{
			CBrush br(RGB(240, 240, 240));
			CBrush *oldbr = reinterpret_cast<CBrush *>(pDC->SelectObject(&br));
			CPen *oldpen = reinterpret_cast<CPen *>(pDC->SelectStockObject(NULL_PEN));
			pDC->Rectangle (xc - 80, yc - 50, xc + 600, yc + 50);
			pDC->SelectObject(oldbr);
			pDC->SelectObject(oldpen);

			tx = xc + yOffset - 24;
			ty = yc - 8;
			yc += yOffset;
		}

		pDC->Polygon (vert, 4);
		pDC->SetBkMode (TRANSPARENT);
		pDC->TextOutW (tx, ty, msg);
	}

	pDC->SelectObject (oldBrush);
}

void Canvas::drawQuad(const Quadrangle *quad)
{
	if (isLearning) pCanvas->Invalidate ();
}

// Canvas 诊断

#ifdef _DEBUG
void Canvas::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void Canvas::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG

bool Canvas::toggleMode(void)
{
	return isLearning = !isLearning;
}