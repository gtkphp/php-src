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
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gtk/gtk.h>

#include "php.h"
#include "php_ini.h"
#include "zend_interfaces.h"
#include "ext/standard/info.h"
#include "php_gtkml.h"



/* If you declare any globals in php_gtkml.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(gtkml)
*/

/* True global resources - no need for thread safety here */
static int le_gtkml;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("gtkml.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_gtkml_globals, gtkml_globals)
    STD_PHP_INI_ENTRY("gtkml.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_gtkml_globals, gtkml_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_gtkml_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_gtkml_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "gtkml", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_gtkml_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_gtkml_init_globals(zend_gtkml_globals *gtkml_globals)
{
	gtkml_globals->global_value = 0;
	gtkml_globals->global_string = NULL;
}
*/
/* }}} */

#define UNUSED 0

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_widget___construct, UNUSED, 0, 0)
    ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_gtk_window___construct, UNUSED, 0, 0)
    ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()


//ZEND_BEGIN_ARG_INFO(arginfo_gtk_window_scale, 0)
//    ZEND_ARG_INFO(1, x) // pass by reference
//ZEND_END_ARG_INFO()

#include <gtk/gtk.h>

/* {{{ proto void Gtk\Widget::__construct(); */
PHP_METHOD(Gtk_Widget, __construct)
{
    g_print("Gtk_Widget, __construct\n");
    /*
    GtkWidget *
    gtk_widget_new (GType type,
                    const gchar *first_property_name,
                    ...);
    */


}
/* }}} end Gtk\Widget::__construct */


#ifdef PHP_WIN32
#	ifdef DOM_EXPORTS
#		define PHP_GTK_EXPORT __declspec(dllexport)
#	elif !defined(DOM_LOCAL_DEFINES) /* Allow to counteract LNK4049 warning. */
#		define PHP_GTK_EXPORT __declspec(dllimport)
#   else
#		define PHP_GTK_EXPORT
#	endif /* DOM_EXPORTS */
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_GTK_EXPORT __attribute__ ((visibility("default")))
#elif defined(PHPAPI)
#   define PHP_GTK_EXPORT PHPAPI
#else
#   define PHP_GTK_EXPORT
#endif

PHP_GTK_EXPORT /*extern*/ zend_class_entry *gtk_widget_class_entry;

PHP_GTK_EXPORT /*extern*/ zend_class_entry *gtk_window_class_entry = NULL;

static void
php_gtk_destroy (GtkWidget *window,
                 gpointer   user_data){
    gtk_widget *gobj = (gtk_widget*)user_data;

    //@TODO: loop tree
    efree((gpointer)gobj);
}

/* {{{ proto void Gtk\Window::__construct([long type]); */
PHP_METHOD(Gtk_Window, __construct)
{
    // TODO arg
    //g_print("Gtk_Window, __construct(%p)\n", gtk_window_class_entry);



    zend_long type = GTK_WINDOW_TOPLEVEL; // default value
    //gtkml_window_t *window = Z_GTKML_WINDOW_P(ZEND_THIS);
    //gtk_widget *intern = Z_GTKOBJ_P();

    //zval *self = getThis();
    zend_object *zobj = Z_OBJ_P(getThis());
    gtk_widget *gobj = php_gtk_widget_from_obj(zobj);
    zend_class_entry *ce = Z_OBJCE_P(getThis());// gtk_window_class_entry/ gtk_widget_class_entry

#if 0
    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
        Z_PARAM_LONG(type)
    ZEND_PARSE_PARAMETERS_END();
#else

    if (zend_parse_parameters_throw(ZEND_NUM_ARGS(),
                                    "l", &type) == FAILURE) {
        return;
    }
#endif

    // TODO check is is toplevel, because we can create multiple window
    GtkWidget *window = gtk_window_new(type);
    gtk_window_set_title(GTK_WINDOW(window), "GTK+PHP Version 0.0.1");
    gtk_widget_show(window);
    g_signal_connect(window, "destroy", G_CALLBACK(php_gtk_destroy), gobj);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gobj->ptr = window;

    //gtk_window_set_interactive_debugging(TRUE);

    /*
    if (ZEND_NUM_ARGS() > 0) {
        zend_update_property_long(ce, getThis(),
            "type", sizeof("type")-1, type);
    }
    */


}
/* }}} end Gtk\Window::__construct */


