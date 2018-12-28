#include "traffic.h"
int TTime[2];
int time[2];
int time1[2];
int time2[2];
int c[MAX_VERTEX_NUM];
int d[MAX_VERTEX_NUM];
/*
  �û���ѯ��Ŀѡ�����
*/
void userAsk(ALGraph G) {
    int i;
    printf("\n                           ��ѯ��Ŀ\n");
    printf("\n            |            1.�������з���           |\n");
    printf("\n            |            2.��������ʱ��           |\n");
    printf("\n            |            3.����������ת����       |\n");
    printf("\n            |            4.������һ���˵�         |\n");
    printf("\nѡ��?");
    scanf("%d", &i);
    getchar();
    while(i != 4) {
        switch(i) {
        case 1:
            askDispose(1, G);  //����
            break;   /*���ٷ��ã�ʱ�䣬��ת ,����*/
        case 2:
            askDispose(2, G); //ʱ��
            break;
        case 3:
            askDispose(3, G); //��ת
            break;
        }
        printf("\n                           ��ѯ��Ŀ\n");
        printf("\n            |            1.�������з���           |\n");
        printf("\n            |            2.��������ʱ��           |\n");
        printf("\n            |            3.����������ת����       |\n");
        printf("\n            |            4.������һ���˵�         |\n");
        printf("\nѡ��?");
        scanf("%d", &i);
        getchar();
    }
    return ;
}

/*��ѯ����*/
void askDispose(int n, ALGraph G) {
    char q;
    ArcNode *plane, *train;
    infoList planeArcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM], trainArcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int i, j, k, final[MAX_VERTEX_NUM], T[MAX_VERTEX_NUM][2];
    float M[MAX_VERTEX_NUM];

    /*��ʼ��*/
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
    printf("\n��ѡ��������ʼ����:\n");
    for(k = 0; k < G.vexNum; k++)
        printf("%d.%s\n", k, G.vexs[k].cityName);
    printf("ѡ��?");
    scanf("%d", &i);
    printf("\n��ѡ�����е������:\n");
    for(k = 0; k < G.vexNum; k++)
        printf("%d.%s\n", k, G.vexs[k].cityName);
    printf("ѡ��?");
    scanf("%d", &j);
    printf("\n��ѡ��ͨ����:\n");
    printf("1.�г�\n2.�ɻ�\n");
    printf("ѡ��?");
    scanf("%d", &k);
    printf("\nȷ��? (Y/N)");
    scanf("%c", &q);
    scanf("%c", &q);
    if(q == 'Y' || q == 'y') {
        if(k == 1 && n == 1)
            moneyDispose(1, trainArcs, G, i, j, M, final); //����
        else if(k == 1 && n == 2)
            timeDispose(1, trainArcs, G, i, j, T, final); //ʱ��
        else if(k == 1 && n == 3)
            transferDispose(1, trainArcs, G, i, j); //��ת����
        else if(k == 2 && n == 1)
            moneyDispose(2, planeArcs, G, i, j, M, final);
        else if(k == 2 && n == 2)
            timeDispose(2, planeArcs, G, i, j, T, final);
        else if(k == 2 && n == 3)
            transferDispose(2, planeArcs, G, i, j);
    } else if(q == 'N' || q == 'n')
        userAsk(G);
    else {
        printf("\nѡ�����\n\n");
        askDispose(n, G);
    }
    return ;
}


/*
  ��ʼ������,�����У����е���ʽ��ʾ
*/
void initQueue(LinkQueue *Q)

{
    Q->front = (QNode *)malloc(sizeof(QNode));
    Q->rear = Q->front;
    Q->front->next = NULL;
}
/*
  ��Ӳ���������Ԫ��xΪQ���µĶ���Ԫ��
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
  ���Ӳ���
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
  �����пղ���
*/
int isEmpty(LinkQueue *Q) {
    if(Q->front == Q->rear)
        return 1;
    else
        return 0;
}

