#ifndef TRAFFIC_H_INCLUDED
#define TRAFFIC_H_INCLUDED
#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#define MAX_VERTEX_NUM 20
#define NULL 0
#define MAX_ARC_SIZE 50
#define MAX_ROUTE_NUM 5
#define False 0
#define True 1
#define INFINITY 10000
/****----------------图相关结构体-----------------****/


/*交通工具*/
typedef struct {
    int num;  //班次
    float money;  //费用
    int beginTime[2]; //出发时间
    int arriveTime[2]; //到达时间
} Vehicle; //交通工具信息
typedef struct {
    Vehicle route[MAX_ROUTE_NUM];  //存储同个目的地和出发地的多个航班
    int last;  //同个出发地和目的地的数量
} infoList;
/*邻接链表的结点类型*/
typedef struct ArcNode {
    int adjvex;     //顶点位序
    struct ArcNode *nextArc;
    infoList info;     //存储
} ArcNode;  //邻接链表的结点类型

/*顶点数组的类型*/
typedef struct VNode {
    char cityName[10]; //城市名
    ArcNode *planeFirstArc, *trainFirstArc; //邻接链表的头指针
} VNode, AdjList[MAX_VERTEX_NUM]; //顶点数组的类型
/*邻接表的类型*/
typedef struct {
    AdjList vexs;  //顶点数组，用于存储顶点信息
    int vexNum, planeArcNum, trainArcNum; //顶点数和边数
} ALGraph;   //邻接表类型


/****----------------链队列的结构体-----------------****/

typedef struct Node {
    int adjvex;
    int route;//同个直达城市的不同班次
    struct Node *next;
} Node;
typedef struct QNode {
    int adjvex;
    struct QNode *next;
} QNode;  //结点类型
typedef struct {
    QNode *front;  //队头指针
    QNode *rear;   //队尾指针
} LinkQueue;   //链队列


/**----------------用来记录时间的结构体--------------**/
typedef struct TimeNode {
    int adjvex;
    int route;    //同个直达城市的不同班次
    int beginTime[2];
    int arriveTime[2];
    struct TimeNode *child[MAX_ROUTE_NUM];
} TimeNode, *TimeTree;



/**----------------管理员系统----------------------------**/
void manager(ALGraph *G); //显示管理员管理项目选择界面

/*初始化交通系统*/
void initGraph(ALGraph *G);
void createCityFile(); //创建城市文件
void createPlaneFile(); // 创建航班文件
void createTrainFile(); //创建列车文件
void createGraph(ALGraph *G); //创建交通系统文件

int save(ALGraph *G);//保存交通系统图
/*城市编辑*/
void cityEdit(ALGraph *G);
void addVex(ALGraph *G);   //添加城市
void deleteVex(ALGraph *G) ;  //删除城市
/*航班编辑*/
void planeEdit(ALGraph *G);
void addPlaneArc(ALGraph *G);  //添加航班班次
int deletePlaneArc(ALGraph *G);  //删除航班班次
/*列车编辑*/
void trainEdit(ALGraph *G);
void addTrainArc(ALGraph *G); // 添加列车班次
int deleteTrainArc(ALGraph *G); //删除列车班次

/**----------------交通查询系统----------------**/
void showGraph(ALGraph *G);
void showTraffic(ALGraph *G); //显示交通总览
void planeDedailByNum(ALGraph *G); //通过航班查询该航班的详细信息
void trainDedailByNum(ALGraph *G);  //通过列车车次查询该车次的详细信息

/**----------------用户咨询------------------------------------**/
void userAsk(ALGraph G);
void askDispose(int n, ALGraph G);    //选择询问类型
void transferDispose(int k, infoList (*arcs)[MAX_VERTEX_NUM], ALGraph G, int v0, int v1);   //中转站最优策略
void minMoney(infoList arcs, float *money, int *route);   //直达城市花费最优
void moneyDispose(int k, infoList (*arcs)[MAX_VERTEX_NUM], ALGraph G, int v0, int v1, float *M, int *final);  //花费最优策略
void minTime(infoList arcs, int *time, int *route);  //直达城市所用时间最优
void createTimeTree(TimeTree p, int i, int j, LinkQueue *Q, infoList (*arcs)[MAX_VERTEX_NUM]);  //创建时间树
void copyTimeTree(TimeTree p, TimeTree q); //复制时间树
void visitTimeTree(TimeTree p);   //访问时间树
void destoryTimeTree(TimeTree p);  //销毁时间树
void timeDispose(int k, infoList (*arcs)[MAX_VERTEX_NUM], ALGraph G, int v0, int v1, int (*T)[2], int *final); //时间最优策略



#endif // TRAFFIC_H_INCLUDED
