//  Copyright (C) 2003  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
//  CEDRAT, EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS 
// 
//  This library is free software; you can redistribute it and/or 
//  modify it under the terms of the GNU Lesser General Public 
//  License as published by the Free Software Foundation; either 
//  version 2.1 of the License. 
// 
//  This library is distributed in the hope that it will be useful, 
//  but WITHOUT ANY WARRANTY; without even the implied warranty of 
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
//  Lesser General Public License for more details. 
// 
//  You should have received a copy of the GNU Lesser General Public 
//  License along with this library; if not, write to the Free Software 
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA 
// 
//  See http://www.opencascade.org/SALOME/ or email : webmaster.salome@opencascade.org 
//
//
//
//  File   : CalculatorEngine.cxx
//  Author : Laurent DADA, CEA
//  Module : CalculatorComponent
//  $Header$

using namespace std;
#include <unistd.h>
#include "utilities.h"
#include "CalculatorEngine.hxx"
#include <iostream>
#include <sstream>
#include "MEDMEM_Support_i.hxx"

#include "MEDMEM_define.hxx"
#include "MEDMEM_STRING.hxx"
#include "MEDMEM_Exception.hxx"
#include "MEDMEM_Unit.hxx"

using namespace MEDMEM;

//================================================================================
// static PrintFieldValues - shows field contents
//================================================================================

static void PrintFieldValues (FIELD<double> * field, int until_index) 
{
  const double * values = field -> getValue(MED_FULL_INTERLACE);
  int nb_comp     = field -> getNumberOfComponents();
  MESSAGE( "Field                    : " << field -> getName() );
  MESSAGE( "    Description          : " << field -> getDescription() );
  MESSAGE( "    Number of components : " << nb_comp );

  for (int i=0 ; i<nb_comp ; i++) {
    MESSAGE ( "       Component " << field -> getComponentName(i+1) << endl \
	     << "                   Unit        : " << field -> getMEDComponentUnit(i+1) << endl \
	     << "                   Description : " << field -> getComponentDescription(i+1) );
  }
  MESSAGE( "    First " << until_index << " values   : " );
  
  for (int j=0 ; j < until_index ; j++) {
    for (int i=0;i<nb_comp;i++) MESSAGE( values[i+j*nb_comp] << " " );
  }
}


//================================================================================
// Constructors
//================================================================================

CalculatorEngine::CalculatorEngine(CORBA::ORB_ptr orb,
				   PortableServer::POA_ptr poa,
				   PortableServer::ObjectId * contId, 
				   const char *instanceName,
				   const char *interfaceName) :
				   Engines_Component_i(orb, poa, contId, instanceName, interfaceName,true)
{
  MESSAGE("CalculatorEngine::CalculatorEngine activate object instanceName("
          << instanceName << ") interfaceName(" << interfaceName << ")" )
    _thisObj = this ;
  _id = _poa->activate_object(_thisObj);
  SALOME_NamingService *NS = new SALOME_NamingService(orb);
  _NS=NS;
}

CalculatorEngine::CalculatorEngine()
{
}

//================================================================================
// Destructors
//================================================================================

CalculatorEngine::~CalculatorEngine()
{
}

