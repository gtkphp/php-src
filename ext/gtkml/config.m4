dnl $Id$
dnl config.m4 for extension gtkml

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(gtkml, for gtkml support,
dnl Make sure that the comment is aligned:
dnl [  --with-gtkml             Include gtkml support])

dnl Otherwise use enable:

PHP_ARG_WITH(gtkml, for Gtk+ support,
dnl Make sure that the comment is aligned:
[  --with-gtkml            Include Gtk+ support])

if test "$PHP_GTKML" != "no"; then

#  PHP_ADD_EXTENSION_DEP(gtkml, libgtk) see dom config.m4

  if test -z "$PKG_CONFIG"; then
    AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  fi

  if test -x "$PKG_CONFIG"; then
    dnl using pkg-config output

    AC_MSG_CHECKING(for gtk+-3.0.pc)
    if test "$PHP_GTKML" = "yes" -o "$PHP_GTKML" = "/usr"; then
      PKNAME=gtk+-3.0
      AC_MSG_RESULT(using default path)
    elif test -r $PHP_GTKML/$PHP_LIBDIR/pkgconfig/gtk+-3.0.pc; then
      PKNAME=$PHP_GTKML/$PHP_LIBDIR/pkgconfig/gtk+-3.0.pc
      AC_MSG_RESULT(using $PKNAME)
    elif test -r $PHP_GTKML/lib/pkgconfig/gtk+-3.0.pc; then
      PKNAME=$PHP_GTKML/lib/pkgconfig/gtk+-3.0.pc
      AC_MSG_RESULT(using $PKNAME)
    else
      AC_MSG_RESULT(not found)
      AC_MSG_WARN(Could not find gtk+-3.0.pc. Try without $PHP_GTKML or set PKG_CONFIG_PATH)
    fi
  fi

  if test -n "$PKNAME"; then
    AC_MSG_CHECKING(for gtk+ 3.22.30 or greater)
    if $PKG_CONFIG --atleast-version 3.22.30 $PKNAME; then
      gtk_version_full=`$PKG_CONFIG --modversion $PKNAME`
      AC_MSG_RESULT($gtk_version_full)
    else
      AC_MSG_ERROR(gtk+ version 3.22.30 or later is required to compile php with Gtk+ support)
    fi

    GTK_LIBS=`$PKG_CONFIG --libs   $PKNAME`
    GTK_INCL=`$PKG_CONFIG --cflags $PKNAME`
  fi

  PHP_EVAL_LIBLINE($GTK_LIBS, GTK_SHARED_LIBADD)
  PHP_EVAL_INCLINE($GTK_INCL, GTK_SHARED_LIBADD)

  dnl Write more examples of tests here...

  dnl # get library FOO build options from pkg-config output
  dnl AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  dnl AC_MSG_CHECKING(for libfoo)
  dnl if test -x "$PKG_CONFIG" && $PKG_CONFIG --exists foo; then
  dnl   if $PKG_CONFIG foo --atleast-version 1.2.3; then
  dnl     LIBFOO_CFLAGS=`$PKG_CONFIG foo --cflags`
  dnl     LIBFOO_LIBDIR=`$PKG_CONFIG foo --libs`
  dnl     LIBFOO_VERSON=`$PKG_CONFIG foo --modversion`
  dnl     AC_MSG_RESULT(from pkgconfig: version $LIBFOO_VERSON)
  dnl   else
  dnl     AC_MSG_ERROR(system libfoo is too old: version 1.2.3 required)
  dnl   fi
  dnl else
  dnl   AC_MSG_ERROR(pkg-config not found)
  dnl fi
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBDIR, GTKML_SHARED_LIBADD)
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)

  dnl # --with-gtkml -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/gtkml.h"  # you most likely want to change this
  dnl if test -r $PHP_GTKML/$SEARCH_FOR; then # path given as parameter
  dnl   GTKML_DIR=$PHP_GTKML
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for gtkml files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       GTKML_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$GTKML_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the gtkml distribution])
  dnl fi

  dnl # --with-gtkml -> add include path
  dnl PHP_ADD_INCLUDE($GTKML_DIR/include)

  dnl # --with-gtkml -> check for lib and symbol presence
  dnl LIBNAME=gtkml # you may want to change this
  dnl LIBSYMBOL=gtkml # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $GTKML_DIR/$PHP_LIBDIR, GTKML_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_GTKMLLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong gtkml lib version or lib not found])
  dnl ],[
  dnl   -L$GTKML_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(GTKML_SHARED_LIBADD)


  PHP_SUBST(GTK_SHARED_LIBADD)

  PHP_NEW_EXTENSION(gtkml, gtkml.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
