#ifndef _POOL_H_
#define _POOL_H_

#define LIST_PREPEND(_head, _item) do {\
  _item->next = _head;\
  _head = _item;\
}while(0)

#define LIST_POP(_head, _item) do {\
  _item = _head;\
  _head = _head->next;\
}while(0)

#define DECLARE_STATIC_POOL(_type) DECLARE_POOL_EX(static, #_type)
#define DECLARE_POOL(_type) DECLARE_POOL_EX(, _type)

#define IMPLEMENT_SIMPLE_STATIC_POOL(_type, _max)\
  static void _type##_init(struct _type *ctx){}\
  static void _type##_deinit(struct _type *ctx){}\
  IMPLEMENT_POOL_EX(static, _type, _max)
#define IMPLEMENT_STATIC_POOL(_type, _max) IMPLEMENT_POOL_EX(static, _type, _max)
#define IMPLEMENT_POOL(_type, _max) IMPLEMENT_POOL_EX(, _type, _max)

#define DECLARE_POOL_EX(_static, _type)\
_static struct _type *_type##_new();\
_static void _type##_del(struct _type *ctx);\
_static void _type##_free_all();

#define IMPLEMENT_POOL_EX(_static, _type, _max)\
static struct _type *_type##_pool = NULL;\
static int _type##_pool_size = 0;\
_static struct _type *_type##_new() {\
  struct _type *ctx = NULL;\
  if (_type##_pool) {\
    LIST_POP(_type##_pool, ctx);\
    _type##_pool_size--;\
  } else {\
    ctx = malloc(sizeof(struct _type));\
  }\
  _type##_init(ctx);\
  ctx->next = NULL;\
  return ctx;\
}\
_static void _type##_del(struct _type *ctx) {\
  _type##_deinit(ctx);\
  if (_type##_pool_size < _max) {\
    LIST_PREPEND(_type##_pool, ctx);\
    _type##_pool_size++;\
  }\
}\
_static void _type##_free_all() {\
  struct _type *r = _type##_pool;\
  while (r) {\
    _type##_pool = r->next;\
    free(r);\
    r = _type##_pool;\
  }\
}
#endif /* _POOL_H_ */

