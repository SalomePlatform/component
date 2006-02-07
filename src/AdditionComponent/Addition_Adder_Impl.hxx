//  SuperVisionTest AddComponent : example of component that adds two numbers
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
//  File   : Adder_Impl.hxx
//  Author : Jean Rahuel, CEA
//  Module : SuperVisionTest
//  $Header:

#ifndef _ADDITION_ADDER_IMPL_HXX_
#define _ADDITION_ADDER_IMPL_HXX_

#include <iostream>
#include <SALOMEconfig.h>
#include CORBA_SERVER_HEADER(AdditionComponent)
#include CORBA_SERVER_HEADER(SALOME_Component)
#include "SALOME_Component_i.hxx"

class Adder_Impl :  public POA_AdditionComponent::Adder ,
                    public Engines_Component_i {
  public:
    Adder_Impl() ;
    Adder_Impl( CORBA::ORB_ptr orb ,
	        PortableServer::POA_ptr poa ,
	        PortableServer::ObjectId * contId , 
	        const char *instanceName ,
                const char *interfaceName , 
                const char * graphName ,
                const char * nodeName );

    virtual ~Adder_Impl();

    virtual void destroy() ;

    virtual double Add( double x , double y , double & z ) ;

    virtual double AddWithoutSleep( double x , double y , double & z ) ;

    virtual double AddAndCompare( const double x , const double y ,
                                  const AdditionComponent::Adder_ptr anOtherAdder ,
                                  double & z ) ;

    virtual void SetLastResult( double z ) ;

    virtual void LastResult( double & z ) ;

    virtual Engines::Component_ptr LccAdditionInterface( const char * aContainer ,
                                                    const char * aComponentName ) ;

  private:

    double LastAddition ;

};

#endif