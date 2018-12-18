#include "traffic.h"

/*
  用户咨询项目选择界面
*/
void userAsk(ALGraph G) {
    int i;
    char q;
    printf("\n                         咨询项目:\n");
    printf("\n            |            1.最少旅行费用           |\n");
    printf("\n            |            2.最少旅行时间           |\n");
    printf("\n            |            3.最少旅行中转次数       |\n");
    printf("\n            |            4.返回上一级菜单         |\n");
    printf("\n选择?");
    scanf("%d", &i);
    getchar();
    while(i != 4) {
        switch(i) {
        case 1:
            askDispose(1, G);  //费用
            break;   /*最少费用，时间，中转 ,次数*/
        case 2:
            askDispose(2, G); //时间
            break;
        case 3:
            askDispose(3, G); //中转
            break;
        }
        printf("\n                         咨询项目:\n");
        printf("\n            |            1.最少旅行费用           |\n");
        printf("\n            |            2.最少旅行时间           |\n");
        printf("\n            |            3.最少旅行中转次数       |\n");
        printf("\n            |            4.返回上一级菜单         |\n");
        printf("\n选择?");
        scanf("%d", &i);
        getchar();
    }
    return ;
}

/*咨询处理*/
void askDispose(int n, ALGraph G)
{
    char q;
    ArcNode *plane, *train;
    infoList planeArcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM], trainArcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int i, j, k, final[MAX_VERTEX_NUM], T[MAX_VERTEX_NUM][2];
    float M[MAX_VERTEX_NUM];

    /*初始化*/
    for(i = 0; i < G.vexNum; i++)
        for(j = 0; j < G.vexNum; j++)
            for(k = 0; k < MAX_ROUTE_NUM; k++) {
                planeArcs[i][j].stata[k].money = INFINITY;
                planeArcs[i][j].stata[k].beginTime[0] = 0;
                planeArcs[i][j].stata[k].beginTime[1] = 0;
                planeArcs[i][j].stata[k].arriveTime[0] = INFINITY;
                planeArcs[i][j].stata[k].arriveTime[1] = INFINITY;
                planeArcs[i][j].last = -1;
                trainArcs[i][j].stata[k].money = INFINITY;
                trainArcs[i][j].stata[k].beginTime[0] = 0;
                trainArcs[i][j].stata[k].beginTime[1] = 0;
                trainArcs[i][j].stata[k].arriveTime[0] = INFINITY;
                trainArcs[i][j].stata[k].arriveTime[1] = INFINITY;
                trainArcs[i][j].last = -1;
            }
    for(i = 0; i < G.vexNum; i++) {
        plane = G.vexs[i].planeFirstArc;
        train = G.vexs[i].trainFirstArc;
        while(plane != NULL) {
            planeArcs[i][plane->adjvex] = plane->info;
            plane = plane->nextArc;
        }
        while(train != NULL) {
            trainArcs[i][train->adjvex] = train->info;
            train = train->nextArc;
        }
    }
    printf("\n请选择旅行起始城市:\n");
    for(k = 0; k < G.vexNum; k++)
        printf("%d.%s\n", k, G.vexs[k].cityName);
    printf("选择?");
    scanf("%d", &i);
    printf("\n请选择旅行到达城市:\n");
    for(k = 0; k < G.vexNum; k++)
        printf("%d.%s\n", k, G.vexs[k].cityName);
    printf("选择?");
    scanf("%d", &j);
    printf("\n请选择交通工具:\n");
    printf("1.列车\n2.飞机\n");
    printf("选择?");
    scanf("%d", &k);
    printf("\n确认? (Y/N)");
    scanf("%c", &q);
    scanf("%c", &q);
    if(q == 'Y' || q == 'y') {
        if(k == 1 && n == 1)
            moneyDispose(1, trainArcs, G, i, j, M, final); //费用
      //  else if(k == 1 && n == 2)
            //TimeDispose(1, trainArcs, G, i, j, T, final); //时间
        else if(k == 1 && n == 3)
            transferDispose(1, trainArcs, G, i, j); //中转次数
        else if(k == 2 && n == 1)
            moneyDispose(2, planeArcs, G, i, j, M, final);
        //else if(k == 2 && n == 2)
            //TimeDispose(2, planeArcs, G, i, j, T, final);
        else if(k == 2 && n == 3)
            transferDispose(2, planeArcs, G, i, j);
    } else if(q == 'N' || q == 'n')
        userAsk(G);
    else {
        printf("\n选择错误\n\n");
        askDispose(k, G);
    }
    return ;
}


/*
  初始化队列,链队列：队列的链式表示，见教材P62
*/
void initQueue(LinkQueue *Q)

