/*
 * PHP Libgit2 Extension
 *
 * https://github.com/libgit2/php-git
 *
 * Copyright 2014 Shuhei Tanuma.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef PHP_GIT2_PRIV_H
#define PHP_GIT2_PRIV_H

extern int git2_resource_handle;

#if PHP_VERSION_ID>=50399
#define PHP_GIT2_LIST_INSERT(type, handle) zend_list_insert(type, handle TSRMLS_CC)
#else
#define PHP_GIT2_LIST_INSERT(type, handle) zend_list_insert(type, handle)
#endif

#  if ZEND_MODULE_API_NO >= 20100525
#  define PHP_GIT2_STD_CREATE_OBJECT(STRUCT_NAME) \
        STRUCT_NAME *object;\
        \
        object = (STRUCT_NAME*)ecalloc(1, sizeof(*object));\
        zend_object_std_init(&object->zo, ce TSRMLS_CC);\
        object_properties_init(&object->zo, ce);\
        \
        retval.handle = zend_objects_store_put(object,\
                (zend_objects_store_dtor_t)zend_objects_destroy_object,\
                (zend_objects_free_object_storage_t) STRUCT_NAME##_free_storage ,\
        NULL TSRMLS_CC);\
        retval.handlers = zend_get_std_object_handlers();
#  else
#  define PHP_GIT2_STD_CREATE_OBJECT(STRUCT_NAME) \
        STRUCT_NAME *object;\
        zval *tmp = NULL;\
        \
        object = (STRUCT_NAME*)ecalloc(1, sizeof(*object));\
        zend_object_std_init(&object->zo, ce TSRMLS_CC);\
        zend_hash_copy(object->zo.properties, &ce->default_properties, (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *)); \
        \
        retval.handle = zend_objects_store_put(object,\
                (zend_objects_store_dtor_t)zend_objects_destroy_object,\
                (zend_objects_free_object_storage_t) STRUCT_NAME##_free_storage ,\
        NULL TSRMLS_CC);\
        retval.handlers = zend_get_std_object_handlers();
#  endif

#define PHP_GIT2_V(git2, type) git2->v.type
#define GIT2_RVAL_P(git2) git2->resource_id
#define GIT2_SHOULD_FREE(git2) git2->should_free_v

#define PHP_GIT2_MAKE_RESOURCE(val) \
do {\
	val = (php_git2_t *)emalloc(sizeof(php_git2_t));\
	if (!val) {\
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "emalloc failed");\
		RETURN_FALSE;\
	}\
	val->should_free_v = 0;\
	val->type = 0;\
	val->mutable = 0;\
} while (0);\


#define PHP_GIT2_MAKE_RESOURCE_NOCHECK(val) \
do {\
	val = (php_git2_t *)emalloc(sizeof(php_git2_t));\
	val->should_free_v = 0;\
	val->type = 0;\
	val->mutable = 0;\
} while (0);\

#define GIT2_OID_HEXSIZE (GIT_OID_HEXSZ+1)
#define GIT2_BUFFER_SIZE 512

int php_git2_make_resource(php_git2_t **out, enum php_git2_resource_type type, void *resource, int should_free TSRMLS_DC);

#include "helper.h"

#endif