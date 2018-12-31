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
/****----------------ͼ��ؽṹ��-----------------****/


/*��ͨ����*/
typedef struct {
    int num;  //���
    float money;  //����
    int beginTime[2]; //����ʱ��
    int arriveTime[2]; //����ʱ��
} Vehicle; //��ͨ������Ϣ
typedef struct {
    Vehicle route[MAX_ROUTE_NUM];  //�洢ͬ��Ŀ�ĵغͳ����صĶ������
    int last;  //ͬ�������غ�Ŀ�ĵص�����
} infoList;
/*�ڽ�����Ľ������*/
typedef struct ArcNode {
    int adjvex;     //����λ��
    struct ArcNode *nextArc;
    infoList info;     //�洢
} ArcNode;  //�ڽ�����Ľ������

/*�������������*/
typedef struct VNode {
    char cityName[10]; //������
    ArcNode *planeFirstArc, *trainFirstArc; //�ڽ������ͷָ��
} VNode, AdjList[MAX_VERTEX_NUM]; //�������������
/*�ڽӱ������*/
typedef struct {
    AdjList vexs;  //�������飬���ڴ洢������Ϣ
    int vexNum, planeArcNum, trainArcNum; //�������ͱ���
} ALGraph;   //�ڽӱ�����


/****----------------�����еĽṹ��-----------------****/

typedef struct Node {
    int adjvex;
    int route;//ͬ��ֱ����еĲ�ͬ���
    struct Node *next;
} Node;
typedef struct QNode {
    int adjvex;
    struct QNode *next;
} QNode;  //�������
typedef struct {
    QNode *front;  //��ͷָ��
    QNode *rear;   //��βָ��
} LinkQueue;   //������


/**----------------������¼ʱ��Ľṹ��--------------**/
typedef struct TimeNode {
    int adjvex;
    int route;    //ͬ��ֱ����еĲ�ͬ���
    int beginTime[2];
    int arriveTime[2];
    struct TimeNode *child[MAX_ROUTE_NUM];
} TimeNode, *TimeTree;



/**----------------����Աϵͳ----------------------------**/
void manager(ALGraph *G); //��ʾ����Ա������Ŀѡ�����

/*��ʼ����ͨϵͳ*/
void initGraph(ALGraph *G);
void createCityFile(); //���������ļ�
void createPlaneFile(); // ���������ļ�
void createTrainFile(); //�����г��ļ�
void createGraph(ALGraph *G); //������ͨϵͳ�ļ�

int save(ALGraph *G);//���潻ͨϵͳͼ
/*���б༭*/
void cityEdit(ALGraph *G);
void addVex(ALGraph *G);   //��ӳ���
void deleteVex(ALGraph *G) ;  //ɾ������
/*����༭*/
void planeEdit(ALGraph *G);
void addPlaneArc(ALGraph *G);  //��Ӻ�����
int deletePlaneArc(ALGraph *G);  //ɾ��������
/*�г��༭*/
void trainEdit(ALGraph *G);
void addTrainArc(ALGraph *G); // ����г����
int deleteTrainArc(ALGraph *G); //ɾ���г����

/**----------------��ͨ��ѯϵͳ----------------**/
void showGraph(ALGraph *G);
void showTraffic(ALGraph *G); //��ʾ��ͨ����
void planeDedailByNum(ALGraph *G); //ͨ�������ѯ�ú������ϸ��Ϣ
void trainDedailByNum(ALGraph *G);  //ͨ���г����β�ѯ�ó��ε���ϸ��Ϣ

/**----------------�û���ѯ------------------------------------**/
void userAsk(ALGraph G);
void askDispose(int n, ALGraph G);    //ѡ��ѯ������
void transferDispose(int k, infoList (*arcs)[MAX_VERTEX_NUM], ALGraph G, int v0, int v1);   //��תվ���Ų���
void minMoney(infoList arcs, float *money, int *route);   //ֱ����л�������
void moneyDispose(int k, infoList (*arcs)[MAX_VERTEX_NUM], ALGraph G, int v0, int v1, float *M, int *final);  //�������Ų���
void minTime(infoList arcs, int *time, int *route);  //ֱ���������ʱ������
void createTimeTree(TimeTree p, int i, int j, LinkQueue *Q, infoList (*arcs)[MAX_VERTEX_NUM]);  //����ʱ����
void copyTimeTree(TimeTree p, TimeTree q); //����ʱ����
void visitTimeTree(TimeTree p);   //����ʱ����
void destoryTimeTree(TimeTree p);  //����ʱ����
void timeDispose(int k, infoList (*arcs)[MAX_VERTEX_NUM], ALGraph G, int v0, int v1, int (*T)[2], int *final); //ʱ�����Ų���



#endif // TRAFFIC_H_INCLUDED
