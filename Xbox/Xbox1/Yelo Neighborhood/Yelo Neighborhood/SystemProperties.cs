﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Windows.Forms;

namespace Yelo_Neighborhood
{
    partial class SystemProperties : Form
    {
        public SystemProperties()
        {
            InitializeComponent();

            xboxProperties.SelectedObject = Program.XBox;
        }
    }
}
