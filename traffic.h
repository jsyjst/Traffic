#ifndef TRAFFIC_H_INCLUDED
#define TRAFFIC_H_INCLUDED
#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#define MAX_VERTEX_NUM 18
#define NULL 0
#define MAX_ARC_SIZE 100
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
    Vehicle stata[MAX_ROUTE_NUM];  //�洢ͬ��Ŀ�ĵغͳ����صĶ������
    int last;  //���һ������
} infoList;
/*�ڽ�����Ľ������*/
typedef struct ArcNode {
    int adjvex;
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
    int route;
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


/**----------------������¼�Ľṹ��--------------**/
typedef struct TimeNode {
    int adjvex;
    int route;
    int begintime[2];
    int arrivetime[2];
    struct TimeNode *child[MAX_ROUTE_NUM];
} TimeNode, *TimeTree;



/**----------------����Ա----------------------------**/
void Administer(ALGraph *G); //��ʾ����Ա������Ŀѡ�����

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




#endif // TRAFFIC_H_INCLUDED
