#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ATHLETES 40//定义一下选手的最大人数
#define MAX_JUDGES 20//定义一下评委的最大人数

int athleteIDs[MAX_ATHLETES];        // 选手编号
float chucipingfen[MAX_ATHLETES][MAX_JUDGES]; // 选手的评分
float xuanshoufenshu[MAX_ATHLETES];    // 选手的最终得分
int athleteCount = 0;               // 选手数量
int judgeCount = 0;                 // 评委数量
int judgeIDs[MAX_JUDGES];           // 裁判编号

bool IsUniqueID(int id, int currentIndex, int ids[], int maxCount);
void InputScores();
void zuihoufenshu();
void SortScores();
void shuchupaiming();

int main() {
    printf("欢迎使用大奖赛现场统分系统！\n");

    // 裁判进行打分
    InputScores();
	
    // 计算最终得分
    zuihoufenshu();

    // 对分数进行排序
    SortScores();

    // 输出排名
    shuchupaiming();

    printf("\n评分系统结束，感谢使用！\n");
	
    return 0;
}

// 判断一下选手和评委的编号有没有重复
bool IsUniqueID(int id, int currentIndex, int ids[], int maxCount) {//第一个参数是当前要检查的编号；
//第二个参数是当前正在输入的编号索引；第三个参数是保存已有编号的数组；第四个参数没有作用
    for (int i = 0; i < currentIndex; i++) {
        if (ids[i] == id) {
            return false;
        }
    }
    return true;
}

// 从键盘接收评委打的分数
void InputScores() {
    printf("有多少位选手? ");
    scanf("%d", &athleteCount);//从键盘输入有几位选手

    printf("有多少评委? ");
    scanf("%d", &judgeCount);//从键盘输入有几位裁判

    // 输入裁判编号，并检查唯一性
    for (int i = 0; i < judgeCount; i++) {
        int valid = 0;//用于控制编号输入的有效性检查循环
        while (valid==0) {
            printf("请输入第 %d 位裁判的编号: ", i + 1);
            char input[20];  // 使用字符串接收输入
            scanf("%s", input);

            // 检查是否为整数
            int id;
            if (sscanf(input, "%d", &id) == 1 && strchr(input, '.') == NULL) {//第一个判断input是不是有效的整数字符串，然后&&后面是看有没有小数点
                // 检查编号是否唯一
                if (IsUniqueID(id, i, judgeIDs, judgeCount)) {
                    judgeIDs[i] = id;
                    valid = 1;  // 输入有效，退出循环
                } else {
                    printf("编号 %d 已经存在，请输入一个唯一的编号！\n", id);
                }
            } else {
                printf("编号输入无效，请输入一个整数编号！\n");
            }
        }
    }

    // 输入选手信息
    for (int i = 0; i < athleteCount; i++) {
        int valid = 0;
        while (valid==0) {
            printf("请输入第 %d 位选手的编号: ", i + 1);
            char input[20];  // 使用字符串接收输入
            scanf("%s", input);

            // 检查是否为整数
            int id;
            if (sscanf(input, "%d", &id) == 1 && strchr(input, '.') == NULL) {//第一个判断input是不是有效的整数字符串，然后&&后面是看有没有小数点
                // 检查编号是否唯一
                if (IsUniqueID(id, i, athleteIDs, athleteCount)) {
                    athleteIDs[i] = id;
                    valid = 1;  // 输入有效，退出循环
                } else {
                    printf("编号 %d 已经存在，请输入一个唯一的编号！\n", id);
                }
            } else {
                printf("编号输入无效，请输入一个整数编号！\n");
            }
        }

        // 输入评委评分
        for (int j = 0; j < judgeCount; j++) {
            float score;
            while (true) {
                printf("请输入裁判 %d (编号: %d) 给选手 %d 的评分 (0.0-10.0): ", j + 1, judgeIDs[j], athleteIDs[i]);
                scanf("%f", &score);

                if (score >= 0.0 && score <= 10.0) {
                    chucipingfen[i][j] = score;//当前裁判给现在的被打分的选手的分数
                    break;  // 输入有效，退出循环
                } else {
                    printf("评分无效，请输入0.0到10.0之间的评分！\n");
                }
            }
        }
    }
}

// 把选手分数汇总计算分数
void zuihoufenshu() {
    for (int i = 0; i < athleteCount; i++) {
        float max = chucipingfen[i][0], min = chucipingfen[i][0], sum = 0.0;

        for (int j = 0; j < judgeCount; j++) {
            if (chucipingfen[i][j] > max) max = chucipingfen[i][j];
            if (chucipingfen[i][j] < min) min = chucipingfen[i][j];
            sum += chucipingfen[i][j];
        }

        // 去掉一个最高分和一个最低分后计算平均分
        xuanshoufenshu[i] = (sum - max - min) / (judgeCount - 2);
    }
}

// 对分数进行排序
void SortScores() {
    for (int i = 0; i < athleteCount - 1; i++) {
        for (int j = i + 1; j < athleteCount; j++) {
            if (xuanshoufenshu[i] < xuanshoufenshu[j]) {
                // 对分数排序的关键,冒泡排序
                float tempScore = xuanshoufenshu[i];
                xuanshoufenshu[i] = xuanshoufenshu[j];
                xuanshoufenshu[j] = tempScore;

                // 交换选手编号
                int tempID = athleteIDs[i];
                athleteIDs[i] = athleteIDs[j];
                athleteIDs[j] = tempID;
            }
        }
    }
}

// 输出排名
void shuchupaiming() {
    printf("\n最终排名:\n");
    printf("排名\t选手编号\t最终得分\n");
    for (int i = 0; i < athleteCount; i++) {
        printf("%d\t%d\t\t%.2f\n", i + 1, athleteIDs[i], xuanshoufenshu[i]);
    }
}
