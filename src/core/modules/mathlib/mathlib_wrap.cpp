/**
* =============================================================================
* Source Python
* Copyright (C) 2012-2015 Source Python Development Team.  All rights reserved.
* =============================================================================
*
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License, version 3.0, as published by the
* Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
* details.
*
* You should have received a copy of the GNU General Public License along with
* this program.  If not, see <http://www.gnu.org/licenses/>.
*
* As a special exception, the Source Python Team gives you permission
* to link the code of this program (as well as its derivative works) to
* "Half-Life 2," the "Source Engine," and any Game MODs that run on software
* by the Valve Corporation.  You must obey the GNU General Public License in
* all respects for all other code used.  Additionally, the Source.Python
* Development Team grants this exception to all derivative works.
*/

//-----------------------------------------------------------------------------
// Includes.
//-----------------------------------------------------------------------------
#include "export_main.h"
#include "mathlib/vector.h"
#include "mathlib/mathlib.h"
#include "utilities/sp_util.h"
#include "modules/memory/memory_tools.h"
#include "modules/mathlib/mathlib.h"


//-----------------------------------------------------------------------------
// Forward declarations.
//-----------------------------------------------------------------------------
void export_vector(scope);
void export_qangle(scope);
void export_quaternion(scope);
void export_cplane_t(scope);
void export_radian_euler(scope);


//-----------------------------------------------------------------------------
// Declare the _mathlib module.
//-----------------------------------------------------------------------------
DECLARE_SP_MODULE(_mathlib)
{
	export_vector(_mathlib);
	export_qangle(_mathlib);
	export_quaternion(_mathlib);
	export_cplane_t(_mathlib);
	export_radian_euler(_mathlib);
}


//-----------------------------------------------------------------------------
// Exports Vector.
//-----------------------------------------------------------------------------
void export_vector(scope _mathlib)
{
	class_<Vector>("Vector", init<float, float, float>())
		.def("__init__", make_constructor(&VectorExt::CreateNullVector))

		.def("__repr__", &VectorExt::__repr__)

		// Members
		.def_readwrite("x",
			&Vector::x
		)

		.def_readwrite("y",
			&Vector::y
		)

		.def_readwrite("z",
			&Vector::z
		)

		// Methods
		.def("init",
			&Vector::Init,
			args("x", "y", "z")
		)

		.def("is_valid",
			&Vector::IsValid,
			"Returns True if the vector is valid."
		)

		.def("invalidated",
			&Vector::Invalidate,
			"Invalidates the vector."
		)

		.def("__getitem__",
			&GetItemIndexer<Vector, float, 0, 2>
		)

		.def("__setitem__",
			&SetItemIndexer<Vector, float, 0, 2>
		)

		.def("as_vector_2D",
			GET_METHOD(Vector2D&, Vector, AsVector2D),
			reference_existing_object_policy()
		)

		.def("random",
			&Vector::Random,
			args("min", "max"),
			"Fills the vector with random values within the given range."
		)

		.def("zero",
			&Vector::Zero,
			"Zeros out the vector."
		)

		.def(self == self)
		.def(self != self)
		.def(self += self)
		.def(self -= self)
		.def(self *= self)
		.def(self *= float())
		.def(self /= self)
		.def(self /= float())
		.def(self += float())
		.def(self -= float())

		.def("negate",
			&Vector::Negate,
			"Negates the vector."
		)

		.def("get_length",
			&Vector::Length,
			"Returns the vector's 3D length."
		)

		.def("get_length_sqr",
			&Vector::LengthSqr,
			"Returns the vector's 3D length as a square product."
		)

		.def("is_zero",
			&Vector::IsZero,
			"Returns True if x, y and z are zero or within the tolerance.",
			(arg("tolerance")=0.01f)
		)

		.def("normalize",
			&Vector::NormalizeInPlace,
			"Normalizes the vector."
		)

		.def("is_length_greater_than",
			&Vector::IsLengthGreaterThan,
			args("value")
		)

		.def("is_length_less_than",
			&Vector::IsLengthLessThan,
			args("value")
		)

		.def("is_within_box",
			&VectorExt::IsWithinBox,
			args("corner1", "corner2"),
			"Returns True if the vector is within the given box coordinates."
		)

		.def("get_distance",
			&Vector::DistTo,
			args("other"),
			"Returns the distance to the other vector."
		)

		.def("get_distance_sqr",
			&Vector::DistToSqr,
			args("other"),
			"Returns the distance to the other vector as a square product."
		)

		.def("mul_add",
			&Vector::MulAdd,
			args("a", "b", "scalar"),
			"Multiply and add. this = a + b * scalar."
		)

		.def("dot",
			&Vector::Dot,
			"Returns the dot product.",
			args("other")
		)

		.def("get_length_2D",
			&Vector::Length2D,
			"Returns the vector's 2D length."
		)

		.def("get_length_2D_sqr",
			&Vector::Length2DSqr,
			"Returns the vector's 2D length as a square product."
		)

		.def(self + self)
		.def(self - self)
		.def(self * self)
		.def(self / self)
		.def(self * float())
		.def(self / float())

		.def("cross",
			&Vector::Cross,
			"Returns the cross product between two vectors.",
			args("other")
		)

		.def("min",
			&Vector::Min,
			"Returns a new vector containing the lowest values of both vectors.",
			args("other")
		)

		.def("max",
			&Vector::Max,
			"Returns a new vector containing the biggest values of both vectors.",
			args("other")
		)

		ADD_MEM_TOOLS(Vector)
	;
}