static const zend_function_entry gtk_widget_methods[] = {
    PHP_ME(Gtk_Widget, __construct, arginfo_gtk_widget___construct, ZEND_ACC_PUBLIC)
    //PHP_ME(GtkWindow, scale, arginfo_gtk_window_scale, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

static const zend_function_entry gtk_window_methods[] = {
    PHP_ME(Gtk_Window, __construct, arginfo_gtk_window___construct, ZEND_ACC_PUBLIC)
    //PHP_ME(GtkWindow, scale, arginfo_gtk_window_scale, ZEND_ACC_PUBLIC)
    PHP_FE_END
};




zend_object_handlers gtk_widget_handlers;

static HashTable classes;
static HashTable gtk_widget_prop_handlers;
static HashTable gtk_window_prop_handlers;

typedef int (*gtk_read_t)(gtk_widget *obj, zval *retval);
typedef int (*gtk_write_t)(gtk_widget *obj, zval *newval);

typedef struct _gtk_prop_handler {
    gtk_read_t read_func;
    gtk_write_t write_func;
} gtk_prop_handler;

static zend_object_handlers* gtk_get_obj_handlers(void) {
    return &gtk_widget_handlers;
}

static gtk_widget* gtk_widgets_set_class(zend_class_entry *class_type, zend_bool hash_copy) /* {{{ */
{
    gtk_widget *intern = ecalloc(1, sizeof(gtk_widget) + zend_object_properties_size(class_type));
    zend_class_entry *base_class = class_type;
    while ((   base_class->type != ZEND_INTERNAL_CLASS
            || base_class->info.internal.module->module_number != gtkml_module_entry.module_number
           )
           && base_class->parent != NULL) {
        base_class = base_class->parent;
    }

    intern->prop_handler = zend_hash_find_ptr(&classes, base_class->name);

    zend_object_std_init(&intern->std, class_type);

    if (hash_copy) {
        object_properties_init(&intern->std, class_type);
    }

    return intern;
}
/* }}} */

/* {{{ gtk_widgets_new */
zend_object *gtk_widgets_new(zend_class_entry *class_type)
{
    gtk_widget *intern = gtk_widgets_set_class(class_type, 1);
    intern->std.handlers = gtk_get_obj_handlers();
    return &intern->std;
}
/* }}} */


/* {{{ nodeName	string
readonly=yes
URL: http://www.w3.org/TR/2003/WD-DOM-Level-3-Core-20030226/DOM3-Core.html#core-ID-F68D095
Since:
*/
int gtk_widget_name_read(gtk_widget *obj, zval *retval)
{
#if 1

    char *str = g_strdup("WidgetName");
    ZVAL_STRING(retval, str);

#else
    xmlNode *nodep;
    xmlNsPtr ns;
    char *str = NULL;
    xmlChar *qname = NULL;

    nodep = dom_object_get_node(obj);

    if (nodep == NULL) {
        php_dom_throw_error(INVALID_STATE_ERR, 0);
        return FAILURE;
    }

    switch (nodep->type) {
        case XML_ATTRIBUTE_NODE:
        case XML_ELEMENT_NODE:
            ns = nodep->ns;
            if (ns != NULL && ns->prefix) {
                qname = xmlStrdup(ns->prefix);
                qname = xmlStrcat(qname, (xmlChar *) ":");
                qname = xmlStrcat(qname, nodep->name);
                str = (char *) qname;
            } else {
                str = (char *) nodep->name;
            }
            break;
        case XML_NAMESPACE_DECL:
            ns = nodep->ns;
            if (ns != NULL && ns->prefix) {
                qname = xmlStrdup((xmlChar *) "xmlns");
                qname = xmlStrcat(qname, (xmlChar *) ":");
                qname = xmlStrcat(qname, nodep->name);
                str = (char *) qname;
            } else {
                str = (char *) nodep->name;
            }
            break;
        case XML_DOCUMENT_TYPE_NODE:
        case XML_DTD_NODE:
        case XML_PI_NODE:
        case XML_ENTITY_DECL:
        case XML_ENTITY_REF_NODE:
        case XML_NOTATION_NODE:
            str = (char *) nodep->name;
            break;
        case XML_CDATA_SECTION_NODE:
            str = "#cdata-section";
            break;
        case XML_COMMENT_NODE:
            str = "#comment";
            break;
        case XML_HTML_DOCUMENT_NODE:
        case XML_DOCUMENT_NODE:
            str = "#document";
            break;
        case XML_DOCUMENT_FRAG_NODE:
            str = "#document-fragment";
            break;
        case XML_TEXT_NODE:
            str = "#text";
            break;
        default:
            php_error_docref(NULL, E_WARNING, "Invalid Node Type");
    }

    if (str != NULL) {
        ZVAL_STRING(retval, str);
    } else {
        ZVAL_EMPTY_STRING(retval);
    }

    if (qname != NULL) {
        xmlFree(qname);
    }
#endif

    return SUCCESS;

}

/* {{{ type	long
readonly=no
URL: https://developer.gnome.org/gtk3/stable/GtkWindow.html#GtkWindow--type
Since:
*/
int gtk_window_type_read(gtk_widget *obj, zval *retval)
{
    GtkWindowType type;
    g_object_get ((gpointer)obj->ptr,
                  "type", &type,
                  NULL);

    ZVAL_LONG(retval, type);

    return SUCCESS;
}/*}}} */

int gtk_window_type_write(gtk_widget *obj, zval *retval)
{
#if 1

#else
    GtkWindowType type = retval->value.lval;
    g_object_set ((gpointer)obj->ptr,
                  "type", &type,
                  NULL);

    g_print("Try to write an readonly property: %p\n", retval->value.lval);
#endif

    return SUCCESS;
}



// TODO use MACRO like in PHP 8.0
gtk_widget *php_gtk_widget_from_obj(zend_object *obj) {
    return (gtk_widget*)((char*)(obj) - XtOffsetOf(gtk_widget, std));
}

/* {{{ dom_objects_free_storage */
void gtk_widgets_free_storage(zend_object *object)
{
    gtk_widget *intern = php_gtk_widget_from_obj(object);
#if defined(__GNUC__) && __GNUC__ >= 3
    int retcount __attribute__((unused)); /* keep compiler quiet */
#else
    int retcount;
#endif

    zend_object_std_dtor(&intern->std);
// FIXME
#if 0
    if (intern->ptr != NULL ) {

        /*
        if (((xmlNodePtr) ((php_libxml_node_ptr *)intern->ptr)->node)->type != XML_DOCUMENT_NODE && ((xmlNodePtr) ((php_libxml_node_ptr *)intern->ptr)->node)->type != XML_HTML_DOCUMENT_NODE) {
            php_libxml_node_decrement_resource((php_libxml_node_object *) intern);
        } else {
            php_libxml_decrement_node_ptr((php_libxml_node_object *) intern);
            retcount = php_libxml_decrement_doc_ref((php_libxml_node_object *)intern);
        }
        */
        intern->ptr = NULL;
    }
#endif
}
/* }}} */


static zval *gtk_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
    gtk_widget *obj = php_gtk_widget_from_obj(Z_OBJ_P(object));
    zend_string *member_str = zval_get_string(member);
    zval *retval = NULL;

    if (!obj->prop_handler || !zend_hash_exists(obj->prop_handler, member_str)) {
        zend_object_handlers *std_hnd = zend_get_std_object_handlers();
        retval = std_hnd->get_property_ptr_ptr(object, member, type, cache_slot);
    }

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ gtk_read_property */
zval *gtk_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv)
{
    gtk_widget *obj = php_gtk_widget_from_obj(Z_OBJ_P(object));
    zend_string *member_str = zval_get_string(member);
    zval *retval;
    gtk_prop_handler *hnd = NULL;

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member_str);
    } else if (instanceof_function(obj->std.ce, gtk_widget_class_entry)) {
        php_error(E_WARNING, "Couldn't fetch %s. Widget no longer exists", ZSTR_VAL(obj->std.ce->name));
    }

    if (hnd) {
        int ret = hnd->read_func(obj, rv);
        if (ret == SUCCESS) {
            retval = rv;
        } else {
            retval = &EG(uninitialized_zval);
        }
    } else {
        zend_object_handlers *std_hnd = zend_get_std_object_handlers();
        retval = std_hnd->read_property(object, member, type, cache_slot, rv);
    }

    zend_string_release(member_str);
    return retval;
}
/* }}} */

