using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace LensSimulator.View._2DPlot
{
    public interface IPlotObject
    {
        public enum Type
        {
            Lens,
            Pivot
        }
        public bool Move(UIElement target, double x, double y);
        //(double?, double?) getPosition();
    }
}
