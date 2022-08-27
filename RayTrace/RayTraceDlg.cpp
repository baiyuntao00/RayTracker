
// RayTraceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RayTrace.h"
#include "RayTraceDlg.h"
#include "afxdialogex.h"
#include <windows.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <iostream>
#include <fstream>
#include <limits>
#include "float.h"
#include <fstream>
#include <vector>
#include <crtdbg.h>

using namespace std;
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


// CRayTraceDlg 对话框



CRayTraceDlg::CRayTraceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRayTraceDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRayTraceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTFILEMAT, show_file_mat);
	DDX_Control(pDX, IDC_EDITMATIN, inMAtindex);
	;
	DDX_Control(pDX, IDC_STAREVISE, m_btuRevise);
	DDX_Control(pDX, IDC_EDITX, m_editx);
	DDX_Control(pDX, IDC_EDITY, m_edity);
	DDX_Control(pDX, IDC_EDITZ, m_editz);
	DDX_Control(pDX, IDC_EDITX2, m_editrx);
	DDX_Control(pDX, IDC_EDITY2, m_editry);
	DDX_Control(pDX, IDC_EDITZ2, m_editrz);
	DDX_Control(pDX, IDC_EDITTHREAD, m_Thread);
}

BEGIN_MESSAGE_MAP(CRayTraceDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTSTART, &CRayTraceDlg::OnBnClickedButStart)
	ON_EN_CHANGE(IDC_EDIT2, &CRayTraceDlg::OnEnChangeEditSize)
	ON_BN_CLICKED(IDC_BUTSAVE, &CRayTraceDlg::OnBnClickedButSave)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTFILEMAT, &CRayTraceDlg::OnDblclkListFileMat)
	ON_EN_KILLFOCUS(IDC_EDITMATIN, &CRayTraceDlg::OnKillfocusEditMatIn)
	ON_WM_LBUTTONUP()
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LISTFILEMAT, &CRayTraceDlg::OnLvnBegindragListfilemat)
	ON_EN_CHANGE(IDC_EDITX, &CRayTraceDlg::OnEnChangeEditx)
	ON_EN_CHANGE(IDC_EDITY, &CRayTraceDlg::OnEnChangeEdity)
	ON_EN_CHANGE(IDC_EDITZ, &CRayTraceDlg::OnEnChangeEditz)
	ON_WM_MOUSEMOVE()
	ON_EN_CHANGE(IDC_EDITX2, &CRayTraceDlg::OnEnChangeEditRotx)
	ON_EN_CHANGE(IDC_EDITY2, &CRayTraceDlg::OnEnChangeEditRoty)
	ON_EN_CHANGE(IDC_EDITZ2, &CRayTraceDlg::OnEnChangeEditRotz)
	ON_WM_LBUTTONDOWN()
	ON_EN_CHANGE(IDC_EDITTHREAD, &CRayTraceDlg::OnEnChangeEditThread)
END_MESSAGE_MAP()


// CRayTraceDlg 消息处理程序

