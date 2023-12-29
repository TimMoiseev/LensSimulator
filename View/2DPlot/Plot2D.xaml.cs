using LensSimulator.Commands;
using Microsoft.Xaml.Behaviors;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace LensSimulator.View._2DPlot
{
    /// <summary>
    /// Логика взаимодействия для Plot2D.xaml
    /// </summary>
    public partial class Plot2D : UserControl
    {
        public Plot2D()
        {
            InitializeComponent();
        }
        private bool PlotObjectCanMove = false;
        private Point MouseOldCoord { get; set; }

        private RelayCommand? plot2DMouseDownCommand;
        public ICommand Plot2DMouseDownCommand => plot2DMouseDownCommand ??= new RelayCommand(Plot2DMouseDown);
        private void Plot2DMouseDown(object commandParameter)
        {
            PlotObjectCanMove = true;
            if (commandParameter is MouseButtonEventArgs e && e.Source is IInputElement target)
            {
                e.MouseDevice.Capture(target);
            }
        }

        private RelayCommand? plot2DMouseUpCommand;
        public ICommand Plot2DMouseUpCommand => plot2DMouseUpCommand ??= new RelayCommand(Plot2DMouseUp);
        private void Plot2DMouseUp(object commandParameter)
        {
            PlotObjectCanMove = false;
            if (commandParameter is MouseButtonEventArgs e)
            {
                e.MouseDevice.Capture(null);
            }
        }

        private RelayCommand plot2DMouseMoveCommand;
        public ICommand Plot2DMouseMoveCommand => plot2DMouseMoveCommand ??= new RelayCommand(Plot2DMouseMove);
        private void Plot2DMouseMove(object commandParameter)
        {
            if (commandParameter is MouseEventArgs e)
            {
                if (PlotObjectCanMove)
                {
                    if(e.Source is IPlotObject && e.Source is UIElement target)
                    {
                        Point CurrentMousePoint = e.GetPosition(this);
                        ((IPlotObject)target).Move(CurrentMousePoint.X-MouseOldCoord.X, CurrentMousePoint.Y - MouseOldCoord.Y);
                        MouseOldCoord = CurrentMousePoint;
                    }
                }
                else
                {
                    var target = e.Source as UIElement;
                    MouseOldCoord = e.GetPosition(this);
                }
            }
        }        
    }
}
