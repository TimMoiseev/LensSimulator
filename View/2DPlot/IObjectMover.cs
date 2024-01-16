using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LensSimulator.View._2DPlot
{
    public interface IObjectMover
    {
        public bool Move(IMoveableObject target, double x, double y);
    }
}
