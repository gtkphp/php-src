/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Sergio de Vasconcelos                                        |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_GTKML_H
#define PHP_GTKML_H

extern zend_module_entry gtkml_module_entry;
#define phpext_gtkml_ptr &gtkml_module_entry

#define PHP_GTKML_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_GTKML_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_GTKML_API __attribute__ ((visibility("default")))
#else
#	define PHP_GTKML_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

typedef struct _gtk_widget {
    GtkWidget *ptr;
    // parent;
    // previousSibling;
    // nextSibling;
    // children;

    //php_libxml_ref_obj *document;
    HashTable *prop_handler;
    zend_object std;
} gtk_widget;

zend_object *gtk_widgets_new(zend_class_entry *class_type);
gtk_widget *php_gtk_widget_from_obj(zend_object *obj);


gtk_widget *gtkml_window_new(char *attrs[]);

/*
  	Declare any global variables you may need between the BEGIN
	and END macros here:

ZEND_BEGIN_MODULE_GLOBALS(gtkml)
	zend_long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(gtkml)
*/

/* Always refer to the globals in your function as GTKML_G(variable).
   You are encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/
#define GTKML_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(gtkml, v)

#if defined(ZTS) && defined(COMPILE_DL_GTKML)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif	/* PHP_GTKML_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
