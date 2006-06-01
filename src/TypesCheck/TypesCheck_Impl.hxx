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
// See http://www.salome-platform.org/ or email : webmaster.salome@opencascade.com
//
//
//
//  File   : SyrComponent_Impl.hxx
//  Author : Jean Rahuel
//  Module : SuperVisionTest
//  $Header:

#ifndef _TYPESCHECK_IMPL_HXX_
#define _TYPESCHECK_IMPL_HXX_

#include <SALOMEconfig.h>
#include CORBA_SERVER_HEADER(AddComponent)
#include CORBA_SERVER_HEADER(TypesCheck)
#include CORBA_SERVER_HEADER(SALOME_Component)
#include "SALOME_Component_i.hxx"

#include "AddComponent_Impl.hxx"

class TypesCheck_Impl : public POA_SuperVisionTest::TypesCheck ,
                        public Engines_Component_i {
  public:
    TypesCheck_Impl() ;
    TypesCheck_Impl( CORBA::ORB_ptr orb ,
		     PortableServer::POA_ptr poa ,
		     PortableServer::ObjectId * contId , 
		     const char *instanceName ,
                     const char *interfaceName ,
                     const bool kactivate = true ) ;

    virtual ~TypesCheck_Impl();

    virtual void StringCheck( const char * InString , _CORBA_String_out OutString ) ;

    virtual void BoolCheck( CORBA::Boolean InBool , CORBA::Boolean & OutBool ) ;

    virtual void CharCheck( unsigned char InChar , unsigned char & OutChar ) ;

    virtual void ShortCheck( short InShort , short & OutShort ) ;

    virtual void IntCheck( int InInt , int & OutInt ) ;

    virtual void LongCheck( CORBA::Long InLong , CORBA::Long & OutLong ) ;

    virtual void FloatCheck( float InFloat , float & OutFloat ) ;

    virtual void DoubleCheck( double InDouble , double & OutDouble ) ;

    virtual void ObjRefCheck( SuperVisionTest::Adder_ptr InObjRef , SuperVisionTest::Adder_out OutObjRef ) ;

    virtual void MiscTypes( const char * InString , CORBA::Boolean InBool , unsigned char InChar , short InShort , CORBA::Long InLong , float InFloat , double InDouble , SuperVisionTest::Adder_ptr InObjRef , _CORBA_String_out OutString , CORBA::Boolean & OutBool , unsigned char & OutChar , short & OutShort , CORBA::Long & OutLong , float & OutFloat , double & OutDouble , SuperVisionTest::Adder_out OutObjRef ) ;

  private:


};

extern "C"
  PortableServer::ObjectId * TypesCheckEngine_factory ( CORBA::ORB_ptr orb ,
                                                        PortableServer::POA_ptr poa , 
                                                        PortableServer::ObjectId * contId ,
                                                        const char *instanceName ,
                                                        const char *interfaceName ) ;

#endif
