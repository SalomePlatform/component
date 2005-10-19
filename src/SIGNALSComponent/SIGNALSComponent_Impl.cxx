//  SuperVisionTest SIGNALSComponent : example of component that devides two numbers
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
//  File   : SIGNALSComponent.cxx
//  Author : MARC TAJCHMAN, CEA
//  Module : SuperVisionTest

using namespace std;
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string>

//#include "utilities.h"
#include "SIGNALSComponent_Impl.hxx"

SIGNALSComponent_Impl::SIGNALSComponent_Impl( CORBA::ORB_ptr orb,
				    PortableServer::POA_ptr poa,
				    PortableServer::ObjectId * contId, 
				    const char *instanceName,
                                    const char *interfaceName) :
  Engines_Component_i(orb, poa, contId, instanceName, interfaceName,1,true)
{
  MESSAGE("SIGNALSComponent_Impl::SIGNALSComponent_Impl activate object instanceName("
          << instanceName << ") interfaceName(" << interfaceName << ")" )
  _thisObj = this ;
  _id = _poa->activate_object(_thisObj);
  NULLPTR = NULL ;
}

SIGNALSComponent_Impl::SIGNALSComponent_Impl() :
  Engines_Component_i()
{
  NULLPTR = NULL ;
}

SIGNALSComponent_Impl::~SIGNALSComponent_Impl()
{
}

long SIGNALSComponent_Impl::SIGSEGVfunc() {
  beginService( " SIGNALSComponent_Impl::SIGSEGVfunc" );
  cout << pthread_self() << "SIGNALSComponent_Impl::SIGSEGVfunc" << endl ;
  int S = 1+(int) (15.0*rand()/(RAND_MAX+1.0));
  while ( S ) {
    S = sleep( S ) ;
  }
  long nullptr = *NULLPTR ;
  endService( " SIGNALSComponent_Impl::SIGSEGVfunc"  );
  return nullptr ;
}

long SIGNALSComponent_Impl::SIGFPEfunc( long a , long b ) {
  beginService( " SIGNALSComponent_Impl::SIGFPEfunc" );
  cout << pthread_self() << "SIGNALSComponent_Impl::SIGFPEfunc" << endl ;
  int S = 1+(int) (15.0*rand()/(RAND_MAX+1.0));
  while ( S ) {
    S = sleep( S ) ;
  }
  long c = a/b ;
  endService( " SIGNALSComponent_Impl::SIGFPEfunc"  );
  return c ;
}

void SIGNALSComponent_Impl::MethodToKill() {
  beginService( " SIGNALSComponent_Impl::MethodToKill" );
  while ( 1 ) {
    sleep(1) ;
  }
  endService( " SIGNALSComponent_Impl::MethodToKill"  );
  return ;
}

void * RunMethodToKill( void * ptr ) {
  SIGNALSComponent_Impl * mySIGNALSComponent ;
  mySIGNALSComponent = ( SIGNALSComponent_Impl * ) ptr ;
  mySIGNALSComponent->MethodToKill() ;
  return ptr ;
}

void SIGNALSComponent_Impl::WaitKill() {
  pthread_t T;
  pthread_create( &T , NULL , RunMethodToKill , this ) ;
  pthread_join( T , NULL ) ;
}

extern "C"
{
  PortableServer::ObjectId * SIGNALSComponentEngine_factory
     (CORBA::ORB_ptr orb,
      PortableServer::POA_ptr poa, 
      PortableServer::ObjectId * contId,
      const char *instanceName,
      const char *interfaceName)
  {
    MESSAGE("SIGNALSComponentEngine_factory SIGNALSComponent_Impl("
            << instanceName << "," << interfaceName << ")");
    SIGNALSComponent_Impl * mySIGNALSComponent 
      = new SIGNALSComponent_Impl(orb, poa, contId, instanceName, interfaceName);
    return mySIGNALSComponent->getId() ;
  }
}


