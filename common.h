#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

/*交通工具信息的录入*/
struct arc {
    int num;   //班次
    float money; //费用
    char beginCity[10];  //出发地
    char arriveCity[10]; //目的地
    int beginTime[2];   //出发时间
    int arriveTime[2];  //到达时间
} VehicleNote[MAX_ARC_SIZE];
char city[MAX_VERTEX_NUM][10];
int TTime[2];
int time[2];
int time1[2];
int time2[2];
int c[MAX_VERTEX_NUM];
int d[MAX_VERTEX_NUM];

#endif // COMMON_H_INCLUDED
