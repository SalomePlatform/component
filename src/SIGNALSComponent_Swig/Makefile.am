# Copyright (C) 2007-2011  CEA/DEN, EDF R&D, OPEN CASCADE
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
#
# See http://www.salome-platform.org/ or email : webmaster.salome@opencascade.com
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
# The file libSIGNALSComponent_Swig.py will be installed in
# <prefix>/lib/python<version>/site-package/salome.
# The library will be installed in the same place.
#

# this option puts it to dist
#BUILT_SOURCES = swig_wrap.cpp

SWIG_FLAGS    = @SWIG_FLAGS@ -I$(srcdir)
SWIG_SOURCES  = libSIGNALSComponent_Swig.i

# Libraries targets
lib_LTLIBRARIES = _libSIGNALSComponent_Swig.la
_libSIGNALSComponent_Swig_la_SOURCES = $(SWIG_SOURCES)
nodist__libSIGNALSComponent_Swig_la_SOURCES = swig_wrap.cpp
nodist_salomescript_DATA = libSIGNALSComponent_Swig.py

EXTRA_DIST += $(SWIG_SOURCES)

libSIGNALSComponent_Swig.py: swig_wrap.cpp

_libSIGNALSComponent_Swig_la_CPPFLAGS = \
	$(PYTHON_INCLUDES) \
	$(CORBA_CXXFLAGS) \
	$(CORBA_INCLUDES) \
	$(KERNEL_CXXFLAGS) \
	-I$(srcdir)/../SIGNALSComponent \
	-I$(top_builddir)/idl

_libSIGNALSComponent_Swig_la_LDFLAGS = -module
_libSIGNALSComponent_Swig_la_LIBADD  = \
	../SIGNALSComponent/libSIGNALSComponentEngine.la \
	$(KERNEL_LDFLAGS) \
	-lSalomeGenericObj \
	-lSalomeContainer \
	-lSalomeNS \
	-lOpUtil \
	-lRegistry \
	-lSalomeNotification

swig_wrap.cpp : $(SWIG_SOURCES)
	$(SWIG) $(SWIG_FLAGS) -o $@ $<

CLEANFILES = swig_wrap.cpp libSIGNALSComponent_Swig.py
