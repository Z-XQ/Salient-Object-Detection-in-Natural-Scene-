
// ShowJpgDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CShowJpgDlg 对话框




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


// CShowJpgDlg 消息处理程序

BOOL CShowJpgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	/*
	CComboBox *combox = NULL;
	combox = (CComboBox*)GetDlgItem(IDC_COMBO1);//获取combobox窗口指针
	*/
	combox01.AddString(_T("FT"));
	combox01.AddString(_T("RC"));
	combox01.AddString(_T("HC"));
	combox01.AddString(_T("LC"));
	combox01.AddString(_T("ITTI"));
	// 默认选择第一项   
	combox01.SetCurSel(0);

	combox02.AddString(_T("gc"));
	combox02.AddString(_T("th"));
	combox02.AddString(_T("ms"));
	// 默认选择第一项   
	combox02.SetCurSel(0);



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CShowJpgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CShowJpgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//************************************
// 方法说明:    显示JPG和GIF、BMP图片
// 参数说明:    CDC * pDC           设备环境对象
// 参数说明:    CString strPath     要显示的图片路径 
// 参数说明:    int x               要显示的X位置
// 参数说明:    int y               要显示的Y位置
// 返回值:      BOOL                成功返回TRUE,否则返回FALSE
//************************************
BOOL CShowJpgDlg::ShowJpgGif(CDC* pDC,CString strPath, int x, int y)

{
    CFileStatus fstatus;  
    CFile file;  
    ULONGLONG cb;  

    // 打开文件并检测文件的有效性
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

     // 根据文件大小分配内存空间,记得释放内存
     HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, (unsigned int)cb);  
      if (hGlobal== NULL) 
      {
          return FALSE;
      }

      // 锁定刚才分配的内存空间
      LPVOID pvData = NULL;  
      pvData = GlobalLock(hGlobal);
      if (pvData == NULL)  
      {  
            GlobalFree(hGlobal);  // 记得释放内存
            return FALSE;
      } 

      // 将文件放到流中
      IStream *pStm;  
      file.Read(pvData,(unsigned int)cb);  
      GlobalUnlock(hGlobal);  
      CreateStreamOnHGlobal(hGlobal, TRUE, &pStm);  
 
    // 从流中加载图片
    // 显示JPEG和GIF格式的图片，GIF只能显示一帧，还不能显示动画，
    // 要显示动画GIF请使用ACTIVE控件。
    IPicture *pPic; 
    if(OleLoadPicture(pStm,(LONG)fstatus.m_size,TRUE,IID_IPicture,(LPVOID*)&pPic)!=S_OK) 
    { 
        GlobalFree(hGlobal);  // 记得释放内存
        return FALSE;
    }

    //获取图像宽和高,注意这里的宽和高不是图像的分辨率
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
        GlobalFree(hGlobal);  // 记得释放内存
        return false;
    }

    pPic->Release(); 
    GlobalFree(hGlobal);  // 记得释放内存
    return true;
}

