#include "traffic.h"

int main() {
    ALGraph G;
    int i;
    printf("\n                         全国交通咨询系统:\n");
    printf("\n            |            1.管理员管理           |\n");
    printf("\n            |            2.交通系统查询         |\n");
    printf("\n            |            3.交通咨询             |\n");
    printf("\n            |            4.退出                 |\n");
    printf("\n选择?");
    scanf("%d", &i);
    getchar();
    while(i != 4) {
        switch(i) {
        case 1:
            manager(&G);
            break;
        case 2:
            showGraph(&G);
            break;
        case 3:
            userAsk(G);
            break;
        }
        printf("                           全国交通咨询系统:\n");
        printf("\n            |              1.管理员管理           |\n");
        printf("\n            |              2.交通系统查询         |\n");
        printf("\n            |              3.交通咨询             |\n");
        printf("\n            |              4.退出                 |\n");
        printf("\n选择?");
        scanf("%d", &i);
        getchar();
    }
    return 1;
}
