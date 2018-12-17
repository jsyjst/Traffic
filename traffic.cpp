#include "traffic.h"
/*交通工具信息的录入*/
struct arc {
    int num;   //班次
    float money; //费用
    char beginCity[10];  //出发地
    char arriveCity[10]; //目的地
    int beginTime[2];   //出发时间
    int arriveTime[2];  //到达时间
}VehicleNote[MAX_ARC_SIZE];
char city[MAX_VERTEX_NUM][10];
int TTime[2];
int time[2];
int time1[2];
int time2[2];
int c[MAX_VERTEX_NUM];
int d[MAX_VERTEX_NUM];

void initGraph(ALGraph *G)     //初始化交通系统
/*
  初始化交通系统方式选择界面
*/
{
    int i;
    printf("请选择初始化方式:\n");
    printf("1=键盘\n2=文档\n");
    printf("选择?");
    scanf("%d", &i);
    getchar();
    switch(i) {
    case 1:
        createCityFile();
        createPlaneFile();
        createTrainFile();
        createGraph(G);
        break;
    case 2:
        createGraph(G);
        break;
    }
}
void createCityFile()
/*
  创建城市名称文档
*/
{
    int i = 0;
    int j;
    char flag = 'y';
    FILE *fpWrite;
    printf("\n请输入城市名称的信息:\n");
    while(flag == 'y' || flag == 'Y') {
        printf("城市名称:");
        gets(city[i]);
        i++;
        printf("继续输入?(Y/N)");
        scanf("%c", &flag);
        getchar();
    }
    printf("\n");
    /*将城市名写入文件*/
    if((fpWrite = fopen("city.txt", "wb")) == NULL) {//wb表示操作二进制格式的文件
        printf("无法打开城市文件!/n");
        return;
    }
    for(j = 0; j < i; j++)
        fprintf(fpWrite, "%10s", city[j]);
    fclose(fpWrite);
}
void createPlaneFile()
/*
  创建飞机航班文档
*/
{
    int num, beginTime[2], arriveTime[2]; //num航班编号，beginTime出发时间，arriveTime到达时间
    float money;  //费用
    int i;
    int k; //用来记录航班的车次
    char beginCity[10], arriveCity[10], flag; //beginCity起始城市，arriveCity目标城市
    FILE *fp;
    flag = 'y';
    k = 0;
    while(flag == 'Y' || flag == 'y') { /*flag为标志位,初值为1*/
        printf("请输入飞机航班的信息:\n"); //提示"输入航班信息"
        printf("飞机航班编号:");  //输入航班num
        scanf("%d", &num);
        getchar();
        printf("起始城市:");   //输入航班的出发城市beginCity
        gets(beginCity);
        printf("目的城市:");  //输入航班的到达城市arriveCity
        gets(arriveCity);
        printf("航班费用:");  //输入机票价格money
        scanf("%f", &money);
        getchar();
        printf("起飞时间:");  //输入航班的出发时间beginTime
        scanf("%d:%d", &beginTime[0], &beginTime[1]);
        getchar();
        while(beginTime[0] < 0 || beginTime[0] >= 24 || beginTime[1] < 0 || beginTime[1] >= 60) {
            printf("\n时间输入有误，请重新输入\n");
            scanf("%d:%d", &beginTime[0], &beginTime[1]);
            getchar();
        }
        printf("到达时间:");  //输入航班的到达时间arriveTime
        scanf("%d:%d", &arriveTime[0], &arriveTime[1]);
        getchar();
        while(arriveTime[0] < 0 || arriveTime[0] >= 24 || arriveTime[1] < 0 || arriveTime[1] >= 60) {
            printf("\n时间输入有误，请重新输入\n");
            scanf("%d:%d", &arriveTime[0], &arriveTime[1]);
            getchar();
        }
        /*VehicleNote为程序头部定义的结构体,存储交通工具的信息*/
        VehicleNote[k].num = num; //班次
        VehicleNote[k].money = money; //费用
        strcpy(VehicleNote[k].beginCity, beginCity); //出发地
        strcpy(VehicleNote[k].arriveCity, arriveCity); //目的地
        /*到达时间*/
        VehicleNote[k].arriveTime[0] = arriveTime[0];
        VehicleNote[k].arriveTime[1] = arriveTime[1];
        /*开始时间*/
        VehicleNote[k].beginTime[0] = beginTime[0];
        VehicleNote[k].beginTime[1] = beginTime[1];
        k++;  //存储下一条边的信息
        printf("继续输入?(Y/N)");  //提示"是否要继续输入航班信息："
        scanf("%c", &flag);
        getchar();
        printf("\n");
    }
    /*将航班信息存入结构体数组，然后将结构体数组写进航班文件*/
    if((fp = fopen("plane.txt", "wb")) == NULL) //航班文件不能以读写形式打开
        printf("\n无法打开航班文件!\n");  //提示"无法打开文件"
    fprintf(fp, "%d", k);  //将计数值k写入航班车文件
    for(i = 0; i < k; i++)
        if(fwrite(&VehicleNote[i], sizeof(struct arc), 1, fp) != 1) //无法将a[i]写入航班文件
            printf("\n文件写入错误!\n");  //提示"文件无法写入"
    fclose(fp);    //关闭航班文件
}