BOOL CRayTraceDlg::OnInitDialog()
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
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO:  在此添加额外的初始化代码
	/*构造文件—材质列表UI*/
	inMAtindex.ShowWindow(SW_HIDE);
	show_file_mat.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	show_file_mat.InsertColumn(0, TEXT("文件名"), LVCFMT_CENTER, 140);
	show_file_mat.InsertColumn(1, TEXT("材质"), LVCFMT_CENTER, 80);
	matIcolist.Create(18, 18,1, 0, 0);
	matIcolist.Add(AfxGetApp()->LoadIcon(IDI_MATICO));
	show_file_mat.SetImageList(&matIcolist, LVSIL_SMALL);
	////获取电脑桌面路径
	TCHAR filePathtchar[255];
	SHGetSpecialFolderPath(0, filePathtchar, CSIDL_DESKTOPDIRECTORY, 0);
	filePathstr = filePathtchar + CString("\\RayTraceData\\");
	////读取模型文件夹，初始化列表
	objNum = 0;
	///如果没有文件夹则创建一个
	SetMaterial();
	if (!PathIsDirectory(filePathstr)) 
	{
		::CreateDirectory(filePathstr, 0);
	}
	else///如果有，则读取
	{
		InitMatList();
		for (int i = 0; i < objNum; i++)
		{
			xm[i] = 0.0;
			ym[i] = 0.0;
			zm[i] = 0.0;
			xr[i] = 0.0;
			yr[i] = 0.0;
			zr[i] = 0.0;
		}
	}
	////初始化模型编辑框
	m_editx.SetWindowTextW(TEXT("x"));
	m_edity.SetWindowTextW(TEXT("y"));
	m_editz.SetWindowTextW(TEXT("z"));
	m_editrx.SetWindowTextW(TEXT("x"));
	m_editry.SetWindowTextW(TEXT("y"));
	m_editrz.SetWindowTextW(TEXT("z"));
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(TEXT("200"));
	m_Thread.SetWindowTextW(TEXT("1"));
	/*初始化生成的图片版本*/
	imgVersion = 1;
	
	/*初始化对话框主题及控件UI*/
	imageSize = 201;
	threadNum = 1;

	run = false;
	GetDlgItem(IDC_EDIT3)->SetWindowTextW(workWord);
	tempIsObj = false;
	tempIsCam = false;
	tempIsLight = false;
	isCam = false;
	isObj = false;
	isLight = false;

	/*初始化材质信息*/
	numMat = 13;

	/*初始化相机参数*/
	viewPoint = CVector3(0, 0, 1.8);///初始化相机坐标
	cameraDir = CVector3(0,1.0,0);///相机方向
	screen_z = 0.8;///屏幕z坐标大小

	/*初始化光源位置*/
	lightPoint = CVector3(100, 100, 100);

	/*次代反射光线距离衰减参数*/
	fadekt =2.1;///该数值为0时表示次代光线传播过程不衰减

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CRayTraceDlg::InitMatList()
{
	int itemNum = 0;
	HANDLE file;
	WIN32_FIND_DATA pNextInfo;
	CString nametemp = filePathstr + L"*.txt";
	CString list;
	file = FindFirstFile(nametemp, &pNextInfo);
	workWord = CString("请点击“开始渲染”");
	if (file == INVALID_HANDLE_VALUE)
	{
		workWord = CString("没有搜索到文件");
	}
	else
	{
		objName[0] = pNextInfo.cFileName;
		list.Format(TEXT("%d"), objMatindex[itemNum]);
		show_file_mat.InsertItem(0, objName[0]);
		show_file_mat.SetItemText(0, 1, list);
		itemNum++;
		while (FindNextFile(file, &pNextInfo))
		{
			objName[itemNum] = pNextInfo.cFileName;
			list.Format(TEXT("%d"), objMatindex[itemNum]);
			show_file_mat.InsertItem(itemNum, objName[itemNum]);
			show_file_mat.SetItemText(itemNum, 1, list);
			itemNum++;
		}
	}
	objNum = itemNum;
}
void CRayTraceDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CRayTraceDlg::SetMaterial()
{
	for (int i = 0; i < 10; i++)
	{
		objMatindex[i] = 1;
	}
	objectMat[0] = new Checker2D(0.3, 0.9, CVector3(180, 0, 180, 0), CVector3(0.5, 0.65, 0.5));
	objectMat[1] = new Checker2D(0.3, 0.9, CVector3(10, 10, 10, 0), CVector3(245, 245, 245, 0));
	objectMat[2] = new Specular(CVector3(100,50,0, 0),90,0.9);
	objectMat[3] = new Specular(CVector3(0, 162, 232, 0), 90, 0.9);
	objectMat[4] = new Specular(CVector3(0, 200, 255, 0), 90, 0.9);
	objectMat[5] = new Diffuse(CVector3(35, 118, 26, 0), 0.9);
	objectMat[6] = new Diffuse(CVector3(130, 6, 6, 0), 0.9);
	objectMat[7] = new Diffuse(CVector3(230, 196, 157, 0), 0.9);
	objectMat[8] = new Friction(CVector3(85, 0, 0, 0),80, 0.9);
	objectMat[9] = new Friction(CVector3(70, 50, 200, 0), 80, 0.87);
	objectMat[10] = new Friction(CVector3(250, 30, 253, 0), 80, 0.87);
	objectMat[11] = new Transparent(CVector3(0, 0, 255, 0),80,1.8);
	objectMat[12] = new Transparent(CVector3(0, 255, 0, 0), 80, 1.3);

}
void CRayTraceDlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	CRect rectImage;
	GetDlgItem(IDC_SHOIMAGE)->SetWindowPos(NULL, 0, 0, imageSize, imageSize, SWP_NOZORDER | SWP_NOMOVE | SWP_NOREDRAW);
	CWnd *pWin = GetDlgItem(IDC_SHOIMAGE); //获取该控件的指针
	pWin->GetClientRect(rectImage);//把控件信息保存在rect里
	CDC *pDc = pWin->GetDC();
	////保证图像的大小不超限制
	if (imageSize > 920)
	{
		imageSize = 921;
	}
	////
	for (int i = objNum; i >= 0; i--)
	{
		show_file_mat.DeleteItem(i);
	}
	InitMatList();
	if (run)//用户允许计算
	{
		ReadObjectVex();///读取数据信息
		GetDlgItem(IDC_EDIT3)->SetWindowTextW(TEXT("正在计算中..."));
		if ((imageSize - 1) % threadNum != 0)
		{
			threadNum = 1;
			GetDlgItem(IDC_EDIT3)->SetWindowTextW(TEXT("不符合要求，已改为单线程。正在计算中..."));
		}
		CString str_showtime;///显示渲染时长
		long t1 = GetTickCount();///当前时间;
		pixCol = new CRGB*[imageSize];
		for (int t = 0; t < imageSize; t++)
		{
			pixCol[t] = new CRGB[imageSize];
		}
		GetInitImage();
		SetSample(pDc);
		str_showtime.Format(_T("运算时间:%dms"), GetTickCount() - t1);
		GetDlgItem(IDC_EDIT3)->SetWindowTextW(str_showtime);
	}
	run = false;
	ReleaseDC(pDc);
}
int CRayTraceDlg::GetMaxInNum(int x1, int x2, int x3, int x4)
{
	int temp=0;
	int array[4] = { x1, x2, x3, x4};
	for (int i = 0; i < 4; i++)
	{
		if (temp < array[i])
			temp = array[i];
	}
	return temp;
}
int CRayTraceDlg::GetMinInNum(int x1, int x2, int x3, int x4)
{
	int temp = 0;
	int array[4] = { x1, x2, x3, x4 };
	for (int i = 0; i < 4; i++)
	{
		if (temp > array[i])
			temp = array[i];
	}
	return temp;
}
bool CRayTraceDlg::IsDiff(float x1, float x2)
{
	if (abs(x1 - x2) <=1e-6)
		return true;
	else
		return false;
}
void CRayTraceDlg::ThreadFun(Camera camera,int low,int heigh,int size)
{
	CDC *pDc = GetDlgItem(IDC_SHOIMAGE)->GetDC();
	for (int j = low; j < heigh; j++)///
	{
		for (int i = 0; i < size; i++)
		{
			Ray rs1 = camera.Get_ray(float(i) / float(size), float(j) / float(size));
			///原像素颜色
			CRGB oldCol = Normalize(PixelColor(rs1, scene, 0));
			int r = int(255.55 * oldCol.red);
			int g = int(255.55 * oldCol.green);
			int b = int(255.55 * oldCol.blue);
			pixCol[j][i] = CRGB(r, g, b);
			pDc->SetPixel(i, size - j - 1, RGB(r, g, b));
		}
	}
	ReleaseDC(pDc);
}
void CRayTraceDlg::GetInitImage()
{
	Camera camera(viewPoint, cameraDir, screen_z);///建立相机
	/*生成原始图像*/
	int threadSize = imageSize / threadNum;
	std::thread *t;
	t = new thread[threadNum];
	for (int j = 0; j < threadNum; j++)///
	{
		int low = j*threadSize;
		int heigh = low + threadSize;
		t[j] = thread(&CRayTraceDlg::ThreadFun, this, camera, low, heigh, imageSize);
	}
	for (int i = 0; i < threadNum; i++)
	{
		t[i].join();
	}
	delete[]t;
	t = NULL;
}
void CRayTraceDlg::SetSample(CDC*pDc)
{
	/*对原图像采样抗锯齿*/
	GetDlgItem(IDC_EDIT3)->SetWindowTextW(TEXT("正在对原图像反走样处理"));
	float Imin, Imax;
	for (int i = 1; i < imageSize - 1; i++)///
	{
		for (int j = 1; j < imageSize - 1; j++)
		{
			///蓝色分量
			int b[9] = {
				pixCol[i - 1][j - 1].blue,
				pixCol[i][j - 1].blue,
				pixCol[i + 1][j - 1].blue,
				pixCol[i - 1][j].blue,
				pixCol[i][j].blue,
				pixCol[i + 1][j].blue,
				pixCol[i - 1][j + 1].blue,
				pixCol[i][j + 1].blue,
				pixCol[i + 1][j + 1].blue };
			Imin = GetMinInNum(b[4], b[7], b[6], b[3]);
			Imax = GetMaxInNum(b[4], b[7], b[6], b[3]);
			if ((Imax - Imin) / (Imax + Imin) > 0.6)
			{
				int tempb = (b[4] * 4 + (b[1] + b[3] + b[5] + b[7]) * 2 + b[0] + b[2] + b[6] + b[8]) / 16 + 0.5;
				pixCol[i][j].blue = tempb;
			}
			////绿色分量
			int g[9] = {
				pixCol[i - 1][j - 1].green,
				pixCol[i][j - 1].green,
				pixCol[i + 1][j - 1].green,
				pixCol[i - 1][j].green,
				pixCol[i][j].green,
				pixCol[i + 1][j].green,
				pixCol[i - 1][j + 1].green,
				pixCol[i][j + 1].green,
				pixCol[i + 1][j + 1].green };
			Imin = GetMinInNum(g[4], g[7], g[6], g[3]);
			Imax = GetMaxInNum(g[4], g[7], g[6], g[3]);
			if ((Imax - Imin) / (Imax + Imin) > 0.3)
			{
				int tempg = (g[4] * 4 + (g[1] + g[3] + g[5] + g[7]) * 2 + g[0] + g[2] + g[6] + g[8]) / 16 + 0.5;
				pixCol[i][j].green = tempg;
			}
			///红色分量
			int r[9] = {
				pixCol[i - 1][j - 1].red,
				pixCol[i][j - 1].red,
				pixCol[i + 1][j - 1].red,
				pixCol[i - 1][j].red,
				pixCol[i][j].red,
				pixCol[i + 1][j].red,
				pixCol[i - 1][j + 1].red,
				pixCol[i][j + 1].red,
				pixCol[i + 1][j + 1].red };
			Imin = GetMinInNum(r[4], r[7], r[6], r[3]);
			Imax = GetMaxInNum(r[4], r[7], r[6], r[3]);
			if ((Imax - Imin) / (Imax + Imin) > 0.4)
			{
				int tempr = (r[4] * 4 + (r[1] + r[3] + r[5] + r[7]) * 2 + r[0] + r[2] + r[6] + r[8]) / 16 + 0.5;
				pixCol[i][j].red = tempr;
			}
		}
	}
	//绘制反走样图片
	for (int j = 0; j < imageSize; j++)///
	{
		for (int i = 0; i < imageSize; i++)
		{
			pDc->SetPixel(i, imageSize - j - 1, RGB(pixCol[j][i].red, pixCol[j][i].green, pixCol[j][i].blue));
		}
	}
}
CRGB CRayTraceDlg::PixelColor(Ray&r, World *world, int depth)
{
	HitRecord rec;
	float shadowk = 0.4;//阴影系数
	CRGB reflectColor = CRGB(0.0, 0.0, 0.0);
	CRGB refractColor = CRGB(0.0, 0.0, 0.0);
	CRGB localColor = CRGB(0.0, 0.0, 0.0);
	if (r.intensity < 0.0001)
		return CRGB(0, 0, 0);
	if (scene->Hit(r, 0.001, (numeric_limits<float>::max)(), rec) && depth < 5) /*如果光线与景物相交*/
	{    
		r.len = rec.t;
		/*透射光线*/
		Ray refractRay;///////折射光线
		float fadeReflect = 1.0;
		if (rec.mat_ptr->Refract(r, refractRay, rec))
		{
			CRGB temp = PixelColor(refractRay, world, depth + 1);
			refractColor = temp*refractRay.intensity;
		}
		/*反射光线*/
		Ray scatterRay;
		if (rec.mat_ptr->Scatter(r, rec, scatterRay))
		{
			CRGB temp = PixelColor(scatterRay, world, depth + 1);
			if (scatterRay.isFade)
				/*次代光线距离衰减*/
			{
				float d = scatterRay.len;
				if (d > 1.0)
				{
					/*次代光线衰减为 0*/
					scatterRay.intensity = 0.0;
				}
				else
				{
					scatterRay.intensity = pow((1.0 - d),5)*scatterRay.intensity;
				}
			}
			reflectColor = temp*scatterRay.intensity;
		}
		///*阴影光线*/
	    Ray shadowRay(rec.P_hit, CVector3(rec.P_hit, lightPoint));
		localColor = rec.mat_ptr->LocalLight(r, rec, viewPoint, lightPoint);
		if (scene->ShadowHit(shadowRay, (numeric_limits<float>::max)()))
		{
			localColor = localColor*shadowk;
		}
		/*Whitted光照明模型*/
		return localColor + reflectColor + refractColor;///返回=>局部反射光+物体反射光+透射光
	}
	else/*如果光线与景物没有相交*/
	{
		return CRGB(0.0, 0.0, 0.0);
	}
	return CRGB(0.0, 0.0, 0.0);
}
void CRayTraceDlg::ReadObjectVex()
{
	int v_num,/*顶点数*/f_num,/*面片数*/ f_index/*面片索引*/;
	int isSmooth;/*0表示平坦，1表示光滑*/
	float zoomNum;/*缩放比例*/
	int isN;
	GetDlgItem(IDC_EDIT3)->SetWindowTextW(TEXT("正在初始化..."));
	for (int objIn = 0; objIn < objNum; objIn++)
	{
		CString fileName = filePathstr + objName[objIn];
		fstream file(fileName, ios::_Nocreate);
		if (!file)
		{
			MessageBox(_T("初始化失败"), _T("警告"));
			GetDlgItem(IDC_EDIT3)->SetWindowTextW(_T("请仔细查看帮助文档"));
		}
		else
		{
			file >> v_num;/*顶点总数*/
			file >> f_num;/*面片总数*/
			file >> isSmooth;/*面片是否光滑着色*/
			file >> zoomNum;/*读取模型缩放比例*/
			file >> isN;
			vector<CVector3>vex(v_num);
			vector<Face>faceList(f_num);
			CVector3 maxp, minp;
			if (isSmooth == 1)/*如果该模型为光滑着色*/
			{
				vector<Vex_Face>vexfaceList(v_num);
				vector<vector<int> >faceData(f_num, vector<int>(3));
				/*读取顶点数据*/
				float x, y, z;
				for (int i = 0; i < v_num; i++)
				{
					file >> x;
					file >> y;
					file >> z;
					vex[i] = MoveTran(ZoomTran(CVector3(x, y, z), zoomNum), xm[objIn], ym[objIn], zm[objIn]);
				}
				/*计算模型框架点,目的：用于计算旋转轴*/
				maxp = vex[0], minp = vex[0];
				for (int i = 1; i < v_num; i++)
				{
					if (vex[i].x > maxp.x)
						maxp.x = vex[i].x;
					if (vex[i].y > maxp.y)
						maxp.y = vex[i].y;
					if (vex[i].z > maxp.z)
						maxp.z = vex[i].z;
					if (vex[i].x < minp.x)
						minp.x = vex[i].x;
					if (vex[i].y < minp.y)
						minp.y = vex[i].y;
					if (vex[i].z < minp.z)
						minp.z = vex[i].z;
				}
				///对模型进行旋转变换
				Transform tran(maxp, minp);
				for (int i = 0; i < v_num; i++)
				{
					vex[i] = tran.RotateTran('x', vex[i], xr[objIn]);
					vex[i] = tran.RotateTran('y', vex[i], yr[objIn]);
					vex[i] = tran.RotateTran('z', vex[i], zr[objIn]);
					vexfaceList[i] = Vex_Face(i);
				}
				/*计算共该顶点面片索引*/
				for (int i = 0; i < f_num; i++)
				{
					file >> f_index;
					for (int j = 0; j < 3; j++)
					{
						file >> faceData[i][j];/*读取面片顶点索引*/
						vexfaceList[faceData[i][j]].faceIndex.push_back(i);/*在容器尾部添加一个元素*/
					}
					faceList[i] = Face((bool)isSmooth, vex[faceData[i][0]], vex[faceData[i][1]], vex[faceData[i][2]], i);
					faceList[i].tri_n = faceList[i].tri_n*isN;
				}
				/*计算三角面片顶点法向量*/
				vector<CVector3>normal(v_num);
				for (int i = 0; i < v_num; i++)
				{
					if (vexfaceList[i].vexIndex < 0)
						continue;
					normal[i] = CVector3(0, 0, 0);
					int num = vexfaceList[i].faceIndex.size();
					for (int j = 0; j < num; j++)
					{
						normal[i] += faceList[vexfaceList[i].faceIndex[j]].tri_n;
					}
					if (normal[i].x == 0 && normal[i].y == 0 && normal[i].z == 0)
						normal[i].y = 1.0;
					else
						normal[i] /= num;
				}
				for (int index = 0; index < f_num; index++)
				{
					for (int j = 0; j < 3; j++)
					{
						faceList[index].smooth_vex_n[j] = normal[faceData[index][j]].Normalize();
					}
				}
			}/*if (isSmooth == 1)*/
			else/*该模型为平坦着色，0==false*/
			{
				/*读取顶点数据*/
				float x, y, z;
				for (int i = 0; i < v_num; i++)
				{
					file >> x;
					file >> y;
					file >> z;
					vex[i] = MoveTran(ZoomTran(CVector3(x, y, z), zoomNum), xm[objIn], ym[objIn], zm[objIn]);
				}
				///计算模型框架点
				maxp = vex[0], minp = vex[0];
				for (int i = 1; i < v_num; i++)
				{
					if (vex[i].x > maxp.x)
						maxp.x = vex[i].x;
					if (vex[i].y > maxp.y)
						maxp.y = vex[i].y;
					if (vex[i].z > maxp.z)
						maxp.z = vex[i].z;
					if (vex[i].x < minp.x)
						minp.x = vex[i].x;
					if (vex[i].y < minp.y)
						minp.y = vex[i].y;
					if (vex[i].z < minp.z)
						minp.z = vex[i].z;
				}
				///对模型进行旋转变换
				Transform tran(maxp, minp);
				for (int i = 0; i < v_num; i++)
				{
					vex[i] = tran.RotateTran('x', vex[i], xr[objIn]);
					vex[i] = tran.RotateTran('y', vex[i], yr[objIn]);
					vex[i] = tran.RotateTran('z', vex[i], zr[objIn]);
				}
				/*读取面片顶点索引*/
				int faceData[3];
				for (int i = 0; i < f_num; i++)
				{
					file >> f_index;
					for (int j = 0; j < 3; j++)
					{
						file >> faceData[j];/*读取面片顶点索引*/
					}
					faceList[i] = Face((bool)isSmooth, vex[faceData[0]], vex[faceData[1]], vex[faceData[2]], i);
					faceList[i].tri_n = faceList[i].tri_n*isN;
				}
			}/*else*/
			///计算新框架点，用于包围盒计算
			for (int i = 1; i < v_num; i++)
			{
				if (vex[i].x > maxp.x)
					maxp.x = vex[i].x;
				if (vex[i].y > maxp.y)
					maxp.y = vex[i].y;
				if (vex[i].z > maxp.z)
					maxp.z = vex[i].z;
				if (vex[i].x < minp.x)
					minp.x = vex[i].x;
				if (vex[i].y < minp.y)
					minp.y = vex[i].y;
				if (vex[i].z < minp.z)
					minp.z = vex[i].z;
			}
			bool isBox;
			if (IsDiff(minp.x, maxp.x) || IsDiff(minp.y, maxp.y) || IsDiff(minp.z, maxp.z))
				isBox = false;
			else
			{
				isBox = true;
			}
			/*初始化物体*/
			obj[objIn] = new Object(objIn, faceList, f_num, objectMat[objMatindex[objIn]],/*包围盒参数*/isBox, maxp, minp);
		}/*else*/
	}/*for*/
	scene = new HitGroup(obj, objNum);
}
/*释放内存*/
CRayTraceDlg::~CRayTraceDlg()
{
	for (int i = 0; i < 13; i++)
	{
		delete objectMat[i];
		objectMat[i] = NULL;
	}
	delete scene;
	scene = NULL;
	for (int i = 0; i < 10; i++)
	{
		delete[]obj[i];
		obj[i] = NULL;
	}
	if (pixCol != NULL)
	{
		for (int i = 0; i < imageSize; i++)
		{
			delete[]pixCol[i];
			pixCol[i] = NULL;
		}
		delete[]pixCol;
		pixCol = NULL;
	}
}
//////
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRayTraceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRayTraceDlg::OnBnClickedButStart()
{
	// TODO:  在此添加控件通知处理程序代码
	run = true;
	Invalidate(false);
	GetDlgItem(IDC_EDIT3)->SetWindowTextW(TEXT("正在计算中...请稍后"));
}

