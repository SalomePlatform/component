//  SuperVisionTest DivComponent : example of component that devides two numbers
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
//  File   : DivComponentEngine.cxx
//  Author : MARC TAJCHMAN, CEA
//  Module : SuperVisionTest

#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string>

//#include "utilities.h"
#include "DivComponent.hxx"

using namespace std;

DivComponentEngine::DivComponentEngine( CORBA::ORB_ptr orb,
				    PortableServer::POA_ptr poa,
				    PortableServer::ObjectId * contId, 
				    const char *instanceName,
                                    const char *interfaceName) :
  Engines_Component_i(orb, poa, contId, instanceName, interfaceName,1,true)
{
//  MESSAGE("DivComponentEngine::DivComponentEngine activate object instanceName("
//          << instanceName << ") interfaceName(" << interfaceName << ")" )
  _thisObj = this ;
  _id = _poa->activate_object(_thisObj);
  _nexec = 0 ;
}

DivComponentEngine::DivComponentEngine()
{
}

DivComponentEngine::~DivComponentEngine()
{
}

void DivComponentEngine::Div( double x , double y , double & z ) {
  beginService( " DivComponentEngine::Div" );
  z = x / y ;
  int S;
  
  sendMessage(NOTIF_STEP, "Div is Computing");
//  S = 1+(int) (15.0*rand()/(RAND_MAX+1.0));
  S = 5 ;
  while ( S ) {
    S = sleep(S);
  }
  sendMessage(NOTIF_TRACE, "Div is Much More Difficult Operation");
  MESSAGE("DivComponentEngine::Div( " <<  x << " , " << y << " , " << z
       << " ) after " << S << " seconds" )
  endService( " DivComponentEngine::Div"  );
}

extern "C"
{
  PortableServer::ObjectId * DivComponentEngine_factory
     (CORBA::ORB_ptr orb,
      PortableServer::POA_ptr poa, 
      PortableServer::ObjectId * contId,
      const char *instanceName,
      const char *interfaceName)
  {
    MESSAGE("DivComponentEngine_factory DivComponentEngine ("
            << instanceName << "," << interfaceName << ")");
    DivComponentEngine * myDivComponent 
      = new DivComponentEngine(orb, poa, contId, instanceName, interfaceName);
    return myDivComponent->getId() ;
  }
}


