#include "traffic.h"

int main() {
    ALGraph G;
    int i;
    printf("\n              ȫ����ͨ��ѯϵͳ:Ԭ����3117004905\n");
    printf("\n            |            1.����ϵͳ             |\n");
    printf("\n            |            2.��ͨϵͳ��ѯ         |\n");
    printf("\n            |            3.��ͨ��ѯ             |\n");
    printf("\n            |            4.�˳�                 |\n");
    printf("\n            ע�����Ҫѡ��2��3���������Ƚ������ϵͳ���г�ʼ����ͨ��Ϣ\n");
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
        printf("\n              ȫ����ͨ��ѯϵͳ:Ԭ����3117004905\n");
        printf("\n            |              1.����ϵͳ             |\n");
        printf("\n            |              2.��ͨϵͳ��ѯ         |\n");
        printf("\n            |              3.��ͨ��ѯ             |\n");
        printf("\n            |              4.�˳�                 |\n");
        printf("\n            ע�����Ҫѡ��2��3���������Ƚ������ϵͳ���г�ʼ����ͨ��Ϣ\n");
        printf("\nѡ��?");
        scanf("%d", &i);
        getchar();
    }
    return 1;
}
