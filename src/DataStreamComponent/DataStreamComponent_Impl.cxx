//  SuperVisionTest DataStreamComponent : example
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
//  File   : DataStreamComponent_Impl.cxx
//  Author : Jean Rahuel
//  Module : SuperVisionTest

using namespace std;
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string>

#include "DataStreamComponent_Impl.hxx"

DataStreamFactory_Impl::DataStreamFactory_Impl( CORBA::ORB_ptr orb,
				                PortableServer::POA_ptr poa,
				                PortableServer::ObjectId * contId, 
				                const char *instanceName,
                                                const char *interfaceName) :
  Engines_Component_i(orb, poa, contId, instanceName, interfaceName,1,true) {
  MESSAGE("DataStreamFactory_Impl::DataStreamFactory_Impl this " << hex << this << dec
          << "activate object instanceName("
          << instanceName << ") interfaceName(" << interfaceName << ")" )
  _thisObj = this ;
  _id = _poa->activate_object(_thisObj);
}

DataStreamFactory_Impl::DataStreamFactory_Impl() {
}

DataStreamFactory_Impl::~DataStreamFactory_Impl() {
}

void DataStreamFactory_Impl::Setxy( const long x , const long y ) {
  _x = x ;
  _y = y ;
}

void DataStreamFactory_Impl::Getxy( long & x , long & y ) {
  x = _x ;
  y = _y ;
}

void DataStreamFactory_Impl::Add( const long x , const long y , long & z ) {
  z = x+y ;
}
void DataStreamFactory_Impl::Sub( const long x , const long y , long & z ) {
  z = x-y ;
}
void DataStreamFactory_Impl::Mul( const long x , const long y , long & z ) {
  z = x*y ;
}
void DataStreamFactory_Impl::Div( const long x , const long y , long & z ) {
  z = x/y ;
}

DataStreamComponent::DataStream_ptr DataStreamFactory_Impl::NewDataStream() {
  beginService( "DataStreamFactory_Impl::NewDataStream" );
  sendMessage(NOTIF_STEP, "DataStreamFactory_Impl creates DataStream_Impl");
  DataStream_Impl * myDataStream ;
  myDataStream = new DataStream_Impl( _orb , _poa, _contId,
                                      instanceName() , interfaceName() ,
                                      graphName() , nodeName() ) ;
  DataStreamComponent::DataStream_var iobject ;
  PortableServer::ObjectId * id = myDataStream->getId() ;
  CORBA::Object_var obj = _poa->id_to_reference(*id);
  iobject = DataStreamComponent::DataStream::_narrow(obj) ;
  endService( "DataStreamFactory_Impl::NewDataStream" );
  return DataStreamComponent::DataStream::_duplicate(iobject) ;
}

extern "C"
{
  PortableServer::ObjectId * DataStreamFactoryEngine_factory
     (CORBA::ORB_ptr orb,
      PortableServer::POA_ptr poa, 
      PortableServer::ObjectId * contId,
      const char *instanceName,
      const char *interfaceName)
  {
    MESSAGE("DataStreamFactoryEngine_factory DataStreamFactoryEngine ("
            << instanceName << "," << interfaceName << "," << getpid() << ")");
    DataStreamFactory_Impl * myDataStreamFactory 
      = new DataStreamFactory_Impl(orb, poa, contId, instanceName, interfaceName);
    return myDataStreamFactory->getId() ;
  }
}

DataStream_Impl::DataStream_Impl( CORBA::ORB_ptr orb ,
			          PortableServer::POA_ptr poa ,
	       	                  PortableServer::ObjectId * contId , 
		          	  const char * instanceName ,
                                  const char * interfaceName , 
		          	  const char * graphName ,
                                  const char * nodeName ) :
  Engines_Component_i(orb, poa, contId, instanceName, interfaceName,1,true) {
  Names( graphName , nodeName ) ;
  MESSAGE("DataStream_Impl::DataStream_Impl activate object instanceName("
          << instanceName << ") interfaceName(" << interfaceName << ") --> "
          << hex << (void *) this << dec )
  beginService( "DataStream_Impl::DataStream_Impl" );
  _thisObj = this ;
  _id = _poa->activate_object(_thisObj);
  sendMessage(NOTIF_STEP, "DataStream_Impl is Created");
  endService( "DataStream_Impl::DataStream_Impl" );
}

DataStream_Impl::DataStream_Impl() {
}

DataStream_Impl::~DataStream_Impl() {
  beginService( "DataStream_Impl::~DataStream_Impl" );
  endService( "DataStream_Impl::~DataStream_Impl" );
}

void DataStream_Impl::StreamSetxy( const long x , const long y ) {
  _x = x ;
  _y = y ;
}

void DataStream_Impl::StreamGetxy( long & x , long & y ) {
  x = _x ;
  y = _y ;
}

void DataStream_Impl::StreamAdd( const long x , const long y , long & z ) {
  z = x+y ;
}
void DataStream_Impl::StreamSub( const long x , const long y , long & z ) {
  z = x-y ;
}
void DataStream_Impl::StreamMul( const long x , const long y , long & z ) {
  z = x*y ;
}
void DataStream_Impl::StreamDiv( const long x , const long y , long & z ) {
  z = x/y ;
}
