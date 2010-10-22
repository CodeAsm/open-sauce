/*
    BlamLib: .NET SDK for the Blam Engine

    Copyright (C) 2005-2010  Kornner Studios (http://kornner.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "Precompile.hpp"
#include "XNA/XNA.hpp"
#using <System.Drawing.dll>

// specify these headers explicitly so we don't get C4793 warnings
// "function compiled as native"
__CPP_CODE_START__

//#ifndef _X86_
//	#define _X86_
//#endif
#ifndef LOWLEVEL_NO_X360
	#include <Xboxmath.h>
	#include <XGraphics.h>
#else
	#include <xnamath.h>
#endif
#include <D3dx9math.h>
#include <d3d9.h>

#include "XNA/XNA.inl"
__CPP_CODE_END__


__MCPP_CODE_START__
namespace LowLevel { namespace Xna {
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.Halfs.inl"

//////////////////////////////////////////////////////////////////////////
//

	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.Color.inl"

	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.UByte4.inl"

	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.Short2.inl"
	
	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.Short4.inl"

	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.UByte4N.inl"

	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.Short2N.inl"

	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.Short4N.inl"

	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.UShort2N.inl"

	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.UShort4N.inl"

	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.UDec3.inl"

	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.Dec3N.inl"

	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.Float16Two.inl"

	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.Float16Four.inl"

	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.UShort2.inl"

	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.UShort4.inl"

	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.UDHen3N.inl"

	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.DHen3N.inl"

	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.UHenD3N.inl"

	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.UDec4N.inl"

	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.Byte4N.inl"

// Legacy:

	//////////////////////////////////////////////////////////////////////////
	#define __XNA_MATH_IMPL_CODE_INCLUDE_ID __XNA_MATH_IMPL_CODE_CLR_CPP
	#include "XNA/MathImpl.HenD3N.inl"
}; };
//////////////////////////////////////////////////////////////////////////

#ifndef LOWLEVEL_NO_X360
namespace LowLevel { namespace Xbox360 {

	mcpp_bool Graphics::FormatIsTiled(mcpp_uint fmt)
	{
		return ::Internal::FormatIsTiled(fmt);
	}

	mcpp_uint Graphics::GetFormatSize(mcpp_uint fmt)
	{
		return ::Internal::GetFormatSize(fmt);
	}

	void Graphics::EndianSwapMemory32(System::IntPtr dst, System::IntPtr src, mcpp_int count)
	{
		return ::Internal::EndianSwapMemory32(dst.ToPointer(), src.ToPointer(), count);
	}

}; };
#endif
__MCPP_CODE_END__