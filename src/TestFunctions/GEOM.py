from LifeCycleCORBA import *
orb = CORBA.ORB_init([''], CORBA.ORB_ID)
lcc = LifeCycleCORBA(orb)
import GEOM_Superv_idl
GEOMComponent = lcc.FindOrLoadComponent('FactoryServer','GEOM_Superv')

theFormats,thePatterns = GEOMComponent.ExportTranslators()
theFormats
thePatterns
