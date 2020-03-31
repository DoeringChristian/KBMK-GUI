#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

#define LIST_NAMESPACE slt

/*
Usage:
    //pointers have to be typedefined to not include *. (e.g. typedef int *int_p;)
    Header File:
        //forward declare list
        LIST_DECLARE_H(_type);

        typedef struct xy{
            //use forward declared list in structs
            list_##_type a;
        } xy_t;

        //define structs and declare functions
        LIST_DEFINE_H(_type);

    C File:
        //define functions
        LIST_DEFINE_C(_type);
*/

/*
Example:
    //lists can be initialized by pushing to nulptr
    list_int l1 = list_push_back_int(NULL, 1);
    list_push_back_int(&l1, 2);
    list_push_back_int(&l1, 3);
    list_for_all_int(&l1, FP({printf("%i\n", *i);}, void, int *i));
*/


typedef unsigned int uint;

#define _HEAD(_x, ...) (_x)

/*
FP(code, return type, arguments)
make function pointer from code snippet
(only GCC)
*/
#define FP(_code, _return_type, ...) ({\
    _return_type _tmp_func(__VA_ARGS__) _code\
    &_tmp_func;\
})

/*
NOT YET IMPLEMENTED
*/
#define LIST_PUSH_BACK(_type, _root_p, ...) ({\
    list_##_type *_tmp = _root_p;\
    typeof(_type) _args[] = {__VA_ARGS__};\
    for(uint i = 0;i < sizeof(_args)/sizeof(_type);i++){\
        list_push_back_##_type(_tmp, _args[i]);\
    }\
    _tmp;\
})

/*
Executes function snippet for all elements in a list
*/
#define LIST_FOR_ALL(_type, _root_p_p, _code) {\
    void tmp_func_##_type(_type *element_p){\
        _code\
    }\
    list_for_all_##_type(root, &tmp_func_##_type);\
}

#define LIST_DECLARE_H(_type)\
    typedef struct _list_node_##_type *list_##_type;\
    typedef struct _list_node_##_type list_node_##_type;

#define LIST_DEFINE_H(_type)\
    typedef struct _list_node_##_type list_node_##_type;\
    typedef struct _list_node_##_type *list_##_type;\
    struct _list_node_##_type{\
        struct _list_node_##_type *next;\
        _type element;\
    };\
    \
    list_node_##_type *list_malloc_##_type(_type element);\
    list_node_##_type *list_push_back_##_type(list_##_type *root, _type element);\
    void list_pop_back_##_type(list_##_type *root);\
    list_node_##_type *list_node_at_##_type(list_##_type *root, uint index);\
    _type *list_element_at_##_type(list_##_type *root, uint index);\
    uint list_size_##_type(list_##_type *root);\
    void list_pop_at_##_type(list_##_type *root, uint index);\
    void list_free_##_type(list_##_type *root);\
    void list_for_all_##_type(list_##_type *root, void (*func)(_type*))

#define LIST_DEFINE_C(_type)\
    list_node_##_type *list_malloc_##_type(_type element){\
        return list_push_back_##_type(NULL, element);\
    }\
    list_node_##_type *list_push_back_##_type(list_##_type *root, _type element){\
        if(root == NULL){\
            list_node_##_type *tmp = malloc(sizeof(list_##_type));\
            tmp->element = element;\
            tmp->next = NULL;\
            return tmp;\
        }\
        else if((*root) == NULL){\
            *root = malloc(sizeof(list_##_type));\
            (*root)->next = NULL;\
            (*root)->element = element;\
            return *root;\
        }\
        else{\
            list_node_##_type *tmp = *root;\
            while(tmp->next != NULL)\
                tmp = tmp->next;\
            tmp->next = malloc(sizeof(list_##_type));\
            tmp->next->next = NULL;\
            tmp->next->element = element;\
            return tmp->next;\
        }\
    }\
    void list_pop_back_##_type(list_##_type *root){\
        if(root == NULL) return;\
        else if((*root)->next == NULL){\
            free(*root);\
            root = NULL;\
        }\
        else{\
            list_node_##_type *tmp = *root;\
            while(tmp->next->next != NULL){\
                tmp = tmp->next;\
            }\
            free(tmp->next);\
            tmp->next = NULL;\
        }\
        return ;\
    }\
    list_node_##_type *list_node_at_##_type(list_##_type *root, uint index){\
        if(index >= list_size_##_type(root)) return NULL;\
        else{\
            list_node_##_type *tmp = *root;\
            for(uint i = 0;i < index;i++) tmp = tmp->next;\
            return tmp;\
        }\
    }\
    _type *list_element_at_##_type(list_##_type *root, uint index){\
        list_node_##_type *tmp = list_node_at_##_type(root, index);\
        if(tmp == NULL) return NULL;\
        else return &(tmp->element);\
    }\
    uint list_size_##_type(list_##_type *root){\
        list_node_##_type *tmp = *root;\
        uint counter = 0;\
        while(tmp != NULL){\
            counter++;\
            tmp = tmp->next;\
        }\
        return counter;\
    }\
    void list_pop_at_##_type(list_##_type *root, uint index){\
        if(index >= list_size_##_type(root)) return ;\
        else{\
            if(index == 0){\
                list_node_##_type *tmp = *root;\
                *root = tmp->next;\
                free(tmp);\
            }\
            else{\
                list_node_##_type *tmp1 = list_node_at_##_type(root, index-1);\
                list_node_##_type *tmp2 = tmp1->next;\
                tmp1->next = tmp2->next;\
                free(tmp2);\
            }\
            return ;\
        }\
    }\
    void list_free_##_type(list_##_type *root){\
        if(root != NULL){\
            list_node_##_type *tmp1 = *root, *tmp2 = *root;\
            while(tmp1->next != NULL){\
                tmp1 = tmp1->next;\
                free(tmp2);\
                tmp2 = tmp1;\
            }\
            free(tmp2);\
        }\
        return ;\
    }\
    void list_for_all_##_type(list_##_type *root, void (*func)(_type*)){\
        list_node_##_type *tmp = *root;\
        while(tmp != NULL){\
            func(&(tmp->element));\
            tmp = tmp->next;\
        }\
    }


#endif //LIST_H
