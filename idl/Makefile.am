# Copyright (C) 2005  OPEN CASCADE, CEA, EDF R&D, LEG
#           PRINCIPIA R&D, EADS CCR, Lip6, BV, CEDRAT
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either 
# version 2.1 of the License.
# 
# This library is distributed in the hope that it will be useful 
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

#
# This Makefile is responsible of generating the client and server
# implementation of IDL interfaces for both C++ and python usage.
# The building process of the C++ files is in charge of each source
# package and then is not manage here.
#

include $(top_srcdir)/adm_local/unix/make_common_starter.am

BASEIDL_FILES = \
	AddComponent.idl \
	AdditionComponent.idl \
	DivComponent.idl \
	FactorialComponent.idl \
	MulComponent.idl \
	SubComponent.idl \
	SyrComponent.idl \
	SyrControlComponent.idl \
	TypesCheck.idl \
	DataStreamComponent.idl \
	SIGNALSComponent.idl \
	UndefinedSymbolComponent.idl \
	Calculator.idl

# This variable defines the files to be installed
dist_salomeidl_DATA = $(BASEIDL_FILES)

# GUI idl common library
lib_LTLIBRARIES = libSalomeIDLCOMPONENT.la

# Sources built from idl files
BASEIDL_SOURCES =\
	AddComponentSK.cc \
	AdditionComponentSK.cc \
	DivComponentSK.cc \
	FactorialComponentSK.cc \
	MulComponentSK.cc \
	SubComponentSK.cc \
	SyrComponentSK.cc \
	SyrControlComponentSK.cc \
	TypesCheckSK.cc \
	DataStreamComponentSK.cc \
	SIGNALSComponentSK.cc \
	UndefinedSymbolComponentSK.cc \
	CalculatorSK.cc
DYNIDL_SOURCES = \
	AddComponentDynSK.cc \
	AdditionComponentDynSK.cc \
	DivComponentDynSK.cc \
	FactorialComponentDynSK.cc \
	MulComponentDynSK.cc \
	SubComponentDynSK.cc \
	SyrComponentDynSK.cc \
	SyrControlComponentDynSK.cc \
	TypesCheckDynSK.cc \
	DataStreamComponentDynSK.cc \
	SIGNALSComponentDynSK.cc \
	UndefinedSymbolComponentDynSK.cc \
	CalculatorDynSK.cc

nodist_libSalomeIDLCOMPONENT_la_SOURCES = ${BASEIDL_SOURCES} ${DYNIDL_SOURCES}
${DYNIDL_SOURCES}: ${BASEIDL_SOURCES}

# header files must be exported: other modules have to use this library
nodist_salomeinclude_HEADERS = $(BASEIDL_FILES:%.idl=%.hh)

libSalomeIDLCOMPONENT_la_CPPFLAGS = \
	$(KERNEL_CXXFLAGS) \
	$(MED_CXXFLAGS) \
	-I$(top_builddir)/salome_adm/unix \
	-I$(top_builddir)/idl \
	@CORBA_CXXFLAGS@ \
	@CORBA_INCLUDES@

libSalomeIDLCOMPONENT_la_LDFLAGS = -no-undefined -version-info=0:0:0
libSalomeIDLCOMPONENT_la_LIBADD  = \
	$(KERNEL_LDFLAGS) -lSalomeIDLKernel \
	$(MED_LDFLAGS) -lSalomeIDLMED \
	@CORBA_LIBS@

# These variables defines the building process of CORBA files
OMNIORB_IDL         = @OMNIORB_IDL@
OMNIORB_IDLCXXFLAGS = @OMNIORB_IDLCXXFLAGS@
OMNIORB_IDLPYFLAGS  = \
	@OMNIORB_IDLPYFLAGS@ \
	-I$(top_builddir)/idl/salome \
	-I$(KERNEL_ROOT_DIR)/idl/salome \
	-I$(MED_ROOT_DIR)/idl/salome

IDLCXXFLAGS = \
	-bcxx \
	@IDLCXXFLAGS@ \
	-I$(top_builddir)/idl/salome \
	-I$(KERNEL_ROOT_DIR)/idl/salome \
	-I$(MED_ROOT_DIR)/idl/salome \
	-I$(top_builddir)/salome_adm/unix
IDLPYFLAGS  = \
	@IDLPYFLAGS@ \
	-I$(KERNEL_ROOT_DIR)/idl/salome \
	-I$(MED_ROOT_DIR)/idl/salome

# potential problem on parallel make on the following - multiple outputs
SUFFIXES = .idl .hh SK.cc
.idlSK.cc:
	$(OMNIORB_IDL) $(IDLCXXFLAGS) $(OMNIORB_IDLCXXFLAGS) $<
.idl.hh:
	$(OMNIORB_IDL) $(IDLCXXFLAGS) $(OMNIORB_IDLCXXFLAGS) $<

install-exec-local: $(BASEIDL_FILES:%=$(top_srcdir)/idl/%)
	$(INSTALL) -d  $(DESTDIR)$(salomepythondir)
	ls $^ | while read file; do \
	  $(OMNIORB_IDL) $(IDLPYFLAGS) -C$(DESTDIR)$(salomepythondir) $$file ; \
	done

# uninstall-local removes too much, but it works in distcheck
uninstall-local:
	rm -rf $(DESTDIR)$(salomepythondir)/*

mostlyclean-local:
	-rm -f *.hh *.cc .depidl

# we use cpp to generate dependencies between idl files.
# option x c tells the preprocessor to consider idl as a c file.
# if an idl is modified, all idl dependencies are rebuilt

.depidl: $(BASEIDL_FILES)
	@echo "" > $@
	@for dep in $^ dummy; do \
	  if [ $$dep != "dummy" ]; then \
	    echo Building dependencies for $$dep; \
	    $(CPP) $(C_DEPEND_FLAG) -x c -I$(srcdir) -I$(KERNEL_ROOT_DIR)/idl/salome -I$(MED_ROOT_DIR)/idl/salome $$dep 2>/dev/null | \
	    sed 's/\.o/\SK.cc/' >>$@; \
	  fi; \
	done ;

-include .depidl
