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
using System;
using System.Xml;
using System.Xml.Serialization;
using System.Collections.Generic;
using BlamLib.Render.COLLADA.Validation;

namespace BlamLib.Render.COLLADA.Core
{
	[SerializableAttribute()]
	[XmlTypeAttribute(AnonymousType = true)]
	public partial class ColladaVertexWeights : ColladaElement
	{
		#region Fields
		ColladaObjectElementList<ColladaInputShared> _input;
		ColladaObjectElement<ColladaValueArray<int>> _vCount;
		ColladaObjectElement<ColladaValueArray<int>> _v;
		ColladaObjectElementList<ColladaExtra> _extra;
		#endregion

		#region Attributes
		[XmlAttribute("count")]
		public uint Count
		{
			get 
			{
				if ((_vCount == null) || (VCount.Values == null))
					return 0;
				else
					return (uint)VCount.Values.Count; 
			}
			set { }
		}
		#endregion

		#region Children
		[XmlElement("input")]
		public List<ColladaInputShared> Input
		{ get { return _input.Value; } set { _input.Value = value; } }

		[XmlElement("vcount")]
		public ColladaValueArray<int> VCount
		{ get { return _vCount.Value; } set { _vCount.Value = value; } }

		[XmlElement("v")]
		public ColladaValueArray<int> V
		{ get { return _v.Value; } set { _v.Value = value; } }

		[XmlElement("extra")]
		public List<ColladaExtra> Extra
		{ get { return _extra.Value; } set { _extra.Value = value; } }
		#endregion

		public ColladaVertexWeights() : base(Enums.ColladaElementType.Core_VertexWeights)
		{
			Fields.Add(_input = new ColladaObjectElementList<ColladaInputShared>());
			Fields.Add(_vCount = new ColladaObjectElement<ColladaValueArray<int>>());
			Fields.Add(_v = new ColladaObjectElement<ColladaValueArray<int>>());
			Fields.Add(_extra = new ColladaObjectElementList<ColladaExtra>());

			ValidationTests.Add(new ColladaIsNull(Enums.ColladaElementType.All, _input));
			ValidationTests.Add(new ColladaListMinCount<ColladaInputShared>(Enums.ColladaElementType.All, _input, 2));
			ValidationTests.Add(new ColladaListHasValue<ColladaInputShared, Enums.ColladaInputSharedSemantic>(Enums.ColladaElementType.All,
				_input, "Semantic", Enums.ColladaInputSharedSemantic.JOINT));
		}
	}
}