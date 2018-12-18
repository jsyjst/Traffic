#include "traffic.h"

/*
  �û���ѯ��Ŀѡ�����
*/
void userAsk(ALGraph G) {
    int i;
    char q;
    printf("\n                         ��ѯ��Ŀ:\n");
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
        printf("\n                         ��ѯ��Ŀ:\n");
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
void askDispose(int n, ALGraph G)
{
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
      //  else if(k == 1 && n == 2)
            //TimeDispose(1, trainArcs, G, i, j, T, final); //ʱ��
        else if(k == 1 && n == 3)
            transferDispose(1, trainArcs, G, i, j); //��ת����
        else if(k == 2 && n == 1)
            moneyDispose(2, planeArcs, G, i, j, M, final);
        //else if(k == 2 && n == 2)
            //TimeDispose(2, planeArcs, G, i, j, T, final);
        else if(k == 2 && n == 3)
            transferDispose(2, planeArcs, G, i, j);
    } else if(q == 'N' || q == 'n')
        userAsk(G);
    else {
        printf("\nѡ�����\n\n");
        askDispose(k, G);
    }
    return ;
}


/*
  ��ʼ������,�����У����е���ʽ��ʾ�����̲�P62
*/
void initQueue(LinkQueue *Q)

{
    Q->front = (QNode *)malloc(sizeof(QNode));
    Q->rear = Q->front;
    Q->front->next = NULL;
}
/*
  ��Ӳ���������Ԫ��xΪQ���µĶ���Ԫ�أ����̲�P62
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
  ���Ӳ���
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
  �����пղ���
*/
int isEmpty(LinkQueue *Q)
{
    if(Q->front == Q->rear)
        return 1;
    else
        return 0;
}

/*
  ����������ת��������,v0Ϊ�����ص�λ��v1ΪĿ�ĵص�λ��
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
                    while(r != NULL) {
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
                EnQueue(&Q, w);   // ������w���
            }
            t = t->nextArc;      //w���ڳ���v��������һ������
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
void moneyDispose(int k, infoList (*arcs)[MAX_VERTEX_NUM], ALGraph G, int v0, int v1, float *M, int *final)
{
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

