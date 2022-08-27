
// RayTraceDlg.h : ͷ�ļ�
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


// CRayTraceDlg �Ի���
class CRayTraceDlg : public CDialogEx
{

// ����
public:
	CRayTraceDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CRayTraceDlg();
// �Ի�������
	enum { IDD = IDD_RAYTRACE_DIALOG };

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
public:
	afx_msg void OnBnClickedButStart();
	afx_msg void OnEnChangeEditSize();
	afx_msg void OnBnClickedButSave();
	afx_msg void OnDblclkListFileMat(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKillfocusEditMatIn();
	///�Զ��庯��
	CRGB PixelColor(Ray&, World *, int);///��������˶�����ɫ
	void ReadObjectVex();///������
	void SetMaterial();///���ò���
	void GetInitImage();///���ò�������
	void SetSample(CDC*);///������
	void InitMatList();///��ʼ���������
	void ThreadFun(Camera camera,int low, int heigh, int size);///���߳�����
	///����ģ�����㣬�ҳ�ģ������ֵ
	int GetMaxInNum(int, int, int, int);
	int GetMinInNum(int, int, int, int);
	///�Զ������
	bool IsDiff(float, float);///����ͼ��ĳ�������Ƿ���Ҫ����
	float screen_z;///��Ļz����
	CVector3 lightPoint;///��Դ����
	CVector3 viewPoint;///�ӵ���
	CVector3 cameraDir;///�������
	int objNum;/*�����������*/
	float fadekt;///�δ����߾���˥������
	World *obj[10];///����ָ�룬�Զ�10������
	//Face *faceList[3];/*��ʼ����*/
	World *scene;/*��ʼ������*/
	////ģ�ͱ༭��
	float xm[10], ym[10], zm[10];
	float xr[10], yr[10], zr[10];
	int numMat;///��������
	Material *objectMat[13];//����
    int imageSize;///ͼƬ�ߴ�
	CRGB **pixCol;///ͼ������ָ��
	int threadNum;///�������߳���
	int objMatindex[10];///����ָ�����������ڳ�ʼ�������б�
	bool run;///�����Ƿ�����
	CString objName[10];///�ļ���
	CString workWord;///�����ı�
	///�����б���ر���
	CString filePathstr;
	CListCtrl show_file_mat;///�б�
	CImageList matIcolist;
	CEdit inMAtindex;
	int mRow, mCol;///ѡȡ�Ĳ�������е�������
	int imgVersion;///����ͼƬ�İ汾��
	///�༭����ر���
	bool isObj;///�Ƿ�����༭ģ��
	bool isCam;///�Ƿ�༭�����
	bool isLight;
	bool tempIsLight;
	bool tempIsCam;
	bool tempIsObj;
	CStatic m_btuRevise;///ģ������ľ�̬��
	///ƽ�Ʊ༭��
	CEdit m_editx;
	CEdit m_edity;
	CEdit m_editz;
	////��ת�༭��
	CEdit m_editrx;
	CEdit m_editry;
	CEdit m_editrz;
	////��Ϣ������
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
