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
