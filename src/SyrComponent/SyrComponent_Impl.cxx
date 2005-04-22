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
//  File   : SyrComponent_Impl.cxx
//  Author : Jean Rahuel, CEA
//  Module : SuperVisionTest

using namespace std;
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string>

//#include "utilities.h"

#include "SyrComponent_Impl.hxx"
#include "Adder_Impl.hxx"

SyrComponent_Impl::SyrComponent_Impl( CORBA::ORB_ptr orb ,
				      PortableServer::POA_ptr poa ,
				      PortableServer::ObjectId * contId , 
				      const char *instanceName ,
                                      const char *interfaceName ,
                                      const bool kactivate ) :
  Engines_Component_i(orb, poa, contId, instanceName, interfaceName,1,true) {
  MESSAGE("SyrComponent_Impl::SyrComponent_Impl this " << hex << this << dec
          << "activate object instanceName("
          << instanceName << ") interfaceName(" << interfaceName << ")" )
  if ( kactivate ) {
    _thisObj = this ;
    _id = _poa->activate_object(_thisObj);
  }
}

SyrComponent_Impl::SyrComponent_Impl() {
}

SyrComponent_Impl::~SyrComponent_Impl() {
}

long SyrComponent_Impl::C_ISEVEN( const long anInteger ) {
  bool RetVal ;
  beginService( " SyrComponent_Impl::C_ISEVEN" );
  sendMessage(NOTIF_STEP, "SyrComponent_Impl::C_ISEVEN is Computing");
//  int S = 1+(int) (2.0*rand()/(RAND_MAX+1.0));
  int S = 1 ;
  while ( S ) {
    S = sleep(S);
  }
  RetVal = ( anInteger & 1 ) == 0 ;
  endService( " SyrComponent_Impl::C_ISEVEN"  );
  return RetVal ;
}

long SyrComponent_Impl::C_ISONE( const long anOddInteger ) {
  bool RetVal ;
  beginService( " SyrComponent_Impl::C_ISONE" );
  sendMessage(NOTIF_STEP, "SyrComponent_Impl::C_ISONE is Computing");
//  int S = 1+(int) (2.0*rand()/(RAND_MAX+1.0));
  int S = 1 ;
  while ( S ) {
    S = sleep(S);
  }
  RetVal = ( anOddInteger == 1 ) ;
  endService( " SyrComponent_Impl::C_ISONE"  );
  return RetVal ;
}

long SyrComponent_Impl::C_M3( const long anOddInteger ) {
  beginService( " SyrComponent_Impl::C_M3" );
  sendMessage(NOTIF_STEP, "SyrComponent_Impl::C_M3 is Computing");
//  int S = 1+(int) (2.0*rand()/(RAND_MAX+1.0));
  int S = 1 ;
  while ( S ) {
    S = sleep(S);
  }
  endService( " SyrComponent_Impl::C_M3"  );
  if ( C_ISEVEN( anOddInteger ) )
    return 0 ;
  return ( 3*anOddInteger ) ;
}

long SyrComponent_Impl::C_M3P1( const long anOddInteger ) {
  beginService( " SyrComponent_Impl::C_M3P1" );
  sendMessage(NOTIF_STEP, "SyrComponent_Impl::C_M3P1 is Computing");
//  int S = 1+(int) (2.0*rand()/(RAND_MAX+1.0));
  int S = 1 ;
  while ( S ) {
    S = sleep(S);
  }
  endService( " SyrComponent_Impl::C_M3P1"  );
  if ( C_ISEVEN( anOddInteger ) )
    return 0 ;
  return ( 3*anOddInteger + 1 ) ;
}

long SyrComponent_Impl::C_DIV2( const long anEvenInteger ) {
  beginService( " SyrComponent_Impl::C_DIV2" );
  sendMessage(NOTIF_STEP, "SyrComponent_Impl::C_DIV2 is Computing");
//  int S = 1+(int) (2.0*rand()/(RAND_MAX+1.0));
  int S = 1 ;
  while ( S ) {
    S = sleep(S);
  }
  endService( " SyrComponent_Impl::C_DIV2"  );
  if ( !C_ISEVEN( anEvenInteger ) )
    return 0 ;
  return ( anEvenInteger >> 1 ) ;
}

long SyrComponent_Impl::C_INCR( const long aCount ) {
  beginService( " SyrComponent_Impl::C_INCR" );
  sendMessage(NOTIF_STEP, "SyrComponent_Impl::C_INCR is Computing");
//  int S = 1+(int) (2.0*rand()/(RAND_MAX+1.0));
  int S = 1 ;
  while ( S ) {
    S = sleep(S);
  }
  endService( " SyrComponent_Impl::C_INCR"  );
  return ( aCount + 1 ) ;
}

