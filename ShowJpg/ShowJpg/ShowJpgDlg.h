
// ShowJpgDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CShowJpgDlg 对话框
class CShowJpgDlg : public CDialogEx
{
// 构造
public:
	CShowJpgDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SHOWJPG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

    BOOL ShowJpgGif(CDC* pDC,CString strPath, int x, int y);
     BOOL ShowImage(CDC* pDC,CString strPath, int x, int y);
public:
    afx_msg void OnBnClickedBtnBrowse();
	afx_msg void OnBnClickedProcess();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	CComboBox combox01;
	CComboBox combox02;
	afx_msg void OnBnClickedBtnProcess2();
};