SALOME_MED::FIELDDOUBLE_ptr CalculatorEngine::PutToStudy(SALOME_MED::FIELDDOUBLE_ptr theField1,
							 long int theStudyId) {
  CORBA::Object_var anObj = _NS->Resolve("/myStudyManager");
  SALOMEDS::StudyManager_var aManager  = SALOMEDS::StudyManager::_narrow(anObj);
//   SALOMEDS::ListOfOpenStudies_var aList = aManager->GetOpenStudies();
//   SALOMEDS::Study_var aStudy = aManager->GetStudyByName(aList[0]);
  SALOMEDS::Study_var aStudy = aManager->GetStudyByID(theStudyId);
  SALOMEDS::StudyBuilder_var aBuilder = aStudy->NewBuilder();

  SALOMEDS::SComponent_var aComponent = aStudy->FindComponent("Calculator");
  if (aComponent->_is_nil()) aComponent = aBuilder->NewComponent("Calculator");
  SALOMEDS::GenericAttribute_var anAttr = aBuilder->FindOrCreateAttribute(aComponent, "AttributeName");
  SALOMEDS::AttributeName_var aName = SALOMEDS::AttributeName::_narrow(anAttr);
  aName->SetValue("Calculator");
  
  SALOMEDS::SObject_var aSO = aBuilder->NewObject(aComponent);
  anAttr = aBuilder->FindOrCreateAttribute(aSO, "AttributeName");
  aName = SALOMEDS::AttributeName::_narrow(anAttr);
  char aFieldName[10];
  sprintf(aFieldName, "Field_%d", (int)aSO->Tag());
  aName->SetValue(strdup(aFieldName));
  
  ORB_INIT &init = *SINGLETON_<ORB_INIT>::Instance() ;
  ASSERT(SINGLETON_<ORB_INIT>::IsAlreadyExisting()) ;
  CORBA::ORB_var &orb = init(0,0);

  string iorStr = orb->object_to_string(theField1);
  anAttr = aBuilder->FindOrCreateAttribute(aSO, "AttributeIOR");
  SALOMEDS::AttributeIOR_var anIOR = SALOMEDS::AttributeIOR::_narrow(anAttr);
  anIOR->SetValue(iorStr.c_str());

  return SALOME_MED::FIELDDOUBLE::_duplicate(theField1);
}


//=======================================================================================
//  Addition of 2 FieldNodeDouble (based on Med library)
//
//  We assume that :
//     - support
//     - number of components
//     - name, type, unit and description of components
//  are the same for the 2 fields.
//
//  Otherwise,
//  the result will be a copy of the first field.
//
//=======================================================================================

