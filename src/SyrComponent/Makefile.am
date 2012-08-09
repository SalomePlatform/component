# Copyright (C) 2007-2012  CEA/DEN, EDF R&D, OPEN CASCADE
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

#  SuperVisionTest SyrComponent : example of component performing some mathinatical operations
#  File   : Makefile.in
#  Author : , CEA
#  Modified by : Alexander BORODIN (OCN) - autotools usage
#  Module : SuperVisionTest
#
include $(top_srcdir)/adm_local/unix/make_common_starter.am

# header files 
salomeinclude_HEADERS = \
	SyrComponent_Impl.hxx 

# Libraries targets
lib_LTLIBRARIES = libSyrComponentEngine.la
dist_libSyrComponentEngine_la_SOURCES = \
	SyrComponent_Impl.cxx 

# Executables targets
bin_PROGRAMS = SyrComponent_CheckOfUndefined
dist_SyrComponent_CheckOfUndefined_SOURCES = \
	SyrComponent_CheckOfUndefined.cxx

${bin_PROGRAMS}: ${lib_LTLIBRARIES}

libSyrComponentEngine_la_CPPFLAGS = \
	$(PYTHON_INCLUDES) \
	$(CORBA_CXXFLAGS) \
	$(CORBA_INCLUDES) \
	$(KERNEL_CXXFLAGS) \
	-I$(srcdir)/../AddComponent \
	-I$(top_builddir)/idl
libSyrComponentEngine_la_LDFLAGS  = \
	../../idl/libSalomeIDLCOMPONENT.la \
	$(KERNEL_LDFLAGS) \
	-lSalomeGenericObj \
	-lSalomeContainer \
	-lSalomeNS \
	-lOpUtil \
	-lRegistry \
        -lSalomeNotification \
	-lSALOMELocalTrace \
        -lSalomeResourcesManager \
	-lSALOMEBasics \
	-lSalomeIDLKernel

SyrComponent_CheckOfUndefined_CPPFLAGS = \
	$(libSyrComponentEngine_la_CPPFLAGS)

SyrComponent_CheckOfUndefined_LDFLAGS = \
	./libSyrComponentEngine.la \
	$(libSyrComponentEngine_la_LDFLAGS)

sharedpkgpython_PYTHON = \
	COMPONENT_shared_modules.py
