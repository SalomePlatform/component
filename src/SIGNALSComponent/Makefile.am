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

#  SuperVisionTest SIGNALSComponent : example of component that devides two numbers
#  File   : Makefile.in
#  Author : , CEA
#  Modified by : Alexander BORODIN (OCN) - autotools usage
#  Module : SuperVisionTest
#  $Header: 
#
include $(top_srcdir)/adm_local/unix/make_common_starter.am

# header files 
salomeinclude_HEADERS = \
	SIGNALSComponent_Impl.hxx 

# Libraries targets
lib_LTLIBRARIES = libSIGNALSComponentEngine.la 
dist_libSIGNALSComponentEngine_la_SOURCES = \
	SIGNALSComponent_Impl.cxx 

bin_PROGRAMS = SIGNALSComponent_CheckOfUndefined
dist_SIGNALSComponent_CheckOfUndefined_SOURCES = \
	SIGNALSComponent_CheckOfUndefined.cxx \
	HandleServerSideSignals.cxx

${bin_PROGRAMS}: ${lib_LTLIBRARIES}

libSIGNALSComponentEngine_la_CPPFLAGS = \
	$(PYTHON_INCLUDES) \
	$(CORBA_CXXFLAGS) \
	$(CORBA_INCLUDES) \
	$(KERNEL_CXXFLAGS) \
	-I$(top_builddir)/idl \
	-I$(top_builddir)

libSIGNALSComponentEngine_la_LDFLAGS  = \
	../../idl/libSalomeIDLCOMPONENT.la \
	$(KERNEL_LDFLAGS) \
	-lSalomeGenericObj \
	-lSalomeContainer \
	-lSalomeNS \
	-lSALOMEBasics \
	-lOpUtil \
	-lRegistry \
	-lSalomeNotification \
	-lSalomeHDFPersist \
	-lSalomeIDLKernel \
	-lResourcesManager

SIGNALSComponent_CheckOfUndefined_CPPFLAGS = \
	$(libSIGNALSComponentEngine_la_CPPFLAGS)

SIGNALSComponent_CheckOfUndefined_LDFLAGS  = \
	./libSIGNALSComponentEngine.la \
	$(libSIGNALSComponentEngine_la_LDFLAGS) \
	$(CORBA_LIBS) \
	$(PYTHON_LIBS) \
	$(KERNEL_LDFLAGS) -lSALOMELocalTrace