SALOME_MED::FIELDDOUBLE_ptr CalculatorEngine::Add(SALOME_MED::FIELDDOUBLE_ptr FirstField,
						  SALOME_MED::FIELDDOUBLE_ptr SecondField)
{
  ostringstream tmp;
  bool          same_support = true;
  
  beginService("CalculatorEngine::Add");
  
  sendMessage(NOTIF_TRACE, "CalculatorEngine::Add is Computing");
  
  BEGIN_OF("CalculatorEngine::Add(SALOME_MED::FIELDDOUBLE_ptr FirstField,SALOME_MED::FIELDDOUBLE_ptr SecondField)");

  SCRUTE(FirstField);
  SCRUTE(SecondField);

  string message = string("\n             CalculatorEngine::Add : ") +
                   string("\n                               first field name  --> ") + FirstField -> getName() +
                   string("\n                               second field name --> ") + SecondField -> getName();

  sendMessage(NOTIF_TRACE, message.c_str());

  // Number of components
  int nb_comp1  = FirstField -> getNumberOfComponents();
  int nb_comp2  = SecondField -> getNumberOfComponents();
  if (nb_comp1 != nb_comp2) same_support = false;
   MESSAGE( "  nb_comp1 --> " << nb_comp1 <<endl );
   MESSAGE( "  nb_comp2 --> " << nb_comp2 <<endl );


  /* Name Description and Unit of each component of the field */

  string * component_name = new string[nb_comp1];
  string * component_unit = new string[nb_comp1];

  for (int i=0 ; i<nb_comp1 ; i++) {
    component_name[i].assign(FirstField -> getComponentName(i+1));
    component_unit[i].assign(FirstField -> getComponentUnit(i+1));

    if (same_support) {
      if (
	  (component_name[i] != SecondField -> getComponentName(i+1)) ||
	  (component_unit[i] != SecondField -> getComponentUnit(i+1)))
	same_support = false;
    }
  }

  MESSAGE("CalculatorEngine::Add Number of entities in the Support of each fields");
 
  // Number of entities in the Support of the field

  int len_value1 = 0;
  int len_value2 = 0;
  SALOME_MED::SUPPORT_ptr support1 = FirstField -> getSupport();
  SALOME_MED::SUPPORT_ptr support2 = SecondField -> getSupport();

  SCRUTE(support1);

  SCRUTE(support2);

  SALOME_MED::MESH_ptr mesh1 = support1 -> getMesh();
  SALOME_MED::MESH_ptr mesh2 = support2 -> getMesh();

  SCRUTE(mesh1);
  SCRUTE(mesh2);

  if (same_support && support1 != support2) same_support = false;

  if (support1 -> isOnAllElements())
    len_value1 = support1 -> getMesh() -> getNumberOfElements(support1 -> getEntity(),SALOME_MED::MED_ALL_ELEMENTS);
  else
    len_value1 = support1 -> getNumberOfElements(SALOME_MED::MED_ALL_ELEMENTS);

  SCRUTE(len_value1);

  if (support2 -> isOnAllElements())
    len_value2 = support2 -> getMesh() -> getNumberOfElements(support2 -> getEntity(),SALOME_MED::MED_ALL_ELEMENTS);
  else
    len_value2 = support2 -> getNumberOfElements(SALOME_MED::MED_ALL_ELEMENTS);

  if (same_support && len_value1 != len_value2) same_support = false;

  SCRUTE(len_value2);

  // Values of new field
  SALOME_MED::double_array * first_value = FirstField -> getValue(SALOME_MED::MED_FULL_INTERLACE);
  SALOME_MED::double_array * second_value;
  if (same_support) {
    second_value = SecondField -> getValue(SALOME_MED::MED_FULL_INTERLACE);
    tmp << "\n             CalculatorEngine::Add : " ;
    tmp << "\n                               Number of entities in the Support of first field  = " << len_value1 ;
    tmp << "\n                               Number of entities in the Support of second field = " << len_value2 ;
    message = tmp.str();

    sendMessage(NOTIF_TRACE, message.c_str());

  }

  int totalLength = nb_comp1*len_value1;
  double * new_value = new double[totalLength];
  if (same_support) 
    {
      sendMessage(NOTIF_TRACE, "CalculatorEngine::Add - field1 and field2 have the same support");

      for(int i=0 ; i<totalLength ; i++) 
	new_value[i] = ((*first_value)[i]) + ((*second_value)[i]);
    }
  else {
    for(int i=0 ; i<totalLength ; i++) 
      new_value[i] = ((*first_value)[i]) ;
  }
  
  // Creation of a Local Field
  
  MESSAGE("CalculatorEngine::Add Creation of the local field "<< totalLength);
  
  FIELD<double> * fieldloc =  new FIELD<double>();
  fieldloc -> allocValue(nb_comp1,len_value1);
  fieldloc  -> setValue(MED_FULL_INTERLACE,new_value);
  fieldloc  -> setValueType(MED_EN::MED_REEL64);
  fieldloc  -> setName("-new_Add-");
  fieldloc  -> setDescription( FirstField -> getDescription() );
  fieldloc -> setComponentsNames(component_name);
  fieldloc -> setMEDComponentsUnits(component_unit);

  // Control
  int until_index = ( 20 > len_value1)? len_value1 : 20;
  PrintFieldValues (fieldloc,until_index);

  sendMessage(NOTIF_TRACE, "CalculatorEngine::Add - new field created");

  // Export result
  // Creation of the new CORBA field

  MESSAGE("CalculatorEngine::Add Creation of the CORBA field");

  // Corrected by APV - November 23, 2004
  // FIELDDOUBLE_i * NewField = new FIELDDOUBLE_i(support1,fieldloc) ;
  FIELDDOUBLE_i * NewField = new FIELDDOUBLE_i(fieldloc) ;

  POA_SALOME_MED::FIELDDOUBLE_tie<FIELDDOUBLE_i> * myFieldTie = new POA_SALOME_MED::FIELDDOUBLE_tie<FIELDDOUBLE_i>(NewField) ;
  SALOME_MED::FIELDDOUBLE_ptr myFieldIOR = myFieldTie->_this() ;

  sleep(4);

  END_OF("CalculatorEngine::Add(SALOME_MED::FIELDDOUBLE_ptr FirstField,SALOME_MED::FIELDDOUBLE_ptr SecondField)");

  endService("CalculatorEngine::Add");
  return myFieldIOR;

}