void createTrainFile()
/*
  创建列车车次文档
*/
{
    int num, beginTime[2], arriveTime[2]; //num航班编号，beginTime出发时间，arriveTime到达时间
    float money;  //费用
    int i;
    int k; //用来记录航班的车次
    char beginCity[10], arriveCity[10], flag; //beginCity起始城市，arriveCity目标城市
    FILE *fp;
    flag = 'y';
    k = 0;
    while(flag == 'Y' || flag == 'y') { /*flag为标志位,初值为1*/
        printf("请输入列车车次的信息:\n"); //提示"输入列车信息"
        printf("列车车次编号:");  //输入列车车次num
        scanf("%d", &num);
        getchar();
        printf("起始城市:");   //输入列车的出发城市beginCity
        gets(beginCity);
        printf("目的城市:");  //输入列车的到达城市arriveCity
        gets(arriveCity);
        printf("车次费用:");  //输入车票money
        scanf("%f", &money);
        getchar();
        printf("发车时间:");  //输入列车的出发时间beginTime
        scanf("%d:%d", &beginTime[0], &beginTime[1]);
        getchar();
        while(beginTime[0] < 0 || beginTime[0] >= 24 || beginTime[1] < 0 || beginTime[1] >= 60) {
            printf("\n时间输入有误，请重新输入\n");
            scanf("%d:%d", &beginTime[0], &beginTime[1]);
            getchar();
        }
        printf("到达时间:");  //输入航班的到达时间arrvieTime
        scanf("%d:%d", &arriveTime[0], &arriveTime[1]);
        getchar();
        while(arriveTime[0] < 0 || arriveTime[0] >= 24 || arriveTime[1] < 0 || arriveTime[1] >= 60) {
            printf("\n时间输入有误，请重新输入\n");
            scanf("%d:%d", &arriveTime[0], &arriveTime[1]);
            getchar();
        }
        /*VehicleNote为程序头部定义的结构体,存储交通工具的信息*/
        VehicleNote[k].num = num; //班次
        VehicleNote[k].money = money; //费用
        strcpy(VehicleNote[k].beginCity, beginCity); //出发地
        strcpy(VehicleNote[k].arriveCity, arriveCity); //目的地
        /*到达时间*/
        VehicleNote[k].arriveTime[0] = arriveTime[0];
        VehicleNote[k].arriveTime[1] = arriveTime[1];
        /*开始时间*/
        VehicleNote[k].beginTime[0] = beginTime[0];
        VehicleNote[k].beginTime[1] = beginTime[1];
        k++;  //存储下一条边的信息
        printf("继续输入?(Y/N)");  //提示"是否要继续输入航班信息："
        scanf("%c", &flag);
        getchar();
        printf("\n");
    }
    /*将航班信息存入结构体数组，然后将结构体数组写进航班文件*/
    if((fp = fopen("train.txt", "wb")) == NULL) //航班文件不能以读写形式打开
        printf("\n无法打开列车文件!\n");  //提示"无法打开文件"
    fprintf(fp, "%d", k);  //将计数值k写入航班车文件
    for(i = 0; i < k; i++)
        if(fwrite(&VehicleNote[i], sizeof(struct arc), 1, fp) != 1) //无法将a[i]写入航班文件
            printf("\n文件写入错误!\n");  //提示"文件无法写入"
    fclose(fp);    //关闭航班文件
}


int LocateVex(ALGraph *G, char *v)
/*
  城市名在交通系统中定位操作，找出城市名在图中对应结点位置
*/
{
    int j, k;
    j = -1;
    for(k = 0; k < G->vexNum; k++)
        if(strcmp(G->vexs[k].cityName, v) == 0) { //第k个结点中的城市名与传过来的城市名相同
            j = k;  /*记录位置*/
            break;
        }
    return j;
}

