# Copyright (C) 2007-2013  CEA/DEN, EDF R&D, OPEN CASCADE
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

#  SuperVisionTest AddComponent : example of component that adds two numbers
#  File   : Makefile.in
#  Author : , CEA
#  Modified by : Alexander BORODIN (OCN) - autotools usage
#  Module : SuperVisionTest
#
include $(top_srcdir)/adm_local/unix/make_common_starter.am

# header files 
salomeinclude_HEADERS = \
	AddComponent_Impl.hxx \
        Adder_Impl.hxx

# Libraries targets
lib_LTLIBRARIES = libAddComponentEngine.la
dist_libAddComponentEngine_la_SOURCES = \
	AddComponent_Impl.cxx  \
	Adder_Impl.cxx 

# Executables targets
bin_PROGRAMS = AddComponent_CheckOfUndefined
dist_AddComponent_CheckOfUndefined_SOURCES = \
	AddComponent_CheckOfUndefined.cxx \
	HandleServerSideSignals.cxx

${bin_PROGRAMS}: ${lib_LTLIBRARIES}

libAddComponentEngine_la_CPPFLAGS = \
	$(PYTHON_INCLUDES) \
	$(CORBA_CXXFLAGS) \
	$(CORBA_INCLUDES) \
	$(KERNEL_CXXFLAGS) \
	-I$(top_builddir)/idl \
	-I$(top_builddir)

libAddComponentEngine_la_LDFLAGS = \
	../../idl/libSalomeIDLCOMPONENT.la \
	$(KERNEL_LDFLAGS) \
	-lSalomeGenericObj \
	-lSalomeContainer \
	-lSalomeHDFPersist \
	-lSalomeNS \
	-lOpUtil \
	-lRegistry \
        -lSalomeNotification \
	-lSALOMELocalTrace \
	-lSalomeLifeCycleCORBA \
        -lSalomeResourcesManager \
	-lSALOMEBasics \
	-lSalomeIDLKernel

AddComponent_CheckOfUndefined_CPPFLAGS = \
	$(libAddComponentEngine_la_CPPFLAGS)

AddComponent_CheckOfUndefined_LDFLAGS  = \
	./libAddComponentEngine.la \
	$(libAddComponentEngine_la_LDFLAGS) \
	$(CORBA_LIBS) \
	$(PYTHON_LIBS)