long SyrComponent_Impl::C_MIN( const long aMinVal , const long anInteger ) {
  beginService( " SyrComponent_Impl::C_MIN" );
  sendMessage(NOTIF_STEP, "SyrComponent_Impl::C_MIN is Computing");
//  int S = 1+(int) (2.0*rand()/(RAND_MAX+1.0));
  int S = 1 ;
  while ( S ) {
    S = sleep(S);
  }
  int min = aMinVal ;
  if ( anInteger < min || aMinVal == 0 ) {
    min = anInteger ;
  }
  string trace = "SyrComponent_Impl::C_MIN : " ;
  char cmin[ 30 ] ;
  sprintf( cmin , "%d" , min ) ;
  trace += cmin ;
  sendMessage(NOTIF_TRACE, trace.c_str() );
  endService( " SyrComponent_Impl::C_MIN"  );
  return min ;
}

long SyrComponent_Impl::C_MAX( const long aMaxVal , const long anInteger ) {
  beginService( " SyrComponent_Impl::C_MAX" );
  sendMessage(NOTIF_STEP, "SyrComponent_Impl::C_MAX is Computing");
//  int S = 1+(int) (2.0*rand()/(RAND_MAX+1.0));
  int S = 1 ;
  while ( S ) {
    S = sleep(S);
  }
  int max = aMaxVal ;
  if ( anInteger > max ) {
    max = anInteger ;
  }
  string trace = "SyrComponent_Impl::C_MAX : " ;
  char cmax[ 30 ] ;
  sprintf( cmax , "%d" , max ) ;
  trace += cmax ;
  sendMessage(NOTIF_TRACE, trace.c_str() );
  endService( " SyrComponent_Impl::C_MAX"  );
  return max ;
}

SuperVisionTest::ListOfSyr_ptr SyrComponent_Impl::C_LISTOFSYR() {
  beginService( " SyrComponent_Impl::C_LISTOFSYR" );
  sendMessage(NOTIF_STEP, "SyrComponent_Impl::C_LISTOFSYR is Computing");
//  int S = 1+(int) (2.0*rand()/(RAND_MAX+1.0));
  int S = 1 ;
  while ( S ) {
    S = sleep(S);
  }
  ListOfSyr_Impl * aNewListOfSyr = new ListOfSyr_Impl( _orb , _poa, _contId,
                        instanceName() , interfaceName() ,
                        graphName() , nodeName() ) ;
  SuperVisionTest::ListOfSyr_var iobject = (SuperVisionTest::ListOfSyr_var ) NULL ;
  PortableServer::ObjectId * id = aNewListOfSyr->getId() ;
  CORBA::Object_var obj = _poa->id_to_reference(*id);
  iobject = SuperVisionTest::ListOfSyr::_narrow(obj) ;
  endService( " SyrComponent_Impl::C_LISTOFSYR"  );
  return SuperVisionTest::ListOfSyr::_duplicate( iobject ) ;
//  return ( aNewListOfSyr._retn() ) ;
}

SuperVisionTest::ListOfSyr_ptr SyrComponent_Impl::C_AVERAGE(
                       const SuperVisionTest::ListOfSyr_ptr aListOfSyr ,
                       const long anInteger ,
                       const long aCount ,
                       double & anAverage ) {
  beginService( " SyrComponent_Impl::C_AVERAGE" );
  sendMessage(NOTIF_STEP, "SyrComponent_Impl::C_AVERAGE is Computing");
//  int S = 1+(int) (2.0*rand()/(RAND_MAX+1.0));
  int S = 1 ;
  while ( S ) {
    S = sleep(S);
  }
  SuperVisionTest::SeqOfSyr * aSeqOfSyr = aListOfSyr->GetSeqOfSyr() ;
  int len = aSeqOfSyr->length() ;
  aSeqOfSyr->length( len + 1 ) ;
  (*aSeqOfSyr)[ len ] = anInteger ;
  aListOfSyr->SetSeqOfSyr( *aSeqOfSyr ) ;
  anAverage = 0 ;
  int i ;
  for ( i = 0 ; i < len + 1 ; i++ ) {
    anAverage += (*aSeqOfSyr)[ i ] ;
  }
  anAverage = anAverage / ( len + 1 ) ;
  string end = " SyrComponent_Impl::C_AVERAGE " ;
  char caverage[ 30 ] ;
  sprintf( caverage , "%fd" , anAverage ) ;
  end += caverage ;
  endService( end.c_str() );
  return SuperVisionTest::ListOfSyr::_duplicate( aListOfSyr ) ;
}