//===============================================================================
//  Multiplication of a FieldNodeDouble by a double value (based on Med library)
//===============================================================================

SALOME_MED::FIELDDOUBLE_ptr CalculatorEngine::Mul(SALOME_MED::FIELDDOUBLE_ptr OldField,
						  CORBA::Double x1)
{
  beginService("CalculatorEngine::Mul");

  BEGIN_OF("CalculatorEngine::Mul(SALOME_MED::FIELDDOUBLE_ptr OldField,CORBA::Double x1)");

  SCRUTE(OldField);
  SCRUTE(x1);

  // Name and description of field
  string field_name        = OldField -> getName();
  string field_description = OldField -> getDescription();

  // Number of components
  int nb_comp  = OldField -> getNumberOfComponents();
  string * component_name = new string[nb_comp];
  string * component_unit = new string[nb_comp];

  for (int i=0 ; i<nb_comp ; i++) {
    component_name[i] = OldField -> getComponentName(i+1);
    component_unit[i] = OldField -> getComponentUnit(i+1);
  }

  MESSAGE("CalculatorEngine::Mul Number of entities in the Support of the field");

  // Number of entities in the Support of the field
  int len_value = 0;

  SALOME_MED::SUPPORT_ptr support = OldField -> getSupport();

  SCRUTE(support);

  SALOME_MED::MESH_ptr mesh = support -> getMesh();

  SCRUTE(mesh);

  if (support -> isOnAllElements())
    len_value = support -> getMesh() -> getNumberOfElements(support -> getEntity(),SALOME_MED::MED_ALL_ELEMENTS);
  else
    len_value = support -> getNumberOfElements(SALOME_MED::MED_ALL_ELEMENTS);

  SCRUTE(len_value);

  // Values of new field
  SALOME_MED::double_array * old_value = OldField -> getValue(SALOME_MED::MED_FULL_INTERLACE);

  int totalLength = nb_comp*len_value;
  double * new_value = new double[totalLength];
  for(int i=0 ; i<totalLength ; i++) {
    new_value[i] = x1 * ((*old_value)[i]);
  }

  // Creation of a Local Field

  MESSAGE("CalculatorEngine::Mul Creation of the local field "<< totalLength);

  FIELD<double> * fieldloc =  new FIELD<double>();
  fieldloc -> allocValue(nb_comp,len_value);
  fieldloc  -> setValue(MED_FULL_INTERLACE,new_value);
  fieldloc  -> setValueType(MED_EN::MED_REEL64);
  fieldloc  -> setName("-new_Mul-");
  fieldloc  -> setDescription(field_description);
  fieldloc -> setComponentsNames(component_name);
  fieldloc -> setMEDComponentsUnits(component_unit);


  // Creation of the new CORBA field

  MESSAGE("CalculatorEngine::Mul Creation of the CORBA field");

  // Corrected by APV - November 23, 2004
  // FIELDDOUBLE_i * NewField = new FIELDDOUBLE_i(support,fieldloc) ;
  FIELDDOUBLE_i * NewField = new FIELDDOUBLE_i(fieldloc) ;

  POA_SALOME_MED::FIELDDOUBLE_tie<FIELDDOUBLE_i> * myFieldTie = new POA_SALOME_MED::FIELDDOUBLE_tie<FIELDDOUBLE_i>(NewField) ;
  SALOME_MED::FIELDDOUBLE_ptr myFieldIOR = myFieldTie->_this() ;

  sleep(4);

  END_OF("CalculatorEngine::Mul(SALOME_MED::FIELDDOUBLE_ptr OldField,CORBA::Double x1)");

  endService("CalculatorEngine::Mul");
  return myFieldIOR;
}


