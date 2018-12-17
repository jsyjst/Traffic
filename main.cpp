#include "traffic.h"

int main(){
    ALGraph G;
    int i;
    printf("请选择程序功能:\n");
    printf("1=管理员管理\n2=用户咨询\n3=显示交通系统\n4=退出\n");
    printf("选择?");
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
        printf("\n请选择程序功能:\n");
        printf("1=管理员管理\n2=用户咨询\n3=显示交通系统\n4=退出\n");
        printf("选择?");
        scanf("%d", &i);
        getchar();
    }
    return 1;
}
