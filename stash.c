#include "php_git2.h"
#include "php_git2_priv.h"
#include "stash.h"

/* {{{ proto resource git_stash_save(resource $repo, array $stasher, string $message, long $flags)
 */
PHP_FUNCTION(git_stash_save)
{
	php_git2_t *_repo = NULL;
	git_oid out = {0};
	zval *repo = NULL, *stasher = NULL;
	char *message = NULL;
	int message_len = 0, error = 0;
	long flags = 0;
	char buf[GIT2_OID_HEXSIZE] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rasl", &repo, &stasher, &message, &message_len, &flags) == FAILURE) {
		return;
	}
	
	if ((_repo = (php_git2_t *) zend_fetch_resource(Z_RES_P(repo), PHP_GIT2_RESOURCE_NAME, git2_resource_handle)) == NULL) {
		RETURN_FALSE;
	}

	error = git_stash_save(&out, PHP_GIT2_V(_repo, repository), stasher, message, flags);
	if (php_git2_check_error(error, "git_stash_save" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	git_oid_fmt(buf, &out);
	RETURN_STRING(buf);
}
/* }}} */

/* {{{ proto long git_stash_foreach(resource $repo, Callable $callback,  $payload)
 */
PHP_FUNCTION(git_stash_foreach)
{
	int result = 0;
	zval *repo = NULL, *payload = NULL;
	php_git2_t *_repo = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rfz", &repo, &fci, &fcc, &payload) == FAILURE) {
		return;
	}
	
	if ((_repo = (php_git2_t *) zend_fetch_resource(Z_RES_P(repo), PHP_GIT2_RESOURCE_NAME, git2_resource_handle)) == NULL) {
		RETURN_FALSE;
	}

	if (php_git2_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	result = git_stash_foreach(PHP_GIT2_V(_repo, repository), php_git2_stash_cb, cb);
	php_git2_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_stash_drop(resource $repo, long $index)
 */
PHP_FUNCTION(git_stash_drop)
{
	int result = 0;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	long index = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &repo, &index) == FAILURE) {
		return;
	}
	
	if ((_repo = (php_git2_t *) zend_fetch_resource(Z_RES_P(repo), PHP_GIT2_RESOURCE_NAME, git2_resource_handle)) == NULL) {
		RETURN_FALSE;
	}

	result = git_stash_drop(PHP_GIT2_V(_repo, repository), index);
	RETURN_LONG(result);
}
/* }}} */