/*
  ����������ת��������,v0Ϊ�����ص�λ��v1ΪĿ�ĵص�λ��
  k����ͨ��ʽ��1��ʾ�ɻ���2��ʾ�г�
  v0Ϊ�����ص�λ��v1Ϊ����ص�λ��
*/
void transferDispose(int k, infoList (*arcs)[MAX_VERTEX_NUM], ALGraph G, int v0, int v1) {

    int visited[MAX_VERTEX_NUM], v, w, n = 1;//visited[]���������ж϶����Ƿ��Ѿ����ʣ��Ӷ�����ѭ������
    LinkQueue Q;   //������
    ArcNode *t;    //����ָ���ڽӱ�Ķ���
    Node *p, *q, *r, *s;
    p = (Node *)malloc(G.vexNum * sizeof(Node));  //pΪNode���飬��Ҫ�����Ǹ��Ʒ��ʹ���Node��Ȼ��õ�ʵ��·�ߡ�
    /*��ʼ�������㶼û������*/
    for(v = 0; v < G.vexNum; v++) {
        visited[v] = 0;
        p[v].next = NULL;
    }
    initQueue(&Q);  //��ʼ��������
    visited[v0] = 1;  //�����ص㱻����
    q = (Node *)malloc(sizeof(Node));
    q->adjvex = v0;
    q->next = NULL;
    p[v0].next = q;
    EnQueue(&Q, v0);
    while(!isEmpty(&Q)) {    //���в���
        DeQueue(&Q, &v);
        if(k == 1)
            t = G.vexs[v].trainFirstArc;
        else
            t = G.vexs[v].planeFirstArc;
        while(t != NULL) {
            w = t->adjvex; //wΪ�����v�����ĵ�һ������
            if(!visited[w]) { //����wδ����
                visited[w] = 1; //������w��Ϊ�ѷ���
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
                if(w == v1) {  //w����v1
                    q = p[w].next;
                    r = q->next;
                    printf("\n����·����:\n");
                    while(r != NULL) {  //����ѭ�����
                        if(k == 1)
                            printf("����No.%d�г�������%d:%d��%s��%s\n",
                                   (*(*(arcs + q->adjvex) + r->adjvex)).stata[0].num, (*(*(arcs + q->adjvex) + r->adjvex)).stata[0].beginTime[0],
                                   (*(*(arcs + q->adjvex) + r->adjvex)).stata[0].beginTime[1], G.vexs[q->adjvex].cityName, G.vexs[r->adjvex].cityName);
                        else
                            printf("����No.%d�ɻ�������%d:%d��%s��%s\n",
                                   (*(*(arcs + q->adjvex) + r->adjvex)).stata[0].num,
                                   (*(*(arcs + q->adjvex) + r->adjvex)).stata[0].beginTime[0],
                                   (*(*(arcs + q->adjvex) + r->adjvex)).stata[0].beginTime[1],
                                   G.vexs[q->adjvex].cityName,
                                   G.vexs[r->adjvex].cityName);
                        q = r;
                        r = r->next;
                        n++;
                    }
                    printf("������ת������%d��\n\n", n - 2);
                    return;
                    /*�ͷ��ڴ�*/
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
                EnQueue(&Q, w);   // ������w���
            }
            t = t->nextArc;      //w���ڳ���v��������һ������
        }
    }
    /*��������»������������*/
    /*�ͷ��ڴ�*/
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
        printf("\n�������г����δ�%s��%s\n\n", G.vexs[v0].cityName, G.vexs[v1].cityName);
    else
        printf("\n�����ڷɻ������%s��%s\n\n", G.vexs[v0].cityName, G.vexs[v1].cityName);
}
void minMoney(infoList arcs, float *money, int *route)
/*
  ��ֱ�����֮���������з��ú���Ӧ·��
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
  �������з��ô���
*/
void moneyDispose(int k, infoList (*arcs)[MAX_VERTEX_NUM], ALGraph G, int v0, int v1, float *M, int *final) {
    int v = -1, w, i, route;
    float m, money;
    Node *p, *q, *r, *s;
    p = (Node *)malloc(G.vexNum * sizeof(Node));
    for(v = 0; v < G.vexNum; v++) {
        *(final + v) = False; //����v��δ������ٷ���
        minMoney(*(*(arcs + v0) + v), M + v, &route); // *(D+v)=����v0��v�����ٷ��ã�
        p[v].next = NULL;   //������v��·������Ϊ��
        if(*(M + v) < INFINITY) {
            q = (Node *)malloc(sizeof(Node)); //������v0��v���뵽����v��·����
            s = (Node *)malloc(sizeof(Node));
            q->adjvex = v0;
            s->adjvex = v;
            s->route = route;
            p[v].next = q;
            q->next = s;
            s->next = NULL;
        }
    }
    *(M + v0) = 0;    // ����v0������v0�����ٷ���Ϊ0
    *(final + v0) = True; //����v0��Ϊ��������ٷ���
    for(i = 1; i < G.vexNum; i++) {
        m = INFINITY;
        v = -1;
        for(w = 0; w < G.vexNum; w++)
            if(*(final + w) == False) //����wδ������ٷ���
                if(*(M + w) < m) {
                    v = w;
                    m = *(M + w);
                }
        if(v == v1) {      //v����v1
            q = p[v].next;
            r = q->next;
            printf("\n����·����:\n");
            while(r != NULL) {
                if(k == 1)
                    printf("����No.%d�г�������%d:%d��%s��%s\n",
                           (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].num,
                           (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].beginTime[0],
                           (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].beginTime[1],
                           G.vexs[q->adjvex].cityName, G.vexs[r->adjvex].cityName);
                else
                    printf("����No.%d�ɻ�������%d:%d��%s��%s\n",
                           (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].num,
                           (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].beginTime[0],
                           (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].beginTime[1],
                           G.vexs[q->adjvex].cityName, G.vexs[r->adjvex].cityName);
                q = r;
                r = r->next;
            }
            printf("�������з�����%.2fԪ\n\n", m);

            /*�ͷ���ռ�ռ�*/
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
            *(final + v) = True; //������v��Ϊ��������ٷ���
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
    /*�ͷ���ռ�ռ�*/
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
        printf("\n�������г����δ�%s��%s\n\n", G.vexs[v0].cityName, G.vexs[v1].cityName);
    else
        printf("\n�����ڷɻ������%s��%s\n\n", G.vexs[v0].cityName, G.vexs[v1].cityName);
}
void minTime(infoList arcs, int *time, int *route)
/*
  ��ֱ�����֮����������ʱ�����Ӧ·��
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
  ʱ��������
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
  ����ʱ����
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
  ����ʱ����
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
  ����ʱ��������
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
  ����ʱ����
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
  ��������ʱ�䴦��
*/
{
    int v, w, i, route, m[2];
    Node *p, *q, *r, *s, *t;
    p = (Node *)malloc(G.vexNum * sizeof(Node));
    for(v = 0; v < G.vexNum; v++) {
        *(final + v) = False; //����v��δ�������ʱ��
        minTime(*(*(arcs + v0) + v), *(T + v), &route); //*(D+v)=����v0��v������ʱ��
        p[v].next = NULL;  //������v��·������Ϊ��
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
    *(*(T + v0) + 0) = 0; // ����v0������v0������ʱ��Ϊ0
    *(*(T + v0) + 1) = 0;
    *(final + v0) = True; //����v0��Ϊ���������ʱ��
    for(i = 1; i < G.vexNum; i++) {
        m[0] = INFINITY;
        m[1] = INFINITY;
        v = -1;
        for(w = 0; w < G.vexNum; w++)
            if(*(final + w) == False) //����wδ�������ʱ��
                if(*(*(T + w) + 0) < m[0] || (*(*(T + w) + 0) == m[0] && *(*(T + w) + 1) < m[1])) {
                    v = w;
                    m[0] = *(*(T + w) + 0);
                    m[1] = *(*(T + w) + 1);
                }
        if(v == v1) {
            q = p[v].next;
            r = q->next;
            printf("\n����·����:\n");
            while(r != NULL) {
                if(k == 1)
                    printf("����No.%d�г�������%d:%d��%s��%s\n", (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].num,
                           (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].beginTime[0],
                           (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].beginTime[1],
                           G.vexs[q->adjvex].cityName, G.vexs[r->adjvex].cityName);
                else
                    printf("����No.%d�ɻ�������%d:%d��%s��%s\n",
                           (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].num,
                           (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].beginTime[0],
                           (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].beginTime[1],
                           G.vexs[q->adjvex].cityName, G.vexs[r->adjvex].cityName);
                q = r;
                r = r->next;
            }
            printf("��������ʱ����%d:%d\n\n", m[0], m[1]);
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
        printf("\n�������г����δ�%s��%s\n\n", G.vexs[v0].cityName, G.vexs[v1].cityName);
    else
        printf("\n�����ڷɻ������%s��%s\n\n", G.vexs[v0].cityName, G.vexs[v1].cityName);
}
