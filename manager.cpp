#include "traffic.h"
#include "common.h"

void manager(ALGraph *G)
/*
  显示管理员管理项目选择界面
*/
{
    int i;
    printf("                         管理员管理:\n");
    printf("\n            |            1.初始化交通系统           |\n");
    printf("\n            |            2.城市编辑                 |\n");
    printf("\n            |            3.飞机航班编辑             |\n");
    printf("\n            |            4.列车车次编辑             |\n");
    printf("\n            |            5.返回上一级菜单           |\n");
    printf("\n选择?");
    scanf("%d", &i);
    getchar();
    while(i != 5) {
        switch(i) {
        case 1:
            initGraph(G);    //初始化交通系统
            break;
        case 2:
            cityEdit(G);     //城市编辑
            break;
        case 3:
            planeEdit(G);  //航班编辑
            break;
        case 4:
            trainEdit(G);  //列车编辑
            break;
        }
        printf("                         管理员管理:\n");
        printf("\n            |            1.初始化交通系统           |\n");
        printf("\n            |            2.城市编辑                 |\n");
        printf("\n            |            3.飞机航班编辑             |\n");
        printf("\n            |            4.列车车次编辑             |\n");
        printf("\n            |            5.返回上一级菜单           |\n");
        printf("\n选择?");
        scanf("%d", &i);
        getchar();
    }
}

