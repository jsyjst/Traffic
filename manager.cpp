#include "traffic.h"
#include "common.h"

void manager(ALGraph *G)
/*
  ��ʾ����Ա������Ŀѡ�����
*/
{
    int i;
    printf("                         ����Ա����:\n");
    printf("\n            |            1.��ʼ����ͨϵͳ           |\n");
    printf("\n            |            2.���б༭                 |\n");
    printf("\n            |            3.�ɻ�����༭             |\n");
    printf("\n            |            4.�г����α༭             |\n");
    printf("\n            |            5.������һ���˵�           |\n");
    printf("\nѡ��?");
    scanf("%d", &i);
    getchar();
    while(i != 5) {
        switch(i) {
        case 1:
            initGraph(G);    //��ʼ����ͨϵͳ
            break;
        case 2:
            cityEdit(G);     //���б༭
            break;
        case 3:
            planeEdit(G);  //����༭
            break;
        case 4:
            trainEdit(G);  //�г��༭
            break;
        }
        printf("                         ����Ա����:\n");
        printf("\n            |            1.��ʼ����ͨϵͳ           |\n");
        printf("\n            |            2.���б༭                 |\n");
        printf("\n            |            3.�ɻ�����༭             |\n");
        printf("\n            |            4.�г����α༭             |\n");
        printf("\n            |            5.������һ���˵�           |\n");
        printf("\nѡ��?");
        scanf("%d", &i);
        getchar();
    }
}

