#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student {
    char student_id[20];
    char name[20];
    char gender[10];
    char phone[20];
    float c_language;
    float higher_math;
    float foreign_language;
    float peer_evaluation;
    float character_score;
    float teacher_evaluation;
    float total_score;
    int total_rank;
};

void save_student_data(struct Student students[], int count) {
    FILE *file = fopen("student_data.txt", "w");
    if (file == NULL) {
        printf("无法打开文件。\n");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %s %s %.2f %.2f %.2f %.2f %.2f %.2f %.2f %d\n", students[i].student_id,
                students[i].name, students[i].gender, students[i].phone, students[i].c_language,
                students[i].higher_math, students[i].foreign_language, students[i].peer_evaluation,
                students[i].character_score, students[i].teacher_evaluation, students[i].total_score,
                students[i].total_rank);
    }

    fclose(file);
}

void load_student_data(struct Student students[], int *count) {
    FILE *file = fopen("student_data.txt", "r");
    if (file == NULL) {
        printf("无法打开文件。\n");
        exit(1);
    }

    *count = 0;
    while (fscanf(file, "%s %s %s %s %f %f %f %f %f %f %f %d\n", students[*count].student_id,
                  students[*count].name, students[*count].gender, students[*count].phone,
                  &students[*count].c_language, &students[*count].higher_math,
                  &students[*count].foreign_language, &students[*count].peer_evaluation,
                  &students[*count].character_score, &students[*count].teacher_evaluation,
                  &students[*count].total_score, &students[*count].total_rank) != EOF) {
        (*count)++;
    }

    fclose(file);
}

void add_or_modify_student(struct Student students[], int *count) {
    printf("请输入学号：");
    char student_id[20];
    scanf("%s", student_id);

    for (int i = 0; i < *count; i++) {
        if (strcmp(students[i].student_id, student_id) == 0) {
            printf("已找到学号为 %s 的学生信息，进行修改。\n", student_id);
            printf("请输入姓名：");
            scanf("%s", students[i].name);
            printf("请输入性别：");
            scanf("%s", students[i].gender);
            printf("请输入联系电话：");
            scanf("%s", students[i].phone);
            printf("请输入C语言成绩：");
            scanf("%f", &students[i].c_language);
            printf("请输入高等数学成绩：");
            scanf("%f", &students[i].higher_math);
            printf("请输入外语成绩：");
            scanf("%f", &students[i].foreign_language);

            save_student_data(students, *count);
            printf("学生信息修改成功。\n");
            return;
        }
    }

    // 如果没有找到该学号的学生，则添加新的学生信息
    if (*count >= MAX_STUDENTS) {
        printf("学生人数已达上限，无法添加新的学生。\n");
        return;
    }

    strcpy(students[*count].student_id, student_id);
    printf("请输入姓名：");
    scanf("%s", students[*count].name);
    printf("请输入性别：");
    scanf("%s", students[*count].gender);
    printf("请输入联系电话：");
    scanf("%s", students[*count].phone);
    printf("请输入C语言成绩：");
    scanf("%f", &students[*count].c_language);
    printf("请输入高等数学成绩：");
    scanf("%f", &students[*count].higher_math);
    printf("请输入外语成绩：");
    scanf("%f", &students[*count].foreign_language);

    (*count)++;
    save_student_data(students, *count);
    printf("学生信息添加成功。\n");
}

void delete_student(struct Student students[], int *count) {
    printf("请输入要删除的学生学号：");
    char student_id[20];
    scanf("%s", student_id);

    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (strcmp(students[i].student_id, student_id) == 0) {
            printf("找到学号为 %s 的学生信息：\n", student_id);
            printf("姓名：%s\n", students[i].name);
            printf("性别：%s\n", students[i].gender);
            printf("联系电话：%s\n", students[i].phone);
            printf("C语言成绩：%.2f\n", students[i].c_language);
            printf("高等数学成绩：%.2f\n", students[i].higher_math);
            printf("外语成绩：%.2f\n", students[i].foreign_language);
            printf("同学互评分：%.2f\n", students[i].peer_evaluation);
            printf("品德成绩：%.2f\n", students[i].character_score);
            printf("任课教师评分：%.2f\n", students[i].teacher_evaluation);
            printf("综合测评总分：%.2f\n", students[i].total_score);
            printf("综合测评名次：%d\n", students[i].total_rank);

            printf("确认是否删除该学生信息（Y/N）：");
            char confirm[2];
            scanf("%s", confirm);

            if (strcmp(confirm, "Y") == 0 || strcmp(confirm, "y") == 0) {
                for (int j = i; j < *count - 1; j++) {
                    students[j] = students[j + 1];
                }
                (*count)--;
                save_student_data(students, *count);
                printf("学生信息删除成功。\n");
            } else {
                printf("取消删除学生信息。\n");
            }

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("未找到学号为 %s 的学生信息。\n", student_id);
    }
}

void browse_student_info(struct Student students[], int count) {
    printf("浏览学生信息：\n");
    for (int i = 0; i < count; i++) {
        printf("学号：%s，姓名：%s，性别：%s，联系电话：%s，C语言成绩：%.2f，高等数学成绩：%.2f，外语成绩：%.2f\n",
               students[i].student_id, students[i].name, students[i].gender, students[i].phone,
               students[i].c_language, students[i].higher_math, students[i].foreign_language);
    }
}

