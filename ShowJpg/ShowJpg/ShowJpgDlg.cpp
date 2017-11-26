
// ShowJpgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ShowJpg.h"
#include "ShowJpgDlg.h"
#include "afxdialogex.h"
#include<saliency.h>
#include<MSaliency.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CShowJpgDlg �Ի���




CShowJpgDlg::CShowJpgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowJpgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShowJpgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, combox01);
	DDX_Control(pDX, IDC_COMBO2, combox02);
}

BEGIN_MESSAGE_MAP(CShowJpgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BTN_BROWSE, &CShowJpgDlg::OnBnClickedBtnBrowse)
	ON_BN_CLICKED(IDC_BTN_PROCESS, &CShowJpgDlg::OnBnClickedProcess)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CShowJpgDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CShowJpgDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BTN_PROCESS2, &CShowJpgDlg::OnBnClickedBtnProcess2)
END_MESSAGE_MAP()


// CShowJpgDlg ��Ϣ�������

BOOL CShowJpgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	/*
	CComboBox *combox = NULL;
	combox = (CComboBox*)GetDlgItem(IDC_COMBO1);//��ȡcombobox����ָ��
	*/
	combox01.AddString(_T("FT"));
	combox01.AddString(_T("RC"));
	combox01.AddString(_T("HC"));
	combox01.AddString(_T("LC"));
	combox01.AddString(_T("ITTI"));
	// Ĭ��ѡ���һ��   
	combox01.SetCurSel(0);

	combox02.AddString(_T("gc"));
	combox02.AddString(_T("th"));
	combox02.AddString(_T("ms"));
	// Ĭ��ѡ���һ��   
	combox02.SetCurSel(0);



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CShowJpgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CShowJpgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CShowJpgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//************************************
// ����˵��:    ��ʾJPG��GIF��BMPͼƬ
// ����˵��:    CDC * pDC           �豸��������
// ����˵��:    CString strPath     Ҫ��ʾ��ͼƬ·�� 
// ����˵��:    int x               Ҫ��ʾ��Xλ��
// ����˵��:    int y               Ҫ��ʾ��Yλ��
// ����ֵ:      BOOL                �ɹ�����TRUE,���򷵻�FALSE
//************************************
BOOL CShowJpgDlg::ShowJpgGif(CDC* pDC,CString strPath, int x, int y)

{
    CFileStatus fstatus;  
    CFile file;  
    ULONGLONG cb;  

    // ���ļ�������ļ�����Ч��
     if (!file.Open(strPath,CFile::modeRead))
     {
         return FALSE;
     }
     if (!file.GetStatus(strPath,fstatus))
     {
         return FALSE;
     }
     if ((cb =fstatus.m_size)<=0)
     {
         return FALSE;
     }

     // �����ļ���С�����ڴ�ռ�,�ǵ��ͷ��ڴ�
     HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, (unsigned int)cb);  
      if (hGlobal== NULL) 
      {
          return FALSE;
      }

      // �����ղŷ�����ڴ�ռ�
      LPVOID pvData = NULL;  
      pvData = GlobalLock(hGlobal);
      if (pvData == NULL)  
      {  
            GlobalFree(hGlobal);  // �ǵ��ͷ��ڴ�
            return FALSE;
      } 

      // ���ļ��ŵ�����
      IStream *pStm;  
      file.Read(pvData,(unsigned int)cb);  
      GlobalUnlock(hGlobal);  
      CreateStreamOnHGlobal(hGlobal, TRUE, &pStm);  
 
    // �����м���ͼƬ
    // ��ʾJPEG��GIF��ʽ��ͼƬ��GIFֻ����ʾһ֡����������ʾ������
    // Ҫ��ʾ����GIF��ʹ��ACTIVE�ؼ���
    IPicture *pPic; 
    if(OleLoadPicture(pStm,(LONG)fstatus.m_size,TRUE,IID_IPicture,(LPVOID*)&pPic)!=S_OK) 
    { 
        GlobalFree(hGlobal);  // �ǵ��ͷ��ڴ�
        return FALSE;
    }

    //��ȡͼ���͸�,ע������Ŀ�͸߲���ͼ��ķֱ���
    OLE_XSIZE_HIMETRIC hmWidth;  
    OLE_YSIZE_HIMETRIC hmHeight;  
    pPic->get_Width(&hmWidth);  
    pPic->get_Height(&hmHeight);  
    RECT rtWnd;
    pDC->GetWindow()->GetWindowRect(&rtWnd);
    int iWndWidth=rtWnd.right-rtWnd.left;
    int iWndHeight=rtWnd.bottom-rtWnd.top;
    
    if(FAILED(pPic->Render(*pDC,x,y,iWndWidth,iWndHeight,0,hmHeight,hmWidth,-hmHeight,NULL)))  
    {
        pPic->Release();
        GlobalFree(hGlobal);  // �ǵ��ͷ��ڴ�
        return false;
    }

    pPic->Release(); 
    GlobalFree(hGlobal);  // �ǵ��ͷ��ڴ�
    return true;
}

