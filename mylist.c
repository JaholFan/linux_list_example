/**@brief 练习使用linux内核链表，功能包括：
 * 定义链表结构，创建链表、插入节点、删除节点、移动节点、遍历节点
 *
 *@auther Jahol @date 2019-3-21
 **/
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include "mylist.h"
//定义链表结构
struct student
{
    unsigned char  score;
    struct    linked_list linked_node;//链表节点
};


struct student* create_student(unsigned char score)
{
    struct student *st = (struct student*)malloc(sizeof(struct student));
    if (st == NULL)
    {
        fprintf(stderr, "Failed to malloc memory, errno:%u, reason:%s\n",errno, strerror(errno));
        return NULL;
    }
    st->score = score;
    return st;
}
static void fore_each_student(const struct linked_list *head)
{
    struct linked_list *pos;
    struct student *st;
    //遍历链表
    list_for_each(pos, head)
    {
        st = list_entry(pos, struct student, linked_node);
        printf("score: %u\n",st->score);

    }
}

void destroy_student_list(struct linked_list *head)
{
    struct linked_list *pos = head->next;
    struct linked_list *tmp = NULL;
    while (pos != head)
    {
        tmp = pos->next;
        list_del(pos);
        pos = tmp;
    }
}


int main()
{
    //创建一个student_info_list
    struct student * student_info_list = (struct student*)malloc(sizeof(struct student));
    struct student *st;
    if (student_info_list == NULL)
    {
        fprintf(stderr, "Failed to malloc memory, errno:%u, reason:%s\n",errno, strerror(errno));
        return -1;
    }

    //初始化链表头部
    struct linked_list *head = &student_info_list->linked_node;
    init_list_head(head);

    //插入三个student
    st = create_student(60);
    list_add_tail(&st->linked_node, head);
    st = create_student(90);
    list_add_tail(&st->linked_node, head);
    st = create_student(88);
    list_add_tail(&st->linked_node, head);

    printf("After insert,score: \n");
    fore_each_student(head);

    //将第一个节点移到末尾
    printf("Move first node to tail,score:\n");
    list_move_tail(head->next, head);
    fore_each_student(head);

    //删除最后一个节点
    printf("Delete the last node,score:\n");
    list_del(head->prev);
    fore_each_student(head);

    destroy_student_list(head);

    free(student_info_list);

    return 0;
}

