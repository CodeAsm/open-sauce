/*
    Yelo: Open Sauce SDK
		Halo 1 (CE) Edition
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
#pragma once

#include "Objects/ObjectDefinitions.hpp"

namespace Yelo
{
	namespace Objects
	{
		struct s_device_data : TStructImpl(Enums::k_object_size_device - Enums::k_object_size_object)
		{
			enum { DATA_OFFSET = Enums::k_object_size_object, };

			TStructSubGetPtrImpl(long_flags,		Flags, 0x1F4);

			TStructSubGetPtrImpl(int16,				PowerDeviceGroupIndex, 0x1F8);
			TStructSubGetPtrImpl(real,				PowerValue, 0x1FC);
			TStructSubGetPtrImpl(real,				PowerUnknown, 0x200);

			TStructSubGetPtrImpl(int16,				PositionDeviceGroupIndex, 0x204);
			TStructSubGetPtrImpl(real,				PositionValue, 0x208);
			TStructSubGetPtrImpl(real,				PositionUnknown, 0x20C);

			// 0x210 - int16
		};

		struct s_device_machine_data : TStructImpl(Enums::k_object_size_machine - Enums::k_object_size_device)
		{
			enum { DATA_OFFSET = Enums::k_object_size_device, };
		};

		struct s_device_control_data : TStructImpl(Enums::k_object_size_control - Enums::k_object_size_device)
		{
			enum { DATA_OFFSET = Enums::k_object_size_device, };
		};

		struct s_device_lightfixture_data : TStructImpl(Enums::k_object_size_light_fixture - Enums::k_object_size_device)
		{
			enum { DATA_OFFSET = Enums::k_object_size_device, };
		};



		struct s_device_datum
		{
			s_object_data object;
			s_device_data device;
		}; BOOST_STATIC_ASSERT( sizeof(s_device_datum) == Enums::k_object_size_device );

		struct s_device_machine_datum : s_device_datum
		{
			s_device_machine_data machine;
		}; BOOST_STATIC_ASSERT( sizeof(s_device_machine_datum) == Enums::k_object_size_machine );

		struct s_device_control_datum : s_device_datum
		{
			s_device_control_data control;
		}; BOOST_STATIC_ASSERT( sizeof(s_device_control_datum) == Enums::k_object_size_control );

		struct s_device_lightfixture_datum : s_device_datum
		{
			s_device_lightfixture_data lightfixture;
		}; BOOST_STATIC_ASSERT( sizeof(s_device_lightfixture_datum) == Enums::k_object_size_light_fixture );
	};
};