#pragma once


// Insertdata �Ի���

class Insertdata : public CDialogEx
{
	DECLARE_DYNAMIC(Insertdata)

public:
	Insertdata(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Insertdata();

// �Ի�������
	enum { IDD = IDD_INSERTDATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