void enter_peer_evaluation(struct Student students[], int count) {
    printf("请输入同学互评分：\n");
    for (int i = 0; i < count; i++) {
        printf("请输入学号为 %s 的学生同学互评分：", students[i].student_id);
        scanf("%f", &students[i].peer_evaluation);
    }

    save_student_data(students, count);
    printf("同学互评分录入成功。\n");
}

void enter_character_scores(struct Student students[], int count) {
    printf("请输入品德成绩：\n");
    for (int i = 0; i < count; i++) {
        printf("请输入学号为 %s 的学生品德成绩：", students[i].student_id);
        scanf("%f", &students[i].character_score);
    }

    save_student_data(students, count);
    printf("品德成绩录入成功。\n");
}

void enter_teacher_evaluation(struct Student students[], int count) {
    printf("请输入任课教师评分：\n");
    for (int i = 0; i < count; i++) {
        printf("请输入学号为 %s 的学生任课教师评分：", students[i].student_id);
        scanf("%f", &students[i].teacher_evaluation);
    }

    save_student_data(students, count);
    printf("任课教师评分录入成功。\n");
}

void calculate_total_scores(struct Student students[], int count) {
    for (int i = 0; i < count; i++) {
        students[i].total_score =
            (students[i].c_language + students[i].higher_math + students[i].foreign_language) / 3 * 0.6 +
            students[i].peer_evaluation * 0.1 +
            students[i].character_score * 0.1 +
            students[i].teacher_evaluation * 0.2;
    }

    save_student_data(students, count);
    printf("综合测评总分计算完成。\n");
}


void print_student_info_by_total_rank(struct Student students[], int count) {
    // 按照综合测评总分排序
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].total_score < students[j + 1].total_score) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("按照综合测评名次输出学生信息：\n");
    for (int i = 0; i < count; i++) {
        printf("学号：%s，姓名：%s，综合测评总分：%.2f，综合测评名次：%d\n", students[i].student_id,
               students[i].name, students[i].total_score, i + 1);
    }
}

void print_student_info_by_subject_score(struct Student students[], int count) {
    // 按照C语言成绩排序
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].c_language < students[j + 1].c_language) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("按照C语言成绩排名输出学生信息：\n");
    for (int i = 0; i < count; i++) {
        printf("学号：%s，姓名：%s，C语言成绩：%.2f\n", students[i].student_id, students[i].name,
               students[i].c_language);
    }
}

void print_student_info(struct Student students[], int count) {
    printf("学生综合信息输出：\n");
    for (int i = 0; i < count; i++) {
        printf("学号：%s\n", students[i].student_id);
        printf("姓名：%s\n", students[i].name);
        printf("性别：%s\n", students[i].gender);
        printf("联系电话：%s\n", students[i].phone);
        printf("C语言成绩：%.2f\n", students[i].c_language);
        printf("高等数学成绩：%.2f\n", students[i].higher_math);
        printf("外语成绩：%.2f\n", students[i].foreign_language);
        printf("同学互评分：%.2f\n", students[i].peer_evaluation);
        printf("品德成绩：%.2f\n", students[i].character_score);
        printf("任课教师评分：%.2f\n", students[i].teacher_evaluation);
        printf("综合测评总分：%.2f\n", students[i].total_score);
        printf("综合测评名次：%d\n", students[i].total_rank);
        printf("\n");
    }
}

int main() {
    struct Student students[MAX_STUDENTS];
    int count = 0;

    load_student_data(students, &count);

    int choice;
    do {
        printf("学生综合测评系统\n");
        printf("1. 录入学生信息\n");
        printf("2. 修改学生信息\n");
        printf("3. 删除学生信息\n");
        printf("4. 浏览学生信息\n");
        printf("5. 录入同学互评分\n");
        printf("6. 录入品德成绩\n");
        printf("7. 录入任课教师评分\n");
        printf("8. 计算综合测评总分\n");
        printf("9. 按照综合测评名次输出学生信息\n");
        printf("10. 按照单科成绩排名输出学生信息\n");
        printf("11. 输出学生综合信息\n");
        printf("0. 退出程序\n");
        printf("请选择操作：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_or_modify_student(students, &count);
                break;
            case 2:
                add_or_modify_student(students, &count);
                break;
            case 3:
                delete_student(students, &count);
                break;
            case 4:
                browse_student_info(students, count);
                break;
            case 5:
                enter_peer_evaluation(students, count);
                break;
            case 6:
                enter_character_scores(students, count);
                break;
            case 7:
                enter_teacher_evaluation(students, count);
                break;
            case 8:
                calculate_total_scores(students, count);
                break;
            case 9:
                print_student_info_by_total_rank(students, count);
                break;
            case 10:
                print_student_info_by_subject_score(students, count);
                break;
            case 11:
                print_student_info(students, count);
                break;
            case 0:
                printf("程序已退出。\n");
                break;
            default:
                printf("无效的操作。\n");
                break;
        }
        printf("\n");
    } while (choice != 0);

    return 0;
}