/*
 ��ʼ����ͨϵͳ��ʽѡ�����
*/
void initGraph(ALGraph *G) {   //��ʼ����ͨϵͳ
    int i;
    printf("                         ��ʼ����ʽ:\n");
    printf("\n            |            1.����           |\n");
    printf("\n            |            2.�ĵ�           |\n");
    printf("\nѡ��?");
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

/*
  �������������ĵ�
*/
void createCityFile() {
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

/*
  �����ɻ������ĵ�
*/
void createPlaneFile() {
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


/*
  �����г������ĵ�
*/
void createTrainFile() {
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


/*
  �������ڽ�ͨϵͳ�ж�λ�������ҳ���������ͼ�ж�Ӧ���λ��
*/
int LocateVex(ALGraph *G, char *v) {
    int j, k;
    j = -1;
    for(k = 0; k < G->vexNum; k++)
        if(strcmp(G->vexs[k].cityName, v) == 0) { //��k������еĳ������봫�����ĳ�������ͬ
            j = k;  /*��¼λ��*/
            break;
        }
    return j;
}


/*
  ��city��plan��train�����ĵ��������н�ͨϵͳ
*/
void createGraph(ALGraph *G) {
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
            if(q->adjvex == j) { //��q�е��ڽӶ�����j���
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


/*
  ������н�ͨϵͳ����Ӧ���ĵ�
*/
int save(ALGraph *G) {
    /*���в���*/
    int i, j, k, t;
    ArcNode *q;
    FILE *fp;
    j = 0;
    while(j < G->vexNum) {
        strcpy(city[j], G->vexs[j].cityName);
        j++;
    }
    i = 0;
    if((fp = fopen("city.txt", "wb")) == NULL)
        printf("\n����,�޷����ļ�!\n");
    while(i < G->vexNum) {
        fprintf(fp, "%10s", city[i]);
        i++;
    }
    fclose(fp);

    /*�������*/
    k = 0;
    for(i = 0; i < G->vexNum; i++) {
        q = G->vexs[i].planeFirstArc;
        while(q != NULL) {
            for(t = 0; t <= q->info.last; t++) {
                strcpy(VehicleNote[k].beginCity, G->vexs[i].cityName);
                strcpy(VehicleNote[k].arriveCity, G->vexs[q->adjvex].cityName);
                VehicleNote[k].num = q->info.stata[t].num;
                VehicleNote[k].money = q->info.stata[t].money;
                VehicleNote[k].beginTime[0] = q->info.stata[t].beginTime[0];
                VehicleNote[k].beginTime[1] = q->info.stata[t].beginTime[1];
                VehicleNote[k].arriveTime[0] = q->info.stata[t].arriveTime[0];
                VehicleNote[k].arriveTime[1] = q->info.stata[t].arriveTime[0];
                k++;
            }
            q = q->nextArc;
        }
    }
    if((fp = fopen("plane.txt", "wb")) == NULL) {
        printf("\n�޷��򿪺����ļ�!\n");
        return 0;
    }
    i = 0;
    fprintf(fp, "%d", k);
    while(i < k) {
        if(fwrite(&VehicleNote[i], sizeof(struct arc), 1, fp) != 1)
            printf("\n�����ļ�д�����!\n");
        i++;
    }
    fclose(fp);


    /*�г�����*/
    k = 0;
    for(i = 0; i < G->vexNum; i++) {
        q = G->vexs[i].trainFirstArc;
        while(q != NULL) {
            for(t = 0; t <= q->info.last; t++) {
                strcpy(VehicleNote[k].beginCity, G->vexs[i].cityName);
                strcpy(VehicleNote[k].arriveCity, G->vexs[q->adjvex].cityName);
                VehicleNote[k].num = q->info.stata[t].num;
                VehicleNote[k].money = q->info.stata[t].money;
                VehicleNote[k].beginTime[0] = q->info.stata[t].beginTime[0];
                VehicleNote[k].beginTime[1] = q->info.stata[t].beginTime[1];
                VehicleNote[k].arriveTime[0] = q->info.stata[t].arriveTime[0];
                VehicleNote[k].arriveTime[1] = q->info.stata[t].arriveTime[0];
                k++;
            }
            q = q->nextArc;
        }
    }
    if((fp = fopen("train.txt", "wb")) == NULL) {
        printf("\n�޷����г��ļ�!\n");
        return 0;
    }
    i = 0;
    fprintf(fp, "%d", k);
    while(i < k) {
        if(fwrite(&VehicleNote[i], sizeof(struct arc), 1, fp) != 1)
            printf("\n�г��ļ�д�����!\n");
        i++;
    }
    fclose(fp);
    return 1;
}


/*
  ��ʾ���б༭��Ŀѡ�����
*/
void cityEdit(ALGraph *G) {
    int i;
    printf("\n��ѡ����б༭��Ŀ:\n");
    printf("1=���ӳ���\n2=ɾ������\n");
    printf("ѡ��?");
    scanf("%d", &i);
    getchar();
    if(i == 1)
        addVex(G);
    if(i == 2)
        deleteVex(G);
}

/*
  ���ӳ���
*/
void addVex(ALGraph *G) {
    char city[10], flag;
    int i;
    printf("\n�������������е�����:");
    gets(city);
    i = LocateVex(G, city);
    if(i >= 0 && i < G->vexNum) {
        printf("\n���󣡴˳����Ѵ���\n");
        return;
    } else {
        printf("\nȷ��?(Y/N)");
        flag = getchar();
        getchar();
        if(flag == 'Y' || flag == 'y') {
            i = G->vexNum;
            strcpy(G->vexs[i].cityName, city);
            G->vexs[i].planeFirstArc = NULL;
            G->vexs[i].trainFirstArc = NULL;
            G->vexNum = i + 1;
            save(G);
        } else
            return;
    }
}

/*
  ɾ������
*/
void deleteVex(ALGraph *G) {
    int i, j, k, n;
    char city[10], flag;
    ArcNode *p, *q, *m;
    printf("\n������ɾ���ĳ���:"); //��ʾ"����ɾ��������"
    gets(city);
    printf("\nȷ��?(Y/N)");  //��ʾ"�Ƿ�ȷ��Ҫɾ��"
    flag = getchar();
    getchar();
    if(flag == 'Y' || flag == 'y') {
        n = 0;         //0�Ǽ�����־������ѭ������
        while(n < G->vexNum && strcmp(G->vexs[n].cityName, city) != 0) //n<ͼG��ͷ�ӵ��ܸ���&&ͼG�Ĵ洢��������v��ͬ,G��ͷ����ܸ�����ʵ�ʴ�1
            n++; //����ֵn+1
        if(n == G->vexNum) //n==ͼG��ͷ����ܸ���
            printf("\n�����޷��ҵ��˳���!\n"); //��ʾ"�޷��ҵ��˳���"
        else {
            i = LocateVex(G, city); //����G�����ҵ��˳�����������G��λ��
            p = G->vexs[i].planeFirstArc;
            while(p != NULL) {
                q = p;
                p = p->nextArc;
                free(q);  //ɾ���Ӵ˽����������к��໡
            }
            p = G->vexs[i].trainFirstArc;
            while(p != NULL) {
                q = p;
                p = p->nextArc;
                free(q);    //ɾ���Ӵ˽������������г���
            }
            for(j = i; j < G->vexNum - 1; j++) {
                strcpy(G->vexs[j].cityName, G->vexs[j + 1].cityName); //��G��j��������Ϣ��ǰ��1λ
                G->vexs[j].planeFirstArc = G->vexs[j + 1].planeFirstArc;
                G->vexs[j].trainFirstArc = G->vexs[j + 1].trainFirstArc;
            }
            G->vexs[j].planeFirstArc = NULL; //��G��j��������Ϣ�ÿ�
            G->vexs[j].trainFirstArc = NULL;
            /*ɾ������ָ��˽��ĺ��໡*/
            for(k = 0; k < G->vexNum - 1; k++) {
                p = G->vexs[k].planeFirstArc;
                while(p != NULL) {
                    if(p->adjvex > i) {
                        p->adjvex = p->adjvex - 1;
                        q = p;
                        p = p->nextArc; //pָ����һ���ɻ���
                    } else if(p->adjvex == i) { //�û�ָ��ɾ���Ķ���λ��
                        if(p == G->vexs[k].planeFirstArc) { //pָ��ͼG��k���ĵ�һ���ɻ���
                            m = p;
                            G->vexs[k].planeFirstArc = p->nextArc; //��ͼG��k���ĵڶ����ɻ�����Ϊ��һ��
                            p = p->nextArc; //pָ����һ���ɻ���
                            free(m);  //�ͷţ�m��
                        } else {
                            q->nextArc = p->nextArc; //��p����һ��������q����һ����
                            m = p;
                            p = p->nextArc; //pָ����һ���ɻ���
                            free(q);  //�ͷ�(q)
                        }
                    } else {
                        q = p;
                        p = p->nextArc; //pָ����һ���ɻ���
                    }
                }
            }
            /*ɾ������ָ��˽����г���*/
            for(k = 0; k < G->vexNum - 1; k++) {
                p = G->vexs[k].trainFirstArc;
                while(p != NULL) {
                    if(p->adjvex > i) {
                        p->adjvex = p->adjvex - 1;
                        q = p;
                        p = p->nextArc; //pָ����һ���ɻ���
                    } else if(p->adjvex == i) { //�û�ָ��ɾ���Ķ���λ��
                        if(p == G->vexs[k].trainFirstArc) { //pָ��ͼG��k���ĵ�һ���ɻ���
                            m = p;
                            G->vexs[k].trainFirstArc = p->nextArc; //��ͼG��k���ĵڶ����ɻ�����Ϊ��һ��
                            p = p->nextArc; //pָ����һ���ɻ���
                            free(m);  //�ͷţ�m��
                        } else {
                            q->nextArc = p->nextArc; //��p����һ��������q����һ����
                            m = p;
                            p = p->nextArc; //pָ����һ���ɻ���
                            free(q);  //�ͷ�(q)
                        }
                    } else {
                        q = p;
                        p = p->nextArc; //pָ����һ���ɻ���
                    }
                }
            }
        }
        G->vexNum--;
        save(G);
    } else
        return;
}

/*
  �ɻ�����༭��Ŀѡ�����
*/
void planeEdit(ALGraph *G) {
    int i;
    printf("\n��ѡ��ɻ�����༭��Ŀ:\n");
    printf("1=��������\n2=ɾ������\n");
    printf("ѡ��?");
    scanf("%d", &i);
    getchar();
    if(i == 1)
        addPlaneArc(G);
    if(i == 2)
        deletePlaneArc(G);
}
/*
  �г����α༭��Ŀѡ�����
*/
void trainEdit(ALGraph *G) {
    int i;
    printf("\n��ѡ���г����α༭��Ŀ:\n");
    printf("1=��������\n2=ɾ������\n");
    printf("ѡ��?");
    scanf("%d", &i);
    getchar();
    if(i == 1)
        addTrainArc(G);
    if(i == 2)
        deleteTrainArc(G);
}


/*
  ���ӷɻ�����
*/
void addPlaneArc(ALGraph *G) {
    int num, beginTime[2], arriveTime[2]; //num�����ţ�beginTime����ʱ�䣬arriveTime����ʱ��
    float money;  //����
    int i, j, m, t;
    int k; //������¼����ĳ���
    char beginCity[10], arriveCity[10], flag; //beginCity��ʼ���У�arriveCityĿ�����
    ArcNode *p, *q;
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
    printf("/nȷ��?(Y/N)");
    flag = getchar();
    getchar();
    if(flag == 'Y' || flag == 'y') {
        i = LocateVex(G, beginCity);
        j = LocateVex(G, arriveCity);
        if(i == -1) {
            printf("\n�����޷��ҵ���ʼ����\n");
            return;
        }
        if(j == -1) {
            printf("\n�����޷��ҵ��������\n");
            return;
        }
        q = G->vexs[i].planeFirstArc;
        m = 0;
        while(q != NULL) {
            if(q->adjvex == j) { //�� q�е��ڽӶ�����j���
                t = q->info.last + 1; // ������VehicleNode�е����ݶ����Ƶ���q��
                q->info.stata[t].num = num;
                q->info.stata[t].money = money;
                q->info.stata[t].beginTime[0] = beginTime[0];
                q->info.stata[t].beginTime[1] = beginTime[1];
                q->info.stata[t].arriveTime[0] = arriveTime[0];
                q->info.stata[t].arriveTime[1] = arriveTime[1];
                q->info.last = t;
                m = 1;
                break;
            }
            q = q->nextArc;
        }
        if(m == 0) {
            p = (ArcNode*)malloc(sizeof(ArcNode)); //����һ�������
            p->adjvex = j; //������VehicleNode�е����ݶ����Ƶ��µĻ������
            p->info.stata[0].num = num;
            p->info.stata[0].money = money;
            p->info.stata[0].beginTime[0] = beginTime[0];
            p->info.stata[0].beginTime[1] = beginTime[1];
            p->info.stata[0].arriveTime[0] = arriveTime[0];
            p->info.stata[0].arriveTime[1] = arriveTime[1];
            p->info.last = 0;
            p->nextArc = G->vexs[i].planeFirstArc;
            G->vexs[i].planeFirstArc = p; // ����������ӵ��ʵ���λ����ȥ
            G->planeArcNum++;
        }
        save(G);
    } else
        return;
}

/*
  �����г�����
*/
void addTrainArc(ALGraph *G) {
    int num, beginTime[2], arriveTime[2]; //num�����ţ�beginTime����ʱ�䣬arriveTime����ʱ��
    float money;  //����
    int i, j, m, t;
    int k; //������¼����ĳ���
    char beginCity[10], arriveCity[10], flag; //beginCity��ʼ���У�arriveCityĿ�����
    ArcNode *p, *q;


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
    printf("/nȷ��?(Y/N)");
    flag = getchar();
    getchar();

    if(flag == 'Y' || flag == 'y') {
        i = LocateVex(G, beginCity);
        j = LocateVex(G, arriveCity);
        if(i == -1) {
            printf("\n�����޷��ҵ���ʼ����\n");
            return;
        }
        if(j == -1) {
            printf("\n�����޷��ҵ��������\n");
            return;
        }
        q = G->vexs[i].trainFirstArc;
        m = 0;
        while(q != NULL) {
            if(q->adjvex == j) { //�� q�е��ڽӶ�����j���
                t = q->info.last + 1; // ������VehicleNode�е����ݶ����Ƶ���q��
                q->info.stata[t].num = num;
                q->info.stata[t].money = money;
                q->info.stata[t].beginTime[0] = beginTime[0];
                q->info.stata[t].beginTime[1] = beginTime[1];
                q->info.stata[t].arriveTime[0] = arriveTime[0];
                q->info.stata[t].arriveTime[1] = arriveTime[1];
                q->info.last = t;
                m = 1;
                break;
            }
            q = q->nextArc;
        }
        if(m == 0) {
            p = (ArcNode*)malloc(sizeof(ArcNode)); //����һ�������
            p->adjvex = j; //������VehicleNode�е����ݶ����Ƶ��µĻ������
            p->info.stata[0].num = num;
            p->info.stata[0].money = money;
            p->info.stata[0].beginTime[0] = beginTime[0];
            p->info.stata[0].beginTime[1] = beginTime[1];
            p->info.stata[0].arriveTime[0] = arriveTime[0];
            p->info.stata[0].arriveTime[1] = arriveTime[1];
            p->info.last = 0;
            p->nextArc = G->vexs[i].trainFirstArc;
            G->vexs[i].trainFirstArc = p; // ����������ӵ��ʵ���λ����ȥ
            G->trainArcNum++;
        }
        save(G);
    } else
        return;
}

int deletePlaneArc(ALGraph *G)
/*
  ɾ���ɻ�����
*/
{
    int i, j;
    int num;
    char beginCity[10], arriveCity[10], flag;
    int n;
    int k;
    ArcNode *p, *q;
    printf("\n������ɾ���ɻ��������Ϣ:\n");
    printf("�ɻ�����ı��:");
    scanf("%d", &num);
    getchar();
    printf("��ʼ����:");
    gets(beginCity);
    printf("Ŀ�ĳ���:");
    gets(arriveCity);

    printf("\nȷ��?(Y/N)");
    flag = getchar();
    getchar();

    if(flag == 'Y' || flag == 'y') {
        i = LocateVex(G, beginCity);
        j = LocateVex(G, arriveCity);
        if(i == -1) {
            printf("\n�����޷��ҵ���ʼ����\n");
            return 0;
        }
        if(j == -1) {
            printf("\n�����޷��ҵ�Ŀ�ĳ���\n");
            return 0;
        }
        p = G->vexs[i].planeFirstArc;
        q = p;
        while(p != NULL) {
            if(p->adjvex == j) {
                n = -1;
                for(k = 0; k <= p->info.last; k++) {
                    if(p->info.stata[k].num == num) {
                        n = k;
                        break;
                    }
                }
                if(n != -1)
                    if(p->info.last == 0) {
                        if(q == p)
                            G->vexs[i].planeFirstArc = p->nextArc;
                        else
                            q->nextArc = p->nextArc;
                        free(p);
                    } else {
                        for(k = n; k < p->info.last; k++) {
                            p->info.stata[k].num = p->info.stata[k + 1].num;
                            p->info.stata[k].money = p->info.stata[k + 1].money;
                            p->info.stata[k].beginTime[0] = p->info.stata[k + 1].beginTime[0];
                            p->info.stata[k].beginTime[1] = p->info.stata[k + 1].beginTime[1];
                            p->info.stata[k].arriveTime[0] = p->info.stata[k + 1].arriveTime[0];
                            p->info.stata[k].arriveTime[1] = p->info.stata[k + 1].arriveTime[1];
                        }
                        p->info.last = p->info.last - 1;
                    }
                else
                    printf("\n�ڴ�������֮���޷��ҵ�No.%d�ɻ�����\n", num);
                save(G);
                return 1;
            }
            q = p;
            p = p->nextArc;
        }
        if(p == NULL)
            printf("\n�ڴ�������֮���޷ɻ��������\n");
    } else
        return 1;
    return 0;
}
int deleteTrainArc(ALGraph *G)
/*
  ɾ���г�����
*/
{
    int i, j;
    int num;
    char beginCity[10], arriveCity[10], flag;
    int n;
    int k;
    ArcNode *p, *q;
    printf("\n������ɾ���г����ε���Ϣ:\n");
    printf("�г����εı��:");
    scanf("%d", &num);
    getchar();
    printf("��ʼ����:");
    gets(beginCity);
    printf("Ŀ�ĳ���:");
    gets(arriveCity);
    printf("\nȷ��?(Y/N)");
    flag = getchar();
    getchar();
    if(flag == 'Y' || flag == 'y') {
        i = LocateVex(G, beginCity);
        j = LocateVex(G, arriveCity);
        if(i == -1) {
            printf("\n�����޷��ҵ���ʼ����\n");
            return 0;
        }
        if(j == -1) {
            printf("\n�����޷��ҵ�Ŀ�ĳ���\n");
            return 0;
        }
        p = G->vexs[i].trainFirstArc;
        q = p;
        while(p != NULL) {
            if(p->adjvex == j) {
                n = -1;
                for(k = 0; k <= p->info.last; k++) {
                    if(p->info.stata[k].num == num) {
                        n = k;
                        break;
                    }
                }
                if(n != -1)
                    if(p->info.last == 0) {
                        if(q == p)
                            G->vexs[i].trainFirstArc = p->nextArc;
                        else
                            q->nextArc = p->nextArc;
                        free(p);
                    } else {
                        for(k = n; k < p->info.last; k++) {
                            p->info.stata[k].num = p->info.stata[k + 1].num;
                            p->info.stata[k].money = p->info.stata[k + 1].money;
                            p->info.stata[k].beginTime[0] = p->info.stata[k + 1].beginTime[0];
                            p->info.stata[k].beginTime[1] = p->info.stata[k + 1].beginTime[1];
                            p->info.stata[k].arriveTime[0] = p->info.stata[k + 1].arriveTime[0];
                            p->info.stata[k].arriveTime[1] = p->info.stata[k + 1].arriveTime[1];
                        }
                        p->info.last = p->info.last - 1;
                    }
                else
                    printf("\n�ڴ�������֮���޷��ҵ�No.%d�г�����\n", num);
                save(G);
                return 1;
            }
            q = p;
            p = p->nextArc;
        }
        if(p == NULL)
            printf("\n�ڴ�������֮���޸��г����δ���\n");
    } else
        return 1;
    return 0;
}
