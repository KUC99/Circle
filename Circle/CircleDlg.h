
// CircleDlg.h: 헤더 파일
//

#pragma once

#include <vector>

using namespace std;
// CCircleDlg 대화 상자
class CCircleDlg : public CDialogEx
{
// 생성입니다.
public:
	CCircleDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CIRCLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	std::vector <CPoint> m_points;
	CPoint m_center;
	int m_radius = 7;
	int m_radius1 = 7;
	bool m_bDrawCircle = false;
	void CCircleDlg::drawCircle(CDC* pDC,int cx,int cy,int radius);
	void CCircleDlg::drawPoint(CDC* pDC, int x, int y);
	void CCircleDlg::drawCircle1(CDC* pDC, int cx, int cy, int radius);
	void CCircleDlg::calculateCircle();
	CPoint m_startPoint;
	bool m_dragging = false;
	int m_dragIndex = -1;CPoint m_endPoint;

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);


	afx_msg void CCircleDlg::OnBnClickedBtnRandom();
	bool m_bRandomRunning = false;
	static UINT Thread(LPVOID pParam);
	afx_msg void CCircleDlg::OnEnChangeRadiusPoint();
	afx_msg void CCircleDlg::OnEnChangeEdt();
	afx_msg void CCircleDlg::OnBnClickedReset();

	bool m_bDrawLine = false;
};