//================================================================================
//  Build a constant field of double based on first field support (Med library)
//================================================================================

SALOME_MED::FIELDDOUBLE_ptr CalculatorEngine::Constant(SALOME_MED::FIELDDOUBLE_ptr FirstField,
						       CORBA::Double x1)
{

  beginService("CalculatorEngine::Const");

  BEGIN_OF("CalculatorEngine::Constant(SALOME_MED::FIELDDOUBLE_ptr FirstField,CORBA::Double x1)");

  // Name and description of field
  string field_name        = FirstField -> getName();
  string field_description = FirstField -> getDescription();

  SALOME_MED::SUPPORT_ptr FirstSupport = FirstField -> getSupport();

  // Number of components
  int nb_comp  = FirstField -> getNumberOfComponents();

  // Type, name, unit and description of components
  string * component_name = new string[nb_comp];
  string * component_unit = new string[nb_comp];

  for (int i = 0 ; i<nb_comp ; i++) {
    component_name[i] = FirstField -> getComponentName(i+1);
    component_unit[i] = FirstField -> getComponentUnit(i+1);
  }

  MESSAGE("CalculatorEngine::Constant Number of entities in the Support of the field");

  // Number of entities in the Support of the field
  int len_value = 0;

  SCRUTE(FirstSupport);

  SALOME_MED::MESH_ptr mesh = FirstSupport -> getMesh();

  SCRUTE(mesh);

  if ( FirstSupport -> isOnAllElements() )
    len_value = FirstSupport -> getMesh() -> getNumberOfElements(FirstSupport -> getEntity(),SALOME_MED::MED_ALL_ELEMENTS);
  else
    len_value = FirstSupport -> getNumberOfElements(SALOME_MED::MED_ALL_ELEMENTS);

  // Values of new field
  SALOME_MED::double_array * old_value = FirstField -> getValue(SALOME_MED::MED_FULL_INTERLACE);

  int totalLength = nb_comp*len_value;
  double * new_value = new double[totalLength];

  for(int i=0 ; i<totalLength ; i++) 
    new_value[i] = x1 ;
 

  // Creation of a Local Field

  MESSAGE("CalculatorEngine::Constant Creation of the local field "<< totalLength);

  FIELD<double> * fieldloc =  new FIELD<double>();
  fieldloc -> allocValue(nb_comp,len_value);
  fieldloc  -> setValue(MED_FULL_INTERLACE,new_value);
  fieldloc  -> setValueType(MED_EN::MED_REEL64);
  fieldloc  -> setName("-new_Const_Field-");
  fieldloc  -> setDescription(field_description);
  fieldloc -> setComponentsNames(component_name);
  fieldloc -> setMEDComponentsUnits(component_unit);

  // Control
  int until_index = ( 20 > len_value)? len_value : 20 ;
  PrintFieldValues (fieldloc,until_index);

  // Creation of the new CORBA field

  MESSAGE("CalculatorEngine::Constant Creation of the CORBA field");

  // Corrected by APV - November 23, 2004
  // FIELDDOUBLE_i * NewField = new FIELDDOUBLE_i(FirstSupport,fieldloc) ;
  FIELDDOUBLE_i * NewField = new FIELDDOUBLE_i(fieldloc) ;

  POA_SALOME_MED::FIELDDOUBLE_tie<FIELDDOUBLE_i> * myFieldTie = new POA_SALOME_MED::FIELDDOUBLE_tie<FIELDDOUBLE_i>(NewField) ;
  SALOME_MED::FIELDDOUBLE_ptr myFieldIOR = myFieldTie->_this() ;
  
  sleep(4);

  endService("CalculatorEngine::Const");
  
  END_OF("CalculatorEngine::Constant(SALOME_MED::FIELDDOUBLE_ptr FirstField,CORBA::Double x1)");
  
  return myFieldIOR;
  
}

//================================================================================
//  write a field in a MED file
//================================================================================