void CRayTraceDlg::OnEnChangeEditSize()
{
	CString csSize;
	GetDlgItem(IDC_EDIT2)->GetWindowText(csSize);
	imageSize = _wtoi(csSize) + 1;
}

void CRayTraceDlg::OnBnClickedButSave()
{
	// TODO:  在此添加控件通知处理程序代码
	CRect rt;
	///////
	GetWindowRect(&rt);
	CWnd *pWin = GetDlgItem(IDC_SHOIMAGE); //获取该控件的指针，就可以对该控件直接操作了
	pWin->GetClientRect(rt);//把控件的长宽、坐标等信息保存在rect里
	CDC *pDC = pWin->GetDC();
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	///
	CBitmap Bmp;
	Bmp.CreateCompatibleBitmap(pDC, imageSize, imageSize);
	CBitmap*pBmpPrev = (CBitmap*)memDC.SelectObject(&Bmp);
	memDC.BitBlt(0, 0, imageSize, imageSize, pDC, 0, 0, SRCCOPY);
	CImage image;
	image.Attach((HBITMAP)Bmp.m_hObject);
	CString imgName;
	imgName.Format(TEXT("RayTrace_%d.bmp"), imgVersion);
	image.Save(imgName);
	imgVersion++;
	GetDlgItem(IDC_EDIT3)->SetWindowTextW(_T("保存成功  " + imgName));
	ReleaseDC(pDC);
}

