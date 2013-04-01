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

#  SUPERV DataStreamComponent : example of component
#  File   : Makefile.in
#  Author : Jean Rahuel
#  Modified by : Alexander BORODIN (OCN) - autotools usage
#  Module : SUPERV
#  $Header: 
#
include $(top_srcdir)/adm_local/unix/make_common_starter.am

# header files 
salomeinclude_HEADERS = \
	DataStreamComponent_Impl.hxx

# Libraries targets
lib_LTLIBRARIES = libDataStreamFactoryEngine.la
dist_libDataStreamFactoryEngine_la_SOURCES = \
	DataStreamComponent_Impl.cxx 

# Executables targets
bin_PROGRAMS = DataStreamComponent_CheckOfUndefined

${bin_PROGRAMS}: ${lib_LTLIBRARIES}

dist_DataStreamComponent_CheckOfUndefined_SOURCES = \
	DataStreamComponent_CheckOfUndefined.cxx

libDataStreamFactoryEngine_la_CPPFLAGS = \
	$(PYTHON_INCLUDES) \
	$(CORBA_CXXFLAGS) \
	$(CORBA_INCLUDES) \
	$(KERNEL_CXXFLAGS) \
	-I$(srcdir)/../AddComponent \
	-I$(top_builddir)/idl \
	-I$(top_builddir)

libDataStreamFactoryEngine_la_LDFLAGS  = \
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

DataStreamComponent_CheckOfUndefined_CPPFLAGS = \
	$(libDataStreamFactoryEngine_la_CPPFLAGS)

DataStreamComponent_CheckOfUndefined_LDFLAGS = \
	./libDataStreamFactoryEngine.la \
	$(libDataStreamFactoryEngine_la_LDFLAGS) \
	$(CORBA_LIBS)