SuperVisionTest::Syr_ptr SyrComponent_Impl::Init( const long anOddInteger ) {
  beginService( "SyrComponent_Impl::Init" );
  sendMessage(NOTIF_STEP, "SyrComponent_Impl creates Syr_Impl");
//  int S = 1+(int) (2.0*rand()/(RAND_MAX+1.0));
  int S = 1 ;
  while ( S ) {
    S = sleep(S);
  }
  Syr_Impl * mySyr ;
  mySyr = new Syr_Impl( _orb , _poa, _contId,
                        instanceName() , interfaceName() ,
                        graphName() , nodeName() , anOddInteger ) ;
  SuperVisionTest::Syr_var iobject = (SuperVisionTest::Syr_var ) NULL ;
  PortableServer::ObjectId * id = mySyr->getId() ;
  CORBA::Object_var obj = _poa->id_to_reference(*id);
  iobject = SuperVisionTest::Syr::_narrow(obj) ;
  endService( "SyrComponent_Impl::Init" );
  return SuperVisionTest::Syr::_duplicate(iobject) ;
}

ListOfSyr_Impl::ListOfSyr_Impl( CORBA::ORB_ptr orb ,
		    PortableServer::POA_ptr poa ,
	       	    PortableServer::ObjectId * contId , 
		    const char * instanceName ,
                    const char * interfaceName , 
		    const char * graphName ,
                    const char * nodeName ) :
  Engines_Component_i(orb, poa, contId, instanceName, interfaceName,1,true) {
  Names( graphName , nodeName ) ;
  MESSAGE("ListOfSyr_Impl::ListOfSyr_Impl activate object instanceName("
          << instanceName << ") interfaceName(" << interfaceName << ") --> "
          << hex << (void *) this << dec )
  beginService( "ListOfSyr_Impl::ListOfSyr_Impl" );
  _thisObj = this ;
  _id = _poa->activate_object(_thisObj);
  sendMessage(NOTIF_STEP, "ListOfSyr_Impl is Created");
  endService( "ListOfSyr_Impl::ListOfSyr_Impl" );
}

ListOfSyr_Impl::ListOfSyr_Impl() {
}

ListOfSyr_Impl::~ListOfSyr_Impl() {
  beginService( "ListOfSyr_Impl::~ListOfSyr_Impl" );
  endService( "ListOfSyr_Impl::~ListOfSyr_Impl" );
}

SuperVisionTest::SeqOfSyr * ListOfSyr_Impl::GetSeqOfSyr() {
  SuperVisionTest::SeqOfSyr_var aSeqOfSyr = new SuperVisionTest::SeqOfSyr( _SeqOfSyr ) ;
  return ( aSeqOfSyr._retn() ) ;
}

void ListOfSyr_Impl::SetSeqOfSyr( const SuperVisionTest::SeqOfSyr & aSeqOfSyr ) {
  _SeqOfSyr = aSeqOfSyr ;
  return ;
}

extern "C"
{
  PortableServer::ObjectId * SyrComponentEngine_factory
     (CORBA::ORB_ptr orb,
      PortableServer::POA_ptr poa, 
      PortableServer::ObjectId * contId,
      const char *instanceName,
      const char *interfaceName)
  {
    MESSAGE("SyrComponentEngine_factory SyrComponentEngine ("
            << instanceName << "," << interfaceName << "," << getpid() << ")");
    SyrComponent_Impl * mySyrComponent 
      = new SyrComponent_Impl(orb, poa, contId, instanceName, interfaceName);
    return mySyrComponent->getId() ;
  }
}

Syr_Impl::Syr_Impl( CORBA::ORB_ptr orb ,
		    PortableServer::POA_ptr poa ,
	       	    PortableServer::ObjectId * contId , 
		    const char * instanceName ,
                    const char * interfaceName , 
		    const char * graphName ,
                    const char * nodeName ,
                    const long anOddInteger ) :
  SyrComponent_Impl(orb, poa, contId, instanceName, interfaceName,false) {
  Names( graphName , nodeName ) ;
  MESSAGE("Syr_Impl::Syr_Impl activate object instanceName("
          << instanceName << ") interfaceName(" << interfaceName << ") --> "
          << hex << (void *) this << dec )
  beginService( "Syr_Impl::Syr_Impl" );
  _thisObj = this ;
  _id = _poa->activate_object(_thisObj);
  _InitialInteger = anOddInteger ;
  _CurrentInteger = anOddInteger ;
  _Count = 0 ;
  sendMessage(NOTIF_STEP, "Syr_Impl is Created");
  endService( "Syr_Impl::Syr_Impl" );
}