void CRayTraceDlg::OnDblclkListFileMat(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CRect rc;
	mRow = pNMListView->iItem;//获得选中的行
	mCol = pNMListView->iSubItem;//获得选中列
	if (mCol == 0)
	{
		tempIsObj = true;
		CString strName = filePathstr + show_file_mat.GetItemText(mRow, mCol);
		ShellExecute(NULL, _T("open"), strName, NULL, NULL, SW_SHOWNORMAL);
	}
	int n = show_file_mat.GetItemCount();//获取当前一共多少行
	if (pNMListView->iSubItem != 0) //如果选择的是子项;
	{
		show_file_mat.GetSubItemRect(mRow, mCol, LVIR_LABEL, rc);//获得子项的RECT；
		inMAtindex.SetParent(&show_file_mat);//转换坐标为列表框中的坐标
		inMAtindex.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		inMAtindex.SetWindowText(show_file_mat.GetItemText(mRow, mCol));//将该子项中的值放在Edit控件中；
		inMAtindex.ShowWindow(SW_SHOW);//显示Edit控件；
		inMAtindex.SetFocus();//设置Edit焦点
		inMAtindex.ShowCaret();//显示光标
		inMAtindex.SetSel(-1);//将光标移动到最后
	}
	*pResult = 0;
}


