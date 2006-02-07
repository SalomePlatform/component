//  SuperVisionTest AdditionComponent : example of component that adds two numbers
//
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
//  File   : AdditionComponent_Impl.hxx
//  Author : Jean Rahuel, CEA
//  Module : SuperVisionTest
//  $Header:

#ifndef _ADDITIONINTERFACE_IMPL_HXX_
#define _ADDITIONINTERFACE_IMPL_HXX_

//#include <iostream.h>
#include <SALOMEconfig.h>
#include CORBA_SERVER_HEADER(AdditionComponent)
#include CORBA_SERVER_HEADER(SALOME_Component)
#include "SALOME_Component_i.hxx"

class AdditionInterface_Impl :  public POA_AdditionComponent::AdditionInterface ,
                           public Engines_Component_i {
public:
  AdditionInterface_Impl() ;
  AdditionInterface_Impl( CORBA::ORB_ptr orb,
		     PortableServer::POA_ptr poa,
		     PortableServer::ObjectId * contId, 
		     const char *instanceName,
                     const char *interfaceName);

  virtual ~AdditionInterface_Impl();

  virtual double Add( double x , double y , double & z ) ;
  virtual double AddWithoutSleep( double x , double y , double & z ) ;

  virtual void Setx( double x ) ;
  virtual void Sety( double y ) ;
  virtual double Addxy() ;
  virtual double AddyTox( double y ) ;

  virtual long Sigma( long n ) ;

  virtual double LastResult() ;

  virtual AdditionComponent::Adder_ptr Addition() ;

  virtual bool AdditionObjRef1( AdditionComponent::Adder_out ) ;

  virtual void AdditionObjRef2( bool & FuncValue , AdditionComponent::Adder_out ) ;

  virtual bool AdditionObjRefs( const AdditionComponent::AdditionInterface_ptr AdditionInterface1 ,
                                const AdditionComponent::AdditionInterface_ptr Adder2 ,
                                const AdditionComponent::AdditionInterface_ptr Adder3 ,
                                AdditionComponent::AdditionInterface_out RetAdditionInterface1 ,
                                AdditionComponent::AdditionInterface_out RetAdder2 ,
                                AdditionComponent::AdditionInterface_out RetAdder3 ) ;

private:

  double xx ;
  double yy ;
  double LastAddition ;

};

extern "C"
  PortableServer::ObjectId * AdditionInterfaceEngine_factory
                                   ( CORBA::ORB_ptr orb ,
                                     PortableServer::POA_ptr poa , 
                                     PortableServer::ObjectId * contId ,
                                     const char *instanceName ,
                                     const char *interfaceName ) ;

#endif