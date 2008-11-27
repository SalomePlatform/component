#  Copyright (C) 2007-2008  CEA/DEN, EDF R&D, OPEN CASCADE
#
#  Copyright (C) 2003-2007  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
#  CEDRAT, EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS
#
#  This library is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public
#  License as published by the Free Software Foundation; either
#  version 2.1 of the License.
#
#  This library is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public
#  License along with this library; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
#
#  See http://www.salome-platform.org/ or email : webmaster.salome@opencascade.com
#
#  SuperVisionTest SIGNALSComponent : example of component that devides two numbers
#  File   : Makefile.in
#  Author : , CEA
#  Modified by : Alexander BORODIN (OCN) - autotools usage
#  Module : SuperVisionTest
#  $Header: 
#
include $(top_srcdir)/adm_local/unix/make_common_starter.am

# ===============================================================
# Swig targets
# ===============================================================
# (cf. http://www.geocities.com/foetsch/python/swig_linux.htm)
#
# Step 1: build the wrapping source files with swig
#
# libSALOME_LifeCycleCORBA.i -- swig --> swig_wrap.cpp
#                                        libSALOME_Swig.py
#
# Step 2: build the dynamic library from cpp built source files and
#         dependant libraries.
#
# swig_wrap.cpp -- gcc --> swig_wrap.o    |-- link --> _libSALOME_Swig.la
#                          +              |
#                          dependant libs |
#
# The file libSALOME_Swigcmodule.py will be installed in
# <prefix>/lib/python<version>/site-package/salome.
# The library will be installed in the same place.
#

# this option puts it to dist
#BUILT_SOURCES = swig_wrap.cpp

SWIG_FLAGS    = \
	@SWIG_FLAGS@ \
	-I$(srcdir)

SWIG_SOURCES  = libSIGNALSComponent_Swig.i

# Libraries targets
lib_LTLIBRARIES = libSIGNALSComponent_Swigcmodule.la

nodist_pkgpython_DATA = libSIGNALSComponent_Swig.py
libSMESH_Swig.py: swig_wrap.cpp

libSIGNALSComponent_Swigcmodule_la_SOURCES = \
	$(BUILT_SOURCES) \
	$(SWIG_SOURCES)

nodist_libSIGNALSComponent_Swigcmodule_la_SOURCES = swig_wrap.cpp

libSIGNALSComponent_Swigcmodule_la_CPPFLAGS = \
	$(PYTHON_INCLUDES) \
	$(CORBA_CXXFLAGS) \
	$(CORBA_INCLUDES) \
	$(KERNEL_CXXFLAGS) \
	-I$(srcdir)/../SIGNALSComponent \
	-I$(top_builddir)/idl \
	-I$(top_builddir)/salome_adm/unix

libSIGNALSComponent_Swigcmodule_la_LDFLAGS  = \
	../SIGNALSComponent/libSIGNALSComponentEngine.la \
	$(KERNEL_LDFLAGS) \
	-lSalomeContainer \
	-lSalomeNS \
	-lOpUtil \
	-lRegistry \
	-lSalomeNotification

swig_wrap.cpp : $(SWIG_SOURCES)
	$(SWIG) $(SWIG_FLAGS) -o $@ $<

CLEANFILES = \
	swig_wrap.cpp

install-exec-hook: $(libdir)/_libSIGNALSComponent_Swig.so

$(libdir)/_libSIGNALSComponent_Swig.so:
	( cd $(libdir); ln -sf libSIGNALSComponent_Swigcmodule.so _libSIGNALSComponent_Swig.so; )
