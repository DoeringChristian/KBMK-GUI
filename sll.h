 #ifndef SLL_H
 #define SLL_H

#define SLL_LIST_INIT {.root = NULL}

/*#define SLL_LIST_NEW(_type, ...) ({\
    typeof(_type) _tmp[] = {__VA_ARGS__};\
    sll_list_##_type *_list = sll_list_new_##_type();\
    for(unsigned int i = 0;i < sizeof(_tmp)/sizeof(_type);i++){\
        sll_list_push_back_##_type(_list, _tmp[i]);\
    }\
    _list;\
})*/

#define IN ,
#define SLL_FOR_EACH(...) _SLL_FOR_EACH(__VA_ARGS__)
#define _SLL_FOR_EACH(_node, _list_p)\
for(typeof(_list_p->root) _node = _list_p->root; _node != NULL; _node = _node->next)


#define SLL_LIST(_type) sll_list_##_type
#define SLL_NODE(_type) sll_node_##_type
#define SLL_LIST_NEW(_type) sll_list_new_##_type
#define SLL_NODE_NEW(_type) sll_node_new_##_type
#define SLL_LIST_DELETE(_type) sll_list_delete_##_type
#define SLL_NODE_DELETE(_type) sll_node_delete_##_type
#define SLL_LIST_PUSH_BACK(_type) sll_list_push_back_##_type
#define SLL_LIST_POP_BACK(_type) sll_list_pop_back_##_type
#define SLL_LIST_SIZE(_type) sll_list_size_##_type
#define SLL_LIST_ELEMENT_AT(_type) sll_list_element_at_##_type
#define SLL_LIST_NODE_AT(_type) sll_list_node_at_##_type
#define SLL_LIST_POP_AT(_type) sll_list_pop_at_##_type
#define SLL_LIST_INDEX(_type) sll_list_index_##_type


#define SLL_TYPEDEF_H(_type)\
\
typedef struct sll_list_##_type##_s sll_list_##_type;\
typedef struct sll_node_##_type##_s sll_node_##_type;

#define SLL_DEFINE_H(_type)\
\
typedef struct sll_node_##_type##_s{\
    struct sll_node_##_type##_s *next;\
    _type element;\
} sll_node_##_type;\
\
typedef struct sll_list_##_type##_s{\
    sll_node_##_type *root;\
} sll_list_##_type;\
\
sll_list_##_type *sll_list_new_##_type();\
sll_node_##_type *sll_node_new_##_type(_type element);\
void sll_list_delete_##_type(sll_list_##_type *list);\
void sll_node_delete_##_type(sll_node_##_type *node);\
sll_node_##_type *sll_list_push_back_##_type(sll_list_##_type *list, _type element);\
void sll_list_pop_back_##_type(sll_list_##_type *list);\
unsigned int sll_list_size_##_type(sll_list_##_type *list);\
_type *sll_list_element_at_##_type(sll_list_##_type *list, unsigned int index);\
sll_node_##_type *sll_list_node_at_##_type(sll_list_##_type *list, unsigned int index);\
void sll_list_pop_at_##_type(sll_list_##_type *list, unsigned int index);\
unsigned int sll_list_index_##_type(sll_list_##_type *list, sll_node_##_type *node)

#define SLL_DEFINE_C(_type)\
sll_node_##_type sll_node_init_##_type(_type element){\
    return (sll_node_##_type){\
        .next = NULL,\
        .element = element\
    };\
}\
sll_list_##_type sll_list_init_##_type(){\
    return (sll_list_##_type){\
        .root = NULL\
    };\
}\
\
sll_list_##_type *sll_list_new_##_type(){\
    sll_list_##_type *list = malloc(sizeof(sll_list_##_type));\
    *list = sll_list_init_##_type();\
    return list;\
}\
\
sll_node_##_type *sll_node_new_##_type(_type element){\
    sll_node_##_type *node = malloc(sizeof(sll_node_##_type));\
    *node = sll_node_init_##_type(element);\
    return node;\
}\
\
void sll_list_delete_##_type(sll_list_##_type *list){\
    sll_node_##_type *tmp1 = list->root, *tmp2 = list->root;\
    while(tmp1 != NULL){\
        tmp1 = tmp1->next;\
        sll_node_delete_##_type(tmp2);\
        tmp2 = tmp1;\
    }\
}\
\
void sll_node_delete_##_type(sll_node_##_type *node){\
    free(node);\
}\
\
sll_node_##_type *sll_list_push_back_##_type(sll_list_##_type *list, _type element){\
    sll_node_##_type *tmp = list->root;\
    if(tmp == NULL) list->root = sll_node_new_##_type(element);\
    else{\
        while(tmp->next != NULL) tmp = tmp->next;\
        tmp->next = sll_node_new_##_type(element);\
        tmp = tmp->next;\
    }\
    return tmp;\
}\
\
void sll_list_pop_back_##_type(sll_list_##_type *list){\
    sll_node_##_type *tmp = list->root;\
    if(tmp == NULL) return;\
    else if(tmp->next == NULL){\
        sll_node_delete_##_type(tmp);\
        list->root = NULL;\
    }\
    else{\
        while(tmp->next->next != NULL) tmp = tmp->next;\
        sll_node_delete_##_type(tmp->next);\
        tmp->next = NULL;\
    }\
    return;\
}\
\
unsigned int sll_list_size_##_type(sll_list_##_type *list){\
    unsigned int c = 0;\
    sll_node_##_type *tmp = list->root;\
    while(tmp != NULL){\
        tmp = tmp->next;\
        c++;\
    }\
    return c;\
}\
\
_type *sll_list_element_at_##_type(sll_list_##_type *list, unsigned int index){\
    sll_node_##_type *tmp = sll_list_node_at_##_type(list, index);\
    if(tmp == NULL) return NULL;\
    else return &tmp->element;\
}\
\
sll_node_##_type *sll_list_node_at_##_type(sll_list_##_type *list, unsigned int index){\
    sll_node_##_type *node = list->root;\
    for(unsigned int i = 0; i < index && node != NULL; i++) node = node->next;\
    return node;\
}\
\
void sll_list_pop_at_##_type(sll_list_##_type *list, unsigned int index){\
    if(list->root == NULL) return;\
    else if(index >= sll_list_size_##_type(list)) return;\
    else if(index == 0){\
        sll_node_##_type *tmp = list->root->next;\
        sll_node_delete_##_type(list->root);\
        list->root = tmp;\
    }\
    else{\
        sll_node_##_type *tmp1 = sll_list_node_at_##_type(list, index-1);\
        sll_node_##_type *tmp2 = tmp1->next->next;\
        sll_node_delete_##_type(tmp1->next);\
        tmp1->next = tmp2;\
    }\
}\
\
unsigned int sll_list_index_##_type(sll_list_##_type *list, sll_node_##_type *node){\
    unsigned int i = 0;\
    for(sll_node_##_type *tmp = list->root; tmp != NULL && tmp != node;){\
        i++;\
        node = node->next;\
    }\
    return i;\
}


 #endif //SLL_H