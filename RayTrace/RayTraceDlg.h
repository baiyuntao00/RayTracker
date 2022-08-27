
// RayTraceDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include"Vector3.h"
#include"Ray.h"
#include"Object.h"
#include"Camera.h"
#include "Specular.h"
#include "Diffuse.h"
#include "Friction.h"
#include "Transparent.h"
#include "Checker2D.h"
#include"World.h"
#include"Face.h"
#include "HitGroup.h"
#include "Diffuse.h"
#include "Transform.h"


// CRayTraceDlg 对话框
class CRayTraceDlg : public CDialogEx
{

// 构造
public:
	CRayTraceDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CRayTraceDlg();
// 对话框数据
	enum { IDD = IDD_RAYTRACE_DIALOG };

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
public:
	afx_msg void OnBnClickedButStart();
	afx_msg void OnEnChangeEditSize();
	afx_msg void OnBnClickedButSave();
	afx_msg void OnDblclkListFileMat(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKillfocusEditMatIn();
	///自定义函数
	CRGB PixelColor(Ray&, World *, int);///计算光线运动后颜色
	void ReadObjectVex();///读数据
	void SetMaterial();///设置材质
	void GetInitImage();///设置采样运算
	void SetSample(CDC*);///反走样
	void InitMatList();///初始化材质面板
	void ThreadFun(Camera camera,int low, int heigh, int size);///子线程运行
	///类似模板运算，找出模板中最值
	int GetMaxInNum(int, int, int, int);
	int GetMinInNum(int, int, int, int);
	///自定义变量
	bool IsDiff(float, float);///表明图像某个区域是否需要采样
	float screen_z;///屏幕z坐标
	CVector3 lightPoint;///光源坐标
	CVector3 viewPoint;///视点坐
	CVector3 cameraDir;///相机参数
	int objNum;/*场景物体个数*/
	float fadekt;///次代光线距离衰减参数
	World *obj[10];///物体指针，对多10个物体
	//Face *faceList[3];/*初始化面*/
	World *scene;/*初始化世界*/
	////模型编辑量
	float xm[10], ym[10], zm[10];
	float xr[10], yr[10], zr[10];
	int numMat;///材质数量
	Material *objectMat[13];//材质
    int imageSize;///图片尺寸
	CRGB **pixCol;///图像像素指针
	int threadNum;///开启的线程数
	int objMatindex[10];///材质指针索引，用于初始化材质列表
	bool run;///表明是否运行
	CString objName[10];///文件名
	CString workWord;///交互文本
	///材质列表相关变量
	CString filePathstr;
	CListCtrl show_file_mat;///列表
	CImageList matIcolist;
	CEdit inMAtindex;
	int mRow, mCol;///选取的材质面板中的行列数
	int imgVersion;///保存图片的版本数
	///编辑框相关变量
	bool isObj;///是否允许编辑模型
	bool isCam;///是否编辑相机；
	bool isLight;
	bool tempIsLight;
	bool tempIsCam;
	bool tempIsObj;
	CStatic m_btuRevise;///模型拖入的静态框
	///平移编辑框
	CEdit m_editx;
	CEdit m_edity;
	CEdit m_editz;
	////旋转编辑框
	CEdit m_editrx;
	CEdit m_editry;
	CEdit m_editrz;
	////消息处理函数
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLvnBegindragListfilemat(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditx();
	afx_msg void OnEnChangeEdity();
	afx_msg void OnEnChangeEditz();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnEnChangeEditRotx();
	afx_msg void OnEnChangeEditRoty();
	afx_msg void OnEnChangeEditRotz();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CEdit m_Thread;
	afx_msg void OnEnChangeEditThread();
};