/* {{{ gtk_write_property */
void gtk_write_property(zval *object, zval *member, zval *value, void **cache_slot)
{
    gtk_widget *obj = php_gtk_widget_from_obj(Z_OBJ_P(object));
    zend_string *member_str = zval_get_string(member);
    gtk_prop_handler *hnd = NULL;

    if (obj->prop_handler != NULL) {
        hnd = zend_hash_find_ptr(obj->prop_handler, member_str);
    }
    if (hnd) {
        hnd->write_func(obj, value);
    } else {
        zend_object_handlers *std_hnd = zend_get_std_object_handlers();
        std_hnd->write_property(object, member, value, cache_slot);
    }

    zend_string_release(member_str);
}
/* }}} */


static void gtk_copy_prop_handler(zval *zv) /* {{{ */
{
    gtk_prop_handler *hnd = Z_PTR_P(zv);
    Z_PTR_P(zv) = malloc(sizeof(gtk_prop_handler));
    memcpy(Z_PTR_P(zv), hnd, sizeof(gtk_prop_handler));
}
/* }}} */

static void gtk_dtor_prop_handler(zval *zv) /* {{{ */
{
    free(Z_PTR_P(zv));
}


/* {{{ dom_read_na */
static int gtk_read_na(gtk_widget *obj, zval *retval)
{
    zend_throw_error(NULL, "Cannot read property");
    return FAILURE;
}
/* }}} */

