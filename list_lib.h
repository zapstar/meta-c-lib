#ifndef __LIST_LIB_H__
#define __LIST_LIB_H__

/*///////////////////////////////////////////////////////////////////////////*/
/* Meta structure definitions                                                */
/*///////////////////////////////////////////////////////////////////////////*/

/* List Node structure's name */
#define DEF_NODE(x) struct x##_node_s
/* List Node name */
#define NODE(x) x##_node_t
/* Field name for nde's next pointer */
#define NODE_NEXT(x) x##_next
/* Field name for node's PTPN pointer */
#define NODE_PTPN(x) x##_ptpn
/* List Node definition */
#define DEFINE_NODE(x) \
    typedef DEF_NODE(x) { \
        DEF_NODE(x)  *NODE_NEXT(x); \
        DEF_NODE(x) **NODE_PTPN(x); \
    } NODE(x)

/* List structure's name */
#define DEF_LIST(x) struct x##_list_s
/* List name */
#define LIST(x) x##_list_t
/* Field name for the first element in the list */
#define LIST_FIRST(x) x##_first
/* Field name for the last element in the list */
#define LIST_LAST(x) x##_last

/* List Definition */
#define DEFINE_LIST(x) \
    DEFINE_NODE(x); \
    typedef DEF_LIST(x) { \
        DEF_NODE(x) *LIST_FIRST(x); \
        DEF_NODE(x) *LIST_LAST(x); \
        int size; \
    } LIST(x)
/*///////////////////////////////////////////////////////////////////////////*/


/*///////////////////////////////////////////////////////////////////////////*/
/* Meta function definitions                                                 */
/*///////////////////////////////////////////////////////////////////////////*/

/* List initiailize */
#define DEFINE_LIST_INIT(x) \
    void x##_list_init(LIST(x) *l)

/* List add */
#define DEFINE_LIST_ADD(x) \
    void x##_list_add(LIST(x) *l, NODE(x) *node)

/* List Insert */
#define DEFINE_LIST_INSERT(x) \
    void x##_list_insert(LIST(x) *l, NODE(x) *node, NODE(x) *new_node)

/* List Delete */
#define DEFINE_LIST_DELETE(x) \
    void x##_list_delete(LIST(x) *l, NODE(x) *node)

/* List Get (Pop one element out of the list) */
#define DEFINE_LIST_GET(x) \
    NODE(x) *x##_list_get(LIST(x) *l)

/*///////////////////////////////////////////////////////////////////////////*/


/*///////////////////////////////////////////////////////////////////////////*/
/* Meta function call macros                                                 */
/*///////////////////////////////////////////////////////////////////////////*/

#define LIST_INIT(x, l) x##_list_init(l)

#define LIST_ADD(x, l, n) x##_list_add(l, n)

#define LIST_INSERT(x, l, m, n) x##_list_insert(l, m, n)

#define LIST_DELETE(x, l, n) x##_list_delete(l, n)

#define LIST_GET(x, l) x##_list_get(l)

/*///////////////////////////////////////////////////////////////////////////*/


/*///////////////////////////////////////////////////////////////////////////*/
/* Meta function declarations                                                */
/*///////////////////////////////////////////////////////////////////////////*/

/* List Init */
#define DECLARE_LIST_INIT(x) \
    DEFINE_LIST_INIT(x) { \
        l->LIST_FIRST(x) = 0; \
        l->LIST_LAST(x) = 0; \
        l->size = 0; \
    }

/* List Addition */
#define DECLARE_LIST_ADD(x) \
    DEFINE_LIST_ADD(x) { \
        if (!l || !node) \
            return; \
        if (!l->size) { \
            l->LIST_FIRST(x) = node; \
            l->LIST_LAST(x) = node; \
            l->size = 1; \
            node->NODE_NEXT(x) = 0; \
            node->NODE_PTPN(x) = &l->LIST_FIRST(x); \
        } else { \
            l->LIST_LAST(x)->NODE_NEXT(x) = node; \
            node->NODE_PTPN(x) = &l->LIST_LAST(x)->NODE_NEXT(x); \
            node->NODE_NEXT(x) = 0; \
            l->LIST_LAST(x) = node; \
            l->size++; \
        } \
    }

/* List insertion */
#define DECLARE_LIST_INSERT(x) \
    DEFINE_LIST_INSERT(x) { \
        if (!l || !new_node) \
            return; \
        if (!node) { \
            LIST_ADD(x, l, new_node); \
        } else { \
            new_node->NODE_NEXT(x) = node; \
            *node->NODE_PTPN(x) = new_node; \
            new_node->NODE_PTPN(x) = node->NODE_PTPN(x); \
            node->NODE_PTPN(x) = &new_node->NODE_NEXT(x); \
            l->size++; \
        } \
    }

/* List Deletion */
#define NODE_PTPN_TO_NODE(e) (e)
#define DECLARE_LIST_DELETE(x) \
    DEFINE_LIST_DELETE(x) { \
        if (!l || !node) { \
            return; \
        } \
        if (l->LIST_LAST(x) == node) \
        { \
            if (l->LIST_FIRST(x) == node) \
            { \
                l->LIST_FIRST(x) = l->LIST_LAST(x) = 0; \
            } \
            else \
            { \
                l->LIST_LAST(x) = \
                        (NODE(x) *) NODE_PTPN_TO_NODE(node->NODE_PTPN(x)); \
            } \
        } \
        else \
        { \
            node->NODE_NEXT(x)->NODE_PTPN(x) = node->NODE_PTPN(x); \
        } \
        *node->NODE_PTPN(x) = node->NODE_NEXT(x); \
        l->size--; \
        if (!l->size) \
        { \
            l->LIST_FIRST(x) = l->LIST_LAST(x) = 0; \
        } \
        node->NODE_NEXT(x) = 0; \
        node->NODE_PTPN(x) = 0; \
    }

/* List get */
#define DECLARE_LIST_GET(x) \
    DEFINE_LIST_GET(x) { \
        NODE(x) *node; \
        if (!l->size) \
        { \
            return 0; \
        } \
        node = l->LIST_FIRST(x); \
        if (node->NODE_NEXT(x)) { \
            l->LIST_FIRST(x) = node->NODE_NEXT(x); \
            node->NODE_NEXT(x)->NODE_PTPN(x) = &l->LIST_FIRST(x); \
        } else { \
            l->LIST_FIRST(x) = l->LIST_LAST(x) = 0; \
        } \
        l->size--; \
        node->NODE_NEXT(x) = 0; \
        node->NODE_PTPN(x) = 0; \
        return node; \
    }

/*///////////////////////////////////////////////////////////////////////////*/
#endif /* __LIST_LIB_H__ */
