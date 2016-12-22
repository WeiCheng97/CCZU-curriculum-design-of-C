#include "stdafx.h"
#include"windows.h" //ListBox类函数定义
#include "resource.h"
#include"stdio.h"
#include"windowsx.h"                       
#include"commdlg.h"
#define MAX_LOADSTRING 100
// Foward declarations of functions included in this code module://声明函数
BOOL				InitInstance(HINSTANCE, int);//运行程序的实例 自带函数
LRESULT CALLBACK	LOADING(HWND, UINT, WPARAM, LPARAM);//登录函数的声明
LRESULT CALLBACK	CHATTING(HWND, UINT, WPARAM, LPARAM);//处理聊天函数的声明
HINSTANCE hInst;								// current instance句柄
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

struct member{//成员聊天信息
	char name[25];
	char chattext[100];
	int flag;//计数为600
	int flag2;//登陆
	int flag3;//退出
}User,User_2;         //自己和通用变量
char User_3[100][100];//用户名单
char tms[600];//聊天前缀显示
char Name[100];//电脑名字
int _i,_p,n=1;//判断发消息的人是否在名单里
HANDLE hMySlot;//
char MyComputerName[16];//获取机器名
char Myaddress[100],address[100]; //聊天室名字//聊天名单成员名字


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	DWORD sz=sizeof(MyComputerName);
	GetComputerName(MyComputerName,&sz);	
	// Initialize global strings
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) //登录界面对话框处理
{
   HWND hWnd;
   hInst = hInstance; // Store instance handle in our global variable
 hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	//弹出登录对话框，如果点击确定，则创建邮件槽并弹出聊天界面
    if(DialogBox(hInst,(LPCTSTR)IDD_INPUT_LOADING,hWnd,(DLGPROC)LOADING)==IDOK)
	{
		hMySlot=CreateMailslot(_T(Myaddress),0,MAILSLOT_WAIT_FOREVER,NULL);//邮件槽
		DialogBox(hInst,(LPCTSTR)IDD_CHATROOM,hWnd,(DLGPROC)CHATTING);//弹出聊天界面
	}
	else
		return FALSE;
     if (!hWnd)
   {
      return FALSE;
   }
   UpdateWindow(hWnd);
   return TRUE;
}