//************************************
// ����˵��:    ��ʾJPG��GIF��BMPͼƬ
// ����˵��:    CDC * pDC           �豸��������
// ����˵��:    CString strPath     Ҫ��ʾ��ͼƬ·�� 
// ����˵��:    int x               Ҫ��ʾ��Xλ��
// ����˵��:    int y               Ҫ��ʾ��Yλ��
// ����ֵ:      BOOL                �ɹ�����TRUE,���򷵻�FALSE
//************************************
BOOL CShowJpgDlg::ShowImage(CDC* pDC,CString strPath, int x, int y)
{
   
    IPicture *pPic=NULL; 
    OleLoadPicturePath(CComBSTR(strPath.GetBuffer()), (LPUNKNOWN)NULL, 0, 0, IID_IPicture,(LPVOID*)&pPic);
    if (NULL==pPic)
    {
        return FALSE;
    }

    // ��ȡͼ���͸�,ע������Ŀ�͸߲���ͼ��ķֱ���
    OLE_XSIZE_HIMETRIC hmWidth;  
    OLE_YSIZE_HIMETRIC hmHeight;  
    pPic->get_Width(&hmWidth);  
    pPic->get_Height(&hmHeight);  

    // ��ͼ���Ⱥ͸߶ȵ�λת��Ϊ���ص�λ
   //#define HIMETRIC_PER_INCH 2540
   //int nPicWidth =  MulDiv(hmWidth, GetDeviceCaps(GetDC()->m_hDC, LOGPIXELSX),2540);
   //int nPicHeight = MulDiv(hmHeight, GetDeviceCaps(GetDC()->m_hDC, LOGPIXELSY),2540);

   // ��ȡ��ʾͼƬ���ڵĿ�Ⱥ͸߶�
   RECT rtWnd;
   pDC->GetWindow()->GetWindowRect(&rtWnd);
   int iWndWidth=rtWnd.right-rtWnd.left;
   int iWndHeight=rtWnd.bottom-rtWnd.top;

   if(FAILED(pPic->Render(*pDC,x,y,iWndWidth,iWndHeight,0,hmHeight,hmWidth,-hmHeight,NULL)))  
   {
       pPic->Release();
       return false;
   }

   pPic->Release(); 
   return true;
}


//************************************
// ����˵��:    ���ͼƬ
// ����ֵ:      void
//************************************
string ff(string w){

	for (size_t i = 0; i<w.size(); i++) {
		if (w[i] == '\\') {
			w.insert(i, string("\\"));
			i++;
		}
	}
	return w;
}
CString basicpath;
CString spath;

CString combox_choose_1="FT";
CString combox_choose_2 = "gc";
int flag = 0;
void CShowJpgDlg::OnBnClickedBtnBrowse()
{
    // TODO: Add your control notification handler code here
    CFileDialog dlg(TRUE,"jpg","*.jpg", OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, 
        "JPEG�ļ�(*.jpg)|*.jpg|GIF�ļ�(*.gif)|*.gif|bmp�ļ�(*.bmp)|*.bmp|",NULL); 
    if(dlg.DoModal()==IDOK) 
    { 
        SetDlgItemText(IDC_TXT_PATH,dlg.GetPathName());
		basicpath = dlg.GetPathName();
		basicpath = ff((string)basicpath).c_str();
		flag = 1;
        //���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ����ʹλͼ��ʾ����
        ((CStatic*)GetDlgItem(IDC_STATIC_IMG))-> ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);

        //ShowJpgGif(GetDlgItem(IDC_STATIC_IMG)->GetDC(),dlg.GetPathName(),0,0);
        ShowImage(GetDlgItem(IDC_STATIC_IMG)->GetDC(),dlg.GetPathName(),0,0);
    } 

}


