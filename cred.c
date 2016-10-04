#include "php_git2.h"
#include "php_git2_priv.h"
#include "cred.h"

/* {{{ proto long git_cred_has_username(resource $cred)
 */
PHP_FUNCTION(git_cred_has_username)
{
	int result = 0;
	zval *cred = NULL;
	php_git2_t *_cred = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &cred) == FAILURE) {
		return;
	}

	if ((_cred = (php_git2_t *) zend_fetch_resource(Z_RES_P(cred), PHP_GIT2_RESOURCE_NAME, git2_resource_handle)) == NULL) {
	    RETURN_FALSE;
	}

	result = git_cred_has_username(PHP_GIT2_V(_cred, cred));
	RETURN_BOOL(result);
}
/* }}} */

/* {{{ proto resource git_cred_userpass_plaintext_new(string $username, string $password)
 */
PHP_FUNCTION(git_cred_userpass_plaintext_new)
{
	php_git2_t *result = NULL;
	git_cred *out = NULL;
	char *username = NULL, *password = NULL;
	int username_len = 0, password_len = 0, error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ss", &username, &username_len, &password, &password_len) == FAILURE) {
		return;
	}

	error = git_cred_userpass_plaintext_new(&out, username, password);
	if (php_git2_check_error(error, "git_cred_userpass_plaintext_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_CRED, out, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */


/* {{{ proto resource git_cred_ssh_key_new(string $username, string $publickey, string $privatekey, string $passphrase)
 */
PHP_FUNCTION(git_cred_ssh_key_new)
{
	php_git2_t *result = NULL;
	git_cred *out = NULL;
	char *username = NULL, *publickey = NULL, *privatekey = NULL, *passphrase = NULL;
	int username_len = 0, publickey_len = 0, privatekey_len = 0, passphrase_len = 0, error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ssss", &username, &username_len, &publickey, &publickey_len, &privatekey, &privatekey_len, &passphrase, &passphrase_len) == FAILURE) {
		return;
	}

	error = git_cred_ssh_key_new(&out, username, publickey, privatekey, passphrase);
	if (php_git2_check_error(error, "git_cred_ssh_key_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_CRED, out, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */



/* {{{ proto resource git_cred_ssh_custom_new(username, publickey, publickey_len, sign_fn, sign_data)
*/
PHP_FUNCTION(git_cred_ssh_custom_new)
{

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_cred_ssh_custom_new not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"ssr", &username, &username_len, &publickey, &publickey_len, &publickey_len, &sign_fn, &sign_data) == FAILURE) {
//		return;
//	}
//	if ((_username = (php_git2_t *) zend_fetch_resource(Z_RES_P(username), PHP_GIT2_RESOURCE_NAME, git2_resource_handle)) == NULL) { 		RETURN_FALSE;     };
}

/* {{{ proto resource git_cred_default_new()
 */
PHP_FUNCTION(git_cred_default_new)
{
	php_git2_t *result = NULL;
	git_cred *out = NULL;
	int error = 0;

	error = git_cred_default_new(&out);
	if (php_git2_check_error(error, "git_cred_default_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_CRED, out, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