/*
 初始化交通系统方式选择界面
*/
void initGraph(ALGraph *G) {   //初始化交通系统
    int i;
    printf("                         初始化方式:\n");
    printf("\n            |            1.键盘           |\n");
    printf("\n            |            2.文档           |\n");
    printf("\n选择?");
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

/*
  创建城市名称文档
*/
void createCityFile() {
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

/*
  创建飞机航班文档
*/
void createPlaneFile() {
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


/*
  创建列车车次文档
*/
void createTrainFile() {
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


/*
  城市名在交通系统中定位操作，找出城市名在图中对应结点位置
*/
int LocateVex(ALGraph *G, char *v) {
    int j, k;
    j = -1;
    for(k = 0; k < G->vexNum; k++)
        if(strcmp(G->vexs[k].cityName, v) == 0) { //第k个结点中的城市名与传过来的城市名相同
            j = k;  /*记录位置*/
            break;
        }
    return j;
}


/*
  用city，plan，train三个文档创建城市交通系统
*/
void createGraph(ALGraph *G) {
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
            if(q->adjvex == j) { //弧q中的邻接顶点与j相等
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


/*
  保存城市交通系统到相应的文档
*/
int save(ALGraph *G) {
    /*城市操作*/
    int i, j, k, t;
    ArcNode *q;
    FILE *fp;
    j = 0;
    while(j < G->vexNum) {
        strcpy(city[j], G->vexs[j].cityName);
        j++;
    }
    i = 0;
    if((fp = fopen("city.txt", "wb")) == NULL)
        printf("\n错误,无法打开文件!\n");
    while(i < G->vexNum) {
        fprintf(fp, "%10s", city[i]);
        i++;
    }
    fclose(fp);

    /*航班操作*/
    k = 0;
    for(i = 0; i < G->vexNum; i++) {
        q = G->vexs[i].planeFirstArc;
        while(q != NULL) {
            for(t = 0; t <= q->info.last; t++) {
                strcpy(VehicleNote[k].beginCity, G->vexs[i].cityName);
                strcpy(VehicleNote[k].arriveCity, G->vexs[q->adjvex].cityName);
                VehicleNote[k].num = q->info.stata[t].num;
                VehicleNote[k].money = q->info.stata[t].money;
                VehicleNote[k].beginTime[0] = q->info.stata[t].beginTime[0];
                VehicleNote[k].beginTime[1] = q->info.stata[t].beginTime[1];
                VehicleNote[k].arriveTime[0] = q->info.stata[t].arriveTime[0];
                VehicleNote[k].arriveTime[1] = q->info.stata[t].arriveTime[0];
                k++;
            }
            q = q->nextArc;
        }
    }
    if((fp = fopen("plane.txt", "wb")) == NULL) {
        printf("\n无法打开航班文件!\n");
        return 0;
    }
    i = 0;
    fprintf(fp, "%d", k);
    while(i < k) {
        if(fwrite(&VehicleNote[i], sizeof(struct arc), 1, fp) != 1)
            printf("\n航班文件写入错误!\n");
        i++;
    }
    fclose(fp);


    /*列车操作*/
    k = 0;
    for(i = 0; i < G->vexNum; i++) {
        q = G->vexs[i].trainFirstArc;
        while(q != NULL) {
            for(t = 0; t <= q->info.last; t++) {
                strcpy(VehicleNote[k].beginCity, G->vexs[i].cityName);
                strcpy(VehicleNote[k].arriveCity, G->vexs[q->adjvex].cityName);
                VehicleNote[k].num = q->info.stata[t].num;
                VehicleNote[k].money = q->info.stata[t].money;
                VehicleNote[k].beginTime[0] = q->info.stata[t].beginTime[0];
                VehicleNote[k].beginTime[1] = q->info.stata[t].beginTime[1];
                VehicleNote[k].arriveTime[0] = q->info.stata[t].arriveTime[0];
                VehicleNote[k].arriveTime[1] = q->info.stata[t].arriveTime[0];
                k++;
            }
            q = q->nextArc;
        }
    }
    if((fp = fopen("train.txt", "wb")) == NULL) {
        printf("\n无法打开列车文件!\n");
        return 0;
    }
    i = 0;
    fprintf(fp, "%d", k);
    while(i < k) {
        if(fwrite(&VehicleNote[i], sizeof(struct arc), 1, fp) != 1)
            printf("\n列车文件写入错误!\n");
        i++;
    }
    fclose(fp);
    return 1;
}


/*
  显示城市编辑项目选择界面
*/
void cityEdit(ALGraph *G) {
    int i;
    printf("\n请选择城市编辑项目:\n");
    printf("1=增加城市\n2=删除城市\n");
    printf("选择?");
    scanf("%d", &i);
    getchar();
    if(i == 1)
        addVex(G);
    if(i == 2)
        deleteVex(G);
}

/*
  增加城市
*/
void addVex(ALGraph *G) {
    char city[10], flag;
    int i;
    printf("\n请输入新增城市的名称:");
    gets(city);
    i = LocateVex(G, city);
    if(i >= 0 && i < G->vexNum) {
        printf("\n错误！此城市已存在\n");
        return;
    } else {
        printf("\n确认?(Y/N)");
        flag = getchar();
        getchar();
        if(flag == 'Y' || flag == 'y') {
            i = G->vexNum;
            strcpy(G->vexs[i].cityName, city);
            G->vexs[i].planeFirstArc = NULL;
            G->vexs[i].trainFirstArc = NULL;
            G->vexNum = i + 1;
            save(G);
        } else
            return;
    }
}

/*
  删除城市
*/
void deleteVex(ALGraph *G) {
    int i, j, k, n;
    char city[10], flag;
    ArcNode *p, *q, *m;
    printf("\n请输入删除的城市:"); //提示"输入删除城市名"
    gets(city);
    printf("\n确认?(Y/N)");  //提示"是否确定要删除"
    flag = getchar();
    getchar();
    if(flag == 'Y' || flag == 'y') {
        n = 0;         //0是记数标志，控制循环次数
        while(n < G->vexNum && strcmp(G->vexs[n].cityName, city) != 0) //n<图G表头接点总个数&&图G的存储城市名与v不同,G表头结点总个数比实际大1
            n++; //记数值n+1
        if(n == G->vexNum) //n==图G表头结点总个数
            printf("\n错误！无法找到此城市!\n"); //提示"无法找到此城市"
        else {
            i = LocateVex(G, city); //利用G函数找到此城市名所处在G中位置
            p = G->vexs[i].planeFirstArc;
            while(p != NULL) {
                q = p;
                p = p->nextArc;
                free(q);  //删除从此结点出发的所有航班弧
            }
            p = G->vexs[i].trainFirstArc;
            while(p != NULL) {
                q = p;
                p = p->nextArc;
                free(q);    //删除从此结点出发的所有列车弧
            }
            for(j = i; j < G->vexNum - 1; j++) {
                strcpy(G->vexs[j].cityName, G->vexs[j + 1].cityName); //将G第j个结点的信息依前移1位
                G->vexs[j].planeFirstArc = G->vexs[j + 1].planeFirstArc;
                G->vexs[j].trainFirstArc = G->vexs[j + 1].trainFirstArc;
            }
            G->vexs[j].planeFirstArc = NULL; //将G第j个结点的信息置空
            G->vexs[j].trainFirstArc = NULL;
            /*删除所有指向此结点的航班弧*/
            for(k = 0; k < G->vexNum - 1; k++) {
                p = G->vexs[k].planeFirstArc;
                while(p != NULL) {
                    if(p->adjvex > i) {
                        p->adjvex = p->adjvex - 1;
                        q = p;
                        p = p->nextArc; //p指向下一条飞机弧
                    } else if(p->adjvex == i) { //该弧指向删除的顶点位置
                        if(p == G->vexs[k].planeFirstArc) { //p指向图G中k结点的第一条飞机弧
                            m = p;
                            G->vexs[k].planeFirstArc = p->nextArc; //将图G中k结点的第二条飞机弧改为第一弧
                            p = p->nextArc; //p指向下一条飞机弧
                            free(m);  //释放（m）
                        } else {
                            q->nextArc = p->nextArc; //将p的下一条弧赋给q的下一条弧
                            m = p;
                            p = p->nextArc; //p指向下一条飞机弧
                            free(q);  //释放(q)
                        }
                    } else {
                        q = p;
                        p = p->nextArc; //p指向下一条飞机弧
                    }
                }
            }
            /*删除所有指向此结点的列车弧*/
            for(k = 0; k < G->vexNum - 1; k++) {
                p = G->vexs[k].trainFirstArc;
                while(p != NULL) {
                    if(p->adjvex > i) {
                        p->adjvex = p->adjvex - 1;
                        q = p;
                        p = p->nextArc; //p指向下一条飞机弧
                    } else if(p->adjvex == i) { //该弧指向删除的顶点位置
                        if(p == G->vexs[k].trainFirstArc) { //p指向图G中k结点的第一条飞机弧
                            m = p;
                            G->vexs[k].trainFirstArc = p->nextArc; //将图G中k结点的第二条飞机弧改为第一弧
                            p = p->nextArc; //p指向下一条飞机弧
                            free(m);  //释放（m）
                        } else {
                            q->nextArc = p->nextArc; //将p的下一条弧赋给q的下一条弧
                            m = p;
                            p = p->nextArc; //p指向下一条飞机弧
                            free(q);  //释放(q)
                        }
                    } else {
                        q = p;
                        p = p->nextArc; //p指向下一条飞机弧
                    }
                }
            }
        }
        G->vexNum--;
        save(G);
    } else
        return;
}

/*
  飞机航班编辑项目选择界面
*/
void planeEdit(ALGraph *G) {
    int i;
    printf("\n请选择飞机航班编辑项目:\n");
    printf("1=新增航班\n2=删除航班\n");
    printf("选择?");
    scanf("%d", &i);
    getchar();
    if(i == 1)
        addPlaneArc(G);
    if(i == 2)
        deletePlaneArc(G);
}
/*
  列车车次编辑项目选择界面
*/
void trainEdit(ALGraph *G) {
    int i;
    printf("\n请选择列车车次编辑项目:\n");
    printf("1=新增车次\n2=删除车次\n");
    printf("选择?");
    scanf("%d", &i);
    getchar();
    if(i == 1)
        addTrainArc(G);
    if(i == 2)
        deleteTrainArc(G);
}


/*
  增加飞机航班
*/
void addPlaneArc(ALGraph *G) {
    int num, beginTime[2], arriveTime[2]; //num航班编号，beginTime出发时间，arriveTime到达时间
    float money;  //费用
    int i, j, m, t;
    int k; //用来记录航班的车次
    char beginCity[10], arriveCity[10], flag; //beginCity起始城市，arriveCity目标城市
    ArcNode *p, *q;
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
    printf("/n确认?(Y/N)");
    flag = getchar();
    getchar();
    if(flag == 'Y' || flag == 'y') {
        i = LocateVex(G, beginCity);
        j = LocateVex(G, arriveCity);
        if(i == -1) {
            printf("\n错误！无法找到起始城市\n");
            return;
        }
        if(j == -1) {
            printf("\n错误！无法找到到达城市\n");
            return;
        }
        q = G->vexs[i].planeFirstArc;
        m = 0;
        while(q != NULL) {
            if(q->adjvex == j) { //弧 q中的邻接顶点与j相等
                t = q->info.last + 1; // 将数组VehicleNode中的内容都复制到弧q中
                q->info.stata[t].num = num;
                q->info.stata[t].money = money;
                q->info.stata[t].beginTime[0] = beginTime[0];
                q->info.stata[t].beginTime[1] = beginTime[1];
                q->info.stata[t].arriveTime[0] = arriveTime[0];
                q->info.stata[t].arriveTime[1] = arriveTime[1];
                q->info.last = t;
                m = 1;
                break;
            }
            q = q->nextArc;
        }
        if(m == 0) {
            p = (ArcNode*)malloc(sizeof(ArcNode)); //开辟一个弧结点
            p->adjvex = j; //将数组VehicleNode中的内容都复制到新的弧结点中
            p->info.stata[0].num = num;
            p->info.stata[0].money = money;
            p->info.stata[0].beginTime[0] = beginTime[0];
            p->info.stata[0].beginTime[1] = beginTime[1];
            p->info.stata[0].arriveTime[0] = arriveTime[0];
            p->info.stata[0].arriveTime[1] = arriveTime[1];
            p->info.last = 0;
            p->nextArc = G->vexs[i].planeFirstArc;
            G->vexs[i].planeFirstArc = p; // 将弧结点连接到适当的位置中去
            G->planeArcNum++;
        }
        save(G);
    } else
        return;
}

/*
  增加列车车次
*/
void addTrainArc(ALGraph *G) {
    int num, beginTime[2], arriveTime[2]; //num航班编号，beginTime出发时间，arriveTime到达时间
    float money;  //费用
    int i, j, m, t;
    int k; //用来记录航班的车次
    char beginCity[10], arriveCity[10], flag; //beginCity起始城市，arriveCity目标城市
    ArcNode *p, *q;


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
    printf("/n确认?(Y/N)");
    flag = getchar();
    getchar();

    if(flag == 'Y' || flag == 'y') {
        i = LocateVex(G, beginCity);
        j = LocateVex(G, arriveCity);
        if(i == -1) {
            printf("\n错误！无法找到起始城市\n");
            return;
        }
        if(j == -1) {
            printf("\n错误！无法找到到达城市\n");
            return;
        }
        q = G->vexs[i].trainFirstArc;
        m = 0;
        while(q != NULL) {
            if(q->adjvex == j) { //弧 q中的邻接顶点与j相等
                t = q->info.last + 1; // 将数组VehicleNode中的内容都复制到弧q中
                q->info.stata[t].num = num;
                q->info.stata[t].money = money;
                q->info.stata[t].beginTime[0] = beginTime[0];
                q->info.stata[t].beginTime[1] = beginTime[1];
                q->info.stata[t].arriveTime[0] = arriveTime[0];
                q->info.stata[t].arriveTime[1] = arriveTime[1];
                q->info.last = t;
                m = 1;
                break;
            }
            q = q->nextArc;
        }
        if(m == 0) {
            p = (ArcNode*)malloc(sizeof(ArcNode)); //开辟一个弧结点
            p->adjvex = j; //将数组VehicleNode中的内容都复制到新的弧结点中
            p->info.stata[0].num = num;
            p->info.stata[0].money = money;
            p->info.stata[0].beginTime[0] = beginTime[0];
            p->info.stata[0].beginTime[1] = beginTime[1];
            p->info.stata[0].arriveTime[0] = arriveTime[0];
            p->info.stata[0].arriveTime[1] = arriveTime[1];
            p->info.last = 0;
            p->nextArc = G->vexs[i].trainFirstArc;
            G->vexs[i].trainFirstArc = p; // 将弧结点连接到适当的位置中去
            G->trainArcNum++;
        }
        save(G);
    } else
        return;
}

int deletePlaneArc(ALGraph *G)
/*
  删除飞机航班
*/
{
    int i, j;
    int num;
    char beginCity[10], arriveCity[10], flag;
    int n;
    int k;
    ArcNode *p, *q;
    printf("\n请输入删除飞机航班的信息:\n");
    printf("飞机航班的编号:");
    scanf("%d", &num);
    getchar();
    printf("起始城市:");
    gets(beginCity);
    printf("目的城市:");
    gets(arriveCity);

    printf("\n确认?(Y/N)");
    flag = getchar();
    getchar();

    if(flag == 'Y' || flag == 'y') {
        i = LocateVex(G, beginCity);
        j = LocateVex(G, arriveCity);
        if(i == -1) {
            printf("\n错误！无法找到起始城市\n");
            return 0;
        }
        if(j == -1) {
            printf("\n错误！无法找到目的城市\n");
            return 0;
        }
        p = G->vexs[i].planeFirstArc;
        q = p;
        while(p != NULL) {
            if(p->adjvex == j) {
                n = -1;
                for(k = 0; k <= p->info.last; k++) {
                    if(p->info.stata[k].num == num) {
                        n = k;
                        break;
                    }
                }
                if(n != -1)
                    if(p->info.last == 0) {
                        if(q == p)
                            G->vexs[i].planeFirstArc = p->nextArc;
                        else
                            q->nextArc = p->nextArc;
                        free(p);
                    } else {
                        for(k = n; k < p->info.last; k++) {
                            p->info.stata[k].num = p->info.stata[k + 1].num;
                            p->info.stata[k].money = p->info.stata[k + 1].money;
                            p->info.stata[k].beginTime[0] = p->info.stata[k + 1].beginTime[0];
                            p->info.stata[k].beginTime[1] = p->info.stata[k + 1].beginTime[1];
                            p->info.stata[k].arriveTime[0] = p->info.stata[k + 1].arriveTime[0];
                            p->info.stata[k].arriveTime[1] = p->info.stata[k + 1].arriveTime[1];
                        }
                        p->info.last = p->info.last - 1;
                    }
                else
                    printf("\n在此两城市之间无法找到No.%d飞机航班\n", num);
                save(G);
                return 1;
            }
            q = p;
            p = p->nextArc;
        }
        if(p == NULL)
            printf("\n在此两城市之间无飞机航班存在\n");
    } else
        return 1;
    return 0;
}
int deleteTrainArc(ALGraph *G)
/*
  删除列车车次
*/
{
    int i, j;
    int num;
    char beginCity[10], arriveCity[10], flag;
    int n;
    int k;
    ArcNode *p, *q;
    printf("\n请输入删除列车车次的信息:\n");
    printf("列车车次的编号:");
    scanf("%d", &num);
    getchar();
    printf("起始城市:");
    gets(beginCity);
    printf("目的城市:");
    gets(arriveCity);
    printf("\n确认?(Y/N)");
    flag = getchar();
    getchar();
    if(flag == 'Y' || flag == 'y') {
        i = LocateVex(G, beginCity);
        j = LocateVex(G, arriveCity);
        if(i == -1) {
            printf("\n错误！无法找到起始城市\n");
            return 0;
        }
        if(j == -1) {
            printf("\n错误！无法找到目的城市\n");
            return 0;
        }
        p = G->vexs[i].trainFirstArc;
        q = p;
        while(p != NULL) {
            if(p->adjvex == j) {
                n = -1;
                for(k = 0; k <= p->info.last; k++) {
                    if(p->info.stata[k].num == num) {
                        n = k;
                        break;
                    }
                }
                if(n != -1)
                    if(p->info.last == 0) {
                        if(q == p)
                            G->vexs[i].trainFirstArc = p->nextArc;
                        else
                            q->nextArc = p->nextArc;
                        free(p);
                    } else {
                        for(k = n; k < p->info.last; k++) {
                            p->info.stata[k].num = p->info.stata[k + 1].num;
                            p->info.stata[k].money = p->info.stata[k + 1].money;
                            p->info.stata[k].beginTime[0] = p->info.stata[k + 1].beginTime[0];
                            p->info.stata[k].beginTime[1] = p->info.stata[k + 1].beginTime[1];
                            p->info.stata[k].arriveTime[0] = p->info.stata[k + 1].arriveTime[0];
                            p->info.stata[k].arriveTime[1] = p->info.stata[k + 1].arriveTime[1];
                        }
                        p->info.last = p->info.last - 1;
                    }
                else
                    printf("\n在此两城市之间无法找到No.%d列车车次\n", num);
                save(G);
                return 1;
            }
            q = p;
            p = p->nextArc;
        }
        if(p == NULL)
            printf("\n在此两城市之间无该列车车次存在\n");
    } else
        return 1;
    return 0;
}
