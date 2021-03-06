// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef STLMAP_H
#define	STLMAP_H

#include <map>

using namespace std;

//================================================================//
// STLMap
//================================================================//
template < typename KEY, typename TYPE, typename COMPARE = less < KEY > >
class STLMap :
	public map < KEY, TYPE, COMPARE > {
public:

	typedef typename map < KEY, TYPE, COMPARE >::iterator iterator;

	//----------------------------------------------------------------//
	bool contains ( const KEY& key ) const {
		return ( this->find ( key ) != this->end ());
	}

	//----------------------------------------------------------------//
	TYPE* key_for_value ( const KEY& key ) {
	
		iterator it = this->find ( key );
		if ( it != this->end ()) {
			return &it->second;
		}
		return 0;
	}
	
	//----------------------------------------------------------------//
	STLMap () {
	}
	
	//----------------------------------------------------------------//
	STLMap ( const COMPARE& comp ) :
		map < KEY, TYPE, COMPARE >( comp ) {
	}
};

//================================================================//
// STLMap < TYPE* >
//================================================================//
template < typename KEY, typename TYPE, typename COMPARE >
class STLMap < KEY, TYPE*, COMPARE > :
	public map < KEY, TYPE*, COMPARE > {
public:

	typedef typename map < KEY, TYPE* >::iterator iterator;

	//----------------------------------------------------------------//
	bool contains ( const KEY& key ) {
		return ( this->find ( key ) != this->end ());
	}

	//----------------------------------------------------------------//
	TYPE* value_for_key ( const KEY& key ) {
	
		iterator it = this->find ( key );
		if ( it != this->end ()) {
			return it->second;
		}
		return 0;
	}
};

#endif
