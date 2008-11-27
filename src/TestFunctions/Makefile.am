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
#  SuperVisionTest TestFunctions : example of component that adds two numbers
#  File   : Makefile.in
#  Author : , CEA
#  Modified by : Alexander BORODIN (OCN) - autotools usage
#  Module : SuperVisionTest
#
include $(top_srcdir)/adm_local/unix/make_common_starter.am

# Libraries targets
lib_LTLIBRARIES = libDynInvoke.la
dist_libDynInvoke_la_SOURCES = \
	DynInvoke.cxx

bin_PROGRAMS = \
	TestFunctions \
	TestFunctionsMemory \
	TestFunctionsMemory1 \
	TestFunctionsMemory2 \
	TestFunctionsMemory3 \
	TestFunctionsMemory4

libDynInvoke_la_CPPFLAGS = \
	$(PYTHON_INCLUDES) \
	$(CORBA_CXXFLAGS) \
	$(CORBA_INCLUDES) \
	$(KERNEL_CXXFLAGS) \
	-I$(srcdir)/../AddComponent \
	-I$(top_builddir)/idl \
	-I$(top_builddir)/salome_adm/unix

libDynInvoke_la_LDFLAGS  = \
	../../idl/libSalomeIDLCOMPONENT.la \
	$(KERNEL_LDFLAGS) \
	-lSalomeContainer \
	-lSalomeNS \
	-lOpUtil \
	-lRegistry \
	-lSalomeNotification \
	-lSALOMELocalTrace \
	-lSalomeLifeCycleCORBA \
        -lSalomeResourcesManager \
	-lSALOMEBasics \
	-lSalomeIDLKernel

TestFunctions_SOURCES = TestFunctions.cxx
TestFunctionsMemory_SOURCES = TestFunctionsMemory.cxx
TestFunctionsMemory1_SOURCES = TestFunctionsMemory1.cxx
TestFunctionsMemory2_SOURCES = TestFunctionsMemory2.cxx
TestFunctionsMemory3_SOURCES = TestFunctionsMemory3.cxx
TestFunctionsMemory4_SOURCES = TestFunctionsMemory4.cxx

AM_CPPFLAGS = \
	$(libDynInvoke_la_CPPFLAGS)

LDADD = \
	./libDynInvoke.la \
	$(libDynInvoke_la_LDFLAGS)
