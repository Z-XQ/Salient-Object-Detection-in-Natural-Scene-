
// ShowJpgDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CShowJpgDlg �Ի���
class CShowJpgDlg : public CDialogEx
{
// ����
public:
	CShowJpgDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SHOWJPG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
