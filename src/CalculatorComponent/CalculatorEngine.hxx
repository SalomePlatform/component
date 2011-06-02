// Copyright (C) 2007-2011  CEA/DEN, EDF R&D, OPEN CASCADE
//
// Copyright (C) 2003-2007  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
// CEDRAT, EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
//
// See http://www.salome-platform.org/ or email : webmaster.salome@opencascade.com
//

//  File   : CalculatorEngine.hxx
//  Author : Laurent DADA, CEA
//  Module : CalculatorComponent
//  $Header   :  Exp $
//
#ifndef _CALCULATORWRAPPER_HXX_
#define _CALCULATORWRAPPER_HXX_

// IDL headers
#include <string>
#include <SALOMEconfig.h>
#include CORBA_SERVER_HEADER(Calculator)
#include "SALOME_Component_i.hxx"
#include CORBA_CLIENT_HEADER(MED)
#include "MEDMEM_Med_i.hxx"
#include "MEDMEM_Field.hxx"
#include "MEDMEM_FieldTemplate_i.hxx"

#include "SALOME_NamingService.hxx"

class CalculatorEngine :  
  virtual public POA_SuperVisionTest::Calculator,
  public Engines_Component_i 
{

public:
  CalculatorEngine() ;
  CalculatorEngine( CORBA::ORB_ptr orb,
		      PortableServer::POA_ptr poa,
		      PortableServer::ObjectId * contId, 
		      const char *instanceName,
                      const char *interfaceName);

  virtual ~CalculatorEngine();


  SALOME_MED::FIELDDOUBLE_ptr PutToStudy(SALOME_MED::FIELDDOUBLE_ptr theField,
					 CORBA::Long theStudyId);

  SALOME_MED::FIELDDOUBLE_ptr Add(SALOME_MED::FIELDDOUBLE_ptr FirstField,
				  SALOME_MED::FIELDDOUBLE_ptr SecondField);

  SALOME_MED::FIELDDOUBLE_ptr Mul(SALOME_MED::FIELDDOUBLE_ptr OldField,
				  CORBA::Double x1);

  SALOME_MED::FIELDDOUBLE_ptr Constant(SALOME_MED::FIELDDOUBLE_ptr FirstField,
				       CORBA::Double x1);

  void writeMEDfile(SALOME_MED::FIELDDOUBLE_ptr field1 , 
		    const char *fileName);

private:

  SALOME_NamingService * _NS ; 

};

extern "C"
  PortableServer::ObjectId * CalculatorEngine_factory
                            (CORBA::ORB_ptr orb ,
			     PortableServer::POA_ptr poa , 
			     PortableServer::ObjectId * contId ,
			     const char *instanceName ,
			     const char *interfaceName ) ;

#endif
