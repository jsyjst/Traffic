#include "traffic.h"
int TTime[2];
int time[2];
int time1[2];
int time2[2];
int c[MAX_VERTEX_NUM];
int d[MAX_VERTEX_NUM];
/*
  用户咨询项目选择界面
*/
void userAsk(ALGraph G) {
    int i;
    printf("\n                           咨询项目\n");
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
        printf("\n                           咨询项目\n");
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
void askDispose(int n, ALGraph G) {
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
        else if(k == 1 && n == 2)
            timeDispose(1, trainArcs, G, i, j, T, final); //时间
        else if(k == 1 && n == 3)
            transferDispose(1, trainArcs, G, i, j); //中转次数
        else if(k == 2 && n == 1)
            moneyDispose(2, planeArcs, G, i, j, M, final);
        else if(k == 2 && n == 2)
            timeDispose(2, planeArcs, G, i, j, T, final);
        else if(k == 2 && n == 3)
            transferDispose(2, planeArcs, G, i, j);
    } else if(q == 'N' || q == 'n')
        userAsk(G);
    else {
        printf("\n选择错误\n\n");
        askDispose(n, G);
    }
    return ;
}


/*
  初始化队列,链队列：队列的链式表示
*/
void initQueue(LinkQueue *Q)

{
    Q->front = (QNode *)malloc(sizeof(QNode));
    Q->rear = Q->front;
    Q->front->next = NULL;
}
/*
  入队操作，插入元素x为Q的新的队列元素
*/
void EnQueue(LinkQueue *Q, int x) {
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
void DeQueue(LinkQueue *Q, int *x) {
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
int isEmpty(LinkQueue *Q) {
    if(Q->front == Q->rear)
        return 1;
    else
        return 0;
}

/*
  最少旅行中转次数处理,v0为出发地的位序，v1为目的地的位序
  k代表交通方式，1表示飞机，2表示列车
  v0为出发地的位序，v1为到达地的位序
*/
void transferDispose(int k, infoList (*arcs)[MAX_VERTEX_NUM], ALGraph G, int v0, int v1) {

    int visited[MAX_VERTEX_NUM], v, w, n = 1;//visited[]数组用来判断顶点是否已经访问，从而减少循环次数
    LinkQueue Q;   //链队列
    ArcNode *t;    //用来指向邻接表的顶点
    Node *p, *q, *r, *s;
    p = (Node *)malloc(G.vexNum * sizeof(Node));  //p为Node数组，主要作用是复制访问过的Node，然后得到实际路线。
    /*初始化，顶点都没被访问*/
    for(v = 0; v < G.vexNum; v++) {
        visited[v] = 0;
        p[v].next = NULL;
    }
    initQueue(&Q);  //初始化链队列
    visited[v0] = 1;  //出发地点被访问
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
                    while(r != NULL) {  //进行循环输出
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
                    return;
                    /*释放内存*/
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

                }
                EnQueue(&Q, w);   // 将城市w入队
            }
            t = t->nextArc;      //w等于城市v相连的下一个城市
        }
    }
    /*错误情况下会运行下面代码*/
    /*释放内存*/
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
void moneyDispose(int k, infoList (*arcs)[MAX_VERTEX_NUM], ALGraph G, int v0, int v1, float *M, int *final) {
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

            /*释放所占空间*/
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
    /*释放所占空间*/
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
void minTime(infoList arcs, int *time, int *route)
/*
  两直达城市之间最少旅行时间和相应路径
*/
{
    int i, t[2];
    time[0] = arcs.stata[0].arriveTime[0] - arcs.stata[0].beginTime[0];
    time[1] = arcs.stata[0].arriveTime[1] - arcs.stata[0].beginTime[1];
    if(time[0] < 0)
        time[0] = time[0] + 24;
    if(time[1] < 0) {
        time[0]--;
        time[1] = time[1] + 60;
    }
    *route = 0;
    for(i = 1; i <= arcs.last; i++) {
        t[0] = arcs.stata[i].arriveTime[0] - arcs.stata[i].beginTime[0];
        t[1] = arcs.stata[i].arriveTime[1] - arcs.stata[i].beginTime[1];
        if(t[0] < 0)
            t[0] = t[0] + 24;
        if(t[1] < 0) {
            t[0]--;
            t[1] = t[1] + 60;
        }
        if(t[0] < time[0] || (t[0] == time[0] && t[1] < time[1])) {
            time[0] = t[0];
            time[1] = t[1];
            *route = i;
        }
    }
}

void timeTreeDispose(Node *head, infoList (*arcs)[MAX_VERTEX_NUM])
/*
  时间树处理
*/
{
    int n, i, j;
    Node *p;
    LinkQueue Q;
    TimeTree root;
    root = (TimeNode *)malloc(sizeof(TimeNode));
    initQueue(&Q);
    TTime[0] = INFINITY;
    TTime[1] = INFINITY;
    p = head->next;
    while(p != NULL) {
        EnQueue(&Q, p->adjvex);
        p = p->next;
    }
    DeQueue(&Q, &i);
    root->adjvex = i;
    DeQueue(&Q, &j);
    createTimeTree(root, i, j, &Q, arcs);
    for(n = 0; n <= (*(*(arcs + i) + j)).last; n++) {
        time1[0] = 0;
        time1[1] = 0;
        time2[0] = root->child[n]->beginTime[0];
        time2[1] = root->child[n]->beginTime[1];
        time[0] = INFINITY;
        time[1] = INFINITY;
        visitTimeTree(root->child[n]);
        if(time[0] < TTime[0] || (time[0] == TTime[0] && time[1] < TTime[1])) {
            TTime[0] = time[0];
            TTime[1] = time[1];
            p = head->next;
            while(p != NULL) {
                p->route = d[p->adjvex];
                p = p->next;
            }
        }
    }
    destoryTimeTree(root);
}
void createTimeTree(TimeTree p, int i, int j, LinkQueue *Q, infoList (*arcs)[MAX_VERTEX_NUM])
/*
  创建时间树
*/
{
    int n, x, y;
    TimeTree q;
    q = (TimeNode *)malloc(sizeof(TimeNode));
    q->adjvex = j;
    q->beginTime[0] = (*(*(arcs + i) + j)).stata[0].beginTime[0];
    q->beginTime[1] = (*(*(arcs + i) + j)).stata[0].beginTime[1];
    q->arriveTime[0] = (*(*(arcs + i) + j)).stata[0].arriveTime[0];
    q->arriveTime[1] = (*(*(arcs + i) + j)).stata[0].arriveTime[1];
    q->route = 0;
    p->child[0] = q;
    for(n = 1; n <= (*(*(arcs + i) + j)).last; n++) {
        q = (TimeNode *)malloc(sizeof(TimeNode));
        q->adjvex = j;
        q->beginTime[0] = (*(*(arcs + i) + j)).stata[n].beginTime[0];
        q->beginTime[1] = (*(*(arcs + i) + j)).stata[n].beginTime[1];
        q->arriveTime[0] = (*(*(arcs + i) + j)).stata[n].arriveTime[0];
        q->arriveTime[1] = (*(*(arcs + i) + j)).stata[n].arriveTime[1];
        q->route = n;
        p->child[n] = q;
    }
    while(n < MAX_ROUTE_NUM) {
        p->child[n] = NULL;
        n++;
    }
    x = j;
    if(!isEmpty(Q)) {
        DeQueue(Q, &y);
        createTimeTree(p->child[0], x, y, Q, arcs);
        for(n = 1; n <= (*(*(arcs + i) + j)).last; n++)
            copyTimeTree(p->child[n], p->child[0]);
    } else {
        for(n = 0; n < MAX_ROUTE_NUM; n++)
            p->child[0]->child[n] = NULL;
        for(n = 1; n <= (*(*(arcs + i) + j)).last; n++)
            copyTimeTree(p->child[n], p->child[0]);
    }
    return ;
}
void copyTimeTree(TimeTree p, TimeTree q)
/*
  复制时间树
*/
{
    TimeTree r;
    int n = 0;
    while(q->child[n] != NULL) {
        r = (TimeNode *)malloc(sizeof(TimeNode));
        r->adjvex = q->child[n]->adjvex;
        r->beginTime[0] = q->child[n]->beginTime[0];
        r->beginTime[1] = q->child[n]->beginTime[1];
        r->arriveTime[0] = q->child[n]->arriveTime[0];
        r->arriveTime[1] = q->child[n]->arriveTime[1];
        r->route = q->child[n]->route;
        p->child[n] = r;
        copyTimeTree(p->child[n], q->child[n]);
        n++;
    }
    while(n < MAX_ROUTE_NUM) {
        p->child[n] = NULL;
        n++;
    }
    return ;
}
void visitTimeTree(TimeTree p)
/*
  访问时间树界面
*/
{
    int n, x[2], y[2];
    x[0] = time1[0];
    x[1] = time1[1];
    y[0] = time2[0];
    y[1] = time2[1];
    if(p->beginTime[0] > time2[0] || (p->beginTime[0] == time2[0] && p->beginTime[1] >= time2[1])) {
        time1[0] = time1[0] + p->beginTime[0] - time2[0];
        time1[1] = time1[1] + p->beginTime[1] - time2[1];
        if(time1[1] < 0) {
            time1[1] = time1[1] + 60;
            time1[0]--;
        }
        if(time1[1] >= 60) {
            time1[1] = time1[1] - 60;
            time1[0]++;
        }
    } else if(p->beginTime[0] < time2[0] || (p->beginTime[0] == time2[0] && p->beginTime[1] < time2[1])) {
        time1[0] = time1[0] + p->beginTime[0] - time2[0] + 24;
        time1[1] = time1[1] + p->beginTime[1] - time2[1];
        if(time1[1] < 0) {
            time1[1] = time1[1] + 60;
            time1[0]--;
        }
        if(time1[1] >= 60) {
            time1[1] = time1[1] - 60;
            time1[0]++;
        }
    }
    if(p->arriveTime[0] > p->beginTime[0] || (p->arriveTime[0] == p->beginTime[0] && p->arriveTime[1] >= p->beginTime[1])) {
        time1[0] = time1[0] + p->arriveTime[0] - p->beginTime[0];
        time1[1] = time1[1] + p->arriveTime[1] - p->beginTime[1];
        if(time1[1] < 0) {
            time1[1] = time1[1] + 60;
            time1[0]--;
        }
        if(time1[1] >= 60) {
            time1[1] = time1[1] - 60;
            time1[0]++;
        }
    } else if(p->arriveTime[0] < p->beginTime[0] || (p->arriveTime[0] == p->beginTime[0] && p->arriveTime[1] < p->beginTime[1])) {
        time1[0] = time1[0] + p->arriveTime[0] - p->beginTime[0] + 24;
        time1[1] = time1[1] + p->arriveTime[1] - p->beginTime[1];
        if(time1[1] < 0) {
            time1[1] = time1[1] + 60;
            time1[0]--;
        }
        if(time1[1] >= 60) {
            time1[1] = time1[1] - 60;
            time1[0]++;
        }
    }
    time2[0] = p->arriveTime[0];
    time2[1] = p->arriveTime[1];
    c[p->adjvex] = p->route;
    if(p->child[0] == NULL) {
        if(time1[0] < time[0] || (time1[0] == time[0] && time1[1] < time[1])) {
            time[0] = time1[0];
            time[1] = time1[1];
            for(n = 0; n < MAX_VERTEX_NUM; n++)
                d[n] = c[n];
        }
    } else {
        n = 0;
        while(p->child[n] != NULL) {
            visitTimeTree(p->child[n]);
            n++;
        }
    }
    time1[0] = x[0];
    time1[1] = x[1];
    time2[0] = y[0];
    time2[1] = y[1];
}
void destoryTimeTree(TimeTree p)
/*
  销毁时间树
*/
{
    if(p != NULL) {
        destoryTimeTree(p->child[0]);
        destoryTimeTree(p->child[1]);
        destoryTimeTree(p->child[2]);
        destoryTimeTree(p->child[3]);
        destoryTimeTree(p->child[4]);
        p->child[0] = NULL;
        p->child[1] = NULL;
        p->child[2] = NULL;
        p->child[3] = NULL;
        p->child[4] = NULL;
        free(p);
    }
    return ;
}

void timeDispose(int k, infoList (*arcs)[MAX_VERTEX_NUM], ALGraph G, int v0, int v1, int (*T)[2], int *final)
/*
  最少旅行时间处理
*/
{
    int v, w, i, route, m[2];
    Node *p, *q, *r, *s, *t;
    p = (Node *)malloc(G.vexNum * sizeof(Node));
    for(v = 0; v < G.vexNum; v++) {
        *(final + v) = False; //城市v还未求得最少时间
        minTime(*(*(arcs + v0) + v), *(T + v), &route); //*(D+v)=城市v0到v的最少时间
        p[v].next = NULL;  //将城市v的路径设置为空
        if(*(*(T + v) + 0) < INFINITY && *(*(T + v) + 1) < INFINITY) {
            q = (Node *)malloc(sizeof(Node));
            s = (Node *)malloc(sizeof(Node));
            q->adjvex = v0;
            s->adjvex = v;
            s->route = route;
            p[v].next = q;
            q->next = s;
            s->next = NULL;
        }
    }
    *(*(T + v0) + 0) = 0; // 城市v0到城市v0的最少时间为0
    *(*(T + v0) + 1) = 0;
    *(final + v0) = True; //城市v0设为已求得最少时间
    for(i = 1; i < G.vexNum; i++) {
        m[0] = INFINITY;
        m[1] = INFINITY;
        v = -1;
        for(w = 0; w < G.vexNum; w++)
            if(*(final + w) == False) //城市w未求得最少时间
                if(*(*(T + w) + 0) < m[0] || (*(*(T + w) + 0) == m[0] && *(*(T + w) + 1) < m[1])) {
                    v = w;
                    m[0] = *(*(T + w) + 0);
                    m[1] = *(*(T + w) + 1);
                }
        if(v == v1) {
            q = p[v].next;
            r = q->next;
            printf("\n旅行路线是:\n");
            while(r != NULL) {
                if(k == 1)
                    printf("乘坐No.%d列车车次在%d:%d从%s到%s\n", (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].num,
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
            printf("最少旅行时间是%d:%d\n\n", m[0], m[1]);
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
            return ;
        } else if(v != -1) {
            *(final + v) = True;
            for(w = 0; w < G.vexNum; w++)
                if(*(final + w) == False && (*(*(arcs + v) + w)).last > -1) {
                    t = p[w].next;
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
                    timeTreeDispose(&p[w], arcs);
                    if(*(*(T + w) + 0) > TTime[0] || (*(*(T + w) + 0) == TTime[0] && *(*(T + w) + 1) > TTime[1])) {
                        *(*(T + w) + 0) = TTime[0];
                        *(*(T + w) + 1) = TTime[1];
                        while(t != NULL) {
                            q = t;
                            t = t->next;
                            free(q);
                        }
                    } else {
                        q = p[w].next;
                        while(q != NULL) {
                            r = q;
                            q = q->next;
                            free(r);
                        }
                        p[w].next = t;
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
