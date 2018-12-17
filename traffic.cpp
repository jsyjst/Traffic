#include "traffic.h"
/*��ͨ������Ϣ��¼��*/
struct arc {
    int num;   //���
    float money; //����
    char beginCity[10];  //������
    char arriveCity[10]; //Ŀ�ĵ�
    int beginTime[2];   //����ʱ��
    int arriveTime[2];  //����ʱ��
}VehicleNote[MAX_ARC_SIZE];
char city[MAX_VERTEX_NUM][10];
int TTime[2];
int time[2];
int time1[2];
int time2[2];
int c[MAX_VERTEX_NUM];
int d[MAX_VERTEX_NUM];

void initGraph(ALGraph *G)     //��ʼ����ͨϵͳ
/*
  ��ʼ����ͨϵͳ��ʽѡ�����
*/
{
    int i;
    printf("��ѡ���ʼ����ʽ:\n");
    printf("1=����\n2=�ĵ�\n");
    printf("ѡ��?");
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
void createCityFile()
/*
  �������������ĵ�
*/
{
    int i = 0;
    int j;
    char flag = 'y';
    FILE *fpWrite;
    printf("\n������������Ƶ���Ϣ:\n");
    while(flag == 'y' || flag == 'Y') {
        printf("��������:");
        gets(city[i]);
        i++;
        printf("��������?(Y/N)");
        scanf("%c", &flag);
        getchar();
    }
    printf("\n");
    /*��������д���ļ�*/
    if((fpWrite = fopen("city.txt", "wb")) == NULL) {//wb��ʾ���������Ƹ�ʽ���ļ�
        printf("�޷��򿪳����ļ�!/n");
        return;
    }
    for(j = 0; j < i; j++)
        fprintf(fpWrite, "%10s", city[j]);
    fclose(fpWrite);
}
void createPlaneFile()
/*
  �����ɻ������ĵ�
*/
{
    int num, beginTime[2], arriveTime[2]; //num�����ţ�beginTime����ʱ�䣬arriveTime����ʱ��
    float money;  //����
    int i;
    int k; //������¼����ĳ���
    char beginCity[10], arriveCity[10], flag; //beginCity��ʼ���У�arriveCityĿ�����
    FILE *fp;
    flag = 'y';
    k = 0;
    while(flag == 'Y' || flag == 'y') { /*flagΪ��־λ,��ֵΪ1*/
        printf("������ɻ��������Ϣ:\n"); //��ʾ"���뺽����Ϣ"
        printf("�ɻ�������:");  //���뺽��num
        scanf("%d", &num);
        getchar();
        printf("��ʼ����:");   //���뺽��ĳ�������beginCity
        gets(beginCity);
        printf("Ŀ�ĳ���:");  //���뺽��ĵ������arriveCity
        gets(arriveCity);
        printf("�������:");  //�����Ʊ�۸�money
        scanf("%f", &money);
        getchar();
        printf("���ʱ��:");  //���뺽��ĳ���ʱ��beginTime
        scanf("%d:%d", &beginTime[0], &beginTime[1]);
        getchar();
        while(beginTime[0] < 0 || beginTime[0] >= 24 || beginTime[1] < 0 || beginTime[1] >= 60) {
            printf("\nʱ��������������������\n");
            scanf("%d:%d", &beginTime[0], &beginTime[1]);
            getchar();
        }
        printf("����ʱ��:");  //���뺽��ĵ���ʱ��arriveTime
        scanf("%d:%d", &arriveTime[0], &arriveTime[1]);
        getchar();
        while(arriveTime[0] < 0 || arriveTime[0] >= 24 || arriveTime[1] < 0 || arriveTime[1] >= 60) {
            printf("\nʱ��������������������\n");
            scanf("%d:%d", &arriveTime[0], &arriveTime[1]);
            getchar();
        }
        /*VehicleNoteΪ����ͷ������Ľṹ��,�洢��ͨ���ߵ���Ϣ*/
        VehicleNote[k].num = num; //���
        VehicleNote[k].money = money; //����
        strcpy(VehicleNote[k].beginCity, beginCity); //������
        strcpy(VehicleNote[k].arriveCity, arriveCity); //Ŀ�ĵ�
        /*����ʱ��*/
        VehicleNote[k].arriveTime[0] = arriveTime[0];
        VehicleNote[k].arriveTime[1] = arriveTime[1];
        /*��ʼʱ��*/
        VehicleNote[k].beginTime[0] = beginTime[0];
        VehicleNote[k].beginTime[1] = beginTime[1];
        k++;  //�洢��һ���ߵ���Ϣ
        printf("��������?(Y/N)");  //��ʾ"�Ƿ�Ҫ�������뺽����Ϣ��"
        scanf("%c", &flag);
        getchar();
        printf("\n");
    }
    /*��������Ϣ����ṹ�����飬Ȼ�󽫽ṹ������д�������ļ�*/
    if((fp = fopen("plane.txt", "wb")) == NULL) //�����ļ������Զ�д��ʽ��
        printf("\n�޷��򿪺����ļ�!\n");  //��ʾ"�޷����ļ�"
    fprintf(fp, "%d", k);  //������ֵkд�뺽�೵�ļ�
    for(i = 0; i < k; i++)
        if(fwrite(&VehicleNote[i], sizeof(struct arc), 1, fp) != 1) //�޷���a[i]д�뺽���ļ�
            printf("\n�ļ�д�����!\n");  //��ʾ"�ļ��޷�д��"
    fclose(fp);    //�رպ����ļ�
}

void createTrainFile()
/*
  �����г������ĵ�
*/
{
    int num, beginTime[2], arriveTime[2]; //num�����ţ�beginTime����ʱ�䣬arriveTime����ʱ��
    float money;  //����
    int i;
    int k; //������¼����ĳ���
    char beginCity[10], arriveCity[10], flag; //beginCity��ʼ���У�arriveCityĿ�����
    FILE *fp;
    flag = 'y';
    k = 0;
    while(flag == 'Y' || flag == 'y') { /*flagΪ��־λ,��ֵΪ1*/
        printf("�������г����ε���Ϣ:\n"); //��ʾ"�����г���Ϣ"
        printf("�г����α��:");  //�����г�����num
        scanf("%d", &num);
        getchar();
        printf("��ʼ����:");   //�����г��ĳ�������beginCity
        gets(beginCity);
        printf("Ŀ�ĳ���:");  //�����г��ĵ������arriveCity
        gets(arriveCity);
        printf("���η���:");  //���복Ʊmoney
        scanf("%f", &money);
        getchar();
        printf("����ʱ��:");  //�����г��ĳ���ʱ��beginTime
        scanf("%d:%d", &beginTime[0], &beginTime[1]);
        getchar();
        while(beginTime[0] < 0 || beginTime[0] >= 24 || beginTime[1] < 0 || beginTime[1] >= 60) {
            printf("\nʱ��������������������\n");
            scanf("%d:%d", &beginTime[0], &beginTime[1]);
            getchar();
        }
        printf("����ʱ��:");  //���뺽��ĵ���ʱ��arrvieTime
        scanf("%d:%d", &arriveTime[0], &arriveTime[1]);
        getchar();
        while(arriveTime[0] < 0 || arriveTime[0] >= 24 || arriveTime[1] < 0 || arriveTime[1] >= 60) {
            printf("\nʱ��������������������\n");
            scanf("%d:%d", &arriveTime[0], &arriveTime[1]);
            getchar();
        }
        /*VehicleNoteΪ����ͷ������Ľṹ��,�洢��ͨ���ߵ���Ϣ*/
        VehicleNote[k].num = num; //���
        VehicleNote[k].money = money; //����
        strcpy(VehicleNote[k].beginCity, beginCity); //������
        strcpy(VehicleNote[k].arriveCity, arriveCity); //Ŀ�ĵ�
        /*����ʱ��*/
        VehicleNote[k].arriveTime[0] = arriveTime[0];
        VehicleNote[k].arriveTime[1] = arriveTime[1];
        /*��ʼʱ��*/
        VehicleNote[k].beginTime[0] = beginTime[0];
        VehicleNote[k].beginTime[1] = beginTime[1];
        k++;  //�洢��һ���ߵ���Ϣ
        printf("��������?(Y/N)");  //��ʾ"�Ƿ�Ҫ�������뺽����Ϣ��"
        scanf("%c", &flag);
        getchar();
        printf("\n");
    }
    /*��������Ϣ����ṹ�����飬Ȼ�󽫽ṹ������д�������ļ�*/
    if((fp = fopen("train.txt", "wb")) == NULL) //�����ļ������Զ�д��ʽ��
        printf("\n�޷����г��ļ�!\n");  //��ʾ"�޷����ļ�"
    fprintf(fp, "%d", k);  //������ֵkд�뺽�೵�ļ�
    for(i = 0; i < k; i++)
        if(fwrite(&VehicleNote[i], sizeof(struct arc), 1, fp) != 1) //�޷���a[i]д�뺽���ļ�
            printf("\n�ļ�д�����!\n");  //��ʾ"�ļ��޷�д��"
    fclose(fp);    //�رպ����ļ�
}


int LocateVex(ALGraph *G, char *v)
/*
  �������ڽ�ͨϵͳ�ж�λ�������ҳ���������ͼ�ж�Ӧ���λ��
*/
{
    int j, k;
    j = -1;
    for(k = 0; k < G->vexNum; k++)
        if(strcmp(G->vexs[k].cityName, v) == 0) { //��k������еĳ������봫�����ĳ�������ͬ
            j = k;  /*��¼λ��*/
            break;
        }
    return j;
}

void createGraph(ALGraph *G)
/*
  ��city��plan��train�����ĵ��������н�ͨϵͳ
*/
{
    int i, j, k;
    int arcNum;  //��������
    int count1, count2;  //�ɻ����г��İ��
    int m, t;
    ArcNode *p, *q;
    FILE *fp;
    i = 0;
    if((fp = fopen("city.txt", "rb")) == NULL) { //�򿪳����ļ����ļ�ָ�뷵��ֵΪ��
        printf("\n�޷��򿪳����ļ�!\n");
        return;
    }
    while(!feof(fp)) { //�ļ���Ϊ��
        fscanf(fp, "%10s", city[i]);
        i++;
    }
    fclose(fp);  //�ر��ļ�
    j = 0;
    while(j < i) {
        strcpy(G->vexs[j].cityName, city[j]); //�� city[i] �е����ݸ��Ƶ�ͼ�Ľṹ��Ľ��������;
        G->vexs[j].planeFirstArc = NULL; // ͼ�Ľṹ���������ֵ;
        G->vexs[j].trainFirstArc = NULL;
        j++;
    }
    G->vexNum = i;

    /*�Ժ����ļ����в���*/
    if((fp = fopen("plane.txt", "rb")) == NULL)
        printf("\n�޷��򿪺����ļ�!\n");
    k = 0;
    fscanf(fp, "%d", &count1); //�򿪺�����Ϣ�ļ�"plane.txt"
    while(k < count1) {
        /*��ȡ�ṹ��*/
        if(fread(&VehicleNote[k], sizeof(struct arc), 1, fp) != 1)
            printf("\n�ļ��������!\n");
        k++;
    }
    fclose(fp);  //�ر��ļ�
    k = 0;       //VehicleNode�ļ�������k=0
    arcNum = 0; //���ļ�������
    while(k < count1) {
        i = LocateVex(G, VehicleNote[k].beginCity); //���ú����õ���ʼ����λ�� i
        j = LocateVex(G, VehicleNote[k].arriveCity); //���ú����õ�ĩ�˽���λ�� j
        q = G->vexs[i].planeFirstArc;
        m = 0;
        while(q != NULL) {
            if(q->adjvex == j) { //�� q�е��ڽӶ�����j���
                t = q->info.last + 1; // ������VehicleNode�е����ݶ����Ƶ���q��
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
            p = (ArcNode*)malloc(sizeof(ArcNode)); //����һ�������
            p->adjvex = j; //������VehicleNode�е����ݶ����Ƶ��µĻ������
            p->info.stata[0].num = VehicleNote[k].num;
            p->info.stata[0].money = VehicleNote[k].money;
            p->info.stata[0].beginTime[0] = VehicleNote[k].beginTime[0];
            p->info.stata[0].beginTime[1] = VehicleNote[k].beginTime[1];
            p->info.stata[0].arriveTime[0] = VehicleNote[k].arriveTime[0];
            p->info.stata[0].arriveTime[1] = VehicleNote[k].arriveTime[1];
            p->info.last = 0;
            p->nextArc = G->vexs[i].planeFirstArc;
            G->vexs[i].planeFirstArc = p; // ����������ӵ��ʵ���λ����ȥ
            arcNum++;
        }
        k++;
    }
    G->planeArcNum = arcNum;
    if((fp = fopen("train.txt", "rb")) == NULL) {
        printf("\n�޷����г��ļ�!\n");
        return;
    }
    k = 0;
    fscanf(fp, "%d", &count2); //���г���Ϣ�ļ�"plane.txt"
    while(k < count2) {
        if(fread(&VehicleNote[k], sizeof(struct arc), 1, fp) != 1)
            printf("\n�ļ��������!\n");
        k++;
    }
    fclose(fp);  //�ر��ļ�
    k = 0;       //VehicleNode�ļ�������k=0
    arcNum = 0; //���ļ�������
    while(k < count2) {
        i = LocateVex(G, VehicleNote[k].beginCity); //���ú����õ���ʼ����λ�� i
        j = LocateVex(G, VehicleNote[k].arriveCity); //���ú����õ�ĩ�˽���λ�� j
        q = G->vexs[i].trainFirstArc;
        m = 0;
        while(q != NULL) {
            if(q->adjvex == j) { //�� q�е��ڽӶ�����j���
                t = q->info.last + 1; // ������VehicleNode�е����ݶ����Ƶ���q��
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
            p = (ArcNode*)malloc(sizeof(ArcNode)); //����һ�������
            p->adjvex = j; //������VehicleNode�е����ݶ����Ƶ��µĻ������
            p->info.stata[0].num = VehicleNote[k].num;
            p->info.stata[0].money = VehicleNote[k].money;
            p->info.stata[0].beginTime[0] = VehicleNote[k].beginTime[0];
            p->info.stata[0].beginTime[1] = VehicleNote[k].beginTime[1];
            p->info.stata[0].arriveTime[0] = VehicleNote[k].arriveTime[0];
            p->info.stata[0].arriveTime[1] = VehicleNote[k].arriveTime[1];
            p->info.last = 0;
            p->nextArc = G->vexs[i].trainFirstArc;
            G->vexs[i].trainFirstArc = p; // ����������ӵ��ʵ���λ����ȥ
            arcNum++;
        }
        k++;
    }
    G->trainArcNum = arcNum;
}
