#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

/*��ͨ������Ϣ��¼��*/
struct arc {
    int num;   //���
    float money; //����
    char beginCity[10];  //������
    char arriveCity[10]; //Ŀ�ĵ�
    int beginTime[2];   //����ʱ��
    int arriveTime[2];  //����ʱ��
} VehicleNote[MAX_ARC_SIZE];
char city[MAX_VERTEX_NUM][10];
int TTime[2];
int time[2];
int time1[2];
int time2[2];
int c[MAX_VERTEX_NUM];
int d[MAX_VERTEX_NUM];

#endif // COMMON_H_INCLUDED
