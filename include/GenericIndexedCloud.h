// SPDX-License-Identifier: LGPL-2.0-or-later
// Copyright © EDF R&D / TELECOM ParisTech (ENST-TSI)

#pragma once

//Local
#include "GenericCloud.h"

namespace CCCoreLib
{
	//! A generic 3D point cloud with index-based point access
	/** Implements the GenericCloud interface.
	**/
	class CC_CORE_LIB_API GenericIndexedCloud : virtual public GenericCloud
	{

	public:
		//! Default constructor
		GenericIndexedCloud() = default;

		//! Default destructor
		~GenericIndexedCloud() override = default;

		//! Returns a given local point (pointer to)
		/**	Virtual method to request a local point with a specific index.
			WARNINGS:
			- the returned object may not be persistent!
			- THIS METHOD MAY NOT BE COMPATIBLE WITH PARALLEL STRATEGIES
			(see the DgmOctree::executeFunctionForAllCellsAtLevel_MT and
			DgmOctree::executeFunctionForAllCellsAtStartingLevel_MT methods).
			Consider the other version of getLocalPoint instead or the
			GenericIndexedCloudPersist class.
			\param index of the requested point (between 0 and the cloud size minus 1)
			\return the requested point (undefined behavior if index is invalid)
		**/
		virtual const CCVector3* getLocalPoint(unsigned index) const = 0;

		//! Returns a given local point (copy)
		/**	Virtual method to request a local point with a specific index.
			Index must be valid (undefined behavior if index is invalid)
			\param index of the requested point (between 0 and the cloud size minus 1)
			\param P output point
		**/
		virtual void getLocalPoint(unsigned index, CCVector3& P) const
		{
			P = *getLocalPoint(index);
		}

		//! Returns a given global point (copy)
		/**	Virtual method to request a global point with a specific index.
			Index must be valid (undefined behavior if index is invalid)
			\param index of the requested point (between 0 and the cloud size minus 1)
			\param P output point
		**/
		virtual void getGlobalPoint(unsigned index, CCVector3d& P) const
		{
			P = toGlobal(*getLocalPoint(index));
		}

		//! Returns whether normals are available
		virtual bool normalsAvailable() const { return false; }

		//! If per-point normals are available, returns the one at a specific index
		/** \warning If overriden, this method should return a valid normal for all points
		**/
		virtual const CCVector3* getNormal(unsigned index) const { (void)index; return nullptr; }
	};
}
