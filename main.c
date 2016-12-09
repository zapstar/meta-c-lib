#include "list_lib.h"

DEFINE_LIST(tt);

DEFINE_LIST_INIT(tt);
DEFINE_LIST_GET(tt);
DEFINE_LIST_ADD(tt);
DEFINE_LIST_INSERT(tt);
DEFINE_LIST_DELETE(tt);

DECLARE_LIST_INIT(tt)
DECLARE_LIST_ADD(tt)
DECLARE_LIST_INSERT(tt)
DECLARE_LIST_DELETE(tt)
DECLARE_LIST_GET(tt)

int main()
{
    NODE(tt) n1, n2, *n;
    LIST(tt) tl;

    LIST_INIT(tt, &tl);
    LIST_ADD(tt, &tl, &n1);
    LIST_INSERT(tt, &tl, 0, &n2);
    LIST_DELETE(tt, &tl, &n2);
    n = LIST_GET(tt, &tl);
    return !(n == &n1);
}
