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
#

SET(COMPONENT_CXXFLAGS -I${COMPONENT_ROOT_DIR}/include/salome)

FIND_LIBRARY(AddComponentEngine AddComponentEngine ${COMPONENT_ROOT_DIR}/lib/salome)
FIND_LIBRARY(AdditionComponentEngine AdditionComponentEngine ${COMPONENT_ROOT_DIR}/lib/salome)
FIND_LIBRARY(DataStreamFactoryEngine DataStreamFactoryEngine ${COMPONENT_ROOT_DIR}/lib/salome)
FIND_LIBRARY(DivComponentEngine DivComponentEngine ${COMPONENT_ROOT_DIR}/lib/salome)
FIND_LIBRARY(MulComponentEngine MulComponentEngine ${COMPONENT_ROOT_DIR}/lib/salome)
FIND_LIBRARY(SIGNALSComponentEngine SIGNALSComponentEngine ${COMPONENT_ROOT_DIR}/lib/salome)
FIND_LIBRARY(SubComponentEngine SubComponentEngine ${COMPONENT_ROOT_DIR}/lib/salome)
FIND_LIBRARY(SyrComponentEngine SyrComponentEngine ${COMPONENT_ROOT_DIR}/lib/salome)
FIND_LIBRARY(DynInvoke DynInvoke ${COMPONENT_ROOT_DIR}/lib/salome)
FIND_LIBRARY(TypesCheckEngine TypesCheckEngine ${COMPONENT_ROOT_DIR}/lib/salome)
FIND_LIBRARY(UndefinedSymbolComponentEngine UndefinedSymbolComponentEngine ${COMPONENT_ROOT_DIR}/lib/salome)
FIND_LIBRARY(SalomeIDLCOMPONENT SalomeIDLCOMPONENT ${COMPONENT_ROOT_DIR}/lib/salome)
