//  SuperVisionTest SyrComponent : example of component performing some mathinatical operations
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
//  File   : SyrComponent_Impl.hxx
//  Author : Jean Rahuel, CEA
//  Module : SuperVisionTest
//  $Header:

#ifndef _SYRCOMPONENT_IMPL_HXX_
#define _SYRCOMPONENT_IMPL_HXX_

//#include <iostream.h>
#include <SALOMEconfig.h>
#include CORBA_SERVER_HEADER(SyrComponent)
#include CORBA_SERVER_HEADER(SALOME_Component)
#include "SALOME_Component_i.hxx"

class SyrComponent_Impl :  public POA_SuperVisionTest::SyrComponent ,
                           public Engines_Component_i {
public:
  SyrComponent_Impl() ;
  SyrComponent_Impl( CORBA::ORB_ptr orb ,
		     PortableServer::POA_ptr poa ,
		     PortableServer::ObjectId * contId , 
		     const char *instanceName ,
                     const char *interfaceName ,
                     const bool kactivate = true ) ;

  virtual ~SyrComponent_Impl();

  virtual long C_ISEVEN( const long anInteger ) ;

  virtual long C_ISONE( const long anOddInteger ) ;

  virtual long C_M3( const long anOddInteger ) ;

  virtual long C_M3P1( const long anOddInteger ) ;

  virtual long C_DIV2( const long anEvenInteger ) ;

  virtual long C_INCR( const long aCount ) ;

  virtual long C_MIN( const long aMinVal , const long anInteger ) ;

  virtual long C_MAX( const long aMaxVal , const long anInteger ) ;

  virtual SuperVisionTest::ListOfSyr_ptr C_LISTOFSYR() ;

  virtual SuperVisionTest::ListOfSyr_ptr C_AVERAGE(
                       const SuperVisionTest::ListOfSyr_ptr aListOfSyr ,
                       const long anInteger ,
                       const long aCount ,
                       double & anAverage ) ;

  virtual SuperVisionTest::Syr_ptr Init( const long anOddInteger ) ;

private:

};

class ListOfSyr_Impl :  public POA_SuperVisionTest::ListOfSyr ,
                        public Engines_Component_i {
public:
  ListOfSyr_Impl( CORBA::ORB_ptr orb ,
	          PortableServer::POA_ptr poa ,
	          PortableServer::ObjectId * contId , 
	          const char *instanceName ,
                  const char *interfaceName , 
                  const char * graphName ,
                  const char * nodeName ) ;
  ListOfSyr_Impl() ;
  virtual ~ListOfSyr_Impl();

  virtual SuperVisionTest::SeqOfSyr * GetSeqOfSyr() ;

  virtual void SetSeqOfSyr( const SuperVisionTest::SeqOfSyr & ) ;

private:
  SuperVisionTest::SeqOfSyr _SeqOfSyr ;

};

extern "C"
  PortableServer::ObjectId * SyrComponentEngine_factory
                                   ( CORBA::ORB_ptr orb ,
                                     PortableServer::POA_ptr poa , 
                                     PortableServer::ObjectId * contId ,
                                     const char *instanceName ,
                                     const char *interfaceName ) ;

class Syr_Impl :  public POA_SuperVisionTest::Syr ,
                  public SyrComponent_Impl {
public:
  Syr_Impl() ;
  Syr_Impl( CORBA::ORB_ptr orb ,
	    PortableServer::POA_ptr poa ,
	    PortableServer::ObjectId * contId , 
	    const char *instanceName ,
            const char *interfaceName , 
            const char * graphName ,
            const char * nodeName ,
            const long anOddInteger );

  virtual ~Syr_Impl();

  virtual long Initial() ;

  virtual long Current() ;

  virtual long IsEven() ;

  virtual long IsOne() ;

  virtual long Count() ;

  virtual void M3p1() ;

  virtual void Div2() ;

  virtual void Incr() ;

private:

  long _InitialInteger ;
  long _CurrentInteger ;
  long _Count ;

};

#endif