void CRayTraceDlg::OnKillfocusEditMatIn()
{
	CString tem;
	inMAtindex.GetWindowText(tem); //得到用户输入的新的内容
	show_file_mat.SetItemText(mRow, mCol, tem); //设置编辑框的新内容
	objMatindex[mRow] = _wtoi(tem);
	inMAtindex.ShowWindow(SW_HIDE); //应藏编辑框
}

void CRayTraceDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	///集群修改
	CRect togeBtuRec;
	GetDlgItem(IDC_STAREVISE)->GetWindowRect(&togeBtuRec);
	ScreenToClient(togeBtuRec);
	if (tempIsCam)
	{
		isCam = true;
		tempIsCam = false;
		isObj = false;
		isLight = false;
	}
	if (tempIsObj)
	{
		tempIsObj = false;
		isObj = true;
		isCam = false;
		isLight = false;
	}
	if (tempIsLight)
	{
		tempIsLight = false;
		isObj = false;
		isCam = false;
		isLight = true;
	}
	if (togeBtuRec.PtInRect(point) && isObj&&!isCam)
	{
		m_btuRevise.SetWindowTextW(show_file_mat.GetItemText(mRow, mCol));
		CString x, y, z, x1, y1, z1;
		x.Format(TEXT("%.3g"), xm[mRow]);
		y.Format(TEXT("%.3g"), ym[mRow]);
		z.Format(TEXT("%.3g"), zm[mRow]);
		x1.Format(TEXT("%.3g"), xr[mRow]);
		y1.Format(TEXT("%.3g"), yr[mRow]);
		z1.Format(TEXT("%.3g"), zr[mRow]);
		m_editx.SetWindowTextW(x);
		m_edity.SetWindowTextW(y);
		m_editz.SetWindowTextW(z);
		m_editrx.SetWindowTextW(x1);
		m_editry.SetWindowTextW(y1);
		m_editrz.SetWindowTextW(z1);
	}
	if (togeBtuRec.PtInRect(point) && isCam&&!isObj)
	{
		m_btuRevise.SetWindowTextW(TEXT("相机"));
		CString x, y, z, x1, y1, z1;
		x.Format(TEXT("%.3g"), viewPoint.x);
		y.Format(TEXT("%.3g"), viewPoint.y);
		z.Format(TEXT("%.3g"), viewPoint.z);
		x1.Format(TEXT("%.3g"),cameraDir.x);
		y1.Format(TEXT("%.3g"), cameraDir.y);
		z1.Format(TEXT("%.3g"), cameraDir.z);
		m_editx.SetWindowTextW(x);
		m_edity.SetWindowTextW(y);
		m_editz.SetWindowTextW(z);
		m_editrx.SetWindowTextW(x1);
		m_editry.SetWindowTextW(y1);
		m_editrz.SetWindowTextW(z1);
	}
	if (togeBtuRec.PtInRect(point) && isLight&&!isObj&&!isCam)
	{
		m_btuRevise.SetWindowTextW(TEXT("光源"));
		CString x, y, z, x1, y1, z1;
		x.Format(TEXT("%.3g"), lightPoint.x);
		y.Format(TEXT("%.3g"), lightPoint.y);
		z.Format(TEXT("%.3g"), lightPoint.z);
		m_editx.SetWindowTextW(x);
		m_edity.SetWindowTextW(y);
		m_editz.SetWindowTextW(z);
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CRayTraceDlg::OnLvnBegindragListfilemat(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CRect rc;
	mRow = pNMListView->iItem;//获得选中的行
	mCol = pNMListView->iSubItem;//获得选中列
	if (mCol == 0 && !tempIsObj)
	{
		tempIsObj = true;
		GetDlgItem(IDC_EDIT3)->SetWindowTextW(TEXT("选择修改数据集"));
	}
}


void CRayTraceDlg::OnEnChangeEditx()
{
	CString tem;
	m_editx.GetWindowText(tem); 
	float valueNew = _ttof(tem);
	if (isObj)
	{
		xm[mRow] = valueNew;
	}
	if (isCam)
	{
		viewPoint.x = valueNew;
	}
	if (isLight)
	{
		lightPoint.x = valueNew;
	}
}


void CRayTraceDlg::OnEnChangeEdity()
{
	CString tem;
	m_edity.GetWindowText(tem); 
	float valueNew = _ttof(tem);
	if (isObj)
	{
		ym[mRow] = valueNew;
	}
	if (isCam)
	{
		viewPoint.y = valueNew;
	}
	if (isLight)
	{
		lightPoint.y = valueNew;
	}
}


void CRayTraceDlg::OnEnChangeEditz()
{
	CString tem;
	m_editz.GetWindowText(tem); 
	float valueNew = _ttof(tem);
	if (isObj)
	{
		zm[mRow] = valueNew;
	}
	if (isCam)
	{
		viewPoint.z = valueNew;
	}
	if (isLight)
	{
		lightPoint.z = valueNew;
	}
}


void CRayTraceDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CRect togeBtuRec;
	CWnd *pWin = GetDlgItem(IDC_STAREVISE); 
	pWin->GetWindowRect(&togeBtuRec);
	ScreenToClient(togeBtuRec);
	if (togeBtuRec.PtInRect(point) && tempIsObj)
	{
		pWin->SetWindowTextW(TEXT("修改模型位置"));
	}
	if (togeBtuRec.PtInRect(point) && tempIsCam)
	{
		pWin->SetWindowTextW(TEXT("修改相机参数"));
	}
	if (togeBtuRec.PtInRect(point) && tempIsLight)
	{
		pWin->SetWindowTextW(TEXT("修改光源参数"));
	}
	CDialogEx::OnMouseMove(nFlags, point);

}


