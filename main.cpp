#include "traffic.h"

int main() {
    ALGraph G;
    int i;
    printf("\n                         ȫ����ͨ��ѯϵͳ:\n");
    printf("\n            |            1.����Ա����           |\n");
    printf("\n            |            2.��ͨϵͳ��ѯ         |\n");
    printf("\n            |            3.��ͨ��ѯ             |\n");
    printf("\n            |            4.�˳�                 |\n");
    printf("\nѡ��?");
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
        printf("                           ȫ����ͨ��ѯϵͳ:\n");
        printf("\n            |              1.����Ա����           |\n");
        printf("\n            |              2.��ͨϵͳ��ѯ         |\n");
        printf("\n            |              3.��ͨ��ѯ             |\n");
        printf("\n            |              4.�˳�                 |\n");
        printf("\nѡ��?");
        scanf("%d", &i);
        getchar();
    }
    return 1;
}
