#include "traffic.h"


void showGraph(ALGraph *G)
/*
  显示城市交通系统
*/
{
    int i, j, k;
    ArcNode *q;
    printf("\n                         城市交通查询系统\n");
    printf("\n            |            1.交通总览           |\n");
    printf("\n            |            2.城市查询           |\n");
    printf("\n            |            3.飞机航班查询       |\n");
    printf("\n            |            4.列车车次查询       |\n");
    printf("\n            |            5.返回上一级         |\n");
    printf("\n选择?");
    scanf("%d", &i);
    getchar();
    while(i != 5) {
        switch(i) {
        case 1:
            showTraffic(G);
            break;
        case 2:
            printf("\n城市:");
            for(j = 0; j < G->vexNum; j++)
                printf("%s  ", G->vexs[j].cityName);
            printf("\n");
            break;
        case 3:
            planeDedailByNum(G);
            break;
        case 4:
            trainDedailByNum(G);
            break;
        }
        printf("\n                         城市交通查询系统\n");
        printf("\n            |            1.交通总览           |\n");
        printf("\n            |            2.城市查询           |\n");
        printf("\n            |            3.飞机航班查询       |\n");
        printf("\n            |            4.列车车次查询       |\n");
        printf("\n            |            5.返回上一级         |\n");
        printf("\n选择?");
        scanf("%d", &i);
        getchar();
    }
}
/*
    交通总览
*/
void showTraffic(ALGraph *G) {
    int i, j, k;
    ArcNode *q;
    printf("\n****************************************飞机时刻表*************************************************\n");
    printf("\n---------------------------------------------------------------------------------------------------\n");
    printf("   航班          起飞时间          到达时间          出发站          终点站            费用");
    printf("\n---------------------------------------------------------------------------------------------------\n");
    for(j = 0; j < G->vexNum; j++) {
        q = G->vexs[j].planeFirstArc;
        while(q != NULL) {
            for(k = 0; k <= q->info.last; k++) {
                printf("   %d            %2d:%2d             %2d:%2d             %4s            %4s            %.2f",
                       q->info.stata[k].num, q->info.stata[k].beginTime[0], q->info.stata[k].beginTime[1],
                       q->info.stata[k].arriveTime[0], q->info.stata[k].arriveTime[1],
                       G->vexs[j].cityName, G->vexs[q->adjvex].cityName, q->info.stata[k].money);
                printf("\n");
            }
            q = q->nextArc;
        }
    }
    printf("\n***************************************************************************************************\n");
    printf("\n****************************************列车时刻表*************************************************\n");
    printf("\n---------------------------------------------------------------------------------------------------\n");
    printf("   航班          发车时间          到达时间          出发站          终点站            费用");
    printf("\n---------------------------------------------------------------------------------------------------\n");
    for(j = 0; j < G->vexNum; j++) {
        q = G->vexs[j].trainFirstArc;
        while(q != NULL) {
            for(k = 0; k <= q->info.last; k++) {
                printf("   %d           %2d:%2d             %2d:%2d             %4s            %4s            %.2f",
                       q->info.stata[k].num, q->info.stata[k].beginTime[0], q->info.stata[k].beginTime[1],
                       q->info.stata[k].arriveTime[0], q->info.stata[k].arriveTime[1],
                       G->vexs[j].cityName, G->vexs[q->adjvex].cityName, q->info.stata[k].money);
                printf("\n");
            }
            q = q->nextArc;
        }
    }
    printf("\n***************************************************************************************************\n");
}
/*根据航班查找详细*/
void planeDedailByNum(ALGraph *G) {
    int num;
    int i, j, k;
    ArcNode *q;
    printf("\n输入飞机航班：");
    scanf("%d", &num);
    getchar();

    for(j = 0; j < G->vexNum; j++) {
        q = G->vexs[j].planeFirstArc;
        while(q != NULL) {
            for(k = 0; k <= q->info.last; k++) {
                if(q->info.stata[k].num == num) {
                    printf("                        %.2f元             \n", q->info.stata[k].money);
                    printf("              %s------------------>%s        ", G->vexs[j].cityName, G->vexs[q->adjvex].cityName);
                    printf("时间:%d:%2d----%2d:%2d", q->info.stata[k].beginTime[0], q->info.stata[k].beginTime[1],
                           q->info.stata[k].arriveTime[0], q->info.stata[k].arriveTime[1]);
                    printf("\n");
                    return;
                }
            }
            q = q->nextArc;
        }
    }
    printf("\n抱歉！找不到该航班的信息！\n");
    return;

}
/*根据车次查找详细*/
void trainDedailByNum(ALGraph *G) {
    int num;
    int i, j, k;
    ArcNode *q;
    printf("\n输入列车车次：");
    scanf("%d", &num);
    getchar();

    for(j = 0; j < G->vexNum; j++) {
        q = G->vexs[j].trainFirstArc;
        while(q != NULL) {
            for(k = 0; k <= q->info.last; k++) {
                if(q->info.stata[k].num == num) {
                    printf("                        %.2f元             \n", q->info.stata[k].money);
                    printf("              %s------------------>%s        ", G->vexs[j].cityName, G->vexs[q->adjvex].cityName);
                    printf("时间:%d:%2d----%2d:%2d", q->info.stata[k].beginTime[0], q->info.stata[k].beginTime[1],
                           q->info.stata[k].arriveTime[0], q->info.stata[k].arriveTime[1]);
                    printf("\n");
                    return;
                }
            }
            q = q->nextArc;
        }
    }
    printf("\n抱歉！找不到该车次的信息！\n");
    return;

}
