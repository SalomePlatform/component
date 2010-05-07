#  Copyright (C) 2007-2010  CEA/DEN, EDF R&D, OPEN CASCADE
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
#  Module : SuperVisionTest
#  Modified by : Alexander BORODIN (OCN) - autotools usage
#
include $(top_srcdir)/adm_local/unix/make_common_starter.am

# header files 
salomeinclude_HEADERS = \
	TypesCheck_Impl.hxx

# Libraries targets
lib_LTLIBRARIES = libTypesCheckEngine.la
dist_libTypesCheckEngine_la_SOURCES = \
	TypesCheck_Impl.cxx 

bin_PROGRAMS = TypesCheck_CheckOfUndefined
dist_TypesCheck_CheckOfUndefined_SOURCES = \
	TypesCheck_CheckOfUndefined.cxx

${bin_PROGRAMS}: ${lib_LTLIBRARIES}

libTypesCheckEngine_la_CPPFLAGS = \
	$(PYTHON_INCLUDES) \
	$(CORBA_CXXFLAGS) \
	$(CORBA_INCLUDES) \
	$(KERNEL_CXXFLAGS) \
	-I$(srcdir)/../AddComponent \
	-I$(top_builddir)/idl
libTypesCheckEngine_la_LDFLAGS  = \
	../../idl/libSalomeIDLCOMPONENT.la \
	$(KERNEL_LDFLAGS) \
	-lSalomeContainer \
	-lSalomeNS \
	-lOpUtil \
	-lRegistry \
        -lSalomeNotification \
	-lSALOMELocalTrace \
        -lSalomeResourcesManager \
	-lSALOMEBasics \
	-lSalomeIDLKernel

TypesCheck_CheckOfUndefined_CPPFLAGS = \
	$(libTypesCheckEngine_la_CPPFLAGS)

TypesCheck_CheckOfUndefined_LDFLAGS  = \
	./libTypesCheckEngine.la \
	$(libTypesCheckEngine_la_LDFLAGS)
