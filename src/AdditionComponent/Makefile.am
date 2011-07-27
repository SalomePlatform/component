#  Copyright (C) 2007-2011  CEA/DEN, EDF R&D, OPEN CASCADE
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

#  SuperVisionTest AddComponent : example of component that adds two numbers
#  File   : Makefile.in
#  Author : , CEA
#  Modified by : Alexander BORODIN (OCN) - autotools usage
#  Module : SuperVisionTest
#
include $(top_srcdir)/adm_local/unix/make_common_starter.am

# header files 
salomeinclude_HEADERS = \
	AdditionComponent_Impl.hxx \
        Addition_Adder_Impl.hxx

# Libraries targets
lib_LTLIBRARIES = libAdditionComponentEngine.la
dist_libAdditionComponentEngine_la_SOURCES = \
	AdditionComponent_Impl.cxx  \
	Addition_Adder_Impl.cxx 

# Executables targets
bin_PROGRAMS = AdditionComponent_CheckOfUndefined
dist_AdditionComponent_CheckOfUndefined_SOURCES = \
	AdditionComponent_CheckOfUndefined.cxx

${bin_PROGRAMS}: ${lib_LTLIBRARIES}

libAdditionComponentEngine_la_CPPFLAGS = \
	$(PYTHON_INCLUDES) \
	$(CORBA_CXXFLAGS) \
	$(CORBA_INCLUDES) \
	$(KERNEL_CXXFLAGS) \
	-I$(srcdir)/../AddComponent \
	-I$(top_builddir)/idl

libAdditionComponentEngine_la_LDFLAGS  = \
	../../idl/libSalomeIDLCOMPONENT.la \
	$(KERNEL_LDFLAGS) \
	-lSalomeContainer \
	-lSalomeHDFPersist \
	-lSalomeNS \
	-lOpUtil \
	-lRegistry \
        -lSalomeNotification \
	-lSALOMELocalTrace \
	-lSalomeLifeCycleCORBA \
        -lSalomeResourcesManager \
        -lResourcesManager \
	-lSALOMEBasics \
	-lSalomeIDLKernel

AdditionComponent_CheckOfUndefined_CPPFLAGS = \
	$(libAdditionComponentEngine_la_CPPFLAGS)

AdditionComponent_CheckOfUndefined_LDFLAGS = \
	./libAdditionComponentEngine.la \
	$(libAdditionComponentEngine_laLDFLAGS)
