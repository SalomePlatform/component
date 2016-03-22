// Copyright (C) 2007-2016  CEA/DEN, EDF R&D, OPEN CASCADE
//
// Copyright (C) 2003-2007  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
// CEDRAT, EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
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

//  SuperVisionTest AdditionComponent : example of component that adds two numbers
//  File   : AdditionComponent_Impl.hxx
//  Author : Jean Rahuel, CEA
//  Module : SuperVisionTest
//  $Header:
//
#ifndef _ADDITIONINTERFACE_IMPL_HXX_
#define _ADDITIONINTERFACE_IMPL_HXX_

#include "AdditionComponent.hxx"
#include <SALOMEconfig.h>
#include CORBA_SERVER_HEADER(AdditionComponent)
#include CORBA_SERVER_HEADER(SALOME_Component)
#include "SALOME_Component_i.hxx"

class ADDITIONCOMPONENTENGINE_EXPORT AdditionInterface_Impl :  public POA_AdditionComponent::AdditionInterface ,
                                                               public Engines_Component_i {
public:
  AdditionInterface_Impl() ;
  AdditionInterface_Impl( CORBA::ORB_ptr orb,
		     PortableServer::POA_ptr poa,
		     PortableServer::ObjectId * contId, 
		     const char *instanceName,
                     const char *interfaceName);

  virtual ~AdditionInterface_Impl();

  virtual char* getVersion();

  virtual CORBA::Double Add( CORBA::Double x , CORBA::Double y , CORBA::Double & z ) ;
  virtual CORBA::Double AddWithoutSleep( CORBA::Double x , CORBA::Double y , CORBA::Double & z ) ;

  virtual void Setx( CORBA::Double x ) ;
  virtual void Sety( CORBA::Double y ) ;
  virtual CORBA::Double Addxy() ;
  virtual CORBA::Double AddyTox( CORBA::Double y ) ;

  virtual CORBA::Long Sigma( CORBA::Long n ) ;

  virtual CORBA::Double LastResult() ;

  virtual AdditionComponent::Adder_ptr Addition() ;

  virtual bool AdditionObjRef1( AdditionComponent::Adder_out ) ;

  virtual void AdditionObjRef2( CORBA::Boolean & FuncValue , AdditionComponent::Adder_out ) ;

  virtual CORBA::Boolean AdditionObjRefs( AdditionComponent::AdditionInterface_ptr AdditionInterface1 ,
                                          AdditionComponent::AdditionInterface_ptr Adder2 ,
                                          AdditionComponent::AdditionInterface_ptr Adder3 ,
                                          AdditionComponent::AdditionInterface_out RetAdditionInterface1 ,
                                          AdditionComponent::AdditionInterface_out RetAdder2 ,
                                          AdditionComponent::AdditionInterface_out RetAdder3 ) ;

private:

  double xx ;
  double yy ;
  double LastAddition ;

};

extern "C"
  ADDITIONCOMPONENTENGINE_EXPORT
  PortableServer::ObjectId * AdditionInterfaceEngine_factory
                                   ( CORBA::ORB_ptr orb ,
                                     PortableServer::POA_ptr poa , 
                                     PortableServer::ObjectId * contId ,
                                     const char *instanceName ,
                                     const char *interfaceName ) ;

#endif