{
    Q->front = (QNode *)malloc(sizeof(QNode));
    Q->rear = Q->front;
    Q->front->next = NULL;
}
/*
  入队操作，插入元素x为Q的新的队列元素，见教材P62
*/
void EnQueue(LinkQueue *Q, int x)
{
    QNode *newnode;
    newnode = (QNode *)malloc(sizeof(QNode));
    newnode->adjvex = x;
    newnode->next = NULL;
    Q->rear->next = newnode;
    Q->rear = newnode;
}

/*
  出队操作
*/
void DeQueue(LinkQueue *Q, int *x)
{
    QNode *p;
    p = Q->front->next;
    Q->front->next = p->next;
    if(Q->rear == p)
        Q->rear = Q->front;
    *x = p->adjvex;
    free(p);
}
/*
  队列判空操作
*/
int isEmpty(LinkQueue *Q)
{
    if(Q->front == Q->rear)
        return 1;
    else
        return 0;
}

/*
  最少旅行中转次数处理,v0为出发地的位序，v1为目的地的位序
*/
void transferDispose(int k, infoList (*arcs)[MAX_VERTEX_NUM], ALGraph G, int v0, int v1)
{
    int visited[MAX_VERTEX_NUM], v, w, n = 1;
    LinkQueue Q;
    ArcNode *t;
    Node *p, *q, *r, *s;
    p = (Node *)malloc(G.vexNum * sizeof(Node));
    for(v = 0; v < G.vexNum; v++) {
        visited[v] = 0;
        p[v].next = NULL;
    }
    initQueue(&Q);
    visited[v0] = 1;
    q = (Node *)malloc(sizeof(Node));
    q->adjvex = v0;
    q->next = NULL;
    p[v0].next = q;
    EnQueue(&Q, v0);
    while(!isEmpty(&Q)) {    //队列不空
        DeQueue(&Q, &v);
        if(k == 1)
            t = G.vexs[v].trainFirstArc;
        else
            t = G.vexs[v].planeFirstArc;
        while(t != NULL) {
            w = t->adjvex; //w为与城市v相连的第一个城市
            if(!visited[w]) { //城市w未访问
                visited[w] = 1; //将城市w设为已访问
                q = &p[w];
                s = p[v].next;
                while(s != NULL) {
                    r = (Node *)malloc(sizeof(Node));
                    r->adjvex = s->adjvex;
                    q->next = r;
                    q = r;
                    s = s->next;
                }
                r = (Node *)malloc(sizeof(Node));
                r->adjvex = w;
                r->next = NULL;
                q->next = r;
                if(w == v1) {  //w等于v1
                    q = p[w].next;
                    r = q->next;
                    printf("\n旅行路线是:\n");
                    while(r != NULL) {
                        if(k == 1)
                            printf("乘坐No.%d列车车次在%d:%d从%s到%s\n",
                                   (*(*(arcs + q->adjvex) + r->adjvex)).stata[0].num, (*(*(arcs + q->adjvex) + r->adjvex)).stata[0].beginTime[0],
                                    (*(*(arcs + q->adjvex) + r->adjvex)).stata[0].beginTime[1], G.vexs[q->adjvex].cityName, G.vexs[r->adjvex].cityName);
                        else
                            printf("乘坐No.%d飞机航班在%d:%d从%s到%s\n",
                                   (*(*(arcs + q->adjvex) + r->adjvex)).stata[0].num,
                                   (*(*(arcs + q->adjvex) + r->adjvex)).stata[0].beginTime[0],
                                   (*(*(arcs + q->adjvex) + r->adjvex)).stata[0].beginTime[1],
                                   G.vexs[q->adjvex].cityName,
                                   G.vexs[r->adjvex].cityName);
                        q = r;
                        r = r->next;
                        n++;
                    }
                    printf("最少中转次数是%d次\n\n", n - 2);
                    for(v = 0; v < G.vexNum; v++) {
                        q = p[v].next;
                        while(q != NULL) {
                            s = q;
                            q = q->next;
                            free(s);
                        }
                        p[v].next = NULL;
                    }
                    free(p);
                    return;
                }
                EnQueue(&Q, w);   // 将城市w入队
            }
            t = t->nextArc;      //w等于城市v相连的下一个城市
        }
    }
    for(v = 0; v < G.vexNum; v++) {
        q = p[v].next;
        while(q != NULL) {
            s = q;
            q = q->next;
            free(s);
        }
        p[v].next = NULL;
    }
    free(p);
    if(k == 1)
        printf("\n不存在列车车次从%s到%s\n\n", G.vexs[v0].cityName, G.vexs[v1].cityName);
    else
        printf("\n不存在飞机航班从%s到%s\n\n", G.vexs[v0].cityName, G.vexs[v1].cityName);
}
void minMoney(infoList arcs, float *money, int *route)
/*
  两直达城市之间最少旅行费用和相应路径
*/
{
    int i;
    *money = arcs.stata[0].money;
    if(*money < INFINITY)
        *route = 0;
    else
        *route = -1;
    for(i = 1; i <= arcs.last; i++)
        if(arcs.stata[i].money < *money) {
            *money = arcs.stata[i].money;
            *route = i;
        }
}
/*
  最少旅行费用处理
*/
void moneyDispose(int k, infoList (*arcs)[MAX_VERTEX_NUM], ALGraph G, int v0, int v1, float *M, int *final)
{
    int v = -1, w, i, route;
    float m, money;
    Node *p, *q, *r, *s;
    p = (Node *)malloc(G.vexNum * sizeof(Node));
    for(v = 0; v < G.vexNum; v++) {
        *(final + v) = False; //城市v还未求得最少费用
        minMoney(*(*(arcs + v0) + v), M + v, &route); // *(D+v)=城市v0到v的最少费用；
        p[v].next = NULL;   //将城市v的路径设置为空
        if(*(M + v) < INFINITY) {
            q = (Node *)malloc(sizeof(Node)); //将城市v0和v加入到城市v的路径中
            s = (Node *)malloc(sizeof(Node));
            q->adjvex = v0;
            s->adjvex = v;
            s->route = route;
            p[v].next = q;
            q->next = s;
            s->next = NULL;
        }
    }
    *(M + v0) = 0;    // 城市v0到城市v0的最少费用为0
    *(final + v0) = True; //城市v0设为已求得最少费用
    for(i = 1; i < G.vexNum; i++) {
        m = INFINITY;
        v = -1;
        for(w = 0; w < G.vexNum; w++)
            if(*(final + w) == False) //城市w未求得最少费用
                if(*(M + w) < m) {
                    v = w;
                    m = *(M + w);
                }
        if(v == v1) {      //v等于v1
            q = p[v].next;
            r = q->next;
            printf("\n旅行路线是:\n");
            while(r != NULL) {
                if(k == 1)
                    printf("乘坐No.%d列车车次在%d:%d从%s到%s\n",
                           (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].num,
                           (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].beginTime[0],
                           (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].beginTime[1],
                            G.vexs[q->adjvex].cityName, G.vexs[r->adjvex].cityName);
                else
                    printf("乘坐No.%d飞机航班在%d:%d从%s到%s\n",
                           (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].num,
                            (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].beginTime[0],
                            (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].beginTime[1],
                           G.vexs[q->adjvex].cityName, G.vexs[r->adjvex].cityName);
                q = r;
                r = r->next;
            }
            printf("最少旅行费用是%.2f元\n\n", m);
            for(v = 0; v < G.vexNum; v++) {
                q = p[v].next;
                while(q != NULL) {
                    s = q;
                    q = q->next;
                    free(s);
                }
                p[v].next = NULL;
            }
            free(p);
            return;
        } else if(v != -1) {
            *(final + v) = True; //将城市v设为已求得最少费用
            for(w = 0; w < G.vexNum; w++)
                if(*(final + w) == False && (*(*(arcs + v) + w)).last > -1) {
                    minMoney(*(*(arcs + v) + w), &money, &route);
                    if(*(M + w) > m + money) {
                        *(M + w) = m + money;
                        q = p[w].next;
                        while(q != NULL) {
                            s = q;
                            q = q->next;
                            free(s);
                        }
                        q = &p[w];
                        s = p[v].next;
                        while(s != NULL) {
                            r = (Node *)malloc(sizeof(Node));
                            r->adjvex = s->adjvex;
                            r->route = s->route;
                            q->next = r;
                            q = r;
                            s = s->next;
                        }
                        r = (Node *)malloc(sizeof(Node));
                        r->adjvex = w;
                        r->route = route;
                        r->next = NULL;
                        q->next = r;
                    }
                }
        }
    }
    for(v = 0; v < G.vexNum; v++) {
        q = p[v].next;
        while(q != NULL) {
            s = q;
            q = q->next;
            free(s);
        }
        p[v].next = NULL;
    }
    free(p);
    if(k == 1)
        printf("\n不存在列车车次从%s到%s\n\n", G.vexs[v0].cityName, G.vexs[v1].cityName);
    else
        printf("\n不存在飞机航班从%s到%s\n\n", G.vexs[v0].cityName, G.vexs[v1].cityName);
}

