#include "traffic.h"

int main(){
    ALGraph G;
    int i;
    printf("��ѡ�������:\n");
    printf("1=����Ա����\n2=�û���ѯ\n3=��ʾ��ͨϵͳ\n4=�˳�\n");
    printf("ѡ��?");
    scanf("%d", &i);
    getchar();
    while(i != 4) {
        switch(i) {
        case 1:
            Administer(&G);
            break;
        case 2:

            break;
        case 3:

            break;
        }
        printf("\n��ѡ�������:\n");
        printf("1=����Ա����\n2=�û���ѯ\n3=��ʾ��ͨϵͳ\n4=�˳�\n");
        printf("ѡ��?");
        scanf("%d", &i);
        getchar();
    }
    return 1;
}