//************************************
// ����˵��:    ����ͼƬ
// ����ֵ:      void
//************************************

void CShowJpgDlg::OnBnClickedProcess()
{
	
	if (flag == 1){
		system("del /q C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Imgs\\*");
		system("del /q C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\*");
		SetDlgItemText(IDC_Label01, _T(basicpath));
		Mat img = imread((string)basicpath);
		imwrite("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Imgs\\1.jpg", img);
		saliency w;
		w.check();
		flag++;
	}
	
	

	//CmSalCut::Demo(inDir + "*.jpg", inDir + "*.png", outDir);	//�ڶ�������ûɶ��
	
	ShowImage(GetDlgItem(IDC_STATIC_IMG)->GetDC(), basicpath, 0, 0);

	if (combox_choose_1 == "FT"){
		spath = "C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_FT.png";
		SetDlgItemText(IDC_Label01, _T(combox_choose_1));
		Mat w = imread("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_FT.png");
		imwrite("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_FT.jpg", w);
		CString m_filename("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_FT.jpg");//�ļ���
		//���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ����ʹλͼ��ʾ����
		((CStatic*)GetDlgItem(IDC_STATIC_IMG2))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
		ShowImage(GetDlgItem(IDC_STATIC_IMG2)->GetDC(), m_filename, 0, 0);

		
	}
	else if (combox_choose_1 == "RC"){
		spath = "C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_RC.jpg";
		SetDlgItemText(IDC_Label01, _T(combox_choose_1));
		Mat w = imread("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_RC.png");
		imwrite("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_RC.jpg", w);
		CString m_filename("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_RC.jpg");//�ļ���
		//���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ����ʹλͼ��ʾ����
		((CStatic*)GetDlgItem(IDC_STATIC_IMG2))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
		ShowImage(GetDlgItem(IDC_STATIC_IMG2)->GetDC(), m_filename, 0, 0);
	}
	else if (combox_choose_1 == "ITTI"){
		spath = "C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_ITTI.jpg";
		SetDlgItemText(IDC_Label01, _T(combox_choose_1));
		CString m_filename("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_ITTI.jpg");//�ļ���
		//���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ����ʹλͼ��ʾ����
		((CStatic*)GetDlgItem(IDC_STATIC_IMG2))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
		ShowImage(GetDlgItem(IDC_STATIC_IMG2)->GetDC(), m_filename, 0, 0);
	}
	else if (combox_choose_1 == "LC"){
		spath = "C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_LC.jpg";
		SetDlgItemText(IDC_Label01, _T(combox_choose_1));
		Mat w = imread("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_LC.png");
		imwrite("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_LC.jpg", w);
		CString m_filename("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_LC.jpg");//�ļ���
		//���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ����ʹλͼ��ʾ����
		((CStatic*)GetDlgItem(IDC_STATIC_IMG2))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
		ShowImage(GetDlgItem(IDC_STATIC_IMG2)->GetDC(), m_filename, 0, 0);
	}
	else if (combox_choose_1 == "HC"){
		spath = "C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_HC.jpg";
		SetDlgItemText(IDC_Label01, _T(combox_choose_1));
		Mat w = imread("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_HC.png");
		imwrite("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_HC.jpg", w);
		CString m_filename("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_HC.jpg");//�ļ���
		//���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ����ʹλͼ��ʾ����
		((CStatic*)GetDlgItem(IDC_STATIC_IMG2))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
		ShowImage(GetDlgItem(IDC_STATIC_IMG2)->GetDC(), m_filename, 0, 0);
	}
}


void CShowJpgDlg::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strWeb;
	int nSel;

	// ��ȡ��Ͽ�ؼ����б����ѡ���������   
	nSel = combox01.GetCurSel();
	// ����ѡ����������ȡ�����ַ���   
	combox01.GetLBText(nSel, strWeb);
	// ����Ͽ���ѡ�е��ַ�����ʾ��IDC_SEL_WEB_EDIT�༭����   
	combox_choose_1 = strWeb;

}