Syr_Impl::Syr_Impl() {
}

Syr_Impl::~Syr_Impl() {
  beginService( "Syr_Impl::~Syr_Impl" );
  endService( "Syr_Impl::~Syr_Impl" );
}

long Syr_Impl::Initial() {
  beginService( " Syr_Impl::Initial" );
  sendMessage(NOTIF_STEP, "Syr_Impl::Initial is Computing");
//  int S = 1+(int) (2.0*rand()/(RAND_MAX+1.0));
  int S = 1 ;
  while ( S ) {
    S = sleep(S);
  }
  endService( " Syr_Impl::Initial"  );
  return _InitialInteger ;
}

long Syr_Impl::Current() {
  beginService( " Syr_Impl::Current" );
  sendMessage(NOTIF_STEP, "Syr_Impl::Current is Computing");
//  int S = 1+(int) (2.0*rand()/(RAND_MAX+1.0));
  int S = 1 ;
  while ( S ) {
    S = sleep(S);
  }
  endService( " Syr_Impl::Current"  );
  return _CurrentInteger ;
}

long Syr_Impl::IsEven() {
  bool RetVal ;
  beginService( " Syr_Impl::IsEven" );
  sendMessage(NOTIF_STEP, "Syr_Impl::IsEven is Computing");
//  int S = 1+(int) (2.0*rand()/(RAND_MAX+1.0));
  int S = 1 ;
  while ( S ) {
    S = sleep(S);
  }
  RetVal = ( _CurrentInteger & 1 ) == 0 ;
  MESSAGE( " Syr_Impl::IsEven " << _CurrentInteger << " " << RetVal );
  endService( " Syr_Impl::IsEven"  );
  return RetVal ;
}

long Syr_Impl::IsOne() {
  bool RetVal ;
  beginService( " Syr_Impl::IsOne" );
  sendMessage(NOTIF_STEP, "Syr_Impl::IsOne is Computing");
//  int S = 1+(int) (2.0*rand()/(RAND_MAX+1.0));
  int S = 1 ;
  while ( S ) {
    S = sleep(S);
  }
  RetVal = ( _CurrentInteger == 1 ) ;
  MESSAGE( " Syr_Impl::IsOne " << _CurrentInteger << " " << RetVal );
  endService( " Syr_Impl::IsOne"  );
  return RetVal ;
}

long Syr_Impl::Count() {
  beginService( " Syr_Impl::Count" );
  sendMessage(NOTIF_STEP, "Syr_Impl::Count is Computing");
//  int S = 1+(int) (2.0*rand()/(RAND_MAX+1.0));
  int S = 1 ;
  while ( S ) {
    S = sleep(S);
  }
  MESSAGE( " Syr_Impl::Count " << _Count );
  endService( " Syr_Impl::Count"  );
  return _Count ;
}

void Syr_Impl::M3p1() {
  beginService( " Syr_Impl::M3p1" );
  sendMessage(NOTIF_STEP, "Syr_Impl::M3p1 is Computing");
//  int S = 1+(int) (2.0*rand()/(RAND_MAX+1.0));
  int S = 1 ;
  while ( S ) {
    S = sleep(S);
  }
  if ( IsEven() )
    _CurrentInteger = 0 ;
  else
    _CurrentInteger = 3*_CurrentInteger + 1 ;
  MESSAGE( " Syr_Impl::M3p1 " << _CurrentInteger );
  endService( " Syr_Impl::M3p1"  );
}

void Syr_Impl::Div2() {
  beginService( " Syr_Impl::Div2" );
  sendMessage(NOTIF_STEP, "Syr_Impl::Div2 is Computing");
//  int S = 1+(int) (2.0*rand()/(RAND_MAX+1.0));
  int S = 1 ;
  while ( S ) {
    S = sleep(S);
  }
  if ( !IsEven() )
    _CurrentInteger = 0 ;
  else
    _CurrentInteger = ( _CurrentInteger >> 1 ) ;
  MESSAGE( " Syr_Impl::Div2 " << _CurrentInteger );
  endService( " Syr_Impl::Div2"  );
}

void Syr_Impl::Incr() {
  beginService( " Syr_Impl::Incr" );
  sendMessage(NOTIF_STEP, "Syr_Impl::Incr is Computing");
//  int S = 1+(int) (2.0*rand()/(RAND_MAX+1.0));
  int S = 1 ;
  while ( S ) {
    S = sleep(S);
  }
  _Count = _Count + 1 ;
  MESSAGE( " Syr_Impl::Incr " << _Count );
  endService( " Syr_Impl::Incr"  );
}



