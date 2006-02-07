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
//  File   : AddComponent_Impl.cxx
//  Author : Jean Rahuel, CEA
//  Module : SuperVisionTest

using namespace std;
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string>

#include "utilities.h"
#include "Utils_ORB_INIT.hxx"
#include "Utils_SINGLETON.hxx"
#include "SALOME_NamingService.hxx"
#include "SALOME_LifeCycleCORBA.hxx"

#include "Addition_Adder_Impl.hxx"

Adder_Impl::Adder_Impl( CORBA::ORB_ptr orb ,
			PortableServer::POA_ptr poa ,
	       	        PortableServer::ObjectId * contId , 
			const char * instanceName ,
                        const char * interfaceName , 
			const char * graphName ,
                        const char * nodeName ) :
  Engines_Component_i(orb, poa, contId, instanceName, interfaceName,1,true) {
  Names( graphName , nodeName ) ;
  MESSAGE("Adder_Impl::Adder_Impl activate object instanceName("
          << instanceName << ") interfaceName(" << interfaceName << ") --> "
          << hex << (void *) this << dec )
  beginService( "Adder_Impl::Adder_Impl" );
  _thisObj = this ;
  _id = _poa->activate_object(_thisObj);
  LastAddition = 0 ;
  sendMessage(NOTIF_STEP, "Adder_Impl is Created");
  endService( "Adder_Impl::Adder_Impl" );
}

Adder_Impl::Adder_Impl() {
  LastAddition = 0 ;
}

Adder_Impl::~Adder_Impl() {
  beginService( "Adder_Impl::~Adder_Impl" );
  endService( "Adder_Impl::~Adder_Impl" );
}

void Adder_Impl::destroy() {
  _poa->deactivate_object(*_id) ;
  CORBA::release(_poa) ;
  delete(_id) ;
  _thisObj->_remove_ref();
}

double Adder_Impl::Add( double x , double y , double & z ) {
  beginService( " Adder_Impl::Add" );
  z = x + y ;
  int S;
  
  sendMessage(NOTIF_STEP, "Adder_Impl::Add is Computing");
//  S = 1+(int) (15.0*rand()/(RAND_MAX+1.0));
  S = 5 ;
  while ( S ) {
    S = sleep(S);
  }
  MESSAGE( "Adder_Impl::Add( " <<  x << " , " << y << " , " << z
       << " ) returns " << -(x - y) << " after " << S << " seconds" )
  LastAddition = z ;
  endService( " Adder_Impl::Add"  );
  return -(x - y) ;
}

double Adder_Impl::AddWithoutSleep( double x , double y , double & z ) {
  beginService( " Adder_Impl::AddWithoutSleep" );
  z = x + y ;
  endService( " Adder_Impl::AddWithoutSleep"  );
  return -(x - y) ;
}

double Adder_Impl::AddAndCompare( const double x , const double y ,
                                  const AdditionComponent::Adder_ptr anOtherAdder ,
                                  double & z ) {
  beginService( " Adder_Impl::AddAndCompare" );
  z = x + y ;
  int S;
  
  sendMessage(NOTIF_STEP, "Adder_Impl::AddAndCompare is Computing");
//  S = 1+(int) (15.0*rand()/(RAND_MAX+1.0));
  S = 5 ;
  while ( S ) {
    S = sleep(S);
  }
  MESSAGE( "Adder_Impl::AddAndCompare( " <<  x << " , " << y << " , " << z
       << " ) returns " << -(x - y) << " after " << S << " seconds" )
  LastAddition = z ;
  double ValFunc ;
  sendMessage(NOTIF_TRACE, "Adder_Impl::AddAndCompare will call anOtherAdder->LastValue()");
  double RetVal ;
  anOtherAdder->LastResult( RetVal ) ;
  if ( RetVal > 0 ) {
    ValFunc = (x - y) ;
  }
  else {
    ValFunc = -(x - y) ;
  }
  sendMessage(NOTIF_TRACE, "Adder_Impl::AddAndCompare has called anOtherAdder->LastValue()");
  sendMessage(NOTIF_STEP, "Adder_Impl::AddAndCompare is Finished");
  endService( " Adder_Impl::AddAndCompare"  );
  return ValFunc ;
}

void Adder_Impl::SetLastResult( double z ) {
  beginService( " Adder_Impl::SetLastResult" );
  sendMessage(NOTIF_STEP, "Adder_Impl::SetLastResult is Computing");
  int S;
//  S = 1+(int) (15.0*rand()/(RAND_MAX+1.0));
  S = 5 ;
  while ( S ) {
    S = sleep(S);
  }
  LastAddition = z ;
  endService( " Adder_Impl::SetLastResult"  );
  return ;
}

void Adder_Impl::LastResult( double & z ) {
  beginService( " Adder_Impl::LastResult" );
  sendMessage(NOTIF_STEP, "Adder_Impl::LastResult is Computing");
  int S;
//  S = 1+(int) (15.0*rand()/(RAND_MAX+1.0));
  S = 5 ;
  while ( S ) {
    S = sleep(S);
  }
  z = LastAddition ;
  endService( " Adder_Impl::LastResult"  );
  return ;
}

Engines::Component_ptr Adder_Impl::LccAdditionInterface( const char * aContainer ,
                                                    const char * aComponentName ) {
  beginService( "Adder_Impl::LccAddComponent" );
  Engines::Component_ptr objComponent ;
  objComponent = Engines::Component::_nil() ;

  ORB_INIT &init = *SINGLETON_<ORB_INIT>::Instance() ;
  ASSERT(SINGLETON_<ORB_INIT>::IsAlreadyExisting());
  CORBA::ORB_var orb = init(0 , 0 ) ;
  SALOME_NamingService *_NS ;
  _NS = new SALOME_NamingService();
  _NS->init_orb( CORBA::ORB::_duplicate(orb) ) ;
	  
  SALOME_LifeCycleCORBA LCC( _NS ) ;
  objComponent = LCC.FindOrLoad_Component( aContainer ,
					   aComponentName );
  endService( "Adder_Impl::LccAddComponent"  );
  return objComponent ;
}
