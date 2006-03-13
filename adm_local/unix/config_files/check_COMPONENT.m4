#  Check availability of COMPONENT module binary distribution
#
#  Author : Marc Tajchman (CEA, 2002)
#------------------------------------------------------------

AC_DEFUN([CHECK_COMPONENT],[

AC_CHECKING(for Component)

Component_ok=no

AC_ARG_WITH(comp,
	    --with-component=DIR root directory path of COMPONENT module installation,
	    COMPONENT_DIR="$withval",COMPONENT_DIR="")

if test "x$COMPONENT_DIR" = "x" ; then

# no --with-component option used

  if test "x$COMPONENT_ROOT_DIR" != "x" ; then

    # COMPONENT_ROOT_DIR environment variable defined
    COMPONENT_DIR=$COMPONENT_ROOT_DIR

  else

    # search component binaries in PATH variable
    AC_PATH_PROG(TEMP, libCalculatorEngine.so)
    if test "x$TEMP" != "x" ; then
      COMPONENT_DIR=`dirname $TEMP`
    fi

  fi

fi

if test -f ${COMPONENT_DIR}/lib/salome/libCalculatorEngine.so  ; then
  Component_ok=yes
  AC_MSG_RESULT(Using COMPONENT module distribution in ${COMPONENT_DIR})

  if test "x$COMPONENT_ROOT_DIR" == "x" ; then
    COMPONENT_ROOT_DIR=${COMPONENT_DIR}
  fi
  AC_SUBST(COMPONENT_ROOT_DIR)
else
  AC_MSG_WARN("Cannot find compiled COMPONENT module distribution")
fi
  
AC_MSG_RESULT(for COMPONENT: $Component_ok)
 
])dnl
 
