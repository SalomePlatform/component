//  SuperVisionTest UndefinedSymbolComponent : example of component that devides two numbers
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
//  File   : UndefinedSymbolComponentEngine.cxx
//  Author : MARC TAJCHMAN, CEA
//  Module : SuperVisionTest

using namespace std;
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string>

//#include "utilities.h"
#include "UndefinedSymbolComponent.hxx"

UndefinedSymbolComponentEngine::UndefinedSymbolComponentEngine( CORBA::ORB_ptr orb,
				    PortableServer::POA_ptr poa,
				    PortableServer::ObjectId * contId, 
				    const char *instanceName,
                                    const char *interfaceName) :
  Engines_Component_i(orb, poa, contId, instanceName, interfaceName,1,true)
{
//  MESSAGE("UndefinedSymbolComponentEngine::UndefinedSymbolComponentEngine activate object instanceName("
//          << instanceName << ") interfaceName(" << interfaceName << ")" )
  _thisObj = this ;
  _id = _poa->activate_object(_thisObj);
}

UndefinedSymbolComponentEngine::UndefinedSymbolComponentEngine() :
  Engines_Component_i()
{
}

UndefinedSymbolComponentEngine::~UndefinedSymbolComponentEngine()
{
}

extern "C" { long CallUndefined() ; } ;

long UndefinedSymbolComponentEngine::UndefinedSymbol() {
  beginService( " UndefinedSymbolComponentEngine::UndefinedSymbol" );
  int S = 10 ;
  while ( S ) {
    S = sleep( S ) ;
  }
  long value = CallUndefined() ;
  endService( " UndefinedSymbolComponentEngine::UndefinedSymbol"  );
  return value ;
}

extern "C"
{
  PortableServer::ObjectId * UndefinedSymbolComponentEngine_factory
     (CORBA::ORB_ptr orb,
      PortableServer::POA_ptr poa, 
      PortableServer::ObjectId * contId,
      const char *instanceName,
      const char *interfaceName)
  {
    MESSAGE("UndefinedSymbolComponentEngine_factory UndefinedSymbolComponentEngine ("
            << instanceName << "," << interfaceName << ")");
    UndefinedSymbolComponentEngine * myUndefinedSymbolComponent 
      = new UndefinedSymbolComponentEngine(orb, poa, contId, instanceName, interfaceName);
    return myUndefinedSymbolComponent->getId() ;
  }
}


