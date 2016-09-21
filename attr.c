#include "php_git2.h"
#include "php_git2_priv.h"
#include "attr.h"

/* {{{ proto resource git_attr_value(string $attr)
 */
PHP_FUNCTION(git_attr_value)
{
	git_attr_t result;
	char *attr = NULL;
	int attr_len = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &attr, &attr_len) == FAILURE) {
		return;
	}
	
	result = git_attr_value(attr);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_attr_get(resource $repo, long $flags, string $path, string $name)
 */
PHP_FUNCTION(git_attr_get)
{
	php_git2_t *_repo = NULL;
	char *value_out = NULL, *path = NULL, *name = NULL;
	zval *repo = NULL;
	long flags = 0;
	int path_len = 0, name_len = 0, error = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rlss", &repo, &flags, &path, &path_len, &name, &name_len) == FAILURE) {
		return;
	}
	
	if ((_repo = (php_git2_t *) zend_fetch_resource(Z_RES_P(repo), PHP_GIT2_RESOURCE_NAME, git2_resource_handle)) == NULL) {
	    RETURN_FALSE;
	}

	error = git_attr_get(&value_out, PHP_GIT2_V(_repo, repository), flags, path, name);
	if (php_git2_check_error(error, "git_attr_get" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	RETURN_STRING(value_out);
}
/* }}} */

/* {{{ proto resource git_attr_get_many(resource $repo, long $flags, string $path, long $num_attr, string $names)
 */
PHP_FUNCTION(git_attr_get_many)
{
	php_git2_t *_repo = NULL;
	char *values_out = NULL, *path = NULL;
	zval *repo = NULL, *names = NULL;
	long flags = 0, num_attr = 0;
	int path_len = 0, error = 0;

	/* TODO(chobie): write array to const char** conversion */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rlsla", &repo, &flags, &path, &path_len, &num_attr, &names) == FAILURE) {
		return;
	}
	
	if ((_repo = (php_git2_t *) zend_fetch_resource(Z_RES_P(repo), PHP_GIT2_RESOURCE_NAME, git2_resource_handle)) == NULL) {
	    RETURN_FALSE;
	}

	/* TODO(chobie): emalloc values_out */
	error = git_attr_get_many(&values_out, PHP_GIT2_V(_repo, repository), flags, path, num_attr, names);
	if (php_git2_check_error(error, "git_attr_get_many" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	RETURN_STRING(values_out);
}
/* }}} */

/* {{{ proto long git_attr_foreach(resource $repo, long $flags, string $path, Callable $callback,  $payload)
 */
PHP_FUNCTION(git_attr_foreach)
{
	int result = 0, path_len = 0;
	zval *repo = NULL, *payload = NULL;
	php_git2_t *_repo = NULL;
	long flags = 0;
	char *path = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rlsfz", &repo, &flags, &path, &path_len, &fci, &fcc, &payload) == FAILURE) {
		return;
	}
	
	if ((_repo = (php_git2_t *) zend_fetch_resource(Z_RES_P(repo), PHP_GIT2_RESOURCE_NAME, git2_resource_handle)) == NULL) {
	    RETURN_FALSE;
	}

	if (php_git2_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	// TODO(chobie): implement this
	//result = git_attr_foreach(PHP_GIT2_V(_repo, repository), flags, path, <CHANGEME>, cb);
	php_git2_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto void git_attr_cache_flush(resource $repo)
 */
PHP_FUNCTION(git_attr_cache_flush)
{
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}

	if ((_repo = (php_git2_t *) zend_fetch_resource(Z_RES_P(repo), PHP_GIT2_RESOURCE_NAME, git2_resource_handle)) == NULL) {
	    RETURN_FALSE;
	}

	git_attr_cache_flush(PHP_GIT2_V(_repo, repository));
}
/* }}} */

/* {{{ proto long git_attr_add_macro(resource $repo, string $name, string $values)
 */
PHP_FUNCTION(git_attr_add_macro)
{
	int result = 0, name_len = 0, values_len = 0;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *name = NULL, *values = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rss", &repo, &name, &name_len, &values, &values_len) == FAILURE) {
		return;
	}

	if ((_repo = (php_git2_t *) zend_fetch_resource(Z_RES_P(repo), PHP_GIT2_RESOURCE_NAME, git2_resource_handle)) == NULL) {
	    RETURN_FALSE;
	}

	result = git_attr_add_macro(PHP_GIT2_V(_repo, repository), name, values);
	RETURN_LONG(result);
}
/* }}} */

