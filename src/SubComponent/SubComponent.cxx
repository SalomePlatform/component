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

//  SuperVisionTest SubComponent : example of component that sunstracts one number from another
//  File   : SubComponentEngine.cxx
//  Author : MARC TAJCHMAN, CEA
//  Module : SuperVisionTest
//
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string>

//#include "utilities.h"
#include "SubComponent.hxx"

using namespace std;

SubComponentEngine::SubComponentEngine( CORBA::ORB_ptr orb,
				    PortableServer::POA_ptr poa,
				    PortableServer::ObjectId * contId, 
				    const char *instanceName,
                                    const char *interfaceName) :
  Engines_Component_i(orb, poa, contId, instanceName, interfaceName,1,true)
{
//  MESSAGE("SubComponentEngine::SubComponentEngine activate object instanceName("
//          << instanceName << ") interfaceName(" << interfaceName << ")" )
  _thisObj = this ;
  _id = _poa->activate_object(_thisObj);
  _nexec = 0 ;
}

SubComponentEngine::SubComponentEngine()
{
}

SubComponentEngine::~SubComponentEngine()
{
}

void SubComponentEngine::Sub( double x , double y , double & z ) {
  beginService( " SubComponentEngine::Sub" );
  z = x - y ;
  int S;
  
  sendMessage(NOTIF_STEP, "Sub is Computing");
//  S = 1+(int) (15.0*rand()/(RAND_MAX+1.0));
  S = 5 ;
  while ( S ) {
    S = sleep(S);
  }
  MESSAGE( "SubComponentEngine::Sub( " <<  x << " , " << y << " , " << z
       << " ) after " << S << " seconds" )
  endService( " SubComponentEngine::Sub"  );
}

extern "C"
{
  PortableServer::ObjectId * SubComponentEngine_factory
     (CORBA::ORB_ptr orb,
      PortableServer::POA_ptr poa, 
      PortableServer::ObjectId * contId,
      const char *instanceName,
      const char *interfaceName)
  {
    MESSAGE("SubComponentEngine_factory SubComponentEngine ("
            << instanceName << "," << interfaceName << ")");
    SubComponentEngine * mySubComponent 
      = new SubComponentEngine(orb, poa, contId, instanceName, interfaceName);
    return mySubComponent->getId() ;
  }
}


