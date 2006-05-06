#  Copyright (C) 2005  CEA/DEN, EDF R&D
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
#  See http://www.salome-platform.org/
#
from LifeCycleCORBA import *
orb = CORBA.ORB_init([''], CORBA.ORB_ID)
lcc = LifeCycleCORBA(orb)
import AddComponent_idl
AddComponent = lcc.FindOrLoadComponent('FactoryServer','AddComponent')

Func,z = AddComponent.Add( 1. , 2. )
Func
z

Bool1,ObjRef1 = AddComponent.AdditionObjRef1()
Bool1
ObjRef1
ObjRef1.ping()
dir (ObjRef1)

Bool2,ObjRef2 = AddComponent.AdditionObjRef2()
Bool2
ObjRef2
ObjRef2.ping()
dir (ObjRef2)
