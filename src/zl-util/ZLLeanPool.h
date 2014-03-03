// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	ZLLEANPOOL_H
#define	ZLLEANPOOL_H

#include <zl-util/ZLLeanArray.h>
#include <zl-util/ZLLeanStack.h>

//================================================================//
// ZLLeanPool
//================================================================//
template < typename TYPE, size_t CHUNKSIZE = 64, size_t MAXCHUNKS = 1024 >
class ZLLeanPool {
private:

	ZLLeanStack < TYPE*, 1 >			mChunks;
	ZLLeanStack < TYPE*, CHUNKSIZE >	mFree;

	//----------------------------------------------------------------//
	void More () {
	
		if ( this->mChunks.Size () < MAXCHUNKS ) {
	
			TYPE* chunk = ( TYPE* )malloc ( CHUNKSIZE * sizeof ( TYPE ));
			this->mChunks.Push ( chunk );
			
			for ( size_t i = 0; i < CHUNKSIZE; ++i ) {
				this->mFree.Push ( &chunk [ i ]);
			}
		}
	}

public:

	//----------------------------------------------------------------//
	TYPE* Alloc () {
		
		size_t top = this->mFree.GetTop ();
		
		if ( !top ) {
			this->More ();
		}
		
		top = this->mFree.GetTop ();
		if ( top ) {
		
			TYPE* type = this->mFree.Pop ();
			new ( type ) TYPE ();
			return type;
		}
		return 0;
	}

	//----------------------------------------------------------------//
	void Clear () {
		
		size_t totalChunks = this->mChunks.Size ();
		for ( size_t i = 0; i < totalChunks; ++i ) {
			
			TYPE* chunk = this->mChunks [ i ];
			for ( size_t j = 0; j < CHUNKSIZE; ++j ) {
				TYPE* type = &chunk [ i ];
				type->TYPE::~TYPE ();
			}
		}
		this->mChunks.Clear ();
		this->mFree.Clear ();
	}

	//----------------------------------------------------------------//
	void Free ( TYPE* type ) {
		
		if ( type ) {
			type->TYPE::~TYPE ();
			this->mFree.Push ( type );
		}
	}
	
	//----------------------------------------------------------------//
	~ZLLeanPool () {
		
		this->Clear ();
	}
};

#endif