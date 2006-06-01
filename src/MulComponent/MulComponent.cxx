//  SuperVisionTest MulComponent : example of component that multiplies two numbers
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
// See http://www.salome-platform.org/ or email : webmaster.salome@opencascade.com
//
//
//
//  File   : MulComponentEngine.cxx
//  Author : MARC TAJCHMAN, CEA
//  Module : SuperVisionTest

#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string>

//#include "utilities.h"
#include "MulComponent.hxx"

using namespace std;

MulComponentEngine::MulComponentEngine( CORBA::ORB_ptr orb,
				    PortableServer::POA_ptr poa,
				    PortableServer::ObjectId * contId, 
				    const char *instanceName,
                                    const char *interfaceName) :
  Engines_Component_i(orb, poa, contId, instanceName, interfaceName,1,true)
{
//  MESSAGE("MulComponentEngine::MulComponentEngine activate object instanceName("
//          << instanceName << ") interfaceName(" << interfaceName << ")" )
  _thisObj = this ;
  _id = _poa->activate_object(_thisObj);
  _nexec = 0 ;
}

MulComponentEngine::MulComponentEngine()
{
}

MulComponentEngine::~MulComponentEngine()
{
}

void MulComponentEngine::Mul( double x , double y , double & z ) {
  beginService( " MulComponentEngine::Mul" );
  z = x * y ;
  int S;
  
  sendMessage(NOTIF_STEP, "Mul is Computing");
//  S = 1+(int) (15.0*rand()/(RAND_MAX+1.0));
  S = 5 ;
  while ( S ) {
    S = sleep(S);
  }
  MESSAGE( "MulComponentEngine::Mul( " <<  x << " , " << y << " , " << z
       << " ) after " << S << " seconds" )
  endService( " MulComponentEngine::Mul"  );
}

extern "C"
{
  PortableServer::ObjectId * MulComponentEngine_factory
     (CORBA::ORB_ptr orb,
      PortableServer::POA_ptr poa, 
      PortableServer::ObjectId * contId,
      const char *instanceName,
      const char *interfaceName)
  {
    MESSAGE("MulComponentEngine_factory MulComponentEngine ("
            << instanceName << "," << interfaceName << ")");
    MulComponentEngine * myMulComponent 
      = new MulComponentEngine(orb, poa, contId, instanceName, interfaceName);
    return myMulComponent->getId() ;
  }
}


