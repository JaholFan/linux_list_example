# define POISON_POINTER_DELTA 0

#define LIST_POISON1  ((void *) 0x00100100 + POISON_POINTER_DELTA)
#define LIST_POISON2  ((void *) 0x00200200 + POISON_POINTER_DELTA)

//计算member在type中的位置
#define offsetof(type, member)  (size_t)(&((type*)0)->member)
//根据member的地址获取type的起始地址
#define container_of(ptr, type, member) ({          \
        const typeof(((type *)0)->member)*__mptr = (ptr);    \
    (type *)((char *)__mptr - offsetof(type, member)); })

//链表结构
struct linked_list
{
    struct linked_list *prev;
    struct linked_list *next;
};

static inline void init_list_head(struct linked_list *list)
{
    list->prev = list;
    list->next = list;
}

static inline void __list_add(struct linked_list *new,
                              struct linked_list *prev, struct linked_list *next)
{
    prev->next = new;
    new->prev = prev;
    new->next = next;
    next->prev = new;
}

//从头部添加
static inline void list_add(struct linked_list *new , struct linked_list *head)
{
    __list_add(new, head, head->next);
}
//从尾部添加
static inline void list_add_tail(struct linked_list *new, struct linked_list *head)
{
    __list_add(new, head->prev, head);
}

static inline  void __list_del(struct linked_list *prev, struct linked_list *next)
{
    prev->next = next;
    next->prev = prev;
}

static inline void list_del(struct linked_list *entry)
{
    __list_del(entry->prev, entry->next);
    entry->next = LIST_POISON1;
    entry->prev = LIST_POISON2;
}

static inline void list_move(struct linked_list *list, struct linked_list *head)
{
    __list_del(list->prev, list->next);
    list_add(list, head);
}

static inline void list_move_tail(struct linked_list *list,
                                  struct linked_list *head)
{
    __list_del(list->prev, list->next);
    list_add_tail(list, head);
}
#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define list_first_entry(ptr, type, member) \
    list_entry((ptr)->next, type, member)

#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)
