using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace LensSimulator.View._2DPlot
{
    public interface IObjectMover
    {
        public bool Move(UIElement? target, double x, double y);
    }
}
