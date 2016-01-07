#pragma once


// Insertdata 对话框

class Insertdata : public CDialogEx
{
	DECLARE_DYNAMIC(Insertdata)

public:
	Insertdata(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Insertdata();

// 对话框数据
	enum { IDD = IDD_INSERTDATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
