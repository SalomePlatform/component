//  SuperVisionTest DataStreamComponent : example of component
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
//  File   : DataStreamComponent_Impl.hxx
//  Author : Jean Rahuel
//  Module : SuperVisionTest
//  $Header:

#ifndef _DATASTREAMINTERFACE_IMPL_HXX_
#define _DATASTREAMINTERFACE_IMPL_HXX_

#include <SALOMEconfig.h>
#include CORBA_SERVER_HEADER(DataStreamComponent)
#include CORBA_SERVER_HEADER(SALOME_Component)
#include "SALOME_Component_i.hxx"

class DataStreamFactory_Impl :  public POA_DataStreamComponent::DataStreamFactory ,
                                public Engines_Component_i {
public:
  DataStreamFactory_Impl() ;
  DataStreamFactory_Impl( CORBA::ORB_ptr orb,
		          PortableServer::POA_ptr poa,
		          PortableServer::ObjectId * contId, 
		          const char *instanceName,
                          const char *interfaceName);

  virtual ~DataStreamFactory_Impl();

  virtual void Setxy( const long x , const long y ) ;

  virtual void Getxy( long & x , long & y ) ;

  virtual void Add( const long x , const long y , long & z ) ;
  virtual void Sub( const long x , const long y , long & z ) ;
  virtual void Mul( const long x , const long y , long & z ) ;
  virtual void Div( const long x , const long y , long & z ) ;

  virtual DataStreamComponent::DataStream_ptr NewDataStream() ;

private:

  long _x ;
  long _y ;

};

extern "C"
  PortableServer::ObjectId * DataStreamFactoryEngine_factory
                                   ( CORBA::ORB_ptr orb ,
                                     PortableServer::POA_ptr poa , 
                                     PortableServer::ObjectId * contId ,
                                     const char *instanceName ,
                                     const char *interfaceName ) ;


class DataStream_Impl :  public POA_DataStreamComponent::DataStream ,
                         public Engines_Component_i {
public:
  DataStream_Impl() ;
  DataStream_Impl( CORBA::ORB_ptr orb ,
	           PortableServer::POA_ptr poa ,
	           PortableServer::ObjectId * contId , 
	           const char *instanceName ,
                   const char *interfaceName , 
                   const char * graphName ,
                   const char * nodeName );

  virtual ~DataStream_Impl();

  virtual void StreamSetxy( const long x , const long y ) ;

  virtual void StreamGetxy( long & x , long & y ) ;

  virtual void StreamAdd( const long x , const long y , long & z ) ;
  virtual void StreamSub( const long x , const long y , long & z ) ;
  virtual void StreamMul( const long x , const long y , long & z ) ;
  virtual void StreamDiv( const long x , const long y , long & z ) ;

private:

  long _x ;
  long _y ;

};

#endif