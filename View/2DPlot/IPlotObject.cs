using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace LensSimulator.View._2DPlot
{
    internal interface IPlotObject
    {
        void Move(double x, double y);

        (double, double) Position { get; }

        //(double?, double?) getPosition();
    }
}
