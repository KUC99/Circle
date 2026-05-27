
// CircleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Circle.h"
#include "CircleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CCircleDlg 대화 상자



CCircleDlg::CCircleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CIRCLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCircleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCircleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_RANDOM, &CCircleDlg::OnBnClickedBtnRandom)
	ON_EN_CHANGE(IDC_EDT, &CCircleDlg::OnEnChangeEdt)
	ON_BN_CLICKED(IDC_RESET, &CCircleDlg::OnBnClickedReset)
END_MESSAGE_MAP()


// CCircleDlg 메시지 처리기

BOOL CCircleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCircleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.
//
// 
// 
void CCircleDlg::drawPoint(CDC* pDC, int x, int y)
{
	for (int j = y - 2; j <= y + 2; j++)
	{
		for (int i = x - 2; i <= x + 2; i++)
		{
			pDC->SetPixel(i, j, RGB(255, 0, 0));
		}
	}
}
//void CCircleDlg::OnPaint()
//{
//	if (IsIconic())
//	{
//		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
//
//		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
//
//		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
//		int cxIcon = GetSystemMetrics(SM_CXICON);
//		int cyIcon = GetSystemMetrics(SM_CYICON);
//		CRect rect;
//		GetClientRect(&rect);
//		int x = (rect.Width() - cxIcon + 1) / 2;
//		int y = (rect.Height() - cyIcon + 1) / 2;
//
//		// 아이콘을 그립니다.
//		dc.DrawIcon(x, y, m_hIcon);
//	}
//	else
//	{
//		CDialogEx::OnPaint();
//	}
//}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.


HCURSOR CCircleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);

}



void CCircleDlg::drawCircle(CDC* pDC,int cx,int cy,
int radius)
{
    for (int y = cy - radius; y <= cy + radius; y++)
    {
        for (int x = cx - radius; x <= cx + radius; x++)
        {
            int dx = x - cx;
            int dy = y - cy;

            // 원 내부 판정
            if (dx * dx + dy * dy <= radius * radius)
            {
                pDC->SetPixel(x, y, RGB(0, 0, 0));
            }
        }
    }
}



void CCircleDlg::drawCircle1(CDC* pDC, int cx, int cy, int radius)
{
	int r2 = radius * radius;

	for (int y = cy - radius; y <= cy + radius; y++)
	{
		for (int x = cx - radius; x <= cx + radius; x++)
		{
			int dx = x - cx;
			int dy = y - cy;
			int d = dx * dx + dy * dy;

			// 테두리만
			if (d >= r2 - radius &&
				d <= r2 + radius)
			{
				pDC->SetPixel(x, y, RGB(0, 0, 0));
			}
		}
	}
}


//void CCircleDlg::OnLButtonDown(UINT nFlags, CPoint point)
//{	m_points.push_back(point);
//	CDialogEx::OnLButtonDown(nFlags, point);
//}


void CCircleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 점 추가
	if (m_points.size() < 3)
	{
		m_points.push_back(point);

		if (m_points.size() == 3)
		{
			calculateCircle();
		}

		Invalidate();

		return;
	}

	// 드래그 시작
	const int radius = 10;

	for (int i = 0; i < m_points.size(); i++)
	{
		int dx = point.x - m_points[i].x;
		int dy = point.y - m_points[i].y;

		if ((dx * dx + dy * dy) <= radius * radius)
		{
			m_dragging = true;
			m_dragIndex = i;

			SetCapture();

			break;
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CCircleDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_dragging)
	{
		m_points[m_dragIndex] = point;

		calculateCircle();

		Invalidate();
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

void CCircleDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_dragging = false;
	m_dragIndex = -1;

	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CCircleDlg::OnPaint()
{
	CPaintDC dc(this);

	// 점 출력
	for (auto& p : m_points)
	{
		drawCircle(&dc, p.x, p.y,m_radius);
	}

	// 원 외각
	if (m_bDrawCircle)
	{
		drawCircle1(&dc,m_center.x,m_center.y,m_radius1);
	}


}





void CCircleDlg::calculateCircle()
{
	CPoint p1 = m_points[0];
	CPoint p2 = m_points[1];
	CPoint p3 = m_points[2];

	double x1 = p1.x;
	double y1 = p1.y;

	double x2 = p2.x;
	double y2 = p2.y;

	double x3 = p3.x;
	double y3 = p3.y;

	double D =
		2 * (x1 * (y2 - y3) +
			x2 * (y3 - y1) +
			x3 * (y1 - y2));

	if (abs(D) < 5000)
	{
		m_bDrawCircle = false;
		m_bDrawLine = true;

		return;
	}

	double cx =
		((x1 * x1 + y1 * y1) * (y2 - y3) +
			(x2 * x2 + y2 * y2) * (y3 - y1) +
			(x3 * x3 + y3 * y3) * (y1 - y2)) / D;

	double cy =
		((x1 * x1 + y1 * y1) * (x3 - x2) +
			(x2 * x2 + y2 * y2) * (x1 - x3) +
			(x3 * x3 + y3 * y3) * (x2 - x1)) / D;

	m_center.x = (int)cx;
	m_center.y = (int)cy;

	double dx = cx - x1;
	double dy = cy - y1;

	m_radius1 = (int)sqrt(dx * dx + dy * dy);

	m_bDrawCircle = true;
}



void CCircleDlg::OnBnClickedBtnRandom()
{
	if (m_bRandomRunning)
		return;

	m_bRandomRunning = true;

	AfxBeginThread(Thread, this);
}

UINT CCircleDlg::Thread(LPVOID pParam)
{
	CCircleDlg* pDlg = (CCircleDlg*)pParam;

	for (int i = 0; i < 10; i++)
	{
		pDlg->m_points.clear();

		for (int j = 0; j < 3; j++)
		{
			int x = rand() % 500 + 50;
			int y = rand() % 400 + 50;

			pDlg->m_points.push_back(CPoint(x, y));
		}
		pDlg->calculateCircle();
		pDlg->Invalidate();

		Sleep(500);
	}

	pDlg->m_bRandomRunning = false;

	return 0;
}



void CCircleDlg::OnEnChangeEdt()
{
	m_radius = GetDlgItemInt(IDC_EDT);
	Invalidate();
}

void CCircleDlg::OnBnClickedReset()
{
	m_points.clear();

	m_dragging = false;
	m_dragIndex = -1;
	m_bDrawCircle = 0;
	Invalidate();
}
