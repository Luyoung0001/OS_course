#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int i, to, sum = 0;
    to = atoi(argv[1]);

    clock_t start = clock(); // 记录开始时间

    for(i = 1; i <= to; i++) {
        sum += i;
        // printf("%d\n", sum);
    }

    clock_t end = clock(); // 记录结束时间
    double duration = (double)(end - start) / CLOCKS_PER_SEC; // 计算运行时间

    printf("程序运行时间：%f秒\n", duration);

    return 0;
}