/* {{{ dom_write_na */
static int gtk_write_na(gtk_widget *obj, zval *newval)
{
    zend_throw_error(NULL, "Cannot write property");
    return FAILURE;
}
/* }}} */

/* {{{ dom_register_prop_handler */
static void gtk_register_prop_handler(HashTable *prop_handler, char *name, size_t name_len, gtk_read_t read_func, gtk_write_t write_func)
{
    gtk_prop_handler hnd;

    hnd.read_func = read_func ? read_func : gtk_read_na;
    hnd.write_func = write_func ? write_func : gtk_write_na;
    zend_hash_str_add_mem(prop_handler, name, name_len, &hnd, sizeof(gtk_prop_handler));
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(gtkml)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
    zend_class_entry ce;

    memcpy(&gtk_widget_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    gtk_widget_handlers.offset = XtOffsetOf(gtk_widget, std);
    gtk_widget_handlers.free_obj = gtk_widgets_free_storage;
    gtk_widget_handlers.read_property = gtk_read_property;
    gtk_widget_handlers.write_property = gtk_write_property;
    gtk_widget_handlers.get_property_ptr_ptr = gtk_get_property_ptr_ptr;
    /*
    gtk_widget_handlers.clone_obj = dom_objects_store_clone_obj;
    gtk_widget_handlers.has_property = dom_property_exists;
    gtk_widget_handlers.get_debug_info = dom_get_debug_info;

    memcpy(&dom_nnodemap_object_handlers, &gtk_widget_handlers, sizeof(zend_object_handlers));
    dom_nnodemap_object_handlers.free_obj = dom_nnodemap_objects_free_storage;
    dom_nnodemap_object_handlers.dtor_obj = dom_nnodemap_object_dtor;
    dom_nnodemap_object_handlers.read_dimension = dom_nodelist_read_dimension;
    dom_nnodemap_object_handlers.has_dimension = dom_nodelist_has_dimension;
    */

    zend_hash_init(&classes, 0, NULL, NULL, 1);



    //REGISTER_DOM_CLASS(ce, "DOMNode", NULL, php_dom_node_class_functions, dom_node_class_entry);
    INIT_CLASS_ENTRY(ce, "Gtk\Widget", gtk_widget_methods);
    ce.create_object = gtk_widgets_new;
    gtk_widget_class_entry = zend_register_internal_class_ex(&ce, NULL);

    // TODO
    zend_hash_init(&gtk_widget_prop_handlers, 0, NULL, gtk_dtor_prop_handler, 1);
    gtk_register_prop_handler(&gtk_widget_prop_handlers, "name", sizeof("name")-1, gtk_widget_name_read, NULL);
    zend_hash_add_ptr(&classes, ce.name, &gtk_widget_prop_handlers);

/**
#define REGISTER_DOM_CLASS(ce, name, parent_ce, funcs, entry) \
    INIT_CLASS_ENTRY(ce, name, funcs); \
    ce.create_object = dom_objects_new; \
    entry = zend_register_internal_class_ex(&ce, parent_ce);
*/

    //REGISTER_DOM_CLASS(ce, "Gtk\\Window", gtk_widget_class_entry, gtk_window_methods, gtk_window_class_entry);
    INIT_CLASS_ENTRY(ce, "Gtk\\Window", gtk_window_methods);
    ce.create_object = gtk_widgets_new;
    gtk_window_class_entry = zend_register_internal_class_ex(&ce, gtk_widget_class_entry);
    //gtk_window_class_entry->ce_flags |= ZEND_ACC_FINAL;
    zend_hash_init(&gtk_window_prop_handlers, 0, NULL, gtk_dtor_prop_handler, 1);
    gtk_register_prop_handler(&gtk_window_prop_handlers, "type", sizeof("type")-1, gtk_window_type_read, gtk_window_type_write);
    zend_hash_merge(&gtk_window_prop_handlers, &gtk_widget_prop_handlers, gtk_copy_prop_handler, 0);
    zend_hash_add_ptr(&classes, ce.name, &gtk_window_prop_handlers);


    /*
    // TODO: make enumeration : Gtk\WindowType::TOPLEVEL
    zend_declare_class_constant_long(gtk_window_class_entry,
        "TOPLEVEL", sizeof("TOPLEVEL")-1, GTK_WINDOW_TOPLEVEL);

    zend_declare_class_constant_long(gtk_window_class_entry,
        "POPUP", sizeof("POPUP")-1, GTK_WINDOW_POPUP);

    zend_declare_property_long(gtk_window_class_entry,
        "type", sizeof("type")-1, GTK_WINDOW_TOPLEVEL, ZEND_ACC_PUBLIC);
    */


	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(gtkml)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
    zend_hash_destroy(&gtk_widget_prop_handlers);
    zend_hash_destroy(&gtk_window_prop_handlers);
    zend_hash_destroy(&classes);

	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(gtkml)
{
#if defined(COMPILE_DL_GTKML) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(gtkml)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(gtkml)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "gtkml support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ gtkml_functions[]
 *
 * Every user visible function must have an entry in gtkml_functions[].
 */
const zend_function_entry gtkml_functions[] = {
	PHP_FE(confirm_gtkml_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in gtkml_functions[] */
};
/* }}} */

/* {{{ gtkml_module_entry
 */
zend_module_entry gtkml_module_entry = {
	STANDARD_MODULE_HEADER,
	"gtkml",
	gtkml_functions,
	PHP_MINIT(gtkml),
	PHP_MSHUTDOWN(gtkml),
	PHP_RINIT(gtkml),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(gtkml),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(gtkml),
	PHP_GTKML_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/*}}} */

static char *gtkml_window_type_property[] = {
    /*0*/ "toplevel",
    /*1*/ "popup",
};

/* {{{ gtkml_window_new
 * @attrs an c array null terminated
 */
gtk_widget *gtkml_window_new(char *attrs[])
{
    zend_object *zobj = gtk_widgets_new(gtk_window_class_entry);
    gtk_widget *gobj = php_gtk_widget_from_obj(zobj);

    // read from attribute <window type="TOLEVEL">
    GtkWindowType type = GTK_WINDOW_TOPLEVEL;

    // FIXME: loop all attrs and feed a struct options
    char *str_attr;
    char *str_value;
    if (attrs!=NULL) {
        int i;
        for(i=0; attrs[i]!=NULL; i+=2) {
            //g_print("attr: %s\n", atts[i]);// <input  disabled /> use libxml2 module HTMLParser
            //g_print("%s=\"%s\"", attrs[i], attrs[i+1]);
            str_attr = g_utf8_casefold (attrs[i], -1);
            if (0==g_strcmp0(str_attr, "type")) {
                str_value = g_utf8_casefold (attrs[i+1], -1);
                if (0==g_strcmp0(str_value, "popup")) {
                    type = GTK_WINDOW_POPUP;
                }
                break;
            }
        }
    }

    zval obj;
    zval arg;
    zval retval;
    ZVAL_OBJ(&obj, zobj);
    ZVAL_LONG(&arg, type);
    zend_call_method_with_1_params(&obj, Z_OBJCE_P(&obj), NULL,
                                   "__construct", &retval, &arg);

    // loop attrs
    // gtk_widget_set_property(gobj, "attribute-name", value);

    return gobj;
}/*}}} */


#ifdef COMPILE_DL_GTKML
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(gtkml)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
