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

//#include "utilities.h"

#include "AddComponent_Impl.hxx"
#include "Adder_Impl.hxx"

AddComponent_Impl::AddComponent_Impl( CORBA::ORB_ptr orb,
				      PortableServer::POA_ptr poa,
				      PortableServer::ObjectId * contId, 
				      const char *instanceName,
                                      const char *interfaceName) :
  Engines_Component_i(orb, poa, contId, instanceName, interfaceName,1,true) {
  MESSAGE("AddComponent_Impl::AddComponent_Impl this " << hex << this << dec
          << "activate object instanceName("
          << instanceName << ") interfaceName(" << interfaceName << ")" )
  _thisObj = this ;
  _id = _poa->activate_object(_thisObj);
  LastAddition = 0 ;
}

AddComponent_Impl::AddComponent_Impl() {
  LastAddition = 0 ;
}

AddComponent_Impl::~AddComponent_Impl() {
}

SuperVisionTest::Adder_ptr AddComponent_Impl::Addition() {
  beginService( "AddComponent_Impl::Addition" );
  sendMessage(NOTIF_STEP, "AddComponent_Impl creates Adder_Impl");
  Adder_Impl * myAdder ;
  myAdder = new Adder_Impl( _orb , _poa, _contId,
                            instanceName() , interfaceName() ,
                            graphName() , nodeName() ) ;
  SuperVisionTest::Adder_var iobject ;
  PortableServer::ObjectId * id = myAdder->getId() ;
  CORBA::Object_var obj = _poa->id_to_reference(*id);
  iobject = SuperVisionTest::Adder::_narrow(obj) ;
  endService( "AddComponent_Impl::Addition" );
  return SuperVisionTest::Adder::_duplicate(iobject) ;
}

double AddComponent_Impl::Add( double x , double y , double & z ) {
  beginService( " AddComponent_Impl::Add" );
  z = x + y ;
  int S;
  
  sendMessage(NOTIF_STEP, "AddComponent_Impl::Add is Computing");
  S = 1+(int) (15.0*rand()/(RAND_MAX+1.0));
  sleep(S);
  MESSAGE( "AddComponent_Impl::Add( " <<  x << " , " << y << " , " << z
       << " ) returns " << (x - y) << " after " << S << " seconds" )
  LastAddition = z ;
  endService( " AddComponent_Impl::Add"  );
  return (x - y) ;
}

long AddComponent_Impl::Sigma( long n ) {
  long sigma = 0 ;
  int i , j ;
  beginService( " AddComponent_Impl::Sigma" );
  for ( j = 0 ; j < 1000000 ; j++ ) {
    sigma = 0 ;
    for ( i = 1 ; i <= n ; i++ ) {
      sigma = sigma + i ;
    }
  }
  endService( " AddComponent_Impl::Sigma"  );
  return sigma ;
}

double AddComponent_Impl::LastResult() {
  beginService( " AddComponent_Impl::LastResult" );
  sendMessage(NOTIF_STEP, "AddComponent_Impl::LastResult is Computing");
  int S;
  S = 1+(int) (15.0*rand()/(RAND_MAX+1.0));
  sleep(S);
  endService( " AddComponent_Impl::LastResult"  );
  return LastAddition ;
}

extern "C"
{
  PortableServer::ObjectId * AddComponentEngine_factory
     (CORBA::ORB_ptr orb,
      PortableServer::POA_ptr poa, 
      PortableServer::ObjectId * contId,
      const char *instanceName,
      const char *interfaceName)
  {
    MESSAGE("AddComponentEngine_factory AddComponentEngine ("
            << instanceName << "," << interfaceName << "," << getpid() << ")");
    AddComponent_Impl * myAddComponent 
      = new AddComponent_Impl(orb, poa, contId, instanceName, interfaceName);
    return myAddComponent->getId() ;
  }
}

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

double Adder_Impl::Add( double x , double y , double & z ) {
  beginService( " Adder_Impl::Add" );
  z = x + y ;
  int S;
  
  sendMessage(NOTIF_STEP, "Adder_Impl::Add is Computing");
  S = 1+(int) (15.0*rand()/(RAND_MAX+1.0));
  sleep(S);
  MESSAGE( "Adder_Impl::Add( " <<  x << " , " << y << " , " << z
       << " ) returns " << -(x - y) << " after " << S << " seconds" )
  LastAddition = z ;
  endService( " Adder_Impl::Add"  );
  return -(x - y) ;
}

double Adder_Impl::AddAndCompare( const double x , const double y ,
                                  const SuperVisionTest::Adder_ptr anOtherAdder ,
                                  double & z ) {
  beginService( " Adder_Impl::AddAndCompare" );
  z = x + y ;
  int S;
  
  sendMessage(NOTIF_STEP, "Adder_Impl::AddAndCompare is Computing");
  S = 1+(int) (15.0*rand()/(RAND_MAX+1.0));
  sleep(S);
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
  S = 1+(int) (15.0*rand()/(RAND_MAX+1.0));
  sleep(S);
  LastAddition = z ;
  endService( " Adder_Impl::SetLastResult"  );
  return ;
}

void Adder_Impl::LastResult( double & z ) {
  beginService( " Adder_Impl::LastResult" );
  sendMessage(NOTIF_STEP, "Adder_Impl::LastResult is Computing");
  int S;
  S = 1+(int) (15.0*rand()/(RAND_MAX+1.0));
  sleep(S);
  z = LastAddition ;
  endService( " Adder_Impl::LastResult"  );
  return ;
}