LRESULT CALLBACK LOADING(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)//登录界面 获取信息
{
	switch (message)
	{
		case WM_INITDIALOG:       //是对话框才能收到的消息,表明对话框及其所有子控件都创建完毕了。
				return TRUE;

		case WM_COMMAND:          //当用户从菜单选中一个命令项目、当一个控件发送通知消息给去父窗口或者按下一个快捷键将发送 WM_COMMAND 消息
			if(LOWORD(wParam) == IDOK)
			{

				GetDlgItemText(hDlg,IDC_USERNAME,User.name,32);//获取用户昵称
				GetDlgItemText(hDlg,IDC_LTSNAME,Name,32);//获取聊天室名字
				sprintf(Myaddress,"//./mailslot/%s",Name);
				sprintf(address,"//*/mailslot/%s",Name);//存入邮件槽
				User.flag=600;//初值设为600
				User.flag2=1;//设置登录初值
				User.flag3=10;//设置登出标识值
				strcpy(User_3[0],User.name);//将本地用户的信息复制到聊天室名单的第一行
				EndDialog(hDlg, LOWORD(wParam));//关闭对话框函		
			}
			if (LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));//关闭对话框函数
				return TRUE;
			}
			break;
	}
    return FALSE;
}
LRESULT CALLBACK CHATTING(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)//消息处理
{			
	
	HWND hWndEdit=GetDlgItem(hDlg,IDC_EDIT1);//获取编辑框的一个引用句柄
	HWND hWndList;
	int nItem,k;//依次为：双击项的位置，双击位置索引
	int del;//删除客户用的索引
	char getname[33];          //双击获取名字
	char secret[100],list[100],msgg1[100],msgg2[100];//msgg1 用来提示新成员进入
	SetTimer(hDlg,1,50,NULL);//计时器1的设定（检索邮箱槽）
	//SetTimer(hDlg,2,2*60*1000,NULL);//计时器2的设定
	//SetTimer(hDlg,3,1000,NULL);//计时器3的设定(递减）
	switch (message)
	{
		case WM_INITDIALOG://对话框创建 完毕并写入了聊天成员
			{
				DWORD Writted;
				HANDLE hMailslot=CreateFile(_T(address),GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);//创建写入区并打开邮件槽的引用句柄
				WriteFile(hMailslot,&User,sizeof(User),&Writted,NULL);//写入
				SendDlgItemMessage(hDlg,IDC_NAMELIST,LB_ADDSTRING,NULL,(long)User.name);//添加一个成员（自己）
				CloseHandle(hMailslot);//关闭邮件槽
			}
				return TRUE;
		case WM_TIMER://处理输入的消息
				{
					if(wParam==1) //如果计时器1（50ms）时间到了//消息响应机制
					{
				    SYSTEMTIME tm;//时间
					HWND hWnd;
					DWORD msgSize,nextMsgSize,Unreaded,readed;
					GetLocalTime(&tm);//获取时间
					while(GetMailslotInfo(hMySlot,&msgSize,&nextMsgSize,&Unreaded,NULL) && Unreaded>0)//如果有消息输入
					{
					ReadFile(hMySlot,&User_2,sizeof(User_2),&readed,NULL);//从客户机读数据
					//如果没有内容则不能输出
					if(User_2.chattext[0])
					{
					sprintf(tms,"%d:%d:%d 【%s】说:%s",tm.wHour,tm.wMinute,tm.wSecond,User_2.name,User_2.chattext);//整合成一个tms
					SendDlgItemMessage(hDlg,IDC_CHAT,LB_ADDSTRING,NULL,(long)tms);//tms输出到聊天窗口
					}
					//判断在用户名单里是否已存在
					//其中，ini为是否重复的标志，pt和n均为判断变量，用来控制次数
					for(_i=0,_p=0;_p<n;_p++)
					{
						if(strcmp(User_2.name,User_3[_p])==0)
							_i++;
					}
					if(_i==0)//如果没有此名字，则添加到名单里
					{
						strcpy(User_3[_p],User_2.name);//复制
						SendDlgItemMessage(hDlg,IDC_NAMELIST,LB_ADDSTRING,NULL,(long)User_3[_p]);//添加
						n++;//用来计要比较几次
					}
					//弹出登录信息
					if(User_2.flag==600&&User_2.flag2==1) //刚进来并且没有下线
					{
						sprintf(msgg1,"用户 %s 已登陆",User_2.name);//复制
						MessageBox(hDlg,msgg1,"Login",MB_OK|MB_ICONEXCLAMATION);//输出
						User.flag2=2;
					}
					//弹出登出信息
					if(User_2.flag==0||User_2.flag3==1000) //检查是否离线或者退出
					{
						hWndList=GetDlgItem(hDlg,IDC_NAMELIST);//获取聊天成员
						del=ListBox_FindString(hWndList,-1,User_2.name);   //找到这个用户
						ListBox_DeleteString(hWndList,del);                //删除此用户
						sprintf(msgg2,"用户 %s 不想和你说话并关闭了聊天窗口",User_2.name); //提示用户退出
						MessageBox(hDlg,msgg2,"LogOut",MB_OK|MB_ICONEXCLAMATION);
						User.flag3=100;//重设flag3的值，用来区别
					}
					}
					}//
				}
				break;

		case WM_COMMAND://鼠标操作
			if(LOWORD(wParam)==IDC_NAMELIST)//私聊有BUG
			{
				if(HIWORD(wParam)==LBN_DBLCLK)//响应双击事件
				{
					hWndEdit=GetDlgItem(hDlg,IDC_EDIT1);
					hWndList=GetDlgItem(hDlg,IDC_NAMELIST);//获取列表框的一个引用句柄
				    nItem=SendMessage(hWndEdit,LB_GETCURSEL,0,0);//获取双击项的位置
					k=SendDlgItemMessage(hDlg,IDC_NAMELIST,LB_GETCURSEL,0,0);//获取双击项的索引
					ListBox_GetText(hWndList,k,getname);//包含在windowsx.h下面，获取双击项所包含的字符串，也就是用户名
					sprintf(secret,">[%s]",getname);
					SetWindowText(hWndEdit,secret);//将>[用户]的内容显示在输入框上
				}
				
			}
			if(LOWORD(wParam) == IDOK)//点击了发送（或按下回车）发送消息
			{
				DWORD Writted;
				DWORD msgSize,nextMsgSize,Unreaded,readed;
				SYSTEMTIME tm;
				GetLocalTime(&tm);
				GetDlgItemText(hDlg,IDC_EDIT1,User.chattext,32);//获取句柄
				HANDLE hMailslot=CreateFile(_T(address),GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);//创建写入区并打开邮件槽的引用句柄
				WriteFile(hMailslot,&User,sizeof(User),&Writted,NULL);//写入
				SetWindowText(hWndEdit,"");//清空输入框
				CloseHandle(hMailslot);//关闭邮件槽
			}
			if (LOWORD(wParam) == IDCANCEL)
			{
				DWORD Writted;
				User.flag3=1000;       //退出时修改参数flag3
				HANDLE hMailslot=CreateFile(_T(address),GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);//创建写入区并打开邮件槽的引用句柄
				WriteFile(hMailslot,&User,sizeof(User),&Writted,NULL);//写入
				CloseHandle(hMailslot);//关闭邮件槽
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