void CalculatorEngine::writeMEDfile(SALOME_MED::FIELDDOUBLE_ptr field, const char *filename)
{
  beginService("CalculatorEngine::writeMEDfile");
  MESSAGE("fichier d'impression du champ resultat:"<<filename);

  // get support of the field

  SALOME_MED::SUPPORT_ptr support = field -> getSupport();
  
  // get mesh from this support
  
  SALOME_MED::MESH_ptr mesh = support -> getMesh();
  
  // write the mesh
  
  int index_m = mesh->addDriver(SALOME_MED::MED_DRIVER,filename,mesh->getName());

  mesh -> write(index_m,"");

  //write the field
  
  const char * LOC = "CalculatorEngine::writeMEDfile ";
  
  MESSAGE("fichier :"<<filename);

  MED_FR::med_idt _medIdt=MED_FR::MEDouvrir(const_cast <char *> (filename) ,(MED_FR::med_mode_acces) MED_LECTURE_ECRITURE);
  SCRUTE(_medIdt);

  if (_medIdt<0) return;
  
  int err ;

  int component_count= field->getNumberOfComponents();
  string   component_name(component_count*MED_TAILLE_PNOM,' ') ;
  string   component_unit(component_count*MED_TAILLE_PNOM,' ') ;
  
  for (int i=0; i < component_count ; i++) {
    component_name.replace(i*MED_TAILLE_PNOM,MED_TAILLE_PNOM,(field -> getComponentName(i+1)),0,MED_TAILLE_PNOM);
    component_unit.replace(i*MED_TAILLE_PNOM,MED_TAILLE_PNOM,(field -> getComponentUnit(i+1)),0,MED_TAILLE_PNOM);
  }
  
  MESSAGE("component_name=|"<<component_name<<"|");
  MESSAGE("component_unit=|"<<component_unit<<"|");
  
  // already existing ?
  
  char * champName = new char[MED_TAILLE_NOM+1] ;
  char * compName,  * compUnit  ;
  bool Find = false ;

  int n = MED_FR::MEDnChamp(_medIdt,0);
  int nbComp ;

  MED_FR::med_type_champ type ;

  for (int i = 1;  i <= n;  i++) 
    {
      nbComp = MED_FR::MEDnChamp(_medIdt,i);
      compName = new char[MED_TAILLE_PNOM*nbComp+1];
      compUnit = new char[MED_TAILLE_PNOM*nbComp+1];

      err = MED_FR::MEDchampInfo(_medIdt,i,champName,&type,compName,compUnit,nbComp);
      if (err == 0)
	if (strcmp(champName, field->getName())==0) { // Found !
	  Find = true ;
	  break ;
	}

      delete[] compName ;
      delete[] compUnit ;

    }
  if (Find) {
    // the same ?
    if (nbComp != component_count)
      throw MEDEXCEPTION ( LOCALIZED (STRING(LOC)
				     <<": Field exist in file, but number of component are different : " \
				     <<nbComp<<" in file and "<<component_count<<" in CORBA object."
				     )
			 );
    // component name and unit
    MESSAGE(LOC<<" Component name in file : "<<compName);
    MESSAGE(LOC<<" Component name in CORBA object : "<<component_name);
    MESSAGE(LOC<<" Component unit in file : "<<compUnit);
    MESSAGE(LOC<<" Component unit in CORBA object : "<<component_unit);
    delete[] compName ;
    delete[] compUnit ;
    
  } else { 
    // Verify the field doesn't exist
    
    string dataGroupName =  "/CHA/"+ string(field->getName());

    MESSAGE(LOC << "|" << dataGroupName << "|" );

    med_idt gid =  H5Gopen(_medIdt, dataGroupName.c_str() );
    
    if ( gid < 0 ) {
      // create field :
      err=MED_FR::MEDchampCr(_medIdt, 
			     const_cast <char*> (field->getName()),
			     MED_FR::MED_FLOAT64,
			     const_cast <char*> ( component_name.c_str() ),
			     const_cast <char*> ( component_unit.c_str() ),
			     component_count);
      if ( err < 0 )
	throw MEDEXCEPTION( LOCALIZED (STRING(LOC) 
				       << ": Error MEDchampCr : "<<err
				       )
			   );
    }
        else H5Gclose(gid);
  }
  
  SALOME_MED::SUPPORT_ptr mySupport = field -> getSupport();
  SCRUTE(mySupport);
  
  if (! mySupport->isOnAllElements())
    throw MEDEXCEPTION ( LOCALIZED (STRING(LOC) 
				   <<": Field must be on all entity"
				    )
			);
  
  SALOME_MED::MESH_ptr myMesh = mySupport -> getMesh();
  SCRUTE(mesh);

  SALOME_MED::medGeometryElement_array* Types = mySupport->getTypes() ;

  int NumberOfType = Types->length() ;

  for ( int i = 0; i < NumberOfType; i++ ) 
    {
      int NumberOfElements   = mySupport->getNumberOfElements ( (*Types)[i] ) ;
      int NumberOfGaussPoint = mySupport->getNumberOfGaussPoint ( (*Types)[i] ) ;
    
      MESSAGE( " " << field->getName() );
      MESSAGE( " " << NumberOfElements );
      MESSAGE( " " << NumberOfGaussPoint );
      MESSAGE( " " << (int) (convertIdlEntToMedEnt(mySupport->getEntity())) );
      MESSAGE( " " << (int)(convertIdlEltToMedElt((*Types)[i])) );
      MESSAGE( " " << field->getIterationNumber() );
      MESSAGE( " " << field->getTime() );
      MESSAGE( " " << field->getOrderNumber() );
      MESSAGE( "MEDchampEcr :" << myMesh->getName() );
    
      SALOME_MED::double_array * value = field->getValue( SALOME_MED::MED_FULL_INTERLACE ) ;
      double *locvalue = new double[NumberOfElements];
      for (int k = 0; k < NumberOfElements; k++) 
	locvalue[k] = (*value) [k];

      err=MED_FR::MEDchampEcr(_medIdt, 
			      const_cast <char*> (myMesh->getName()) , 
			      const_cast <char*> (field->getName()),
			      (unsigned char*)locvalue, 
			      MED_FR::MED_FULL_INTERLACE,
			      NumberOfElements,
			      MED_NOGAUSS,
			      MED_ALL,
			      MED_NOPFL,
			      MED_FR::MED_NO_PFLMOD,
			      (MED_FR::med_entite_maillage)convertIdlEntToMedEnt(mySupport->getEntity()),
			      (MED_FR::med_geometrie_element)(convertIdlEltToMedElt((*Types)[i])),
			      field->getIterationNumber(),
			      "        ",
			      field->getTime(),
			      field->getOrderNumber()
			      );
      delete locvalue;
      
      if (err < MED_VALID )
	throw MEDEXCEPTION(LOCALIZED( STRING(LOC)
				     <<": Error in writing Field "<< field->getName() <<", type "<<(*Types)[i]
				     )
			   );
    }
  END_OF( LOC );
  
  SCRUTE( err );
  if (err < 0 ) return ;
  
  MED_FR::MEDfermer(_medIdt) ;
  
  endService("CalculatorEngine::writeMEDfile");
  return ;
  
}

extern "C"
{
  //===========================================================================
  // CalculatorEngine_factory
  //===========================================================================
  PortableServer::ObjectId * CalculatorEngine_factory
     (CORBA::ORB_ptr orb,
      PortableServer::POA_ptr poa, 
      PortableServer::ObjectId * contId,
      const char *instanceName,
      const char *interfaceName)
  {
    MESSAGE("CalculatorEngine_factory CalculatorEngine ("
            << instanceName << "," << interfaceName << ")");
    CalculatorEngine * myCalculator 
      = new CalculatorEngine(orb, poa, contId, instanceName, interfaceName);
    return myCalculator->getId() ;
  }
}