void CShowJpgDlg::OnCbnSelchangeCombo2()
{
	CString strWeb;
	int nSel;
	nSel = combox02.GetCurSel();
	combox02.GetLBText(nSel, strWeb);
	combox_choose_2 = strWeb;
}


int flagth = 0;
void CShowJpgDlg::OnBnClickedBtnProcess2()
{

	ShowImage(GetDlgItem(IDC_STATIC_IMG)->GetDC(), basicpath, 0, 0);
	ShowImage(GetDlgItem(IDC_STATIC_IMG2)->GetDC(), spath, 0, 0);
	if (!flagth){
		system("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\Salient_Object_Detection_A_Benchmark\\CmCode-master\\Debug\\segeITTI.exe");
		flagth = 1;
	}
	
	if (combox_choose_2 == "gc"){
		Mat	srcImage2 = imread("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1.jpg");
		Mat srcImage3 = imread("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_RCC.png");
		threshold(srcImage3, srcImage3, 170, 255, CV_THRESH_BINARY);
		for (int i = 0; i < srcImage3.rows; i++){
			for (int j = 0; j < srcImage3.cols; j++){
				if (srcImage3.at<Vec3b>(i, j)[0] == 0 && srcImage3.at<Vec3b>(i, j)[1] == 0 && srcImage3.at<Vec3b>(i, j)[2] == 0){
					srcImage2.at<Vec3b>(i, j)[0] = srcImage3.at<Vec3b>(i, j)[0];
					srcImage2.at<Vec3b>(i, j)[1] = srcImage3.at<Vec3b>(i, j)[0];
					srcImage2.at<Vec3b>(i, j)[2] = srcImage3.at<Vec3b>(i, j)[0];
				}
			}
		}
		imwrite("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_RCC.jpg", srcImage2);
		CString m_filename("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_RCC.jpg");//�ļ���
		//���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ����ʹλͼ��ʾ����
		((CStatic*)GetDlgItem(IDC_STATIC_IMG3))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
		ShowImage(GetDlgItem(IDC_STATIC_IMG3)->GetDC(), m_filename, 0, 0);

	}
	else if (combox_choose_2 == "th"){

		Mat filee = imread("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_" + (string)combox_choose_1 + "_TH.jpg");

			//SetDlgItemText(IDC_Label02, _T(combox_choose_2));
			string ss = "C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_" + (string)combox_choose_1 + "_TH.jpg";
			CString m_filename(ss.c_str());//�ļ���
			//���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ����ʹλͼ��ʾ����
			((CStatic*)GetDlgItem(IDC_STATIC_IMG3))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
			ShowImage(GetDlgItem(IDC_STATIC_IMG3)->GetDC(), m_filename, 0, 0);
	}
	else if (combox_choose_2 == "ms"){

		Mat filee = imread("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_" + (string)combox_choose_1 + "_MS.jpg");
		string ss = "1_" + (string)combox_choose_1 + "_MS.jpg";
		//SetDlgItemText(IDC_Label02, _T(ss.c_str()));
		if (!filee.empty()){
			//SetDlgItemText(IDC_Label02, _T(combox_choose_2));
			string ss = "C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_" + (string)combox_choose_1 + "_MS.jpg";
			CString m_filename(ss.c_str());//�ļ���
			//���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ����ʹλͼ��ʾ����
			((CStatic*)GetDlgItem(IDC_STATIC_IMG3))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
			ShowImage(GetDlgItem(IDC_STATIC_IMG3)->GetDC(), m_filename, 0, 0);
		}
		else{
			meanshift s;
			Mat img = imread("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_" + (string)combox_choose_1 + ".jpg");
			Mat img2 = imread("C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1.jpg");
			s.pro(img, img2, (string)combox_choose_1);
			string ss = "C:\\Users\\Administrator\\Desktop\\�γ����\\��Ȼ����������Ŀ�����ȡ\\test\\Saliency\\1_" + (string)combox_choose_1 + "_MS.jpg";
			CString m_filename(ss.c_str());//�ļ���
			//���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ����ʹλͼ��ʾ����
			((CStatic*)GetDlgItem(IDC_STATIC_IMG3))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
			ShowImage(GetDlgItem(IDC_STATIC_IMG3)->GetDC(), m_filename, 0, 0);
		}
	}
}
