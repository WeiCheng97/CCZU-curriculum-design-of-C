#include <stdio.h>
#include <cv.h>
#include <highgui.h>

IplImage *img = 0;  //定义图像
int height,width,step,channels,depth;
int i,j,k;
uchar *data;
//定义函数
void loadimg();//加载图像并且显示图像信息
void slco();//选择图像操作
void saveimg();//保存图像
void toGrayimg();//转换灰度图像
void roGimg();//旋转灰度图像
void roRGBimg();//旋转彩色图像
void rollGimg();//翻转灰度图像
void rollRGBimg();//翻转彩色图像
void seltype();//选择灰度图片镜像种类
void seltype1();//选择彩色图片镜像种类
void rollkd1(IplImage *src);//水平镜像
void rollkd2(IplImage *src);//垂直镜像
int main()
{
	printf("  数字图像处理\n   几何变换 1\nBy 华院152 蒋炜成\n\n");
	loadimg();
	return 0;
}
void loadimg()//加载图像并且显示图像信息,提供操作选项
{
	img=cvLoadImage("input.png");
	if(!img)
		{
		    printf("无法加载本目录以下图片: %s\n，"
             "请把图片改名为\"input.png\"放于本目录下","input.png");
            getchar();
		}
    else
    {
        height    = img->height;//图片参数
        width     = img->width;
        step      = img->widthStep;
        channels  = img->nChannels;
        depth     = img->depth;
        data      = (uchar *)img->imageData;
        printf("程序正在处理一个尺寸为%dx%d的%d通道%d位图像\n",height,width,depth,channels);
        cvNamedWindow("原图",CV_WINDOW_AUTOSIZE);//创建窗口
        cvShowImage("原图",img);
        cvWaitKey(0);
        cvDestroyWindow("原图");
        slco();
    }
}
void slco()
{
    int n;
    printf("请选择您要进行的操作\n"
		"0------退出程序\n"
		"1------把图像转换成灰度图像\n"
		"2------把灰度图像旋转任意角度\n"
		"3------把彩色图像旋转任意角度\n"
		"4------镜像变换灰度图片\n"
		"5------镜像变换彩色图片\n");

    scanf("%d",&n);
    switch(n)
    {

        case 0:
            break;

        case 1:
            toGrayimg();
            break;

        case 2:
            roGimg();
            break;

        case 3:
            roRGBimg();
            break;

        case 4:
            seltype();
            break;

        case 5:
            seltype1();
            break;
    }
}

void saveimg(IplImage *src)//保存图像
{
    cvSaveImage("out.bmp",src);
	if(!cvSaveImage("out.bmp",src))
		printf("Could not save: %s\n","output.bmp");
	else
		printf("图像已经保存为%s。\n","output.bmp");
    cvNamedWindow("转换后",CV_WINDOW_AUTOSIZE);//创建窗口
    cvShowImage("转换后",src);
    cvWaitKey(0);
    cvDestroyWindow("转换后");
    slco();
}

void toGrayimg()//转换灰度图像
{
    IplImage *result=cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,1);//使用库转换图像空间
    cvCvtColor(img,result,CV_RGB2GRAY);
    saveimg(result);
}

void roGimg()
{
    IplImage *result=cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,1);
    IplImage *res=cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,1);
    cvCvtColor(img,result,CV_RGB2GRAY);
    double angle;
    printf("请输入要旋转的角度: ");
    scanf("%lf", &angle);
    float m[6];
    CvMat rotMat = cvMat(2, 3, CV_32F, m);
    CvPoint2D32f center;
    center.x = (float) (result->width / 2.0 + 0.5);
    center.y = (float) (result->height / 2.0 + 0.5);
    cv2DRotationMatrix(center, -angle, 1, &rotMat);
    cvWarpAffine(result,res, &rotMat, CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
    //图像仿射变换函数
    saveimg(res);
}

void roRGBimg()
{
    double angle;
    printf("请输入要旋转的角度: ");
    scanf("%lf", &angle);
    float m[6];
    CvMat rotMat = cvMat(2, 3, CV_32F, m);
    CvPoint2D32f center;
    center.x = (float) (img->width / 2.0 + 0.5);
    center.y = (float) (img->height / 2.0 + 0.5);//计算二维旋转的仿射变换矩阵
    cv2DRotationMatrix(center, -angle, 1, &rotMat);
    IplImage *result = cvCreateImage(cvGetSize(img),8,3);
    cvWarpAffine(img, result, &rotMat, CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
    //图像仿射变换函数
    saveimg(result);
}

void seltype()
{
    IplImage *result=cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,1);
    cvCvtColor(img,result,CV_RGB2GRAY);
    int q;
    printf("请选择镜像类型"
		"0------水平镜像\n"
		"1------垂直镜像\n");
    scanf("%d",&q);
    switch(q)
    {
        case 0:
            rollkd1(result);

        case 1:
            rollkd2(result);
    }
}

void seltype1()
{
    IplImage *result=img;
    int q;
    printf("请选择镜像类型"
		"0------水平镜像\n"
		"1------垂直镜像\n");
    scanf("%d",&q);
    switch(q)
    {
        case 0:
            rollkd1(result);

        case 1:
            rollkd2(result);
    }
}

void rollkd1(IplImage *src)//水平镜像
{
    float m[6] = {-1.0f, 0, (float) src->width,
                  0, 10f, 0};//构建变换矩阵
    CvMat fliper = cvMat(2, 3, CV_32F, m);//构建Mat
    IplImage *result = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);//现场判断位深和通道以免出错
    cvWarpAffine(src, result, &fliper, CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
    saveimg(result);
}

void rollkd2(IplImage *src)//垂直镜像
{
    float m[6] = {1.0f, 0, 0,
                  0, -1.0f, (float) src->height};
    CvMat fliper = cvMat(2, 3, CV_32F, m);
    IplImage *result = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    cvWarpAffine(src, result, &fliper, CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
    saveimg(result);
}


