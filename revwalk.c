#include "php_git2.h"
#include "php_git2_priv.h"
#include "revwalk.h"

/* {{{ proto resource git_revwalk_new(resource $repo)
 */
PHP_FUNCTION(git_revwalk_new)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_revwalk *out = NULL;
	zval *repo = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_revwalk_new(&out, PHP_GIT2_V(_repo, repository));
	if (php_git2_check_error(error, "git_revwalk_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_REVWALK, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */


/* {{{ proto void git_revwalk_reset(walker)
*/
PHP_FUNCTION(git_revwalk_reset)
{
	zval *walker;
	php_git2_t *_walker;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &walker) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_walker, php_git2_t*, &walker, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	git_revwalk_reset(PHP_GIT2_V(_walker, revwalk));
}

/* {{{ proto long git_revwalk_push(resource $walk, string $id)
 */
PHP_FUNCTION(git_revwalk_push)
{
	int result = 0, id_len = 0;
	zval *walk = NULL;
	php_git2_t *_walk = NULL;
	char *id = NULL;
	git_oid __id = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &walk, &id, &id_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__id, id, id_len)) {
		RETURN_FALSE;
	}
	result = git_revwalk_push(PHP_GIT2_V(_walk, revwalk), &__id);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_revwalk_push_glob(resource $walk, string $glob)
 */
PHP_FUNCTION(git_revwalk_push_glob)
{
	int result = 0, glob_len = 0;
	zval *walk = NULL;
	php_git2_t *_walk = NULL;
	char *glob = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &walk, &glob, &glob_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_revwalk_push_glob(PHP_GIT2_V(_walk, revwalk), glob);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_revwalk_push_head(walk)
*/
PHP_FUNCTION(git_revwalk_push_head)
{
	zval *walk;
	php_git2_t *_walk;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &walk) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	error = git_revwalk_push_head(PHP_GIT2_V(_walk, revwalk));
	if (php_git2_check_error(error, "git_revwalk_push_head" TSRMLS_CC)) {
		RETURN_FALSE;
	} else {
		RETURN_TRUE;
	}
}

/* {{{ proto long git_revwalk_hide(walk, commit_id)
*/
PHP_FUNCTION(git_revwalk_hide)
{
	zval *walk;
	php_git2_t *_walk;
	char *commit_id = {0};
	int commit_id_len;
	git_oid oid;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &walk, &commit_id, &commit_id_len) == FAILURE) {
		return;
	}
	if (git_oid_fromstrn(&oid, commit_id, commit_id_len) != GIT_OK) {
		return;
	}

	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_revwalk_hide(PHP_GIT2_V(_walk, revwalk), &oid);

	if (php_git2_check_error(error, "git_revwalk_hide" TSRMLS_CC)) {
		RETURN_FALSE;
	} else {
		RETURN_TRUE;
	}

}

/* {{{ proto long git_revwalk_hide_glob(resource $walk, string $glob)
 */
PHP_FUNCTION(git_revwalk_hide_glob)
{
	int result = 0, glob_len = 0;
	zval *walk = NULL;
	php_git2_t *_walk = NULL;
	char *glob = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &walk, &glob, &glob_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_revwalk_hide_glob(PHP_GIT2_V(_walk, revwalk), glob);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_revwalk_hide_head(walk)
*/
PHP_FUNCTION(git_revwalk_hide_head)
{
	zval *walk;
	php_git2_t *_walk;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &walk) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	error = git_revwalk_hide_head(PHP_GIT2_V(_walk, revwalk));
	if (php_git2_check_error(error, "git_revwalk_hide_head" TSRMLS_CC)) {
		RETURN_FALSE;
	} else {
		RETURN_TRUE;
	}
}

/* {{{ proto long git_revwalk_push_ref(resource $walk, string $refname)
 */
PHP_FUNCTION(git_revwalk_push_ref)
{
	int result = 0, refname_len = 0;
	zval *walk = NULL;
	php_git2_t *_walk = NULL;
	char *refname = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &walk, &refname, &refname_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_revwalk_push_ref(PHP_GIT2_V(_walk, revwalk), refname);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_revwalk_hide_ref(resource $walk, string $refname)
 */
PHP_FUNCTION(git_revwalk_hide_ref)
{
	int result = 0, refname_len = 0;
	zval *walk = NULL;
	php_git2_t *_walk = NULL;
	char *refname = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &walk, &refname, &refname_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_revwalk_hide_ref(PHP_GIT2_V(_walk, revwalk), refname);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto string git_revwalk_next(walk)
*/
PHP_FUNCTION(git_revwalk_next)
{
	zval *walk;
	php_git2_t *_walk;
	git_oid id = {0};
	char out[GIT2_OID_HEXSIZE] = {0};
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &walk) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_revwalk_next(&id, PHP_GIT2_V(_walk, revwalk));
	if (error == GIT_ITEROVER) {
		RETURN_FALSE;
	}

	git_oid_fmt(out, &id);
	RETURN_STRING(out);
}

/* {{{ proto void git_revwalk_sorting(walk, sort_mode)
*/
PHP_FUNCTION(git_revwalk_sorting)
{
	zval *walk;
	php_git2_t *_walk;
	long sort_mode = GIT_SORT_NONE;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &walk, &sort_mode) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	git_revwalk_sorting(PHP_GIT2_V(_walk, revwalk), sort_mode);
}

/* {{{ proto long git_revwalk_push_range(resource $walk, string $range)
 */
PHP_FUNCTION(git_revwalk_push_range)
{
	int result = 0, range_len = 0;
	zval *walk = NULL;
	php_git2_t *_walk = NULL;
	char *range = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &walk, &range, &range_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_revwalk_push_range(PHP_GIT2_V(_walk, revwalk), range);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto void git_revwalk_simplify_first_parent(walk)
*/
PHP_FUNCTION(git_revwalk_simplify_first_parent)
{
	zval *walk;
	php_git2_t *_walk;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &walk) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	git_revwalk_simplify_first_parent(PHP_GIT2_V(_walk, revwalk));
}

/* {{{ proto void git_revwalk_free(resource $walk)
 */
PHP_FUNCTION(git_revwalk_free)
{
	zval *walk = NULL;
	php_git2_t *_walk = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &walk) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_walk)) {
		git_revwalk_free(PHP_GIT2_V(_walk, revwalk));
		GIT2_SHOULD_FREE(_walk) = 0;
	};
	zval_ptr_dtor(&walk);
}
/* }}} */


/* {{{ proto resource git_revwalk_repository(walk)
*/
PHP_FUNCTION(git_revwalk_repository)
{
	zval *walk;
	php_git2_t *_walk, *result;
	git_repository *repository;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &walk) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	repository = git_revwalk_repository(PHP_GIT2_V(_walk, revwalk));
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_REPOSITORY, repository, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}

	ZVAL_RESOURCE(return_value, result->resource_id);
}