void createGraph(ALGraph *G)
/*
  用city，plan，train三个文档创建城市交通系统
*/
{
    int i, j, k;
    int arcNum;  //弧的数量
    int count1, count2;  //飞机和列车的班次
    int m, t;
    ArcNode *p, *q;
    FILE *fp;
    i = 0;
    if((fp = fopen("city.txt", "rb")) == NULL) { //打开城市文件，文件指针返回值为空
        printf("\n无法打开城市文件!\n");
        return;
    }
    while(!feof(fp)) { //文件不为空
        fscanf(fp, "%10s", city[i]);
        i++;
    }
    fclose(fp);  //关闭文件
    j = 0;
    while(j < i) {
        strcpy(G->vexs[j].cityName, city[j]); //将 city[i] 中的内容复制到图的结构体的结点数组中;
        G->vexs[j].planeFirstArc = NULL; // 图的结构体其他项赋初值;
        G->vexs[j].trainFirstArc = NULL;
        j++;
    }
    G->vexNum = i;

    /*对航班文件进行操作*/
    if((fp = fopen("plane.txt", "rb")) == NULL)
        printf("\n无法打开航班文件!\n");
    k = 0;
    fscanf(fp, "%d", &count1); //打开航班信息文件"plane.txt"
    while(k < count1) {
        /*读取结构体*/
        if(fread(&VehicleNote[k], sizeof(struct arc), 1, fp) != 1)
            printf("\n文件读入错误!\n");
        k++;
    }
    fclose(fp);  //关闭文件
    k = 0;       //VehicleNode的计数变量k=0
    arcNum = 0; //弧的计数变量
    while(k < count1) {
        i = LocateVex(G, VehicleNote[k].beginCity); //调用函数得到起始结点的位置 i
        j = LocateVex(G, VehicleNote[k].arriveCity); //调用函数得到末端结点的位置 j
        q = G->vexs[i].planeFirstArc;
        m = 0;
        while(q != NULL) {
            if(q->adjvex == j) { //弧 q中的邻接顶点与j相等
                t = q->info.last + 1; // 将数组VehicleNode中的内容都复制到弧q中
                q->info.stata[t].num = VehicleNote[k].num;
                q->info.stata[t].money = VehicleNote[k].money;
                q->info.stata[t].beginTime[0] = VehicleNote[k].beginTime[0];
                q->info.stata[t].beginTime[1] = VehicleNote[k].beginTime[1];
                q->info.stata[t].arriveTime[0] = VehicleNote[k].arriveTime[0];
                q->info.stata[t].arriveTime[1] = VehicleNote[k].arriveTime[1];
                q->info.last = t;
                m = 1;
                break;
            }
            q = q->nextArc;
        }
        if(m == 0) {
            p = (ArcNode*)malloc(sizeof(ArcNode)); //开辟一个弧结点
            p->adjvex = j; //将数组VehicleNode中的内容都复制到新的弧结点中
            p->info.stata[0].num = VehicleNote[k].num;
            p->info.stata[0].money = VehicleNote[k].money;
            p->info.stata[0].beginTime[0] = VehicleNote[k].beginTime[0];
            p->info.stata[0].beginTime[1] = VehicleNote[k].beginTime[1];
            p->info.stata[0].arriveTime[0] = VehicleNote[k].arriveTime[0];
            p->info.stata[0].arriveTime[1] = VehicleNote[k].arriveTime[1];
            p->info.last = 0;
            p->nextArc = G->vexs[i].planeFirstArc;
            G->vexs[i].planeFirstArc = p; // 将弧结点连接到适当的位置中去
            arcNum++;
        }
        k++;
    }
    G->planeArcNum = arcNum;
    if((fp = fopen("train.txt", "rb")) == NULL) {
        printf("\n无法打开列车文件!\n");
        return;
    }
    k = 0;
    fscanf(fp, "%d", &count2); //打开列车信息文件"plane.txt"
    while(k < count2) {
        if(fread(&VehicleNote[k], sizeof(struct arc), 1, fp) != 1)
            printf("\n文件读入错误!\n");
        k++;
    }
    fclose(fp);  //关闭文件
    k = 0;       //VehicleNode的计数变量k=0
    arcNum = 0; //弧的计数变量
    while(k < count2) {
        i = LocateVex(G, VehicleNote[k].beginCity); //调用函数得到起始结点的位置 i
        j = LocateVex(G, VehicleNote[k].arriveCity); //调用函数得到末端结点的位置 j
        q = G->vexs[i].trainFirstArc;
        m = 0;
        while(q != NULL) {
            if(q->adjvex == j) { //弧 q中的邻接顶点与j相等
                t = q->info.last + 1; // 将数组VehicleNode中的内容都复制到弧q中
                q->info.stata[t].num = VehicleNote[k].num;
                q->info.stata[t].money = VehicleNote[k].money;
                q->info.stata[t].beginTime[0] = VehicleNote[k].beginTime[0];
                q->info.stata[t].beginTime[1] = VehicleNote[k].beginTime[1];
                q->info.stata[t].arriveTime[0] = VehicleNote[k].arriveTime[0];
                q->info.stata[t].arriveTime[1] = VehicleNote[k].arriveTime[1];
                q->info.last = t;
                m = 1;
                break;
            }
            q = q->nextArc;
        }
        if(m == 0) {
            p = (ArcNode*)malloc(sizeof(ArcNode)); //开辟一个弧结点
            p->adjvex = j; //将数组VehicleNode中的内容都复制到新的弧结点中
            p->info.stata[0].num = VehicleNote[k].num;
            p->info.stata[0].money = VehicleNote[k].money;
            p->info.stata[0].beginTime[0] = VehicleNote[k].beginTime[0];
            p->info.stata[0].beginTime[1] = VehicleNote[k].beginTime[1];
            p->info.stata[0].arriveTime[0] = VehicleNote[k].arriveTime[0];
            p->info.stata[0].arriveTime[1] = VehicleNote[k].arriveTime[1];
            p->info.last = 0;
            p->nextArc = G->vexs[i].trainFirstArc;
            G->vexs[i].trainFirstArc = p; // 将弧结点连接到适当的位置中去
            arcNum++;
        }
        k++;
    }
    G->trainArcNum = arcNum;
}