//************************************
// 方法说明:    显示JPG和GIF、BMP图片
// 参数说明:    CDC * pDC           设备环境对象
// 参数说明:    CString strPath     要显示的图片路径 
// 参数说明:    int x               要显示的X位置
// 参数说明:    int y               要显示的Y位置
// 返回值:      BOOL                成功返回TRUE,否则返回FALSE
//************************************
BOOL CShowJpgDlg::ShowImage(CDC* pDC,CString strPath, int x, int y)
{
   
    IPicture *pPic=NULL; 
    OleLoadPicturePath(CComBSTR(strPath.GetBuffer()), (LPUNKNOWN)NULL, 0, 0, IID_IPicture,(LPVOID*)&pPic);
    if (NULL==pPic)
    {
        return FALSE;
    }

    // 获取图像宽和高,注意这里的宽和高不是图像的分辨率
    OLE_XSIZE_HIMETRIC hmWidth;  
    OLE_YSIZE_HIMETRIC hmHeight;  
    pPic->get_Width(&hmWidth);  
    pPic->get_Height(&hmHeight);  

    // 将图像宽度和高度单位转化为像素单位
   //#define HIMETRIC_PER_INCH 2540
   //int nPicWidth =  MulDiv(hmWidth, GetDeviceCaps(GetDC()->m_hDC, LOGPIXELSX),2540);
   //int nPicHeight = MulDiv(hmHeight, GetDeviceCaps(GetDC()->m_hDC, LOGPIXELSY),2540);

   // 获取显示图片窗口的宽度和高度
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
// 方法说明:    浏览图片
// 返回值:      void
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
        "JPEG文件(*.jpg)|*.jpg|GIF文件(*.gif)|*.gif|bmp文件(*.bmp)|*.bmp|",NULL); 
    if(dlg.DoModal()==IDOK) 
    { 
        SetDlgItemText(IDC_TXT_PATH,dlg.GetPathName());
		basicpath = dlg.GetPathName();
		basicpath = ff((string)basicpath).c_str();
		flag = 1;
        //设置静态控件的样式，使其可以使用位图，并使位图显示居中
        ((CStatic*)GetDlgItem(IDC_STATIC_IMG))-> ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);

        //ShowJpgGif(GetDlgItem(IDC_STATIC_IMG)->GetDC(),dlg.GetPathName(),0,0);
        ShowImage(GetDlgItem(IDC_STATIC_IMG)->GetDC(),dlg.GetPathName(),0,0);
    } 

}


//************************************
// 方法说明:    处理图片
// 返回值:      void
//************************************

void CShowJpgDlg::OnBnClickedProcess()
{
	
	if (flag == 1){
		system("del /q C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Imgs\\*");
		system("del /q C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\*");
		SetDlgItemText(IDC_Label01, _T(basicpath));
		Mat img = imread((string)basicpath);
		imwrite("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Imgs\\1.jpg", img);
		saliency w;
		w.check();
		flag++;
	}
	
	

	//CmSalCut::Demo(inDir + "*.jpg", inDir + "*.png", outDir);	//第二个参数没啥用
	
	ShowImage(GetDlgItem(IDC_STATIC_IMG)->GetDC(), basicpath, 0, 0);

	if (combox_choose_1 == "FT"){
		spath = "C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_FT.png";
		SetDlgItemText(IDC_Label01, _T(combox_choose_1));
		Mat w = imread("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_FT.png");
		imwrite("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_FT.jpg", w);
		CString m_filename("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_FT.jpg");//文件名
		//设置静态控件的样式，使其可以使用位图，并使位图显示居中
		((CStatic*)GetDlgItem(IDC_STATIC_IMG2))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
		ShowImage(GetDlgItem(IDC_STATIC_IMG2)->GetDC(), m_filename, 0, 0);

		
	}
	else if (combox_choose_1 == "RC"){
		spath = "C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_RC.jpg";
		SetDlgItemText(IDC_Label01, _T(combox_choose_1));
		Mat w = imread("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_RC.png");
		imwrite("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_RC.jpg", w);
		CString m_filename("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_RC.jpg");//文件名
		//设置静态控件的样式，使其可以使用位图，并使位图显示居中
		((CStatic*)GetDlgItem(IDC_STATIC_IMG2))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
		ShowImage(GetDlgItem(IDC_STATIC_IMG2)->GetDC(), m_filename, 0, 0);
	}
	else if (combox_choose_1 == "ITTI"){
		spath = "C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_ITTI.jpg";
		SetDlgItemText(IDC_Label01, _T(combox_choose_1));
		CString m_filename("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_ITTI.jpg");//文件名
		//设置静态控件的样式，使其可以使用位图，并使位图显示居中
		((CStatic*)GetDlgItem(IDC_STATIC_IMG2))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
		ShowImage(GetDlgItem(IDC_STATIC_IMG2)->GetDC(), m_filename, 0, 0);
	}
	else if (combox_choose_1 == "LC"){
		spath = "C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_LC.jpg";
		SetDlgItemText(IDC_Label01, _T(combox_choose_1));
		Mat w = imread("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_LC.png");
		imwrite("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_LC.jpg", w);
		CString m_filename("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_LC.jpg");//文件名
		//设置静态控件的样式，使其可以使用位图，并使位图显示居中
		((CStatic*)GetDlgItem(IDC_STATIC_IMG2))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
		ShowImage(GetDlgItem(IDC_STATIC_IMG2)->GetDC(), m_filename, 0, 0);
	}
	else if (combox_choose_1 == "HC"){
		spath = "C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_HC.jpg";
		SetDlgItemText(IDC_Label01, _T(combox_choose_1));
		Mat w = imread("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_HC.png");
		imwrite("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_HC.jpg", w);
		CString m_filename("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_HC.jpg");//文件名
		//设置静态控件的样式，使其可以使用位图，并使位图显示居中
		((CStatic*)GetDlgItem(IDC_STATIC_IMG2))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
		ShowImage(GetDlgItem(IDC_STATIC_IMG2)->GetDC(), m_filename, 0, 0);
	}
}


void CShowJpgDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strWeb;
	int nSel;

	// 获取组合框控件的列表框中选中项的索引   
	nSel = combox01.GetCurSel();
	// 根据选中项索引获取该项字符串   
	combox01.GetLBText(nSel, strWeb);
	// 将组合框中选中的字符串显示到IDC_SEL_WEB_EDIT编辑框中   
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
		system("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\Salient_Object_Detection_A_Benchmark\\CmCode-master\\Debug\\segeITTI.exe");
		flagth = 1;
	}
	
	if (combox_choose_2 == "gc"){
		Mat	srcImage2 = imread("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1.jpg");
		Mat srcImage3 = imread("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_RCC.png");
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
		imwrite("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_RCC.jpg", srcImage2);
		CString m_filename("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_RCC.jpg");//文件名
		//设置静态控件的样式，使其可以使用位图，并使位图显示居中
		((CStatic*)GetDlgItem(IDC_STATIC_IMG3))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
		ShowImage(GetDlgItem(IDC_STATIC_IMG3)->GetDC(), m_filename, 0, 0);

	}
	else if (combox_choose_2 == "th"){

		Mat filee = imread("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_" + (string)combox_choose_1 + "_TH.jpg");

			//SetDlgItemText(IDC_Label02, _T(combox_choose_2));
			string ss = "C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_" + (string)combox_choose_1 + "_TH.jpg";
			CString m_filename(ss.c_str());//文件名
			//设置静态控件的样式，使其可以使用位图，并使位图显示居中
			((CStatic*)GetDlgItem(IDC_STATIC_IMG3))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
			ShowImage(GetDlgItem(IDC_STATIC_IMG3)->GetDC(), m_filename, 0, 0);
	}
	else if (combox_choose_2 == "ms"){

		Mat filee = imread("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_" + (string)combox_choose_1 + "_MS.jpg");
		string ss = "1_" + (string)combox_choose_1 + "_MS.jpg";
		//SetDlgItemText(IDC_Label02, _T(ss.c_str()));
		if (!filee.empty()){
			//SetDlgItemText(IDC_Label02, _T(combox_choose_2));
			string ss = "C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_" + (string)combox_choose_1 + "_MS.jpg";
			CString m_filename(ss.c_str());//文件名
			//设置静态控件的样式，使其可以使用位图，并使位图显示居中
			((CStatic*)GetDlgItem(IDC_STATIC_IMG3))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
			ShowImage(GetDlgItem(IDC_STATIC_IMG3)->GetDC(), m_filename, 0, 0);
		}
		else{
			meanshift s;
			Mat img = imread("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_" + (string)combox_choose_1 + ".jpg");
			Mat img2 = imread("C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1.jpg");
			s.pro(img, img2, (string)combox_choose_1);
			string ss = "C:\\Users\\Administrator\\Desktop\\课程设计\\自然场景下显著目标的提取\\test\\Saliency\\1_" + (string)combox_choose_1 + "_MS.jpg";
			CString m_filename(ss.c_str());//文件名
			//设置静态控件的样式，使其可以使用位图，并使位图显示居中
			((CStatic*)GetDlgItem(IDC_STATIC_IMG3))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
			ShowImage(GetDlgItem(IDC_STATIC_IMG3)->GetDC(), m_filename, 0, 0);
		}
	}
}