//-----------------------------------------------------------------------------
// Exports QAngle.
//-----------------------------------------------------------------------------
void export_qangle(scope _mathlib)
{
	class_<QAngle>("QAngle")
		.def(init<float, float, float>())

		.def_readwrite("x",
			&QAngle::x
		)

		.def_readwrite("y",
			&QAngle::y
		)
		
		.def_readwrite("z",
			&QAngle::z
		)

		.def("random",
			&QAngle::Random,
			args("min_val", "max_val"),
			"Generates some random values between <min_val> and <max_val>."
		)

		.def("is_valid",
			&QAngle::IsValid,
			"Returns True if the angle is valid."
		)

		.def("invalidate",
			&QAngle::Invalidate,
			"Invalidates the angle."
		)

		.def("__getitem__",
			&GetItemIndexer<QAngle, float, 0, 2>,
			"Returns the value at the given index."
		)

		.def("__setitem__",
			&SetItemIndexer<QAngle, float, 0, 2>,
			"Sets the value at the given index."
		)

		.def(self == self)
		.def(self != self)
		
		.def(self += self)
		.def(self -= self)
		.def(self *= other<float>())
		.def(self /= other<float>())

		.def("get_length",
			&QAngle::Length,
			"Returns the length of the angle."
		)

		.def("get_length_sqr",
			&QAngle::LengthSqr,
			"Returns the square of the angle's length."
		)

		.def(self + self)
		.def(self - self)
		.def(self * other<float>())
		.def(self / other<float>())

		ADD_MEM_TOOLS(QAngle)
	;
}


//-----------------------------------------------------------------------------
// Exports Quaternion.
//-----------------------------------------------------------------------------
void export_quaternion(scope _mathlib)
{
	class_<Quaternion>("Quaternion")
		.def(init<float, float, float, float>())
		.def(init<RadianEuler>())

		.def("is_valid",
			&Quaternion::IsValid,
			"Returns True if all values are valid."
		)

		.def("invalidate",
			&Quaternion::Invalidate,
			"Invalidates all values."
		)

		.def(self == self)
		.def(self != self)

		.def("__getitem__",
			&GetItemIndexer<Quaternion, float, 0, 3>,
			"Returns the value at the given index."
		)

		.def("__setitem__",
			&SetItemIndexer<Quaternion, float, 0, 3>,
			"Sets the value at the given index."
		)

		.def_readwrite("x",
			&Quaternion::x
		)

		.def_readwrite("y",
			&Quaternion::y
		)

		.def_readwrite("z",
			&Quaternion::z
		)

		.def_readwrite("w",
			&Quaternion::w
		)

		ADD_MEM_TOOLS(Quaternion)
	;
}


//-----------------------------------------------------------------------------
// Exports cplane_t.
//-----------------------------------------------------------------------------
void export_cplane_t(scope _mathlib)
{
	// TODO: Documentation
	class_<cplane_t>("Plane")
		.def_readwrite("normal",
			&cplane_t::normal
		)

		.def_readwrite("dist",
			&cplane_t::dist
		)

		.def_readwrite("type",
			&cplane_t::type
		)

		.def_readwrite("signbits",
			&cplane_t::signbits
		)

		ADD_MEM_TOOLS(cplane_t)
	;
}


//-----------------------------------------------------------------------------
// Exports RadianEuler.
//-----------------------------------------------------------------------------
void export_radian_euler(scope _mathlib)
{
	class_<RadianEuler>("RadianEuler")
		.def(init<float, float, float>())
		.def(init<Quaternion>())
		.def(init<QAngle>())

		.def("to_qangle",
			&RadianEuler::ToQAngle,
			"Converts the instance to a QAngle instance."
		)

		.def("is_valid",
			&RadianEuler::IsValid,
			"Returns True if all values are valid."
		)

		.def("invalidate",
			&RadianEuler::Invalidate,
			"Invalidates all values."
		)

		.def("__getitem__",
			&GetItemIndexer<RadianEuler, float, 0, 2>,
			"Returns the value at the given index."
		)

		.def("__setitem__",
			&SetItemIndexer<RadianEuler, float, 0, 2>,
			"Sets the value at the given index."
		)

		.def_readwrite("x",
			&RadianEuler::x
		)

		.def_readwrite("y",
			&RadianEuler::y
		)

		.def_readwrite("z",
			&RadianEuler::z
		)

		ADD_MEM_TOOLS(RadianEuler)
	;
}
