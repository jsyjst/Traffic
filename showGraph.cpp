#include "traffic.h"


void showGraph(ALGraph *G)
/*
  ��ʾ���н�ͨϵͳ
*/
{
    int i, j, k;
    ArcNode *q;
    printf("\n                         ���н�ͨ��ѯϵͳ\n");
    printf("\n            |            1.��ͨ����           |\n");
    printf("\n            |            2.���в�ѯ           |\n");
    printf("\n            |            3.�ɻ������ѯ       |\n");
    printf("\n            |            4.�г����β�ѯ       |\n");
    printf("\n            |            5.������һ��         |\n");
    printf("\nѡ��?");
    scanf("%d", &i);
    getchar();
    while(i != 5) {
        switch(i) {
        case 1:
            showTraffic(G);
            break;
        case 2:
            printf("\n����:");
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
        printf("\n                         ���н�ͨ��ѯϵͳ\n");
        printf("\n            |            1.��ͨ����           |\n");
        printf("\n            |            2.���в�ѯ           |\n");
        printf("\n            |            3.�ɻ������ѯ       |\n");
        printf("\n            |            4.�г����β�ѯ       |\n");
        printf("\n            |            5.������һ��         |\n");
        printf("\nѡ��?");
        scanf("%d", &i);
        getchar();
    }
}
/*
    ��ͨ����
*/
void showTraffic(ALGraph *G) {
    int i, j, k;
    ArcNode *q;
    printf("\n****************************************�ɻ�ʱ�̱�*************************************************\n");
    printf("\n---------------------------------------------------------------------------------------------------\n");
    printf("   ����          ���ʱ��          ����ʱ��          ����վ          �յ�վ            ����");
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
    printf("\n****************************************�г�ʱ�̱�*************************************************\n");
    printf("\n---------------------------------------------------------------------------------------------------\n");
    printf("   ����          ����ʱ��          ����ʱ��          ����վ          �յ�վ            ����");
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
/*���ݺ��������ϸ*/
void planeDedailByNum(ALGraph *G) {
    int num;
    int i, j, k;
    ArcNode *q;
    printf("\n����ɻ����ࣺ");
    scanf("%d", &num);
    getchar();

    for(j = 0; j < G->vexNum; j++) {
        q = G->vexs[j].planeFirstArc;
        while(q != NULL) {
            for(k = 0; k <= q->info.last; k++) {
                if(q->info.stata[k].num == num) {
                    printf("                        %.2fԪ             \n", q->info.stata[k].money);
                    printf("              %s------------------>%s        ", G->vexs[j].cityName, G->vexs[q->adjvex].cityName);
                    printf("ʱ��:%d:%2d----%2d:%2d", q->info.stata[k].beginTime[0], q->info.stata[k].beginTime[1],
                           q->info.stata[k].arriveTime[0], q->info.stata[k].arriveTime[1]);
                    printf("\n");
                    return;
                }
            }
            q = q->nextArc;
        }
    }
    printf("\n��Ǹ���Ҳ����ú������Ϣ��\n");
    return;

}
/*���ݳ��β�����ϸ*/
void trainDedailByNum(ALGraph *G) {
    int num;
    int i, j, k;
    ArcNode *q;
    printf("\n�����г����Σ�");
    scanf("%d", &num);
    getchar();

    for(j = 0; j < G->vexNum; j++) {
        q = G->vexs[j].trainFirstArc;
        while(q != NULL) {
            for(k = 0; k <= q->info.last; k++) {
                if(q->info.stata[k].num == num) {
                    printf("                        %.2fԪ             \n", q->info.stata[k].money);
                    printf("              %s------------------>%s        ", G->vexs[j].cityName, G->vexs[q->adjvex].cityName);
                    printf("ʱ��:%d:%2d----%2d:%2d", q->info.stata[k].beginTime[0], q->info.stata[k].beginTime[1],
                           q->info.stata[k].arriveTime[0], q->info.stata[k].arriveTime[1]);
                    printf("\n");
                    return;
                }
            }
            q = q->nextArc;
        }
    }
    printf("\n��Ǹ���Ҳ����ó��ε���Ϣ��\n");
    return;

}