void CRayTraceDlg::OnEnChangeEditRotx()
{
	CString tem;
	m_editrx.GetWindowText(tem); 
	float valueNew = _ttof(tem);
	if (isObj)
	{
		xr[mRow] = valueNew;
	}
	if (isCam)
	{
		cameraDir.x = valueNew;
	}
}


void CRayTraceDlg::OnEnChangeEditRoty()
{
	CString tem;
	m_editry.GetWindowText(tem); 
	float valueNew = _ttof(tem);
	if (isObj)
	{
		yr[mRow] = valueNew;
	}
	if (isCam)
	{
		cameraDir.y = valueNew;
	}
}


void CRayTraceDlg::OnEnChangeEditRotz()
{
	CString tem;
	m_editrz.GetWindowText(tem); 
	float valueNew = _ttof(tem);
	if (isObj)
	{
		zr[mRow] = valueNew;
	}
	if (isCam)
	{
		cameraDir.z = valueNew;
	}
}


void CRayTraceDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CRect camRec;
	CRect lightRec;
	GetDlgItem(IDC_STACAM)->GetWindowRect(&camRec);
	GetDlgItem(IDC_STALIGHT)->GetWindowRect(&lightRec);
	ScreenToClient(camRec);
	ScreenToClient(lightRec);
	if (camRec.PtInRect(point))
	{
		tempIsCam = true;
	}
	if (lightRec.PtInRect(point))
	{
		tempIsLight = true;
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CRayTraceDlg::OnEnChangeEditThread()
{
	CString nuThread;
	m_Thread.GetWindowText(nuThread);
	threadNum = _wtoi(nuThread);
}
